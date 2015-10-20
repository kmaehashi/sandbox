package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
    idx, v1, v2 := 0, 0, 1
    return func() int {
        idx++
        if idx == 1 {
            return v1
        } else if idx == 2 {
            return v2
        } else {
            ret := v1 + v2
            v1, v2 = v2, ret
            return ret
        }
    }
}

func main() {
    f := fibonacci()
    for i := 0; i < 10; i++ {
        fmt.Println(f())
    }
}
