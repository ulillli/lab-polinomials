#include "cyclicList.h"
#include <gtest.h>

TEST(cyclicList, can_create_cyclicList_with_0_length)
{
  ASSERT_NO_THROW(cyclicList<int> m());
}
TEST(cyclicList, can_not_create_cyclicList_with_negative_length)
{
	ASSERT_ANY_THROW(cyclicList<int> m(-2));
}
TEST(cyclicList, can_create_cyclicList_with_positive_length)
{
	ASSERT_NO_THROW(cyclicList<int> m(10));
}
TEST(cyclicList, can_create_cyclicList_with_one_length)
{
	ASSERT_NO_THROW(cyclicList<int> m(1));
}
TEST(cyclicList, can_create_cyclicList_using_other_cyclicList)
{
	cyclicList<int> m(3);

	ASSERT_NO_THROW(cyclicList<int> l(m));
}
TEST(cyclicList, can_find_zero_element)
{
	cyclicList<int> m(3);

	ASSERT_NO_THROW(m[0]);
}
TEST(cyclicList, can_find_not_zero_element)
{
	cyclicList<int> m(3);

	ASSERT_NO_THROW(m[2]);
}
TEST(cyclicList, can_not_find_element_outside_range)
{
	cyclicList<int> m(3);

	ASSERT_ANY_THROW(m[3]);
}
TEST(cyclicList, can_find_zero_element_in_list_with_one_element)
{
	cyclicList<int> m(1);

	ASSERT_NO_THROW(m[0]);
}
TEST(cyclicList, can_assign_other_list)
{
	cyclicList<int> m(1),l(4);

	ASSERT_NO_THROW(m=l);
}
TEST(cyclicList, can_count_size_of_big_list)
{
	size_t size = 10;
	cyclicList<int> m(size);

	EXPECT_EQ(size, m.size());
}
TEST(cyclicList, can_count_size_of_list_with_one_element)
{
	size_t size = 1;
	cyclicList<int> m(size);

	EXPECT_EQ(size, m.size());
}
TEST(cyclicList, can_count_size_of_list_with_zero_elements)
{
	size_t size = 0;
	cyclicList<int> m(size);

	EXPECT_EQ(size, m.size());
}
TEST(cyclicList, can_insert_element)
{
	size_t size = 10;
	cyclicList<int> m(size);

	m.insert(4);

	EXPECT_EQ(4, m[0].value);
}
TEST(cyclicList, can_insert_element_and_size_will_be_correct)
{
	size_t size = 10;
	cyclicList<int> m(size);

	m.insert(4);
	EXPECT_EQ(size+1, m.size());
}
TEST(cyclicList, can_insert_some_elements)
{
	size_t size = 10;
	cyclicList<int> m(size);
	
	for (int i = 0; i < 8; i++) m.insert(i);

	EXPECT_EQ(m[0].value, 7);
}
TEST(cyclicList, can_erase_after_last_element)
{
	size_t size = 0;
	cyclicList<int> m(size);
	for (int i = 0; i < 8; i++) m.insert(i);
	
	m.erase_after(&m[7]);

	EXPECT_EQ(m[0].value, 6);
}
TEST(cyclicList, can_erase_after_any_element)
{
	size_t size = 0;
	cyclicList<int> m(size);
	for (int i = 0; i < 8; i++) m.insert(i);

	m.erase_after(&m[4]);

	EXPECT_EQ(m[5].value, 1);
}
TEST(cyclicList, can_erase_front)
{
	size_t size = 0;
	cyclicList<int> m(size);
	for (int i = 0; i < 8; i++) m.insert(i);

	m.erase_front();

	EXPECT_EQ(m[0].value, 6);
}
TEST(cyclicList, can_erase_front_some_elements)
{
	size_t size = 0;
	cyclicList<int> m(size);
	for (int i = 0; i < 8; i++) m.insert(i);

	for(int i=0;i<6; i++) m.erase_front();
	
	EXPECT_EQ(m[0].value, 1);
}
TEST(cyclicList, can_erase_back_one_element)
{
	size_t size = 0;
	cyclicList<int> m(size);
	for (int i =0; i < 8; i++) m.insert(i);
	
	m.erase_back();
	
	EXPECT_EQ(m[6].value, 1);
}
TEST(cyclicList, can_erase_back_some_elements)
{
	size_t size = 0;
	cyclicList<int> m(size);
	for (int i = 0; i < 8; i++) m.insert(i);

	for(int i=0;i<4;i++) m.erase_back();

	EXPECT_EQ(m[3].value, 4);
}
TEST(cyclicList, can_erase_back_some_elements_and_erase_front_some_element)
{
	cyclicList<int> m;
	for (int i = 0; i < 10; i++) m.insert(i);
	
	for (int i = 0; i < 5; i++)
	{
		m.erase_front();
		m.erase_back();
	}
	
	EXPECT_EQ(m.size(), 0);
}
TEST(cyclicList, can_erase_after_some_times)
{
	cyclicList<int> m;
	for (int i = 0; i < 10; i++) m.insert(i);

	for (int i = 0; i < 10; i++)
	{
		m.erase_after(&m[0]);
	}

	EXPECT_EQ(m.size(), 0);
}