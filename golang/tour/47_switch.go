package main

import "fmt"

// fibonacci is a function that returns
// a function that returns an int.
func fibonacci() func() int {
    idx, v1, v2 := 0, 0, 1
    return func() int {
        idx++
        switch idx {
        case 1:
            return v1
        case 2:
            return v2
        default:
            ret := v1 + v2
            v1, v2 = v2, ret
            return ret
        }
    }
}

func main() {
    f := fibonacci()
    for i := 0; i < 15; i++ {
        fmt.Println(f())
    }
}
