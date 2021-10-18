/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 장현수 2018136114
 * @file SingleUnsortedLinkedList.h
 * 중복 허용, 단일 연결구조를 이용한 비정렬 정수 리스트
 * 두 개의 포인터를 이용하여 popBack, remove 연산 구현
 * head과 tail 유지, dummy 노드를 사용함, 코드 중복을 제거함.
 */

#ifndef SINGLEUNSORTEDLINKEDLIST_H_
#define SINGLEUNSORTEDLINKEDLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class SingleUnsortedLinkedList {
private:
	struct Node{
		int item{0};
		Node* next{nullptr};
		Node() = default;
		Node(int item, Node* next = nullptr): item{item}, next{next}{}
	};
	template <typename U>
	class ListIterator: public std::iterator<std::input_iterator_tag,U>{
        Node *p;
    public:
        explicit ListIterator(Node *p): p{p} {}
        const ListIterator& operator++() noexcept {p = p->next; return *this;}
        ListIterator operator++(int) noexcept {auto retval{*this}; p = p->next; return retval;}
        bool operator==(const ListIterator& other) const noexcept {return p == other.p;}
        bool operator!=(const ListIterator& other) const noexcept {return p != other.p;}
        U& operator*() noexcept {return p->item;}
    };

	Node* head{nullptr};
	Node* tail{nullptr};
	size_t numItems{0};

	void copyList(const SingleUnsortedLinkedList& other){
		Node* dest{nullptr};
		Node* src{other.head};
		while(src){
			Node* newNode{new Node{src->item}};
			if(dest){
				dest->next = newNode;
				dest = newNode;
			}
			else head = dest = newNode;
			src = src->next;
			++numItems;
		}
		// 위에서 dest가 마지막 노드까지 진행됨으로 아래처럼 코드를 작성하였다.
		tail = dest;
	}
	void moveList(SingleUnsortedLinkedList& tmp){
		numItems = tmp.numItems;
		head = tmp.head;
		tail = tmp.tail;
		tmp.head = nullptr;
		tmp.tail = nullptr;
		tmp.numItems = 0;
	}
	int& getItem(int index) const {
		Node* curr{head};
		for(int i=0; i<index; ++i) curr = curr->next;
		return curr->item;
	}

	void removeNode(Node* prev, Node* curr){
		// curr->next가 nullptr이면 마지막 노드이기 때문에 tail을 옮겨야 한다.
		if(curr->next == nullptr){
			// curr가 head이면 노드가 하나 남았기 때문에 tail=nullptr를 해야한다.
			if(curr==head) tail = nullptr;
			else tail = prev;
		}
		prev->next = curr->next;
		delete curr;
		--numItems;
	}
public:
	explicit SingleUnsortedLinkedList() = default;

	explicit SingleUnsortedLinkedList(const std::initializer_list<int>& initList){
		Node* curr{nullptr};
		for(auto item: initList){
			Node* newNode{new Node{item}};
			if(curr){
				curr->next = newNode;
				curr = newNode;
			}
			else head = curr = newNode;
			++numItems;
		}
		// 위에서 curr가 마지막 노드까지 진행됨으로 아래처럼 코드를 작성하였다.
		tail = curr;
	}

	virtual ~SingleUnsortedLinkedList(){
		clear();
	}

	SingleUnsortedLinkedList(const SingleUnsortedLinkedList& other){
		copyList(other);
	}

	SingleUnsortedLinkedList(SingleUnsortedLinkedList&& tmp){
		moveList(tmp);
	}

	const SingleUnsortedLinkedList& operator=(const SingleUnsortedLinkedList& other){
		clear();
		copyList(other);
		return *this;
	}

	const SingleUnsortedLinkedList& operator=(SingleUnsortedLinkedList&& tmp){
		clear();
		moveList(tmp);
		return *this;
	}

	bool isEmpty() const noexcept {
		//return numItems==0;
		//return head==nullptr;
		return !head;
	}

	bool isFull() const noexcept {
		return false;
	}
	bool checkTail(){
		return tail;
	}

	size_t size() const noexcept{
		return numItems;
	}

	void clear() noexcept{
		Node* curr{head};
		while(curr){
			Node* deleteNode{curr};
			curr = curr->next;
			delete deleteNode;
		}
		head = nullptr;
		tail = nullptr;
		numItems = 0;
	}

	int operator[](int index) const{
		if(index>=0&&index<numItems) return getItem(index);
		else throw std::out_of_range("Index ERROR: [] const");
	}

	int& operator[](int index){
		if(index>=0&&index<numItems) return getItem(index);
		else throw std::out_of_range("Index ERROR: []");
	}

	void pushBack(int item){
		Node *newNode{new Node(item)};
		if(isEmpty()) {
			head = newNode;
			tail = newNode;
		}
		else {
			tail->next = newNode;
			tail = tail->next;
		}
		++numItems;
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: empty state");
		Node dummy{-1,head};
		Node* prev{&dummy};
		while(prev->next->next){
			prev = prev->next;
		}
		int ret{prev->next->item};
		Node* deleteNode{prev->next};
		prev->next = nullptr;
		head = dummy.next;
		// head가 없으면 empty이기 때문에 tail을 nullptr로 바꿔야한다.
		if(head) tail = prev;
		else tail = nullptr;
		delete deleteNode;
		--numItems;
		return ret;
	}

	void pushFront(int item){
		Node *newNode{new Node(item)};
		// head가 없다면 빈 노드에서 추가하는 것이기 때문에 tail=newNode를 해준다.
		if(!head) tail = newNode;
		newNode->next = head;
		head = newNode;
		++numItems;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: empty state");
		int ret{head->item};
		Node* deleteNode{head};
		head = head->next;
		// head가 없으면 empty이기 때문에 tail도 nullptr로 바꿔야한다.
		if(isEmpty()) tail = nullptr;
		delete deleteNode;
		--numItems;
		return ret;
	}

	int peekFront() const{
		if(isEmpty()) throw std::runtime_error("peekFront: empty state");
		return head->item;
	}

	int peekBack() const{
		if(isEmpty()) throw std::runtime_error("peekBack: empty state");
		return tail->item;
	}

	bool find(int item) const noexcept{
		if(isEmpty()) return false;
		Node *curr{head};
		while(curr){
			if(curr->item==item) return true;
			curr = curr->next;
		}
		return false;
	}

	// remove는 위에서 처리했기 때문에 바꿀게 없다.
	void removeFirst(int item) noexcept{
		if(isEmpty()) return;
		Node dummy{-1,head};
		Node* prev{&dummy};
		while(prev->next){
			if(prev->next->item==item){
				removeNode(prev, prev->next);
				break;
			}
			prev = prev->next;
		}
		head = dummy.next;
	}

	void removeAll(int item) noexcept{
		if(isEmpty()) return;
		Node dummy{-1,head};
		Node* prev{&dummy};
		while(prev->next){
			if(prev->next->item==item)
				removeNode(prev,prev->next);
			else prev = prev->next;
		}
		head = dummy.next;
	}

	auto begin() {return ListIterator<int>(head);}
	auto end() {return ListIterator<int>(nullptr);}
	auto cbegin() const {return ListIterator<const int>(head);}
	auto cend() const {return ListIterator<const int>(nullptr);}
};

#endif /* SINGLEUNSORTEDLINKEDLIST_H_ */
