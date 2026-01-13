package main

import "fmt"

func QPUSH(queue *Queue, value string) {
	newNode := &QNode{Data: value, Next: nil}
	if queue.Rear == nil {
		queue.Front = newNode
		queue.Rear = newNode
	} else {
		queue.Rear.Next = newNode
		queue.Rear = newNode
	}
	queue.Size++
}

func QPOP(queue *Queue) {
	if queue.Front == nil {
		fmt.Println("Очередь пуста!")
		return
	}
	
	queue.Front = queue.Front.Next
	if queue.Front == nil {
		queue.Rear = nil
	}
	queue.Size--
}

func QPRINT(queue *Queue) {
	if queue.Front == nil {
		fmt.Println("Очередь пуста!")
		return
	}
	
	fmt.Printf("Очередь (%d): ", queue.Size)
	curr := queue.Front
	for curr != nil {
		fmt.Print(curr.Data)
		if curr.Next != nil {
			fmt.Print(" -> ")
		}
		curr = curr.Next
	}
	fmt.Println()
}

func QCLEAR(queue *Queue) {
	queue.Front = nil
	queue.Rear = nil
	queue.Size = 0
	fmt.Println("Очередь очищена")
}
