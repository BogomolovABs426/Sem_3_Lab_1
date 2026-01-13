package main

import "fmt"

func SPUSH(stack *Stack, value string) {
	newNode := &SNode{Data: value, Next: stack.Top}
	stack.Top = newNode
	stack.Size++
}

func SPOP(stack *Stack) {
	if stack.Top == nil {
		fmt.Println("Стек пуст!")
		return
	}
	
	stack.Top = stack.Top.Next
	stack.Size--
}

func SPRINT(stack *Stack) {
	if stack.Top == nil {
		fmt.Println("Стек пуст!")
		return
	}
	
	fmt.Printf("Стек (%d): ", stack.Size)
	curr := stack.Top
	for curr != nil {
		fmt.Print(curr.Data)
		if curr.Next != nil {
			fmt.Print(" -> ")
		}
		curr = curr.Next
	}
	fmt.Println()
}

func SCLEAR(stack *Stack) {
	stack.Top = nil
	stack.Size = 0
	fmt.Println("Стек очищен")
}
