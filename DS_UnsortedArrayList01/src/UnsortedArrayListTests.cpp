/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 장현수 (2018136114)
 * @file UnsortedArrayListTests.cpp
 * 테스트 프로그램
 */

#include <string>
#include "UnsortedArrayList.h"
#include "gtest/gtest.h"


TEST(UnsortedArrayList_Duplicate_OrderPreserving, listEmptyInitializationTest)
{
	UnsortedArrayList list{};
	ASSERT_EQ(list.size(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(UnsortedArrayList_Duplicate_OrderPreserving, PushAndPopBackTest)
{
	UnsortedArrayList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	list.pushBack(3);
	ASSERT_EQ(list.size(),4);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"3,7,5,3,");
}

TEST(UnsortedArrayList_Duplicate_OrderPreserving, PushAndPopBackTest_EXTRA)
{
	UnsortedArrayList list;
	ASSERT_THROW(list.popBack(), std::runtime_error);
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(1);
	list.pushBack(2);
	ASSERT_THROW(list.pushBack(3), std::runtime_error);
}

TEST(UnsortedArrayList_Duplicate_OrderPreserving, PushAndPopFrontTest)
{
	UnsortedArrayList list;
	ASSERT_THROW(list.popFront(), std::runtime_error);
	list.pushFront(3);
	list.pushFront(5);
	list.pushFront(7);
	list.pushFront(3);
	list.pushFront(7);
	ASSERT_EQ(list.size(),5);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"7,3,7,5,3,");
}

TEST(UnsortedArrayList_Duplicate_OrderPreserving, PushPopBackFrontTest)
{
	UnsortedArrayList list;
	list.pushFront(3);
	ASSERT_EQ(list.peekFront(), 3);
	ASSERT_EQ(list.peekBack(), 3);
	list.pushFront(5);
	list.pushFront(7);
	ASSERT_EQ(list.peekFront(), 7);
	ASSERT_EQ(list.peekBack(), 3);
	list.pushBack(1);
	list.pushBack(2); // 7 5 3 1 2
	ASSERT_EQ(list.peekFront(), 7);
	ASSERT_EQ(list.peekBack(), 2);
	ASSERT_EQ(list.size(),5);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popFront())+",";
	ASSERT_EQ(output,"7,5,3,1,2,");
}



TEST(UnsortedArrayList_Duplicate_OrderPreserving, listInitializationTest)
{
	// requires pushBack, popFront
	UnsortedArrayList list1{3,5,7};
	list1.pushBack(9);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"3,5,7,9,");

	UnsortedArrayList list2{1,2,3,4,5,6,7,8,9,10,11};
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,10,");
}

TEST(UnsortedArrayList_Duplicate_OrderPreserving, findTest){
	UnsortedArrayList list{3,3,5,7,9};
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));
}

TEST(UnsortedArrayList_Duplicate_OrderPreserving, removeFirstTest){
	UnsortedArrayList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	list.removeFirst(3);
	ASSERT_EQ(list.size(),2);
	list.removeFirst(7);
	ASSERT_EQ(list.size(),1);
	ASSERT_EQ(5,list.popFront());
	ASSERT_TRUE(list.isEmpty());
	list.pushFront(3);
	list.pushBack(5);
	ASSERT_EQ(list.size(),2);
	list.removeFirst(5);
	list.removeFirst(3);
	ASSERT_TRUE(list.isEmpty());
}

TEST(UnsortedArrayList_Duplicate_OrderPreserving, removeAllTest){
	UnsortedArrayList list{1,3,1,1,3,4,5,4,4,6};
	list.removeAll(3);
	ASSERT_EQ(list.size(),8);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"1,1,1,4,5,4,4,6,");
	list.removeAll(1);
	ASSERT_EQ(list.size(),5);
	output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,5,4,4,6,");
	list.removeFirst(5);
	ASSERT_EQ(list.size(),4);
	list.removeAll(4);
	ASSERT_EQ(list.size(),1);
	ASSERT_EQ(6,list.popFront());
	ASSERT_TRUE(list.isEmpty());
	list.pushBack(3);
	list.pushFront(3);
	list.pushFront(3);
	list.removeAll(3);
	ASSERT_TRUE(list.isEmpty());
}


TEST(UnsortedArrayList_Duplicate_OrderPreserving, iteratorTest){
	UnsortedArrayList list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	std::string output = "";
	for(auto b = list.cbegin(); b!=list.cend(); ++b){
		//*b = 4;
		output += std::to_string(*b)+",";
	}
	ASSERT_EQ(output,"3,5,7,");

	output = "";
	auto it{list.begin()};
	*it = 0;
	for(auto n: list)
		output += std::to_string(n)+",";
	ASSERT_EQ(output,"0,5,7,");
}

TEST(UnsortedArrayList_Duplicate_OrderPreserving, IndexOperator){
	UnsortedArrayList list;
	list.pushBack(3);
	list.pushBack(5);
	ASSERT_EQ(list[1], 5);
	ASSERT_THROW(list[2], std::out_of_range);
	ASSERT_THROW(list[2]=0, std::out_of_range);

	list.pushBack(7);
	list[0] = 4;	// list.set(0, 4);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,5,7,");
}

TEST(UnsortedArrayList_Duplicate_OrderPreserving, clearTest){
	UnsortedArrayList list{1,3,1,1,3,4,5,4,4,6};
	list.clear();
	ASSERT_TRUE(list.isEmpty());
	list.pushBack(4);
	ASSERT_EQ(list.size(),1);
	ASSERT_EQ(4,list.popFront());
	ASSERT_TRUE(list.isEmpty());
	list.clear();
	ASSERT_TRUE(list.isEmpty());
	ASSERT_EQ(list.size(),0);
}


TEST(UnsortedArrayList_Duplicate_OrderPreserving, Big5)
{
	UnsortedArrayList list1{1,2,3,4,5};
	UnsortedArrayList list2{6,7,8,9,10};
	UnsortedArrayList list3;
	UnsortedArrayList list4(list2);
	// copy constructor test
	for(int i=0; i<list2.size(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.size(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	UnsortedArrayList list5(std::move(list3));
	for(int i=0; i<list5.size(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.size(); i++)
		ASSERT_EQ(list3[i], list2[i]);
}

TEST(UnsortedArrayList_Duplicate_OrderPreserving, InsertTest){
	UnsortedArrayList list;
	list.pushBack(1);
	list.pushBack(2);
	list.pushBack(3);
	list.pushBack(4);
	list.pushBack(5);
	list.insert(2, 0);
	list.insert(3, 0);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"1,2,0,0,3,4,5,");
	ASSERT_THROW(list.insert(9, 1), std::out_of_range); // 현재 numItem이 7이기 때문에 out of range가 발생함.
	list.pushBack(6);
	list.pushBack(7);
	list.pushBack(8);
	ASSERT_THROW(list.insert(9, 1), std::runtime_error); // 현재 full state 상태이기 때문에 runtime error가 발생함.

}
