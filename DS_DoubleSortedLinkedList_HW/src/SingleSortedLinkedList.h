/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * @file SingleSortedLinkedList.h
 * 중복 허용, 단일 연결구조를 이용한 정렬 정수 리스트
 * 두 개의 포인터를 이용하여 popBack, remove 연산 구현
 * head와 tail 유지, dummy 노드를 사용함, 코드 중복 제거
 */

#ifndef SINGLESORTEDLINKEDLIST_H_
#define SINGLESORTEDLINKEDLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class SingleSortedLinkedList {
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

	void copyList(const SingleSortedLinkedList& other){
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
		tail = dest;
	}

	void moveList(SingleSortedLinkedList& tmp){
		numItems = tmp.numItems;
		head = tmp.head;
		tail = tmp.tail;
		tmp.head = tmp.tail = nullptr;
		tmp.numItems = 0;
	}

public:
	explicit SingleSortedLinkedList() = default;

	explicit SingleSortedLinkedList(const std::initializer_list<int>& initList){
		for(auto item: initList) add(item);
	}

	virtual ~SingleSortedLinkedList(){
		clear();
	}

	SingleSortedLinkedList(const SingleSortedLinkedList& other){
		copyList(other);
	}

	SingleSortedLinkedList(SingleSortedLinkedList&& tmp){
		moveList(tmp);
	}

	const SingleSortedLinkedList& operator=(const SingleSortedLinkedList& other){
		clear();
		copyList(other);
		return *this;
	}

	const SingleSortedLinkedList& operator=(SingleSortedLinkedList&& tmp){
		clear();
		moveList(tmp);
		return *this;
	}

	bool isEmpty() const noexcept {
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
		head = tail = nullptr;
		numItems = 0;
	}

	void add(int item){
		Node *newNode{new Node(item)};
		if(isEmpty()) head = tail = newNode;
		else{
			Node dummy{-1, head};
			Node* prev{&dummy};
			Node* curr{head};
			while(curr&& curr->item<item){
				prev = curr;
				curr = curr->next;
			}
			prev->next = newNode;
			newNode->next = curr;
			if(!curr) tail = newNode;
			head = dummy.next;
		}
		++numItems;
	}

	int peekFront() const{
		if(isEmpty()) throw std::runtime_error("peekFront: empty state");
		return head->item;
	}

	int peekBack() const{
		if(isEmpty()) throw std::runtime_error("peekBack: empty state");
		return tail->item;
	}

	// 중간시험 문제
	void merge(SingleSortedLinkedList& other);
	void removeDuplicates();

	void debugPrint(){
		std::cout << "head: " << head->item  << ": " << head << '\n';
		std::cout << "tail: " << tail->item << ": " << tail << '\n';
		Node* curr{head};
		while(curr){
			std::cout << curr->item << ": " << curr << ", " ;
			curr = curr->next;
		}
		std::cout << '\n';

	}

	auto begin() {return ListIterator<int>(head);}
	auto end() {return ListIterator<int>(nullptr);}
	auto cbegin() const {return ListIterator<const int>(head);}
	auto cend() const {return ListIterator<const int>(nullptr);}
};

#endif /* SINGLESORTEDLINKEDLIST_H_ */
