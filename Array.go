package main

import "fmt"

func MPUSH(arr *Array, value string) {
	if arr.Size >= arr.Capacity {
		newCap := arr.Capacity * 2
		if newCap == 0 {
			newCap = 4
		}
		newData := make([]string, newCap)
		copy(newData, arr.Data)
		arr.Data = newData
		arr.Capacity = newCap
	}
	
	if arr.Size < len(arr.Data) {
		arr.Data[arr.Size] = value
	} else {
		arr.Data = append(arr.Data, value)
	}
	arr.Size++
}

func MADD_INDEX(arr *Array, value string, index int) {
	if index > arr.Size {
		fmt.Printf("Неверный индекс! Максимальный допустимый индекс: %d\n", arr.Size)
		return
	}
	
	if arr.Size >= arr.Capacity {
		newCap := arr.Capacity * 2
		if newCap == 0 {
			newCap = 4
		}
		newData := make([]string, newCap)
		copy(newData, arr.Data)
		arr.Data = newData
		arr.Capacity = newCap
	}
	
	// Сдвигаем элементы
	for i := arr.Size; i > index; i-- {
		if i < len(arr.Data) {
			arr.Data[i] = arr.Data[i-1]
		} else {
			arr.Data = append(arr.Data, arr.Data[i-1])
		}
	}
	
	if index < len(arr.Data) {
		arr.Data[index] = value
	} else {
		arr.Data = append(arr.Data, value)
	}
	arr.Size++
}

func MREMOVE(arr *Array, index int) {
	if index >= arr.Size {
		fmt.Println("Неверный индекс!")
		return
	}
	
	for i := index; i < arr.Size-1; i++ {
		if i+1 < len(arr.Data) {
			arr.Data[i] = arr.Data[i+1]
		}
	}
	arr.Size--
}

func MREPLACE(arr *Array, index int, value string) {
	if index >= arr.Size {
		fmt.Println("Неверный индекс!")
		return
	}
	
	if index < len(arr.Data) {
		arr.Data[index] = value
	}
}

func MGET(arr *Array, index int) (string, error) {
	if index >= arr.Size {
		return "", fmt.Errorf("Неверный индекс")
	}
	
	if index < len(arr.Data) {
		return arr.Data[index], nil
	}
	return "", fmt.Errorf("Индекс вне диапазона")
}

func MLENGTH(arr *Array) int {
	return arr.Size
}

func MPRINT(arr *Array) {
	if arr.Size == 0 {
		fmt.Println("Массив пуст!")
		return
	}
	
	fmt.Printf("Массив [%d]: ", arr.Size)
	for i := 0; i < arr.Size; i++ {
		fmt.Print(arr.Data[i])
		if i < arr.Size-1 {
			fmt.Print(", ")
		}
	}
	fmt.Println()
}

func MCLEAR(arr *Array) {
	arr.Data = nil
	arr.Size = 0
	arr.Capacity = 0
	fmt.Println("Массив очищен")
}
