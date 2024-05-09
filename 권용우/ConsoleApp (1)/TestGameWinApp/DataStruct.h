#pragma once
template <typename T>
class List
{
	typedef struct _Node {
		T data;
		_Node* Next;
		_Node() {
			Next = nullptr;
		}
		_Node(T _data) {
			data = _data;
			Next = nullptr;
		}
		~_Node() {
			if (Next != nullptr)
				delete Next;
		}
	} Node;

	Node* topPointer;
public:
	List() {
		topPointer = nullptr;
	}

	~List() {
		if (topPointer != nullptr) {
			delete topPointer;
			topPointer = nullptr;
		}
	}

	void Push(T t) {
		if (topPointer == nullptr) {
			topPointer = new Node(t);
		}
		else {
			Node* ptr = topPointer;
			while (true) {
				if (ptr->Next == nullptr) {
					ptr->Next = new Node(t);
					break;
				}
				ptr = ptr->Next;
			}
		}
	}
	T Pop() {
		//if (topPointer == nullptr) return;
		Node* ptr = topPointer;
		while (true) {
			if (ptr->Next == nullptr) {
				return ptr->data;
				break;
			}
			ptr = ptr->Next;
		}
	}
	void LastDelete() {
		if (topPointer == nullptr) return;

		Node* ptr = topPointer;
		Node* prev = nullptr;
		int count = 0;			// push�� ������ 1�� ������ �� pop�� �ϸ� topPointer�� ���� �� ���� �̸� ī���� �ϱ� ����.

		while (true) {
			if (ptr->Next == nullptr) {
				delete ptr;
				if (prev != nullptr)
					prev->Next = nullptr;
				if (count == 0)
					topPointer = nullptr;
				break;
			}
			prev = ptr;
			ptr = ptr->Next;
			count++;
		}
	}
	int Size() {
		int count = 0;
		Node* ptr = topPointer;
		while (ptr != nullptr) {
			count++;
			ptr = ptr->Next;
		}
		return count;
	}
};

template <typename T>
struct Queue
{
	T* queue;
	int rear = 0;
	int front = 0;
	int length;
	int count = 0;
	Queue(int arrayLength) {
		length = arrayLength;
		queue = new T[arrayLength];
	}
	void Enqueue(T t) {
		if (isFull()) {
			return;
		}
		queue[(rear++) % length] = t;
		count++;
	}
	T Dequeue() {
		if (isEmpty()) {
			return 0;
		}
		count--;
		return queue[(front++) % length];
	}
	bool isFull() {
		return count == length;
	}
	bool isEmpty() {
		return count == 0;
	}
	int GetCount() {
		return count;
	}
};

template <typename T>
class DoubleLinkedList {
public:
	class Node
	{
	public:
		T data;
		Node* Prev = nullptr;
		Node* Next = nullptr;
	};

	Node* m_pHead = nullptr;
	Node* m_pTail = nullptr;

	struct Iterator
	{
		Node* pCurr = nullptr;

		Iterator(Node* p = nullptr)
		{
			pCurr = p;
		}
		Iterator& operator++()
		{
			pCurr = pCurr->Next;
			return *this;
		}
		T& operator*()
		{
			return pCurr->data;
		}
		bool operator==(const Iterator& ref)
		{
			return  pCurr == ref.pCurr;
		}
		bool operator!=(const Iterator& ref)
		{
			return  pCurr != ref.pCurr;
		}

	};

	Iterator begin() // �ҹ��ڷ� �����ؾ� for������ ������ �νĵ�.
	{
		return Iterator(m_pHead);
	}
	Iterator end()
	{
		return Iterator(nullptr);
	}

	Node* Insert(Node* pPos, T data) // pos��� ������ Data�� �߰��ϰ� ��带 ����, Insert(m_pTail,data);
	{
		Node* temp = new Node();
		temp->data = data;
		if (m_pHead == nullptr) {
			m_pHead = temp;
			temp->Prev = nullptr;
		}
		if (m_pTail == nullptr) {
			m_pTail = temp;
			temp->Next = nullptr;
		}
		Node* next = pPos->Next;
		temp->Prev = pPos;
		temp->Next = next;
		pPos->Next = temp;
		next->Prev = temp;
		return temp;
	}
	Node* PushBack(T data) // PushBack�� �����ص� ���ӿ� �����ϴµ� ������ ����.������ ���ʿ����� �߰��Ѵٰ� �����Ѵ�.
	{
		Node* temp = new Node();
		temp->data = data;
		if (m_pHead == nullptr)
		{
			m_pHead = m_pTail = temp;
			temp->Prev = temp->Next = nullptr;
		}
		else {
			m_pTail->Next = temp;
			temp->Prev = m_pTail;
			m_pTail = temp;
		}
		return temp;
	}
	Node* Erase(Node* pPos) // ��带 ����� ���� ��� ����
	{
		Node* temp = pPos->Next;
		if (pPos->Prev != nullptr)
			pPos->Prev->Next = pPos->Next;
		if (pPos->Next != nullptr)
			pPos->Next->Prev = pPos->Prev;
		delete pPos;
		return temp;
	}

};
