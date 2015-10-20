package main

import (
    "fmt"
    "math"
)

type ErrNegativeSqrt float64

func (e ErrNegativeSqrt) Error() string {
    return fmt.Sprintf("cannot Sqrt negative number: %v", float64(e))
}

func Sqrt(x float64) (float64, error) {
    if x < 0 { return 0, ErrNegativeSqrt(x) }

    z:= 1.0
    var diff = x
    for 0.0001 < diff {
        new_z := z - (z*z - x) / 2*z
        diff = math.Abs(new_z - z)
        z = new_z
    }
    return z, nil
}


func main() {
    fmt.Println(Sqrt(2))
    fmt.Println(Sqrt(-2))
}
