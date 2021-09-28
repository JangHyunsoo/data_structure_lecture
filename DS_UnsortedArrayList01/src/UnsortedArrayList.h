/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 장현수 (2018136114)
 * @file UnsortedArrayList.h
 * 용량 고정, 중복 허용, 배열을 이용한 비정렬 정수 리스트
 * 순서를 유지하는 방법으로 pushFront, popFront, remove, insert를 구현함
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
	const static inline size_t MAX{10};
	int items[MAX];
	size_t numItems{0};

	void shiftLeft(size_t startIdx){
		for(size_t i{startIdx}; i<numItems-1; ++i)
			items[i] = items[i+1];
		--numItems;
	}
	size_t search(int item, size_t startLoc=0) const noexcept{
		for(size_t i{startLoc}; i<numItems; ++i)
			if(items[i] == item) return i;
		return MAX;
	}
public:
	explicit UnsortedArrayList() = default;
	explicit UnsortedArrayList(const std::initializer_list<int>& initList){
		numItems = std::min(initList.size(), MAX);
		auto it{initList.begin()};
		for(size_t i{0}; i<numItems; ++i){
			items[i] = *it;
			++it;
		}
	}

	virtual ~UnsortedArrayList() = default;

	bool isEmpty() const noexcept {
		return numItems == 0;
	}

	bool isFull() const noexcept {
		return numItems==MAX;
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
		if(isFull()) throw std::runtime_error("pushBack: full state");
		items[numItems++] = item;
	}

	int popBack(){
		if(isEmpty()) throw std::runtime_error("popBack: empty state");
		return items[--numItems];
	}

	void pushFront(int item){
		if(isFull()) throw std::runtime_error("pushFront: full state");
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
		return search(item)!=MAX;
	}

	void removeFirst(int item) noexcept{
		if(isEmpty()) return;
		size_t itemLoc{search(item)};
		if(itemLoc!=MAX) shiftLeft(itemLoc);
	}

	void removeAll(int item) noexcept{
		if(isEmpty()) return;
		size_t itemLoc{search(item)};
		while(itemLoc!=MAX){
			shiftLeft(itemLoc);
			itemLoc = search(item, itemLoc);
		}
	}

	void insert(int index, int item){
		// full state에는 insert가 불가능하다고 판단하여 full state 애러를 발생시켰다,
		if(isFull()) throw std::runtime_error("insert: full state");
		// 만약 numItems 밖에 인덱스에 접근하면 out of range 애러를 발생시켰다.
		if(!(index>=0&&index<numItems)) throw std::out_of_range("insert: out of range");
		// ShiftRight를 만들려했지만 생각보다 중복되는 부분이 별로 없어 생략하기로 했다.
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
