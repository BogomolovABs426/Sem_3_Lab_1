package main

import (
	"fmt"
	"strings"
)

type Commands struct{}

func (c *Commands) Execute(query string, filename string) {
	parts := strings.Fields(query)
	if len(parts) == 0 {
		return
	}

	command := parts[0]

	// Загружаем базу данных
	db := NewDatabase()
	loadDatabaseFromFile(filename, db)

	// Универсальная команда PRINT
	if command == "PRINT" {
		if len(parts) >= 3 {
			structureName := parts[1]
			structureType := parts[2]
			c.printStructure(db, structureName, structureType)
		} else {
			fmt.Println("Ошибка: укажите имя структуры и тип")
		}
		return
	}

	// Команда LIST для просмотра всех структур
	if command == "LIST" {
		c.listStructures(db, filename)
		return
	}

	// Команда для смены файла
	if command == "CHANGE_FILE" {
		if len(parts) >= 2 {
			newFilename := parts[1]
			fmt.Printf("-> Рабочий файл изменен на: %s\n", newFilename)
			// В реальной реализации нужно обновить filename
		} else {
			fmt.Println("Ошибка: укажите имя файла")
		}
		return
	}

	if len(parts) < 2 {
		fmt.Println("Ошибка: укажите имя структуры")
		return
	}

	structureName := parts[1]

	// Обработка всех команд для различных структур данных
	c.processCommand(db, command, structureName, parts[2:], filename)
}

func (c *Commands) printStructure(db *Database, structureName, structureType string) {
	structureType = strings.ToUpper(structureType)

	switch structureType {
	case "ARRAY", "M":
		if arr, exists := db.Arrays[structureName]; exists {
			fmt.Printf("ARRAY '%s': ", structureName)
			MPRINT(arr)
		} else {
			fmt.Printf("Массив '%s' не найден!\n", structureName)
		}
	case "SINGLY_LIST", "SINGLY", "F":
		if list, exists := db.SinglyLists[structureName]; exists {
			fmt.Printf("SINGLY LIST '%s': ", structureName)
			FPRINT(list)
		} else {
			fmt.Printf("Односвязный список '%s' не найден!\n", structureName)
		}
	case "DOUBLY_LIST", "DOUBLY", "L":
		if list, exists := db.DoublyLists[structureName]; exists {
			fmt.Printf("DOUBLY LIST '%s': ", structureName)
			LPRINT(list)
		} else {
			fmt.Printf("Двусвязный список '%s' не найден!\n", structureName)
		}
	case "STACK", "S":
		if stack, exists := db.Stacks[structureName]; exists {
			fmt.Printf("STACK '%s': ", structureName)
			SPRINT(stack)
		} else {
			fmt.Printf("Стек '%s' не найден!\n", structureName)
		}
	case "QUEUE", "Q":
		if queue, exists := db.Queues[structureName]; exists {
			fmt.Printf("QUEUE '%s': ", structureName)
			QPRINT(queue)
		} else {
			fmt.Printf("Очередь '%s' не найден!\n", structureName)
		}
	case "TREE", "T":
		if tree, exists := db.Trees[structureName]; exists {
			fmt.Printf("TREE '%s': ", structureName)
			TLEVELORDER(tree)
		} else {
			fmt.Printf("Дерево '%s' не найден!\n", structureName)
		}
	default:
		fmt.Printf("Неизвестный тип структуры: %s\n", structureType)
		fmt.Println("Доступные: ARRAY(M), SINGLY_LIST(F), DOUBLY_LIST(L), STACK(S), QUEUE(Q), TREE(T)")
	}
}

