package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	x := New(4, 4)
	fmt.Println("---- Adding tasks...")
	for i := 0; i < 20; i++ {
		func(i int) {
			x.Add(func() (interface{}, error) {
				sec := rand.Intn(10)
				fmt.Printf("START   : task %v (sleep %v)\n", i, sec)
				time.Sleep(time.Duration(sec) * time.Second)
				fmt.Printf("END     : task %v (sleep %v)\n", i, sec)
				return sec, nil
			}, func(result interface{}, err error) {
				fmt.Printf("CALLBACK: task %v (sleep %v)\n", i, result)
			})
			fmt.Printf("ADD     : task %v\n", i)
		}(i)
	}
	fmt.Println("---- All tasks added, now waiting for tasks to complete...")
	x.Stop()
	fmt.Println("---- Done!")
}
