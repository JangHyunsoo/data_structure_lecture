/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 장현수 2018136114
 * @file SortedArrayListTests.cpp
 * 용량 동적, 중복 허용, 배열 기반 정수 리스트
 * 테스트 프로그램
 */
#include <string>
#include "gtest/gtest.h"
#include "SortedArrayList.h"


TEST(SortedArrayList_Duplicate, listEmptyInitializationTest)
{
	SortedArrayList list{};
	ASSERT_EQ(list.size(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(SortedArrayList_Duplicate, addfindTest){
	SortedArrayList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.add(3);
	list.add(9);
	list.add(9); // 3, 3, 5, 7, 9, 9
	ASSERT_EQ(list.size(),6);
	std::string output = "";
	for(auto n: list){
		output += std::to_string(n)+",";
	}
	ASSERT_EQ(output,"3,3,5,7,9,9,");

	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(SortedArrayList_Duplicate, popTest)
{
	SortedArrayList list;
	list.add(3);
	list.add(5);
	list.add(7);
	list.add(3);
	ASSERT_EQ(list.size(),4);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"7,5,3,3,");
	ASSERT_TRUE(list.isEmpty());

	list.add(5);
	list.add(5);
	ASSERT_EQ(list.size(),2);
	list.add(3);
	list.add(7);
	output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"3,5,5,7,");
}

TEST(SortedArrayList_Duplicate, listInitializationTest)
{
	SortedArrayList list1{3,5,7};
	list1.add(9);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"3,5,7,9,");

	SortedArrayList list2{1,11,2,7,8,5,6,3,4,9,10,};
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,10,11,");
}

TEST(SortedArrayList_Duplicate, findTest){
	SortedArrayList list{3,3,5,7,9};
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(SortedArrayList_Duplicate, removeFirstTest){
	SortedArrayList list{3,3,5,6,6,6,9};
	list.removeFirst(3);
	ASSERT_EQ(list.peekFront(), 3);
	ASSERT_EQ(list.size(),6);
	list.removeFirst(9);
	ASSERT_EQ(list.peekBack(), 6);
	ASSERT_EQ(list.size(),5);
	list.removeFirst(3);
	ASSERT_EQ(list.size(),4);
	list.removeFirst(6);
	ASSERT_EQ(list.size(),3);
	list.removeFirst(6);
	ASSERT_EQ(list.size(),2);
	list.removeFirst(6);
	ASSERT_EQ(list.size(),1);
	ASSERT_EQ(5,list.popFront());
	ASSERT_TRUE(list.isEmpty());
	list.add(7);
	list.add(3);
	list.add(5);
	ASSERT_EQ(list.size(),3);
	list.removeFirst(5);
	list.removeFirst(3);
	list.removeFirst(7);
	ASSERT_TRUE(list.isEmpty());
}

TEST(SortedArrayList_Duplicate, removeAllTest){
	SortedArrayList list{1,1,1,3,3,4,4,7,9,9};
	list.removeAll(3);
	ASSERT_EQ(list.size(),8);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"1,1,1,4,4,7,9,9,");
	list.removeAll(1);
	ASSERT_EQ(list.size(),5);
	output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,4,7,9,9,");
	list.removeAll(9);
	ASSERT_EQ(list.size(),3);
	output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,4,7,");
	list.removeAll(7);
	output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,4,");
	list.removeAll(4);
	ASSERT_TRUE(list.isEmpty());
	list.add(7);
	list.add(7);
	list.add(7);
	ASSERT_EQ(list.size(),3);
	list.removeAll(7);
	ASSERT_TRUE(list.isEmpty());
}

TEST(SortedArrayList_Duplicate, iteratorTest){
	SortedArrayList list;
	list.add(3);
	list.add(5);
	list.add(7);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,5,7,");
}

TEST(SortedArrayList_Duplicate, IndexOperator){
	SortedArrayList list;
	list.add(3);
	list.add(5);
	ASSERT_EQ(list[1], 5);
	list.add(7);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,5,7,");
}

TEST(SortedArrayList_Duplicate, clearTest){
	SortedArrayList list{1,3,1,1,3,4,5,4,4,6};
	list.clear();
	ASSERT_TRUE(list.isEmpty());
	list.add(4);
	ASSERT_EQ(list.size(),1);
	ASSERT_EQ(4,list.popFront());
	ASSERT_TRUE(list.isEmpty());
}

TEST(SortedArrayList_Duplicate, Big5)
{
	SortedArrayList list1{1,2,3,4,5};
	SortedArrayList list2{6,7,8,9,10};
	SortedArrayList list3;
	SortedArrayList list4(list2);
	// copy constructor test
	for(int i=0; i<list2.size(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.size(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	SortedArrayList list5(std::move(list3));
	for(int i=0; i<list5.size(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.size(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}

TEST(SortedArrayList_Duplicate, removeRangeTest){
	SortedArrayList list{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	list.removeRange(5, 7);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(list.size(),9);
	ASSERT_EQ(output,"0,1,2,3,4,7,8,9,10,");
	// out_of_range test
	// first<=last이어야 함. first==last이면 아무런 삭제도 이루어지지 않음.
	list.removeRange(1, 1);
	output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(list.size(),9);
	ASSERT_EQ(output,"0,1,2,3,4,7,8,9,10,");
	ASSERT_THROW(list.removeRange(9, 1), std::out_of_range);
	ASSERT_THROW(list.removeRange(2, 10), std::out_of_range);
}
