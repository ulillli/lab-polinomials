#include "polynoms.h"
#include "translator.h"
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
TEST(Polynom, can_compare_equal_polynoms) {
	Polynom P1(translator("+1.x^1y^1z^2+1.x^1y^3z^3").getPolynom());
	Polynom P2(P1);

	bool flag = (P1 == P2);

	EXPECT_EQ(flag,1);
}
TEST(Polynom, can_compare_not_equal_polynoms) {
	Polynom P1(translator("+1.x^1y^1z^2+1.x^1y^3z^3").getPolynom());
	Polynom P2(translator("+2.x^1y^1z^2+1.x^1y^3z^3").getPolynom());

	bool flag = (P1 == P2);

	EXPECT_EQ(flag, 0);
}
TEST(Polynom, can_assign_polynom) {
	Polynom P1(translator("+1.x^1y^1z^2+1.x^1y^3z^3").getPolynom());
	Polynom P2(translator("+1.x^2y^3z^2+3.x^1y^3z^3").getPolynom());

	P1 = P2;
	
	EXPECT_EQ(P1, P2);
}
TEST(Polynom, can_add_monom) {
	Polynom P(translator("+1.x^1y^1z^2+1.x^1y^3z^3").getPolynom());
	Monom M(2.5, { 3,4,5 });

	P += M;

	EXPECT_EQ(P, translator("+2.5x^3y^4z^5+1.x^1y^1z^2+1.x^1y^3z^3").getPolynom());
}
TEST(Polynom, can_add_null_monom) {
	Polynom P(translator("+1.x^1y^1z^2+1.x^1y^3z^3").getPolynom());
	Monom M(0, { 3,4,5 });

	P += M;
	
	EXPECT_EQ(P, translator("+1.x^1y^1z^2+1.x^1y^3z^3+0.x^0y^0z^0").getPolynom());
}
TEST(Polynom, can_add_polynom_with_all_similar_summand) {
	Polynom P1(translator("+1.x^1y^1z^2+1.x^1y^3z^3").getPolynom());
	Polynom P2(translator("+1.x^1y^1z^2+3.x^1y^3z^3").getPolynom());
	
	P1 += P2;

	EXPECT_EQ(P1, translator("+4x^1y^3z^3+2x^1y^1z^2").getPolynom());
}
TEST(Polynom, can_add_polynom_without_similar_summand) {
	Polynom P1(translator("+1.x^1y^1z^2+1.x^1y^3z^3").getPolynom());
	Polynom P2(translator("+1.x^2y^1z^2+3.x^1y^1z^3").getPolynom());

	P1 += P2;

	EXPECT_EQ(P1, translator("+1x^2y^1z^2+1x^1y^3z^3+3x^1y^1z^3+1x^1y^1z^2").getPolynom());
}
TEST(Polynom, can_add_polynom_with_some_similar_summand) {
	Polynom P1(translator("+1.x^1y^1z^2+1.x^1y^3z^3-3x^2y^1z^2+10x^1y^1z^3").getPolynom());
	Polynom P2(translator("+1.x^2y^1z^2+3.x^1y^1z^3").getPolynom());

	P1 += P2;
	
	EXPECT_EQ(P1, translator("-2x^2y^1z^2+1x^1y^3z^3+13x^1y^1z^3+1x^1y^1z^2").getPolynom());
}
TEST(Polynom, can_use_unary_minus) {

	Polynom P(translator("+1.x^1y^1z^2+1.x^1y^3z^3-3x^2y^1z^2").getPolynom());

	P=-P;
	
	EXPECT_EQ(P, translator("+3x^2y^1z^2-1x^1y^3z^3-1x^1y^1z^2").getPolynom());
}
TEST(Polynom, can_multiply_polynom_on_const) {

	Polynom P(translator("+1.x^1y^1z^2+1.x^1y^3z^3-3x^2y^1z^2").getPolynom());

	P *= 3;

	EXPECT_EQ(P, translator("+3.x^1y^1z^2+3.x^1y^3z^3-9x^2y^1z^2").getPolynom());
}
TEST(Polynom, can_multiply_polynom_on_monom) {

	Polynom P(translator("+1.x^1y^1z^2+1.x^1y^3z^3-3x^2y^1z^2").getPolynom());
	Monom M(2, { 2,1,1 });
	
	P *= M;

	EXPECT_EQ(P, translator("-6x^4y^2z^3+2x^3y^4z^4+2x^3y^2z^3").getPolynom());
}
TEST(Polynom, can_multiply_polynom_on_polynom1) { //(x+y)^3

	Polynom P1(translator("+1.x^1y^0z^0+1.x^0y^1z^0").getPolynom());
	Polynom P2(P1);
	
	P1 *= P1;
	P1 *= P2;

	EXPECT_EQ(P1, translator("+1x^3y^0z^0+3x^2y^1z^0+3x^1y^2z^0+1x^0y^3z^0").getPolynom());
}
TEST(Polynom, can_multiply_polynom_on_polynom2) { 

	Polynom P1(translator("+1.x^1y^0z^0+1.x^0y^1z^0").getPolynom());
	Polynom P2(translator("+2.x^4y^2z^3+1.x^3y^1z^0").getPolynom());

	P1 *= P2;
	
	EXPECT_EQ(P1, translator("+2x^5y^2z^3+2x^4y^3z^3+1x^4y^1z^0+1x^3y^2z^0").getPolynom());
}
TEST(Polynom, can_multiply_polynom_on_polynom3) { //с приведением подобных

	Polynom P1(translator("+1.x^1y^0z^0+1.x^0y^1z^0").getPolynom());
	Polynom P2(translator("+1.x^2y^1z^0+1.x^1y^2z^0").getPolynom());

	P1 *= P2;

	EXPECT_EQ(P1, translator("+1x^3y^1z^0+2x^2y^2z^0+1x^1y^3z^0").getPolynom());
}
