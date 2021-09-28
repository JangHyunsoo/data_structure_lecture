/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 자료구조및실습
 * @version 2021년도 2학기
 * @author 김상진
 * @file UnsortedArrayListTests.cpp
 * 테스트 프로그램
 */

#include <string>
#include "UnsortedArrayList.h"
#include "gtest/gtest.h"
using namespace std::string_literals;

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, listEmptyInitializationTest)
{
	UnsortedArrayList<int> list{};
	ASSERT_EQ(list.size(), 0);
	ASSERT_TRUE(list.isEmpty());
	ASSERT_FALSE(list.isFull());
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, PushAndPopBackTest)
{
	UnsortedArrayList<int> list;
	list.pushBack(3);
	list.pushBack(5);
	list.pushBack(7);
	list.pushBack(3);
	ASSERT_EQ(list.size(),4);
	std::string output = "";
	while(!list.isEmpty())
		output += std::to_string(list.popBack())+",";
	ASSERT_EQ(output,"3,7,5,3,");

	UnsortedArrayList<std::string> slist;
	slist.pushBack("apple"s);
	slist.pushBack("grape"s);
	slist.pushBack("banana"s);
	slist.pushBack("apple"s);
	ASSERT_EQ(slist.size(),4);
	output = "";
	while(!slist.isEmpty())
		output += slist.popBack()+",";
	ASSERT_EQ(output,"apple,banana,grape,apple,");
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, PushAndPopBackTest_EXTRA)
{
	UnsortedArrayList<int> list;
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
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, PushAndPopFrontTest)
{
	UnsortedArrayList<int> list;
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

	UnsortedArrayList<std::string> slist;
	ASSERT_THROW(list.popFront(), std::runtime_error);
	slist.pushFront("apple"s);
	slist.pushFront("grape");
	slist.pushFront("banana"s);
	slist.pushFront("apple"s);
	slist.pushFront("banana"s);
	ASSERT_EQ(slist.size(),5);
	output = "";
	while(!slist.isEmpty())
		output += slist.popFront()+",";
	ASSERT_EQ(output,"banana,apple,banana,grape,apple,");
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, PushPopBackFrontTest)
{
	UnsortedArrayList<int> list;
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

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, listInitializationTest)
{
	// requires pushBack, popFront
	UnsortedArrayList<int> list1{3,5,7};
	list1.pushBack(9);
	std::string output = "";
	while(!list1.isEmpty())
		output += std::to_string(list1.popFront())+",";
	ASSERT_EQ(output,"3,5,7,9,");

	UnsortedArrayList<int> list2{1,2,3,4,5,6,7,8,9,10,11,12};
	output = "";
	while(!list2.isEmpty())
		output += std::to_string(list2.popFront())+",";
	ASSERT_EQ(output,"1,2,3,4,5,6,7,8,9,10,11,12,");

	UnsortedArrayList<std::string> slist{"kiwi"s,"apple"s,"melon"s,"mango"s,"banana"s,"grape"s};
	output = "";
	while(!slist.isEmpty())
		output += slist.popFront()+",";
	ASSERT_EQ(output,"kiwi,apple,melon,mango,banana,grape,");
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, findTest){
	UnsortedArrayList<int> list{3,3,5,7,9};
	ASSERT_TRUE(list.find(3));
	ASSERT_TRUE(list.find(5));
	ASSERT_TRUE(list.find(7));
	ASSERT_TRUE(list.find(9));
	ASSERT_FALSE(list.find(2));
	ASSERT_FALSE(list.find(4));
	ASSERT_FALSE(list.find(11));

	UnsortedArrayList<std::string> slist{"apple"s,"apple"s,"mango"s,"kiwi"s,"rasberry"s};
	ASSERT_TRUE(slist.find("apple"s));
	ASSERT_TRUE(slist.find("mango"s));
	ASSERT_TRUE(slist.find("kiwi"s));
	ASSERT_TRUE(slist.find("rasberry"s));
	ASSERT_FALSE(slist.find("banana"s));
	ASSERT_FALSE(slist.find("melon"s));
	ASSERT_FALSE(slist.find("strawberry"s));
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, removeFirstTest){
	UnsortedArrayList<int> list;
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

	UnsortedArrayList<std::string> slist{"apple"s,"grape"s,"melon"s};
	slist.removeFirst("apple"s);
	ASSERT_EQ(slist.size(),2);
	slist.removeFirst("melon"s);
	ASSERT_EQ(slist.size(),1);
	ASSERT_EQ("grape"s,slist.popFront());
	ASSERT_TRUE(slist.isEmpty());
	slist.pushFront("apple"s);
	slist.pushBack("grape"s);
	slist.pushBack("grape"s);
	ASSERT_EQ(slist.size(),3);
	slist.removeFirst("grape"s);
	slist.removeFirst("apple"s);
	slist.removeFirst("grape"s);
	ASSERT_TRUE(slist.isEmpty());
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, removeAllTest){
	UnsortedArrayList<int> list{1,3,1,1,3,4,5,4,4,6};
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

	UnsortedArrayList<std::string> slist{"apple"s,"banana"s,"apple"s,"apple"s,"banana"s,
		"grape"s,"kiwi"s,"grape"s,"grape"s,"mango"s};
	slist.removeAll("banana"s);
	ASSERT_EQ(slist.size(),8);
	output = "";
	for(auto s: slist)
		output += s+",";
	ASSERT_EQ(output,"apple,apple,apple,grape,kiwi,grape,grape,mango,");
	slist.removeAll("apple"s);
	ASSERT_EQ(slist.size(),5);
	output = "";
	for(auto s: slist)
		output += s+",";
	ASSERT_EQ(output,"grape,kiwi,grape,grape,mango,");
	slist.removeFirst("kiwi"s);
	ASSERT_EQ(slist.size(),4);
	slist.removeAll("grape"s);
	ASSERT_EQ(slist.size(),1);
	ASSERT_EQ("mango"s,slist.popFront());
	ASSERT_TRUE(slist.isEmpty());
	slist.pushBack("banana"s);
	slist.pushFront("banana"s);
	slist.pushFront("banana"s);
	slist.removeAll("banana"s);
	ASSERT_TRUE(slist.isEmpty());

}


TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, iteratorTest){
	UnsortedArrayList<int> list;
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

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, IndexOperator){
	UnsortedArrayList<int> list;
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

	UnsortedArrayList<std::string> slist{"banana"s,"grape"s};
	ASSERT_EQ(slist[1], "grape"s);
	ASSERT_THROW(slist[2], std::out_of_range);
	ASSERT_THROW(slist[2]="melon"s, std::out_of_range);

	slist.pushBack("mango"s);
	slist[0] = "apple"s;	// list.set(0, 4);
	output = "";
	for(auto s: slist)
		output += s+",";
	ASSERT_EQ(output,"apple,grape,mango,");
}

TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, clearTest){
	UnsortedArrayList<int> list{1,3,1,1,3,4,5,4,4,6};
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


TEST(UnsortedArrayList_Generic_Dynamic_Duplicate_OrderPreserving, Big5)
{
	UnsortedArrayList<int> list1{1,2,3,4,5};
	UnsortedArrayList<int> list2{6,7,8,9,10};
	UnsortedArrayList<int> list3;
	UnsortedArrayList<int> list4(list2);
	// copy constructor test
	for(int i=0; i<list2.size(); i++)
		ASSERT_EQ(list2[i], list4[i]);
	list3 = list1;
	// copy assignment test
	for(int i=0; i<list1.size(); i++)
		ASSERT_EQ(list1[i], list3[i]);
	// move constructor test
	UnsortedArrayList<int> list5(std::move(list3));
	for(int i=0; i<list5.size(); i++)
		ASSERT_EQ(list5[i], list1[i]);
	// move assignment test
	list3 = std::move(list4);
	for(int i=0; i<list3.size(); i++)
		ASSERT_EQ(list3[i], list2[i]);

	UnsortedArrayList<std::string> slist1{"apple"s,"banana"s,"grape"s,"lemon"s,"kiwi"s};
	UnsortedArrayList<std::string> slist2{"mango"s,"melon"s,"peach"s,"rasberry"s,"strawberry"s};
	UnsortedArrayList<std::string> slist3;
	UnsortedArrayList<std::string> slist4(slist2);
	// copy constructor test
	for(int i=0; i<slist2.size(); i++)
		ASSERT_EQ(slist2[i], slist4[i]);
	slist3 = slist1;
	// copy assignment test
	for(int i=0; i<slist1.size(); i++)
		ASSERT_EQ(slist1[i], slist3[i]);
	// move constructor test
	UnsortedArrayList<std::string> slist5(std::move(slist3));
	for(int i=0; i<slist5.size(); i++)
		ASSERT_EQ(slist5[i], slist1[i]);
	// move assignment test
	slist3 = std::move(slist4);
	for(int i=0; i<slist3.size(); i++)
		ASSERT_EQ(slist3[i], slist2[i]);

}
