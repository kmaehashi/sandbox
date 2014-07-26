package main

import (
    "io"
    "os"
    "strings"
)

type rot13Reader struct {
    r io.Reader
}

func (v *rot13Reader) Read(p []byte) (n int, err error) {
    n, err = v.r.Read(p)
    if err != nil { return }

    for i := 0; i < n; i++ {
        c := p[i]
        switch {
        case 65 <= c && c <= 90:  // capital letters
            c = ((c - 65) + 13) % 26 + 65
        case 97 <= c && c <= 122: // small letters
            c = ((c - 97) + 13) % 26 + 97
        }
        p[i] = c
    }

    return
}

func main() {
    s := strings.NewReader(
        "Lbh penpxrq gur pbqr!")
    r := rot13Reader{s}
    io.Copy(os.Stdout, &r)
}
