package main

import (
    "code.google.com/p/go-tour/pic"
    "image"
    "image/color"
)

type Image struct{}

func (v Image) ColorModel() color.Model {
  return color.RGBAModel
}

func (v Image) Bounds() image.Rectangle {
  return image.Rect(0, 0, 100, 100)
}

func (v Image) At(x, y int) color.Color {
  return color.RGBA{200, 100, 255, 255}
}

func main() {
    m := Image{}
    pic.ShowImage(m)
}

