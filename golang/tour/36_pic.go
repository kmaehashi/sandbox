package main

import "code.google.com/p/go-tour/pic"

func Pic(dx, dy int) [][]uint8 {
    var result = make([][]uint8, dx)
    for x:=0; x < dx; x++ {
        result[x] = make([]uint8, dy)
        for y:=0; y < dy; y++ {
            result[x][y] = uint8((x*4+y*3))
        }
    }

    return result
}

func main() {
    pic.Show(Pic)
}
