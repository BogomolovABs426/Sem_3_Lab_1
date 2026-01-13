package main

// Array
type Array struct {
	Data     []string
	Size     int
	Capacity int
	Filename string
}

// Singly List
type FNode struct {
	Data string
	Next *FNode
}

type SingleList struct {
	Head     *FNode
	Size     int
	Filename string
}

// Doubly List
type LNode struct {
	Data string
	Next *LNode
	Prev *LNode
}

type DoublyList struct {
	Head     *LNode
	Tail     *LNode
	Size     int
	Filename string
}

// Stack
type SNode struct {
	Data string
	Next *SNode
}

type Stack struct {
	Top      *SNode
	Size     int
	Filename string
}

// Queue
type QNode struct {
	Data string
	Next *QNode
}

type Queue struct {
	Front    *QNode
	Rear     *QNode
	Size     int
	Filename string
}

// Tree
type TNode struct {
	Data   string
	Left   *TNode
	Right  *TNode
	Parent *TNode
}

type Tree struct {
	Root     *TNode
	Size     int
	Filename string
}

// Database
type Database struct {
	Arrays      map[string]*Array
	SinglyLists map[string]*SingleList
	DoublyLists map[string]*DoublyList
	Stacks      map[string]*Stack
	Queues      map[string]*Queue
	Trees       map[string]*Tree
}

func NewDatabase() *Database {
	return &Database{
		Arrays:      make(map[string]*Array),
		SinglyLists: make(map[string]*SingleList),
		DoublyLists: make(map[string]*DoublyList),
		Stacks:      make(map[string]*Stack),
		Queues:      make(map[string]*Queue),
		Trees:       make(map[string]*Tree),
	}
}
