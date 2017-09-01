package main

import (
    "strings"
    "code.google.com/p/go-tour/wc"
)

func WordCount(s string) map[string]int {
    var result = make(map[string]int)
    for _, v := range strings.Fields(s) {
        result[v] = result[v] + 1
    }
    return result
}

func main() {
    wc.Test(WordCount)
}
