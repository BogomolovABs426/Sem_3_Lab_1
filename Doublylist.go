package main

import "fmt"

func LADD_HEAD(list *DoublyList, value string) {
	newNode := &LNode{Data: value, Next: list.Head, Prev: nil}
	
	if list.Head == nil {
		list.Head = newNode
		list.Tail = newNode
	} else {
		newNode.Next = list.Head
		list.Head.Prev = newNode
		list.Head = newNode
	}
	list.Size++
}

func LADD_TAIL(list *DoublyList, value string) {
	newNode := &LNode{Data: value, Next: nil, Prev: list.Tail}
	
	if list.Head == nil {
		list.Head = newNode
		list.Tail = newNode
	} else {
		newNode.Prev = list.Tail
		list.Tail.Next = newNode
		list.Tail = newNode
	}
	list.Size++
}

func LADD_BEFORE(list *DoublyList, value string, target string) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	curr := list.Head
	for curr != nil && curr.Data != target {
		curr = curr.Next
	}
	
	if curr == nil {
		fmt.Printf("Элемент %s не найден!\n", target)
		return
	}
	
	newNode := &LNode{Data: value, Next: curr, Prev: curr.Prev}
	
	if curr == list.Head {
		newNode.Next = list.Head
		list.Head.Prev = newNode
		list.Head = newNode
	} else {
		newNode.Prev = curr.Prev
		newNode.Next = curr
		curr.Prev.Next = newNode
		curr.Prev = newNode
	}
	list.Size++
}

func LADD_AFTER(list *DoublyList, value string, target string) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	curr := list.Head
	for curr != nil && curr.Data != target {
		curr = curr.Next
	}
	
	if curr == nil {
		fmt.Printf("Элемент %s не найден!\n", target)
		return
	}
	
	newNode := &LNode{Data: value, Next: curr.Next, Prev: curr}
	
	if curr == list.Tail {
		newNode.Prev = list.Tail
		list.Tail.Next = newNode
		list.Tail = newNode
	} else {
		newNode.Prev = curr
		newNode.Next = curr.Next
		curr.Next.Prev = newNode
		curr.Next = newNode
	}
	list.Size++
}

func LREMOVE_HEAD(list *DoublyList) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	if list.Head == list.Tail {
		list.Head = nil
		list.Tail = nil
	} else {
		list.Head = list.Head.Next
		list.Head.Prev = nil
	}
	list.Size--
}

func LREMOVE_TAIL(list *DoublyList) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	if list.Head == list.Tail {
		list.Head = nil
		list.Tail = nil
	} else {
		list.Tail = list.Tail.Prev
		list.Tail.Next = nil
	}
	list.Size--
}

func LREMOVE_BEFORE(list *DoublyList, target string) {
	if list.Head == nil || list.Head.Next == nil {
		fmt.Println("Недостаточно элементов!")
		return
	}
	
	curr := list.Head
	for curr != nil && curr.Data != target {
		curr = curr.Next
	}
	
	if curr == nil {
		fmt.Printf("Элемент %s не найден!\n", target)
		return
	}
	
	if curr.Prev == nil {
		fmt.Printf("Нет элемента до %s!\n", target)
		return
	}
	
	toRemove := curr.Prev
	
	if toRemove == list.Head {
		list.Head = curr
		list.Head.Prev = nil
	} else {
		toRemove.Prev.Next = curr
		curr.Prev = toRemove.Prev
	}
	list.Size--
}

func LREMOVE_AFTER(list *DoublyList, target string) {
	if list.Head == nil || list.Head.Next == nil {
		fmt.Println("Недостаточно элементов!")
		return
	}
	
	curr := list.Head
	for curr != nil && curr.Data != target {
		curr = curr.Next
	}
	
	if curr == nil {
		fmt.Printf("Элемент %s не найден!\n", target)
		return
	}
	
	if curr.Next == nil {
		fmt.Printf("Нет элемента после %s!\n", target)
		return
	}
	
	toRemove := curr.Next
	
	if toRemove == list.Tail {
		list.Tail = curr
		list.Tail.Next = nil
	} else {
		curr.Next = toRemove.Next
		toRemove.Next.Prev = curr
	}
	list.Size--
}

func LREMOVE_BY_VALUE(list *DoublyList, value string) bool {
	curr := list.Head
	for curr != nil {
		if curr.Data == value {
			if curr == list.Head {
				list.Head = curr.Next
				if list.Head != nil {
					list.Head.Prev = nil
				}
			} else if curr == list.Tail {
				list.Tail = curr.Prev
				if list.Tail != nil {
					list.Tail.Next = nil
				}
			} else {
				curr.Prev.Next = curr.Next
				curr.Next.Prev = curr.Prev
			}
			list.Size--
			return true
		}
		curr = curr.Next
	}
	
	fmt.Printf("Элемент %s не найден!\n", value)
	return false
}

func LFIND(list *DoublyList, value string) bool {
	curr := list.Head
	position := 0
	for curr != nil {
		if curr.Data == value {
			fmt.Printf("Элемент %s найден на позиции %d\n", value, position)
			return true
		}
		curr = curr.Next
		position++
	}
	fmt.Printf("Элемент %s не найден!\n", value)
	return false
}

func LPRINT_FORWARD(list *DoublyList) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	fmt.Printf("Двусвязный вперед (%d): ", list.Size)
	curr := list.Head
	for curr != nil {
		fmt.Print(curr.Data)
		if curr.Next != nil {
			fmt.Print(" <-> ")
		}
		curr = curr.Next
	}
	fmt.Println()
}

func LPRINT_BACKWARD(list *DoublyList) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	fmt.Printf("Двусвязный назад (%d): ", list.Size)
	curr := list.Tail
	for curr != nil {
		fmt.Print(curr.Data)
		if curr.Prev != nil {
			fmt.Print(" <-> ")
		}
		curr = curr.Prev
	}
	fmt.Println()
}

func LPRINT(list *DoublyList) {
	LPRINT_FORWARD(list)
}

func LCLEAR(list *DoublyList) {
	list.Head = nil
	list.Tail = nil
	list.Size = 0
	fmt.Println("Список очищен")
}
