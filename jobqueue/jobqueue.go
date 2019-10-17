package main

import (
	"container/list"
	"fmt"
	"sync"
	"sync/atomic"
)

type job struct {
	id       uint64
	target   func() (interface{}, error)
	callback func(interface{}, error)
	retval   interface{}
	reterr   error
}

type orderedJobQueue struct {
	count        uint64
	waitingJobs  chan *job
	finishedJobs chan *job
	workerGroup  sync.WaitGroup
	callbackLock *sync.Mutex
}

// New creates a new ordered job queue, where the order of input jobs and
// output callbacks is guranteed to be consistent.
func New(workers int, capacity int) *orderedJobQueue {
	queue := &orderedJobQueue{
		// Waiting jobs queue is for jobs not yet invoked and waiting to be
		// picked by the worker.
		waitingJobs: make(chan *job, capacity),

		// Finished jobs queue is for jobs invoked, completed and waiting
		// to be picked by the callbacker.
		finishedJobs: make(chan *job, capacity),

		callbackLock: &sync.Mutex{},
	}

	// Launch workers.
	// A worker picks a job from the waiting jobs queue, invoke it,
	// then queue it to the finished jobs queue.
	queue.workerGroup.Add(workers)
	for i := 0; i < workers; i++ {
		go func() {
			defer queue.workerGroup.Done()

			for {
				j, ok := <-queue.waitingJobs
				if !ok {
					return
				}
				j.retval, j.reterr = j.target()
				queue.finishedJobs <- j
			}
		}()
	}

	// Launch a callbacker.
	// A callbacker picks a job from the finished jobs queue and perform
	// callback.  If it is not possible to perform callback immedeately
	// (in case some younger jobs are not completed yet), add it to the
	// waiters list (TODO naming is a bit confusing) and retry when another
	// job has completed.  Note that the size of the waiters list is not
	// limited.
	queue.callbackLock.Lock()
	go func() {
		defer queue.callbackLock.Unlock()

		// The initial job ID is 1.
		callbackID := uint64(1)

		// Dispatch the job if all younger jobs are already dispatched.
		tryCallback := func(j *job) bool {
			if j.id == callbackID {
				j.callback(j.retval, j.reterr)
				callbackID += 1
				return true
			}
			return false
		}

		// Try to flush the waiters list.
		flushWaiters := func(waiters *list.List) {
			for e := waiters.Front(); e != nil; {
				if tryCallback(e.Value.(*job)) {
					waiters.Remove(e)
					e = waiters.Front()
				} else {
					e = e.Next()
				}
			}
		}

		waiters := list.New()
		for {
			j, ok := <-queue.finishedJobs
			if !ok {
				if waiters.Len() != 0 {
					panic(fmt.Errorf("failed to callback some jobs"))
				}
				return
			}
			if tryCallback(j) {
				flushWaiters(waiters)
			} else {
				waiters.PushBack(j)
			}
		}
	}()

	return queue
}

// Add registers a new job to the queue.
// target is a (generally heavy) function to be invoked by multiple
// workers, and thus must be thread safe.  callback is a function to be
// invoked with the returned value from the target function, and is not
// necessary to be thread safe.
func (queue *orderedJobQueue) Add(
	target func() (interface{}, error),
	callback func(interface{}, error)) {
	queue.waitingJobs <- &job{
		id:       atomic.AddUint64(&queue.count, 1),
		target:   target,
		callback: callback,
	}
}

// Stop waits for all jobs to complete and then discard the queue.
// No jobs can be added after calling Stop.
func (queue *orderedJobQueue) Stop() {
	// Stop workers.
	close(queue.waitingJobs)

	// Wait until all workers are finished.
	queue.workerGroup.Wait()

	// Stop callbacker.
	close(queue.finishedJobs)

	// Wait until callbacker is finished.
	queue.callbackLock.Lock()
	defer queue.callbackLock.Unlock()
}
