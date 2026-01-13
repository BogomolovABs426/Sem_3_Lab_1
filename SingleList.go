package main

import "fmt"

func FADD_HEAD(list *SingleList, value string) {
	newNode := &FNode{Data: value, Next: list.Head}
	list.Head = newNode
	list.Size++
}

func FADD_TAIL(list *SingleList, value string) {
	newNode := &FNode{Data: value, Next: nil}
	
	if list.Head == nil {
		list.Head = newNode
	} else {
		curr := list.Head
		for curr.Next != nil {
			curr = curr.Next
		}
		curr.Next = newNode
	}
	list.Size++
}

func FADD_BEFORE(list *SingleList, value string, target string) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	if list.Head.Data == target {
		FADD_HEAD(list, value)
		return
	}
	
	curr := list.Head
	for curr.Next != nil && curr.Next.Data != target {
		curr = curr.Next
	}
	
	if curr.Next == nil {
		fmt.Printf("Элемент %s не найден!\n", target)
		return
	}
	
	newNode := &FNode{Data: value, Next: curr.Next}
	curr.Next = newNode
	list.Size++
}

func FADD_AFTER(list *SingleList, value string, target string) {
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
	
	newNode := &FNode{Data: value, Next: curr.Next}
	curr.Next = newNode
	list.Size++
	fmt.Printf("-> вставлен %s после %s\n", value, target)
}

func FREMOVE_HEAD(list *SingleList) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	list.Head = list.Head.Next
	list.Size--
}

func FREMOVE_TAIL(list *SingleList) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	if list.Head.Next == nil {
		list.Head = nil
	} else {
		curr := list.Head
		for curr.Next.Next != nil {
			curr = curr.Next
		}
		curr.Next = nil
	}
	list.Size--
}

func FREMOVE_BEFORE(list *SingleList, target string) {
	if list.Head == nil || list.Head.Next == nil {
		fmt.Println("Недостаточно элементов!")
		return
	}
	
	if list.Head.Next.Data == target {
		FREMOVE_HEAD(list)
		return
	}
	
	curr := list.Head
	for curr.Next != nil && curr.Next.Next != nil && curr.Next.Next.Data != target {
		curr = curr.Next
	}
	
	if curr.Next == nil || curr.Next.Next == nil {
		fmt.Printf("Элемент %s не найден или нет элемента перед ним!\n", target)
		return
	}
	
	curr.Next = curr.Next.Next
	list.Size--
}

func FREMOVE_AFTER(list *SingleList, target string) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	curr := list.Head
	for curr != nil && curr.Data != target {
		curr = curr.Next
	}
	
	if curr == nil || curr.Next == nil {
		fmt.Printf("Элемент %s не найден или нет элемента после него!\n", target)
		return
	}
	
	curr.Next = curr.Next.Next
	list.Size--
}

func FREMOVE_BY_VALUE(list *SingleList, value string) bool {
	if list.Head == nil {
		return false
	}
	
	if list.Head.Data == value {
		list.Head = list.Head.Next
		list.Size--
		return true
	}
	
	curr := list.Head
	for curr.Next != nil && curr.Next.Data != value {
		curr = curr.Next
	}
	
	if curr.Next != nil {
		curr.Next = curr.Next.Next
		list.Size--
		return true
	}
	
	fmt.Printf("Элемент %s не найден!\n", value)
	return false
}

func FFIND(list *SingleList, value string) bool {
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

func FPRINT_FORWARD(list *SingleList) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	fmt.Printf("Список вперед (%d): ", list.Size)
	curr := list.Head
	for curr != nil {
		fmt.Print(curr.Data)
		if curr.Next != nil {
			fmt.Print(" -> ")
		}
		curr = curr.Next
	}
	fmt.Println()
}

func FPRINT_BACKWARD(list *SingleList) {
	if list.Head == nil {
		fmt.Println("Список пуст!")
		return
	}
	
	// Собираем данные в массив
	var data []string
	curr := list.Head
	for curr != nil {
		data = append(data, curr.Data)
		curr = curr.Next
	}
	
	fmt.Printf("Список назад (%d): ", list.Size)
	for i := len(data) - 1; i >= 0; i-- {
		fmt.Print(data[i])
		if i > 0 {
			fmt.Print(" <- ")
		}
	}
	fmt.Println()
}

func FPRINT(list *SingleList) {
	FPRINT_FORWARD(list)
}

func FCLEAR(list *SingleList) {
	list.Head = nil
	list.Size = 0
	fmt.Println("Список очищен")
}
