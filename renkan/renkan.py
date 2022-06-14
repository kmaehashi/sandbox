#!/usr/bin/env python

import sys


class Simulator:
    def __init__(self, n, init_state=True):
        assert 0 < n
        self._n = n
        self._locked = [init_state] * n
        self._steps = 0

    def lock(self, i):
        self._set_state(i, True)

    def unlock(self, i):
        self._set_state(i, False)

    def _set_state(self, i, state):
        assert 0 <= i < self._n
        assert i == 0 or (self._locked[:i][-1] and not any(self._locked[:i-1]))
        assert self._locked[i] != state
        self._locked[i] = state
        self._steps += 1

    def is_locked(self, i):
        assert 0 <= i < self._n
        return self._locked[i]

    def is_all_locked(self):
        return all(self._locked)

    def is_all_unlocked(self):
        return not any(self._locked)

    def steps(self):
        return self._steps

    def __str__(self):
        line_locked = ''
        line_unlocked = ''
        width = len(str(self._n - 1))
        fmt = '-{:>' + str(width) + '}-'
        for i, state in reversed(list(enumerate(self._locked))):
            if state:
                line_locked += fmt.format(i)
                line_unlocked += '-' * (width + 2)
            else:
                line_locked += '-' * (width + 2)
                line_unlocked += fmt.format(i)
        return 'X==({})\n    {}'.format(line_locked, line_unlocked)


class Solver:
    def __init__(self):
        self._sim = None

    def solve(self, n):
        assert 0 < n
        self._sim = Simulator(n)
        expected_steps = self.expected_steps(n)
        self.report('### Start! (steps = {})'.format(expected_steps))
        self.dump()
        for i in reversed(range(n)):
            self.report('### Trying to unlock: {}'.format(i))
            self._unlock(i)
        assert self._sim.is_all_unlocked()
        assert self._sim.steps() == expected_steps
        self.report('### Solved!')

    def solve_backward(self, n):
        assert 0 < n
        self._sim = Simulator(n, init_state=False)
        expected_steps = self.expected_steps(n)
        self.report('### Start backward! (steps = {})'.format(expected_steps))
        self.dump()
        for i in reversed(range(n)):
            self.report('### Trying to lock: {}'.format(i))
            self._lock(i)
        assert self._sim.is_all_locked()
        assert self._sim.steps() == expected_steps
        self.report('### Solved backward!')

    def report(self, log):
        print(log)

    def dump(self):
        self.report('{}\n'.format(str(self._sim)))

    def _unlock(self, i):
        if not self._sim.is_locked(i):
            return
        self._make_movable(i)
        self._sim.unlock(i)
        self.report('> [{}] Unlock: {}'.format(self._sim.steps(), i))
        self.dump()

    def _lock(self, i):
        if self._sim.is_locked(i):
            return
        self._make_movable(i)
        self._sim.lock(i)
        self.report('> [{}] Lock: {}'.format(self._sim.steps(), i))
        self.dump()

    def _make_movable(self, i):
        if i == 0:
            return
        if not self._sim.is_locked(i-1):
            self._lock(i-1)
        for j in reversed(range(i-1)):
            self._unlock(j)

    def expected_steps(self, n):
        # S(n) = 1 if n == 1 else (S(n - 1) * 2 + (0 if n % 2 == 0 else 1))
        return (2 ** (n + 1) - (2 if n % 2 == 0 else 1)) // 3


def main():
    n = 9 if len(sys.argv) <= 1 else int(sys.argv[1])
    solver = Solver()
    solver.solve(n)
    solver.solve_backward(n)


if __name__ == '__main__':
    main()
