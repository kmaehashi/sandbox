package main

import (
    "fmt"
    "math"
)

func Sqrt_orig(x float64) float64 {
    z:= 1.0
    for i:= 0; i < 1000000; i++ {
        z = z - (z*z - x) / 2*z
    }
    return z
}

func Sqrt(x float64) float64 {
    z:= 1.0
    var diff = x
    for 0.0001 < diff {
        new_z := z - (z*z - x) / 2*z
        diff = math.Abs(new_z - z)
        z = new_z
    }
    return z
}


func main() {
    fmt.Println(Sqrt(2))
}
