/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 장현수 2018136114
 * @file SingleUnsortedLinkedList.h
 * 중복 허용, 단일 연결구조를 이용한 비정렬 정수 리스트
 * 두 개의 포인터를 이용하여 popBack, remove 연산 구현
 * head만 유지, dummy 노드를 사용하지 않음, 코드 중복을 제거하지 않음
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
	size_t numItems{0};

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
	}

	virtual ~SingleUnsortedLinkedList(){
		clear();
	}

	SingleUnsortedLinkedList(const SingleUnsortedLinkedList& other){
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
	}

	SingleUnsortedLinkedList(SingleUnsortedLinkedList&& tmp){
		numItems = tmp.numItems;
		head = tmp.head;
		tmp.head = nullptr;
		tmp.numItems = 0;
	}

	const SingleUnsortedLinkedList& operator=(const SingleUnsortedLinkedList& other){
		clear();
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
		return *this;
	}

	const SingleUnsortedLinkedList& operator=(SingleUnsortedLinkedList&& tmp){
		clear();
		numItems = tmp.numItems;
		head = tmp.head;
		tmp.head = nullptr;
		tmp.numItems = 0;
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
		numItems = 0;
	}

	int operator[](int index) const{
		if(index>=0&&index<numItems){
			Node* curr{head};
			for(int i=0; i<index; ++i) curr = curr->next;
			return curr->item;
		}
		else throw std::out_of_range("Index ERROR: [] const");
	}

	int& operator[](int index){
		if(index>=0&&index<numItems){
			Node* curr{head};
			for(int i=0; i<index; ++i) curr = curr->next;
			return curr->item;
		}
		else throw std::out_of_range("Index ERROR: []");
	}

	void pushBack(int item){
		Node *newNode{new Node(item)};
		if(isEmpty())
			head = newNode;
		else{
			Node *tail{head};
			while(tail->next) tail = tail->next;
			tail->next = newNode;
		}
		++numItems;
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: empty state");
		Node* prev{nullptr};
		Node* curr{head};
		while(curr->next){
			prev = curr;
			curr = curr->next;
		}
		int ret{curr->item};
		if(prev) prev->next = nullptr;
		else head = nullptr;
		delete curr;
		--numItems;
		return ret;
	}

	void pushFront(int item){
		Node *newNode{new Node(item)};
		newNode->next = head;
		head = newNode;
		++numItems;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: empty state");
		int ret{head->item};
		Node* deleteNode{head};
		head = head->next;
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
		Node *tail{head};
		while(tail->next) tail = tail->next;
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

	void removeFirst(int item) noexcept{
		if(isEmpty()) return;
		Node* prev{nullptr};
		Node* curr{head};
		while(curr){
			if(curr->item==item) break;
			prev = curr;
			curr = curr->next;
		}
		if(curr){
			if(prev) prev->next = curr->next;
			else head = head->next;
			delete curr;
			--numItems;
		}
	}

	void removeAll(int item) noexcept{
		if(isEmpty()) return;
		Node* prev{nullptr};
		Node* curr{head};
		while(curr){
			if(curr->item==item){
				Node* next{curr->next};
				if(prev) prev->next = curr->next;
				else head = head->next;
				delete curr;
				curr = next;
				--numItems;
			}
			else{
				prev = curr;
				curr = curr->next;
			}
		}
	}

	auto begin() {return ListIterator<int>(head);}
	auto end() {return ListIterator<int>(nullptr);}
	auto cbegin() const {return ListIterator<const int>(head);}
	auto cend() const {return ListIterator<const int>(nullptr);}
};

#endif /* SINGLEUNSORTEDLINKEDLIST_H_ */
