/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * @file UnsortedArrayList.h
 * 용량 고정, 중복 허용, 배열을 이용한 비정렬 정수 리스트
 * 순서를 유지하는 방법으로 pushFront, popFront, remove를 구현함
 */

#ifndef UNSORTEDARRAYLIST_H_
#define UNSORTEDARRAYLIST_H_
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <iterator>
#include <initializer_list>

class UnsortedArrayList {
	template <typename U>
	class ListIterator: public std::iterator<std::input_iterator_tag,U>{
        U *p;
    public:
        explicit ListIterator(U *p): p{p} {}
        const ListIterator& operator++() noexcept {++p; return *this;}
        ListIterator operator++(int) noexcept {auto retval{*this}; ++p; return retval;}
        bool operator==(const ListIterator& other) const noexcept {return p == other.p;}
        bool operator!=(const ListIterator& other) const noexcept {return p != other.p;}
        U& operator*() const noexcept {return *p;}
    };
private:
	// 검사 목적으로 용량을 작게 설정
	size_t capacity;
	int* items;
	size_t numItems{0};

	void shiftLeft(size_t startIdx){
		for(size_t i{startIdx}; i<numItems-1; ++i)
			items[i] = items[i+1];
		--numItems;
	}
	size_t search(int item, size_t startLoc=0) const noexcept{
		for(size_t i{startLoc}; i<numItems; ++i)
			if(items[i] == item) return i;
		return capacity;
	}
	void increaseCapacity(){
		capacity *= 2;
		int* tmp{new int[capacity]};
		std::copy(items, items+numItems, tmp);
		if(items) delete[] items;
		items = tmp;
	}
public:
	explicit UnsortedArrayList(size_t capacity = 5) : capacity{capacity}, items{new int[capacity]}{}
	explicit UnsortedArrayList(const std::initializer_list<int>& initList) :
		UnsortedArrayList(initList.size()){
		numItems = initList.size();
		size_t i{0};
		std::copy(initList.begin(), initList.end(), items);
	}

	virtual ~UnsortedArrayList(){
		if(items) delete[] items;
	}

	UnsortedArrayList(const UnsortedArrayList& other):
		UnsortedArrayList(other.capacity){
		numItems = other.numItems;
		std::copy(other.items, other.items+numItems, items);
	}

	UnsortedArrayList(UnsortedArrayList&& tmp):
		capacity{tmp.capacity}, numItems{tmp.numItems}{
		items = tmp.items;
		tmp.items = nullptr;
	}

	const UnsortedArrayList& operator=(const UnsortedArrayList& other){
		capacity = other.capacity;
		numItems = other.numItems;
		if(items) delete[] items;
		items = new int[capacity];
		std::copy(other.items, other.items+numItems, items);
		return *this;
	}

	const UnsortedArrayList& operator=(UnsortedArrayList&& tmp){
		capacity = tmp.capacity;
		numItems = tmp.numItems;
		if(items) delete[] items;
		items = tmp.items;
		tmp.items = nullptr;
		return *this;
	}

	bool isEmpty() const noexcept {
		return numItems == 0;
	}

	bool isFull() const noexcept {
		return false;
	}

	size_t size() const noexcept{
		return numItems;
	}

	void clear() noexcept{
		numItems = 0;
	}

	int operator[](int index) const{
		if(index>=0&&index<numItems) return items[index];
		else throw std::out_of_range("Index Error: [] const");
	}

	int& operator[](int index){
		if(index>=0&&index<numItems) return items[index];
		else throw std::out_of_range("Index Error: [] const");
	}

	void pushBack(int item){
		if(numItems==capacity) increaseCapacity();
		items[numItems++] = item;
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: empty state");
		return items[--numItems];
	}

	void pushFront(int item){
		if(numItems==capacity) increaseCapacity();
		for(size_t i{numItems}; i >0; --i)
			items[i] = items[i-1];
		items[0] = item;
		++numItems;
	}

	int popFront(){
		if(isEmpty()) throw std::runtime_error("popFront: empty state");
		int ret{items[0]};
		shiftLeft(0);
		return ret;
	}

	int peekFront() const{
		if(isEmpty()) throw std::runtime_error("peekFront: empty state");
		return items[0];
	}

	int peekBack() const{
		if(isEmpty()) throw std::runtime_error("peekBak: empty state");
		return items[numItems-1];
	}

	bool find(int item) const noexcept{
		if(isEmpty()) return false;
		return search(item)!=capacity;
	}

	void removeFirst(int item) noexcept{
		if(isEmpty()) return;
		size_t itemLoc{search(item)};
		if(itemLoc!=capacity) shiftLeft(itemLoc);
	}

	void removeAll(int item) noexcept{
		if(isEmpty()) return;
		size_t itemLoc{search(item)};
		while(itemLoc!=capacity){
			shiftLeft(itemLoc);
			itemLoc = search(item, itemLoc);
		}
	}

	void insert(int index, int item){
		if(numItems==capacity) increaseCapacity();
		if(!(index>=0&&index<numItems)) throw std::out_of_range("insert: out of range");
		for(size_t i{numItems}; i >index; --i)
			items[i] = items[i-1];
		items[index] = item;
		++numItems;
	}

	auto begin() {return ListIterator<int>(items);}
	auto end() {return ListIterator<int>(items+numItems);}
	auto cbegin() const {return ListIterator<const int>(items);}
	auto cend() const {return ListIterator<const int>(items+numItems);}
};

#endif /* UNSORTEDARRAYLIST_H_ */
