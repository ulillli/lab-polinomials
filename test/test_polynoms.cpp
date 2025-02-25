#include "polynoms.h"
#include <gtest.h>
TEST(Polynom, can_create_polynom_without_monoms)
{
	ASSERT_NO_THROW(Polynom P());
}
TEST(Polynom, can_create_polynom_with_some_monoms)
{
	Monom m1(3., { 2,2,2 }), m2(2.1, { 2,1,1 }), m3(1., { 1,1,1 });
	ASSERT_NO_THROW(Polynom P({ m3,m2,m1 }));
}