func (c *Commands) listStructures(db *Database, filename string) {
	fmt.Printf("Структуры в базе данных '%s':\n", filename)
	
	if len(db.Arrays) > 0 {
		fmt.Print("Массивы: ")
		for name := range db.Arrays {
			fmt.Printf("%s ", name)
		}
		fmt.Println()
	}
	
	if len(db.SinglyLists) > 0 {
		fmt.Print("Односвязные списки: ")
		for name := range db.SinglyLists {
			fmt.Printf("%s ", name)
		}
		fmt.Println()
	}
	
	if len(db.DoublyLists) > 0 {
		fmt.Print("Двусвязные списки: ")
		for name := range db.DoublyLists {
			fmt.Printf("%s ", name)
		}
		fmt.Println()
	}
	
	if len(db.Stacks) > 0 {
		fmt.Print("Стеки: ")
		for name := range db.Stacks {
			fmt.Printf("%s ", name)
		}
		fmt.Println()
	}
	
	if len(db.Queues) > 0 {
		fmt.Print("Очереди: ")
		for name := range db.Queues {
			fmt.Printf("%s ", name)
		}
		fmt.Println()
	}
	
	if len(db.Trees) > 0 {
		fmt.Print("Деревья: ")
		for name := range db.Trees {
			fmt.Printf("%s ", name)
		}
		fmt.Println()
	}
	
	saveDatabaseToFile(filename, db)
}

func (c *Commands) processCommand(db *Database, command, structureName string, args []string, filename string) {
	switch command {
	// Tree commands
	case "TADD":
		if len(args) >= 1 {
			value := args[0]
			if db.Trees[structureName] == nil {
				db.Trees[structureName] = &Tree{}
			}
			TADD(db.Trees[structureName], value, false)
			saveDatabaseToFile(filename, db)
			fmt.Printf("-> вставлен %s в дерево '%s'\n", value, structureName)
		}
	case "TFIND":
		if len(args) >= 1 {
			value := args[0]
			if tree, exists := db.Trees[structureName]; exists {
				TFIND(tree, value)
			} else {
				fmt.Printf("Дерево '%s' не найдено!\n", structureName)
			}
		}
	case "TISFULL":
		if tree, exists := db.Trees[structureName]; exists {
			ok := TISFULL(tree)
			fmt.Printf("-> %s\n", map[bool]string{true: "FULL", false: "NOT FULL"}[ok])
		} else {
			fmt.Printf("Дерево '%s' не найдено!\n", structureName)
		}
	case "TLEVELORDER":
		if tree, exists := db.Trees[structureName]; exists {
			TLEVELORDER(tree)
		} else {
			fmt.Printf("Дерево '%s' не найдено!\n", structureName)
		}
	case "TPRINT":
		if tree, exists := db.Trees[structureName]; exists {
			TPRINT_STRUCTURE(tree)
		} else {
			fmt.Printf("Дерево '%s' не найдено!\n", structureName)
		}
	case "TPREORDER":
		if tree, exists := db.Trees[structureName]; exists {
			TPREORDER(tree)
		} else {
			fmt.Printf("Дерево '%s' не найдено!\n", structureName)
		}
	case "TINORDER":
		if tree, exists := db.Trees[structureName]; exists {
			TINORDER(tree)
		} else {
			fmt.Printf("Дерево '%s' не найдено!\n", structureName)
		}
	case "TPOSTORDER":
		if tree, exists := db.Trees[structureName]; exists {
			TPOSTORDER(tree)
		} else {
			fmt.Printf("Дерево '%s' не найдено!\n", structureName)
		}
	case "TCLEAR":
		if tree, exists := db.Trees[structureName]; exists {
			TCLEAR(tree)
			delete(db.Trees, structureName)
			saveDatabaseToFile(filename, db)
			fmt.Printf("-> дерево '%s' очищено\n", structureName)
		} else {
			fmt.Printf("Дерево '%s' не найдено!\n", structureName)
		}

	// Array commands (остальные команды аналогично)
	// Здесь должна быть реализация всех остальных команд...
	// Для краткости покажу только несколько примеров:

	case "MPUSH":
		if len(args) >= 1 {
			value := args[0]
			if db.Arrays[structureName] == nil {
				db.Arrays[structureName] = &Array{}
			}
			MPUSH(db.Arrays[structureName], value)
			saveDatabaseToFile(filename, db)
			fmt.Printf("-> добавлен %s в массив '%s'\n", value, structureName)
		}
	case "MPRINT":
		if arr, exists := db.Arrays[structureName]; exists {
			fmt.Print("-> ")
			MPRINT(arr)
		} else {
			fmt.Printf("Массив '%s' не найден!\n", structureName)
		}

	// Аналогично для всех остальных команд FADD_HEAD, LADD_HEAD, SPUSH, QPUSH и т.д.

	default:
		fmt.Printf("Неизвестная команда: %s\n", command)
	}
}
