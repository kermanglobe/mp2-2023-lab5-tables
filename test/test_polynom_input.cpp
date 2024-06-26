﻿#include "polynoms.h"
#include <gtest.h>
#include <sstream>
#include <string>

TEST(Polynom_Inp, can_create_polynom_from_string)
{
	ASSERT_NO_THROW(Polynom p("x"));
}

TEST(Polynom_Inp, can_read_simple_polynoms)
{
	Polynom p1("x+y+z");
	Polynom p2;
	p2.insertMonom(1, 0, 0, 1.0);
	p2.insertMonom(0, 1, 0, 1.0);
	p2.insertMonom(0, 0, 1, 1.0);
	EXPECT_EQ(p2, p1);
}

TEST(Polynom_Inp, can_ignore_spaces)
{
	Polynom p1("x +\ty+ \nz");
	Polynom p2;
	p2.insertMonom(1, 0, 0, 1.0);
	p2.insertMonom(0, 1, 0, 1.0);
	p2.insertMonom(0, 0, 1, 1.0);
	EXPECT_EQ(p2, p1);
}

TEST(Polynom_Inp, can_stack_degrees)
{
	Polynom p1("z^2yzx^3x^2xyyxzx");
	Polynom p2;
	p2.insertMonom(8, 3, 4, 1.0);
	EXPECT_EQ(p2, p1);
}

TEST(Polynom_Inp, can_recreate_polynom_from_getstring)
{
	Polynom p1;
	p1.insertMonom(2, 0, 0, 1.0);
	p1.insertMonom(1, 0, 0, 2.0);
	p1.insertMonom(1, 1, 1, -3.5);
	p1.insertMonom(1, 1, 0, 1.0);
	p1.insertMonom(0, 1, 1, 3.5);
	p1.insertMonom(0, 0, 0, 1e-6);
	EXPECT_EQ(p1, Polynom(p1.getString()));
}

TEST(Polynom_Inp, can_create_constant_from_string)
{
	Polynom p1("2+2");
	Polynom p2;
	p2.insertMonom(0, 0, 0, 4.0);
	EXPECT_EQ(p2, p1);
}

TEST(Polynom_Inp, can_use_exp_form_of_coefs)
{
	Polynom p1("3.823378e+04x");
	Polynom p2("3.823378e-04x");
	Polynom p3;
	Polynom p4;
	p3.insertMonom(1, 0, 0, 38233.78);
	p4.insertMonom(1, 0, 0, 0.0003823378);
	ASSERT_EQ(p3, p1);
	ASSERT_EQ(p4, p2);
}

TEST(Polynom_Inp, can_use_zero_in_exp)
{
	Polynom p1("3.823378e+04");
	Polynom p2("3.823378e+4");
	EXPECT_EQ(p1, p2);
}

TEST(Polynom_Inp, throws_when_polynom_starts_with_plus)
{
	ASSERT_ANY_THROW(Polynom p("+x"));
}

TEST(Polynom_Inp, throws_when_polynom_ends_with_plus_or_minus)
{
	ASSERT_ANY_THROW(Polynom p("x+"));
	ASSERT_ANY_THROW(Polynom p("x-"));
}

TEST(Polynom_Inp, throws_when_encountered_two_plus_or_minus_in_row)
{
	ASSERT_ANY_THROW(Polynom p("x++x"));
	ASSERT_ANY_THROW(Polynom p("x+-x"));
	ASSERT_ANY_THROW(Polynom p("x-+x"));
	ASSERT_ANY_THROW(Polynom p("x--x"));
}

TEST(Polynom_Inp, throws_when_encountered_an_unexpected_symbol)
{
	ASSERT_ANY_THROW(Polynom p("x+(x)"));
	ASSERT_ANY_THROW(Polynom p("x*2x"));
	ASSERT_ANY_THROW(Polynom p("x/3"));
}

TEST(Polynom_Inp, throws_when_encountered_single_dot)
{
	ASSERT_ANY_THROW(Polynom p("."));
	ASSERT_ANY_THROW(Polynom p("x+."));
	ASSERT_ANY_THROW(Polynom p("x-."));
	ASSERT_ANY_THROW(Polynom p("x+.x"));
	ASSERT_ANY_THROW(Polynom p("x-.x"));
}

TEST(Polynom_Inp, throws_when_encountered_multiple_dots)
{
	ASSERT_ANY_THROW(Polynom p("1.23.4"));
	ASSERT_ANY_THROW(Polynom p("1.."));
	ASSERT_ANY_THROW(Polynom p(".1."));
	ASSERT_ANY_THROW(Polynom p("1.2.2x+.8.y"));
}

TEST(Polynom_Inp, throws_when_exp_misplaced)
{
	ASSERT_ANY_THROW(Polynom p("e+1"));
	ASSERT_ANY_THROW(Polynom p("1.2e"));
	ASSERT_ANY_THROW(Polynom p("1.e"));
	ASSERT_ANY_THROW(Polynom p("1.2e+1e+2"));
	ASSERT_ANY_THROW(Polynom p("1.2e+1.2"));
}

TEST(Polynom_Inp, cant_use_rational_in_deg_coef)
{
	ASSERT_ANY_THROW(Polynom p("x^1.3"));
}

#if MAX_MONOM_DEGREE > 12
TEST(Polynom_Inp, can_use_big_degrees)
{
	Polynom p1("2.5x^12y^9z");
	Polynom p2;
	p2.insertMonom(12, 9, 1, 2.5);
	EXPECT_EQ(p1, p2);
}
#endif