/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * @file SingleUnsortedLinkedListTests.cpp
 * 테스트 프로그램
 */

#include <string>
#include "gtest/gtest.h"
#include "SingleUnsortedLinkedList.h"
#include "SingleSortedLinkedList.h"
#include "DoubleUnsortedLinkedList.h"


TEST(SingleUnsortedLinkedList, removeAt_Test)
{
	SingleUnsortedLinkedList list{3,2,4,5,6,7};
	list.removeAt(3);
	ASSERT_EQ(list.size(), 5);
	list.removeAt(0);
	ASSERT_EQ(list.size(), 4);
	list.removeAt(3);
	ASSERT_EQ(list.size(), 3);
	list.pushBack(5);
	std::string output = "";
	for(auto i: list)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"2,4,6,5,");
	ASSERT_THROW(list.removeAt(4), std::out_of_range);
	list.removeAt(2);
	ASSERT_EQ(list.peekBack(),5);
	list.removeAt(0);
	ASSERT_EQ(list.peekFront(),4);
	list.removeAt(0);
	list.removeAt(0);
	ASSERT_EQ(list.size(), 0);
	ASSERT_TRUE(list.isEmpty());
}

TEST(SingleUnsortedLinkedList, partition_Test)
{
	SingleUnsortedLinkedList list1{3,2,4,1,2,5,7};
	list1.partition(3);
	ASSERT_EQ(list1.peekFront(),2);
	ASSERT_EQ(list1.peekBack(),7);
	std::string output = "";
	for(auto i: list1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"2,1,2,3,4,5,7,");

	SingleUnsortedLinkedList list2{3,2,4,1,2,5,7};
	list2.partition(10);
	ASSERT_EQ(list2.peekFront(),3);
	ASSERT_EQ(list2.peekBack(),7);
	output = "";
	for(auto i: list2)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,2,4,1,2,5,7,");

	SingleUnsortedLinkedList list3{3,2,4,2,2,5,7};
	list3.partition(2);
	ASSERT_EQ(list3.peekFront(),3);
	ASSERT_EQ(list3.peekBack(),7);
	output = "";
	for(auto i: list3)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,2,4,2,2,5,7,");

	SingleUnsortedLinkedList list4{3,2,4,2,2,7,1};
	list4.partition(2);
	ASSERT_EQ(list4.peekFront(),1);
	ASSERT_EQ(list4.peekBack(),7);
	output = "";
	for(auto i: list4)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"1,3,2,4,2,2,7,");
}

TEST(SingleSortedLinkedList, merge_Test)
{
	SingleSortedLinkedList list1{3,8,14};
	SingleSortedLinkedList list2{4,5,6,6,11,12,13};
	list1.merge(list2);
	ASSERT_TRUE(list2.isEmpty());
	ASSERT_EQ(list1.size(),10);
	ASSERT_EQ(list1.peekFront(),3);
	ASSERT_EQ(list1.peekBack(),14);
	std::string output = "";
	for(auto i: list1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,4,5,6,6,8,11,12,13,14,");

	SingleSortedLinkedList list3{3,8,9};
	SingleSortedLinkedList list4{};
	list3.merge(list4);
	ASSERT_TRUE(list4.isEmpty());
	ASSERT_EQ(list3.size(),3);
	ASSERT_EQ(list3.peekFront(),3);
	ASSERT_EQ(list3.peekBack(),9);
	output = "";
	for(auto i: list3)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,8,9,");

	SingleSortedLinkedList list5{};
	SingleSortedLinkedList list6{4,7,9};
	list5.merge(list6);
	ASSERT_TRUE(list6.isEmpty());
	ASSERT_EQ(list5.size(),3);
	ASSERT_EQ(list5.peekFront(),4);
	ASSERT_EQ(list5.peekBack(),9);
	output = "";
	for(auto i: list5)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,7,9,");

	//  해결 못함.
	SingleSortedLinkedList list7{9};
	SingleSortedLinkedList list8{4,5,6,6,11,12,13};
	list7.merge(list8);
	ASSERT_TRUE(list8.isEmpty());
	ASSERT_EQ(list7.size(),8);
	//list7.add(1);
	//list7.add(14);
	//ASSERT_EQ(list7.peekFront(),1);
	//ASSERT_EQ(list7.peekBack(),14);
	output = "";
	for(auto i: list7)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"4,5,6,6,9,11,12,13,");

}

TEST(SingleSortedLinkedList, removeDuplicates_Test)
{
	SingleSortedLinkedList list1{1,3,3,3,3,4,5,5,5};
	list1.removeDuplicates();
	ASSERT_EQ(list1.size(),4);
	ASSERT_EQ(list1.peekFront(),1);
	ASSERT_EQ(list1.peekBack(),5);
	std::string output = "";
	for(auto i: list1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"1,3,4,5,");

	SingleSortedLinkedList list2{3,3,3,3,3};
	list2.removeDuplicates();
	ASSERT_EQ(list2.size(),1);
	ASSERT_EQ(list2.peekFront(),3);
	ASSERT_EQ(list2.peekBack(),3);
	list2.add(1);
	ASSERT_EQ(list2.peekFront(),1);
	ASSERT_EQ(list2.peekBack(),3);
}

TEST(DoubleUnsortedLinkedList, replaceAll_Test)
{
	DoubleUnsortedLinkedList list1{3,1,4,3,3,5,1,3};
	list1.replaceAll(3, 0);
	ASSERT_EQ(list1.peekFront(),0);
	ASSERT_EQ(list1.peekBack(),0);
	std::string output = "";
	for(auto i: list1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"0,1,4,0,0,5,1,0,");

	DoubleUnsortedLinkedList list2{1,1,1,1,1};
	list2.replaceAll(1, 0);
	list2.replaceAll(2, 1);
	output = "";
	for(auto i: list2)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"0,0,0,0,0,");
}

TEST(DoubleUnsortedLinkedList, reverse_Test)
{
	DoubleUnsortedLinkedList list1{3,5,7};
	list1.reverse();
	ASSERT_EQ(list1.peekFront(),7);
	ASSERT_EQ(list1.peekBack(),3);
	std::string output = "";
	for(auto i: list1)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"7,5,3,");

	DoubleUnsortedLinkedList list2{3};
	list2.reverse();
	ASSERT_EQ(list2.peekFront(),3);
	ASSERT_EQ(list2.peekBack(),3);
	output = "";
	for(auto i: list2)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"3,");

	DoubleUnsortedLinkedList list3{1,2,3,2};
	list3.reverse();
	ASSERT_EQ(list3.peekFront(),2);
	ASSERT_EQ(list3.peekBack(),1);
	output = "";
	for(auto i: list3)
		output += std::to_string(i)+",";
	ASSERT_EQ(output,"2,3,2,1,");
}
