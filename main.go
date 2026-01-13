package main

import (
	"bufio"
	"fmt"
	"os"
)

func main() {
	cmd := &Commands{}
	filename := ""
	query := ""

	// Если переданы аргументы командной строки
	if len(os.Args) > 1 {
		filename, query = parseCommandLine(os.Args)
		
		if filename == "" || query == "" {
			fmt.Printf("Использование: %s --file <filename> --query <command>\n", os.Args[0])
			fmt.Printf("Пример: %s --file file.data --query 'SPUSH mystack item'\n", os.Args[0])
			return
		}
		
		// Выполняем команду
		cmd.Execute(query, filename)
	} else {
		// Интерактивный режим
		fmt.Print("Введите имя файла для работы: ")
		fmt.Scan(&filename)
		fmt.Println("Введите команды:")
		scanner := bufio.NewScanner(os.Stdin)
		
		for {
			fmt.Print("> ")
			if !scanner.Scan() {
				break
			}
			
			query = scanner.Text()
			
			if query == "exit" || query == "quit" {
				break
			}
			
			if query != "" {
				cmd.Execute(query, filename)
			}
		}
	}

	fmt.Println("Программа завершена")
}

func parseCommandLine(args []string) (string, string) {
	filename := ""
	query := ""
	
	for i := 1; i < len(args); i++ {
		arg := args[i]
		if arg == "--file" && i+1 < len(args) {
			filename = args[i+1]
			i++
		} else if arg == "--query" && i+1 < len(args) {
			query = args[i+1]
			i++
		}
	}
	
	return filename, query
}
