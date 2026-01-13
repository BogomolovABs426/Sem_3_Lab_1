package main

import (
	"bufio"
	"container/list"
	"fmt"
	"os"
	"strings"
)

func loadDatabaseFromFile(filename string, db *Database) error {
	file, err := os.Open(filename)
	if err != nil {
		// Файл не существует, база пустая
		return nil
	}
	defer file.Close()

	scanner := bufio.NewScanner(file)
	currentStructure := ""
	currentType := ""

	for scanner.Scan() {
		line := strings.TrimSpace(scanner.Text())
		if line == "" {
			continue
		}

		// Проверяем, является ли строка заголовком структуры
		if strings.HasPrefix(line, "[") && strings.HasSuffix(line, "]") {
			header := line[1 : len(line)-1]
			parts := strings.Split(header, ":")
			if len(parts) == 2 {
				currentStructure = parts[0]
				currentType = parts[1]
			}
			continue
		}

		// Загружаем данные в соответствующую структуру
		switch currentType {
		case "ARRAY":
			if db.Arrays[currentStructure] == nil {
				db.Arrays[currentStructure] = &Array{}
			}
			MPUSH(db.Arrays[currentStructure], line)
		case "SINGLY_LIST":
			if db.SinglyLists[currentStructure] == nil {
				db.SinglyLists[currentStructure] = &SingleList{}
			}
			FADD_TAIL(db.SinglyLists[currentStructure], line)
		case "DOUBLY_LIST":
			if db.DoublyLists[currentStructure] == nil {
				db.DoublyLists[currentStructure] = &DoublyList{}
			}
			LADD_TAIL(db.DoublyLists[currentStructure], line)
		case "STACK":
			if db.Stacks[currentStructure] == nil {
				db.Stacks[currentStructure] = &Stack{}
			}
			SPUSH(db.Stacks[currentStructure], line)
		case "QUEUE":
			if db.Queues[currentStructure] == nil {
				db.Queues[currentStructure] = &Queue{}
			}
			QPUSH(db.Queues[currentStructure], line)
		case "TREE":
			if db.Trees[currentStructure] == nil {
				db.Trees[currentStructure] = &Tree{}
			}
			TADD(db.Trees[currentStructure], line, true)
		}
	}

	return scanner.Err()
}

func saveDatabaseToFile(filename string, db *Database) error {
	file, err := os.Create(filename)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := bufio.NewWriter(file)

	// Сохраняем массивы
	for name, arr := range db.Arrays {
		fmt.Fprintf(writer, "[%s:ARRAY]\n", name)
		for i := 0; i < arr.Size; i++ {
			if i < len(arr.Data) {
				fmt.Fprintln(writer, arr.Data[i])
			}
		}
		fmt.Fprintln(writer)
	}

	// Сохраняем односвязные списки
	for name, list := range db.SinglyLists {
		fmt.Fprintf(writer, "[%s:SINGLY_LIST]\n", name)
		curr := list.Head
		for curr != nil {
			fmt.Fprintln(writer, curr.Data)
			curr = curr.Next
		}
		fmt.Fprintln(writer)
	}

	// Сохраняем двусвязные списки
	for name, list := range db.DoublyLists {
		fmt.Fprintf(writer, "[%s:DOUBLY_LIST]\n", name)
		curr := list.Head
		for curr != nil {
			fmt.Fprintln(writer, curr.Data)
			curr = curr.Next
		}
		fmt.Fprintln(writer)
	}

	// Сохраняем стеки (в обратном порядке)
	for name, stack := range db.Stacks {
		fmt.Fprintf(writer, "[%s:STACK]\n", name)
		var temp []string
		curr := stack.Top
		for curr != nil {
			temp = append(temp, curr.Data)
			curr = curr.Next
		}
		for i := len(temp) - 1; i >= 0; i-- {
			fmt.Fprintln(writer, temp[i])
		}
		fmt.Fprintln(writer)
	}

	// Сохраняем очереди
	for name, queue := range db.Queues {
		fmt.Fprintf(writer, "[%s:QUEUE]\n", name)
		curr := queue.Front
		for curr != nil {
			fmt.Fprintln(writer, curr.Data)
			curr = curr.Next
		}
		fmt.Fprintln(writer)
	}

	// Сохраняем деревья (level-order)
	for name, tree := range db.Trees {
		fmt.Fprintf(writer, "[%s:TREE]\n", name)
		if tree.Root != nil {
			queue := list.New()
			queue.PushBack(tree.Root)
			for queue.Len() > 0 {
				front := queue.Front()
				current := front.Value.(*TNode)
				queue.Remove(front)
				fmt.Fprintln(writer, current.Data)
				if current.Left != nil {
					queue.PushBack(current.Left)
				}
				if current.Right != nil {
					queue.PushBack(current.Right)
				}
			}
		}
		fmt.Fprintln(writer)
	}

	return writer.Flush()
}
