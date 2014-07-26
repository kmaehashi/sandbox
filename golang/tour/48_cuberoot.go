package main

import "fmt"
import "math/cmplx"

func Cbrt(x complex128) complex128 {
    z := complex128(1.0)
    for i:= 0; i < 1000000; i++ {
        z = z - (z*z*z - x) / 3*z*z
    }
    return z
}

func main() {
    fmt.Println(Cbrt(2))
    fmt.Println(cmplx.Pow(Cbrt(2), 3))
}
