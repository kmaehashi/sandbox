package main

import "code.google.com/p/go-tour/tree"
import "fmt"

// Walk walks the tree t sending all values
// from the tree to the channel ch.
func Walk(t *tree.Tree, ch chan int) {
    var walk_node func(*tree.Tree)
    walk_node = func(node *tree.Tree) {
        if node == nil { return }
        walk_node(node.Left)
        ch <- node.Value
        walk_node(node.Right)
    }
    walk_node(t)
    close(ch)
}

// Same determines whether the trees
// t1 and t2 contain the same values.
func Same(t1, t2 *tree.Tree) bool {
    c1, c2 := make(chan int), make(chan int)
    go Walk(t1, c1)
    go Walk(t2, c2)

    for v1 := range c1 {
        v2 := <- c2
        if v1 != v2 {
            return false
        }
    }
    return true
}

func main() {
    ch := make(chan int)
    go Walk(tree.New(1), ch)
    for v := range ch {
        fmt.Printf("%d, ", v)
    }
    fmt.Printf("\n")
    fmt.Printf("%v, ", Same(tree.New(1), tree.New(1)))
    fmt.Printf("%v, ", Same(tree.New(1), tree.New(2)))
}
