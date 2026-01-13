package main

import (
	"container/list"
	"fmt"
)

func clearTree(node *TNode) {
	if node == nil {
		return
	}
	clearTree(node.Left)
	clearTree(node.Right)
}

func TADD(tree *Tree, value string, silent bool) {
	newNode := &TNode{Data: value, Left: nil, Right: nil, Parent: nil}
	
	if tree.Root == nil {
		tree.Root = newNode
	} else {
		queue := list.New()
		queue.PushBack(tree.Root)
		var parent *TNode
		
		for queue.Len() > 0 {
			front := queue.Front()
			parent = front.Value.(*TNode)
			queue.Remove(front)
			
			if parent.Left == nil {
				parent.Left = newNode
				newNode.Parent = parent
				break
			} else if parent.Right == nil {
				parent.Right = newNode
				newNode.Parent = parent
				break
			} else {
				queue.PushBack(parent.Left)
				queue.PushBack(parent.Right)
			}
		}
	}
	
	tree.Size++
	if !silent {
		fmt.Printf("Добавлен в дерево: %s\n", value)
	}
}

func TFIND(tree *Tree, value string) bool {
	if tree.Root == nil {
		fmt.Println("Дерево пусто!")
		return false
	}
	
	queue := list.New()
	queue.PushBack(tree.Root)
	
	for queue.Len() > 0 {
		front := queue.Front()
		current := front.Value.(*TNode)
		queue.Remove(front)
		
		if current.Data == value {
			fmt.Printf("Элемент '%s' найден в дереве\n", value)
			return true
		}
		
		if current.Left != nil {
			queue.PushBack(current.Left)
		}
		if current.Right != nil {
			queue.PushBack(current.Right)
		}
	}
	
	fmt.Printf("Элемент '%s' не найден в дереве\n", value)
	return false
}

func TISFULL(tree *Tree) bool {
	if tree.Root == nil {
		return true
	}
	
	queue := list.New()
	queue.PushBack(tree.Root)
	foundNonFullNode := false
	
	for queue.Len() > 0 {
		front := queue.Front()
		current := front.Value.(*TNode)
		queue.Remove(front)
		
		hasZeroChildren := (current.Left == nil && current.Right == nil)
		hasTwoChildren := (current.Left != nil && current.Right != nil)
		
		if !hasZeroChildren && !hasTwoChildren {
			return false
		}
		
		if foundNonFullNode && !hasZeroChildren {
			return false
		}
		
		if hasZeroChildren {
			foundNonFullNode = true
		}
		
		if current.Left != nil {
			queue.PushBack(current.Left)
		}
		if current.Right != nil {
			queue.PushBack(current.Right)
		}
	}
	
	return true
}

func TLEVELORDER(tree *Tree) {
	if tree.Root == nil {
		fmt.Println("Дерево пусто!")
		return
	}
	
	fmt.Print("Level-order: ")
	queue := list.New()
	queue.PushBack(tree.Root)
	
	for queue.Len() > 0 {
		front := queue.Front()
		current := front.Value.(*TNode)
		queue.Remove(front)
		fmt.Printf("%s ", current.Data)
		
		if current.Left != nil {
			queue.PushBack(current.Left)
		}
		if current.Right != nil {
			queue.PushBack(current.Right)
		}
	}
	fmt.Println()
}

func TPRINT_STRUCTURE(tree *Tree) {
	if tree.Root == nil {
		fmt.Println("Дерево пусто!")
		return
	}
	
	fmt.Println("Структура дерева:")
	queue := list.New()
	queue.PushBack(tree.Root)
	level := 0
	nodesInLevel := 1
	
	for queue.Len() > 0 {
		nextLevelCount := 0
		fmt.Printf("Уровень %d: ", level)
		
		for i := 0; i < nodesInLevel; i++ {
			if queue.Len() == 0 {
				break
			}
			
			front := queue.Front()
			current := front.Value.(*TNode)
			queue.Remove(front)
			
			if current != nil {
				fmt.Printf("%s ", current.Data)
				queue.PushBack(current.Left)
				queue.PushBack(current.Right)
				nextLevelCount += 2
			} else {
				fmt.Print("NULL ")
				queue.PushBack(nil)
				queue.PushBack(nil)
				nextLevelCount += 2
			}
		}
		
		fmt.Println()
		level++
		nodesInLevel = nextLevelCount
		
		// Проверяем, есть ли ненулевые узлы в следующем уровне
		hasNonNull := false
		tempQueue := list.New()
		for e := queue.Front(); e != nil; e = e.Next() {
			if e.Value.(*TNode) != nil {
				hasNonNull = true
				break
			}
		}
		tempQueue.Init()
		
		if !hasNonNull {
			break
		}
	}
}

func TPREORDER(tree *Tree) {
	if tree.Root == nil {
		fmt.Println("Дерево пусто!")
		return
	}
	
	fmt.Print("Pre-order: ")
	stack := list.New()
	stack.PushBack(tree.Root)
	
	for stack.Len() > 0 {
		back := stack.Back()
		current := back.Value.(*TNode)
		stack.Remove(back)
		fmt.Printf("%s ", current.Data)
		
		if current.Right != nil {
			stack.PushBack(current.Right)
		}
		if current.Left != nil {
			stack.PushBack(current.Left)
		}
	}
	fmt.Println()
}

func TINORDER(tree *Tree) {
	if tree.Root == nil {
		fmt.Println("Дерево пусто!")
		return
	}
	
	fmt.Print("In-order: ")
	stack := list.New()
	current := tree.Root
	
	for current != nil || stack.Len() > 0 {
		for current != nil {
			stack.PushBack(current)
			current = current.Left
		}
		
		back := stack.Back()
		current = back.Value.(*TNode)
		stack.Remove(back)
		fmt.Printf("%s ", current.Data)
		
		current = current.Right
	}
	fmt.Println()
}

func TPOSTORDER(tree *Tree) {
	if tree.Root == nil {
		fmt.Println("Дерево пусто!")
		return
	}
	
	fmt.Print("Post-order: ")
	stack1 := list.New()
	stack2 := list.New()
	stack1.PushBack(tree.Root)
	
	for stack1.Len() > 0 {
		back := stack1.Back()
		current := back.Value.(*TNode)
		stack1.Remove(back)
		stack2.PushBack(current)
		
		if current.Left != nil {
			stack1.PushBack(current.Left)
		}
		if current.Right != nil {
			stack1.PushBack(current.Right)
		}
	}
	
	for stack2.Len() > 0 {
		back := stack2.Back()
		fmt.Printf("%s ", back.Value.(*TNode).Data)
		stack2.Remove(back)
	}
	fmt.Println()
}

func TCLEAR(tree *Tree) {
	clearTree(tree.Root)
	tree.Root = nil
	tree.Size = 0
	fmt.Println("Дерево очищено")
}
