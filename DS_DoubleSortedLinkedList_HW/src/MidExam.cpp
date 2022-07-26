/*
 * 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * 2021년도 2학기 중간시험
 * 학번:     성명:
 */
#include <iostream>
#include "SingleUnsortedLinkedList.h"
#include "SingleSortedLinkedList.h"
#include "DoubleUnsortedLinkedList.h"

// (10점) 주어진 색인에 해당하는 노드를 삭제해야 함. 첫 번째 노드의 색인은 0임
// 주어진 인자가 유효한 범위가 아니면 std::out_of_range 예외를 발생해야 함
// 리스트의 현재 모습이 1(head)->5-2->4(tail)일 때,
// removeAt(3)이 수행되면 리스트가 다음과 같이 변경되어야 함
// ==> 1(head)->5->2(tail)
void SingleUnsortedLinkedList::removeAt(size_t index){
	if(numItems<=index||index<0) throw std::out_of_range("removeAt: out_of_range");
	Node* newNode{new Node(index)};
	Node dummy{-1};
	Node* curr{head};
	Node* prev{&dummy};
	dummy.next=head;

	for(int i = 0; i < index; ++i){
		prev = curr;
		curr = curr->next;
	}
	if(curr==head){
		dummy.next = nullptr;
	}
	if(curr==tail){
		tail = prev;
	}
	if(isEmpty()){
		tail = nullptr;
	}
	prev->next=curr->next;
	delete curr;
	head = dummy.next;
	--numItems;
}

// (15점) 주어진 값을 기준으로 비정렬 리스트를 주어진 값보다 작은 것과 큰 것으로
// 분할(두 개의 리스트를 만드는 것은 아님)해야 함
// 분할 후 원래 순서는 유지해야 함
// 추가 공간을 사용하지 않고 구현해야 함
// 새 노드를 생성하거나 리스트의 내용을 배열이나 벡터로 옮긴 후 작업하지 않아야 함
// 리스트의 모습이 1(head)->4-1->5->3->2(tail)일 때,
// partition(3)이 호출되면 다음과 같이 변경되어야 함
// ==> 1(head)->1->2->3->4->5(tail)
void SingleUnsortedLinkedList::partition(int item){

}


// (15점) 현재 정렬 리스트와 주어진 정렬 리스트를 결합하여야 함
// 결합 후 인자로 주어진 리스트는 빈 리스트가 되어야 함
// 결합 과정에서 새 노드를 생성하지 않고 기존 노드들을 그대로 이용해야 함
// 현재 리스트의 모습이 1(head)->5->7(tail)이고, 주어진 리스트의 모습이 2(head)->3->6(tail)이면
// 원래 리스트는 1(head)->2->3->5->6->7(tail)로 바뀌어야 하고 인자는 빈 리스트가 되어야 함
void SingleSortedLinkedList::merge(SingleSortedLinkedList& other){
	Node* node{other.head};
	other.clear();

	while(node){
		Node* tmp{node->next};
		if(isEmpty()) {
			node->next = nullptr;
			head = tail = node;
		}
		else{
			Node dummy{-1, head};
			Node* prev{&dummy};
			Node* curr{head};
			while(curr&& curr->item<node->item){
				prev = curr;
				curr = curr->next;
			}
			prev->next = node;
			node->next = curr;
			if(!curr) tail = node;
			head = dummy.next;
		}
		numItems++;
		node = tmp;
	}
}

// (15점) 정렬 리스트에 있는 중복된 요소를 제거함
// 현재 리스트의 모습이 1(head)->1->2->5->5(tail)일
// 중복 요소를 제거한 후에 모습은 다음과 같아야 함
// ==> 1(head)->2->5(tail)
void SingleSortedLinkedList::removeDuplicates(){
	if(isEmpty()) throw std::runtime_error("removeDuplicates: empty state");
	Node* curr{head};

	while(curr){
		if(!curr->next) return;
		if(curr->item == curr->next->item){
			curr->next = curr->next->next;
			delete curr->next;
			numItems--;
		}
		else curr = curr->next;
	}

}

// (10점) 이중 연결구조 기반 비정렬 리스트에서 특정 값을 모두 교체함
// 현재 리스트의 모습이 5(head)<->2<->2<->1<->2<->5(tail)이고,
// 인자로 2, 0이 주어지면 리스트에 있는 2를 모두 0으로 바꾸어야 함
// ==> 5(head)<->0<->0<->1<->0<->5(tail)
void DoubleUnsortedLinkedList::replaceAll(int olditem, int newitem){
	if(isEmpty()) throw std::runtime_error("replaceAll: empty state");
	Node dummy{-1,head};
	Node* curr{head};
	head->prev=&dummy;
	while(curr){
		if(curr->item == olditem){
			Node* newNode{new Node(newitem)};
			newNode->next = curr->next;
			newNode->prev = curr->prev;
			curr->prev->next=newNode;
			if(curr==head)
				head = newNode;
			if(curr==tail){
				tail=newNode;
			}else {
				curr->next->prev=newNode;
			}
			delete curr;
			curr=newNode;
		}
		curr = curr->next;
	}
	head->prev=nullptr;
}

// (10점) 이중 연결구조 기반 비정렬 리스트를 뒤집어 줌
// 추가 공간을 사용하지 않고 구현해야
// 새 노드를 생성하거나 리스트의 내용을 배열이나 벡터로 옮긴 후 작업하지 않아야 함
// 리스트의 현재 모습이 5(head)<->3<->7<->2<->4(tail)일 때 뒤집으면
// 다음과 같이 변경되어야 함
// ==> 4(head)<->2<->7<->3<->5(tail)
void DoubleUnsortedLinkedList::reverse(){
	if(isEmpty()) throw std::runtime_error("reverse: Empty state");
	Node* curr{tail};
	Node* cache{nullptr};
	head = tail;
	while(curr){
		if(!curr->prev) tail = curr;
		cache=curr->prev;
		curr->prev = curr->next;
		curr->next = cache;
		curr = curr->next;
	}

}




