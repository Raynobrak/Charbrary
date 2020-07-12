#pragma once

#include "pch.h"

#include "../Physics/vector_type_definition.h"

TEST(Vector, ctor) {
	CB::Vector v(54.f, -23.f);

	EXPECT_FLOAT_EQ(v.x, 54.f);
	EXPECT_FLOAT_EQ(v.y, -23.f);
}

TEST(Vector, ctor_default) {
	CB::Vector v; 

	EXPECT_FLOAT_EQ(v.x, 0.f);
	EXPECT_FLOAT_EQ(v.y, 0.f);
}

TEST(Vector, add_assign_operator) {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(2.f, -10.f);

	EXPECT_EQ(first += second, expected);
}

TEST(Vector, substract_assign_operator) {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(-4.f, 50.f);

	EXPECT_EQ(first -= second, expected);
}

TEST(Vector, multiply_assign_operator) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 1.5f;

	CB::Vector expected(4.5f, -7.5f);

	EXPECT_EQ(vector *= scalar, expected);
}

TEST(Vector, divide_assign_operator) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 2.f;

	CB::Vector expected(1.5f, -2.5f);

	EXPECT_EQ(vector /= scalar, expected);
}

TEST(Vector, divide_assign_operator_div0_exception) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 0.f;

	EXPECT_THROW(vector /= scalar, std::invalid_argument);
}

TEST(Vector, assign_operator) {
	CB::Vector vector(-456.f, 201.f);

	CB::Vector expected(13.f, -8.f);

	vector = expected;

	EXPECT_EQ(vector, expected);
}

TEST(Vector, add_operator) {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(2.f, -10.f);

	EXPECT_EQ(first + second, expected);
}

TEST(Vector, substract_operator) {
	CB::Vector first(-1.f, 20.f);
	CB::Vector second(3.f, -30);

	CB::Vector expected(-4.f, 50.f);

	EXPECT_EQ(first - second, expected);
}

TEST(Vector, unary_minus_operator) 	{
	CB::Vector v(45.f, -39.f);
	CB::Vector expected(-45.f, 39.f);

	EXPECT_EQ(-v, expected);
}

TEST(Vector, multiply_operator) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 1.5f;

	CB::Vector expected(4.5f, -7.5f);

	EXPECT_EQ(vector * scalar, expected);
}

TEST(Vector, divide_operator) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 2.f;

	CB::Vector expected(1.5f, -2.5f);

	EXPECT_EQ(vector / scalar, expected);
}

TEST(Vector, divide_operator_div0_exception) {
	CB::Vector vector(3.f, -5.f);
	float scalar = 0.f;

	EXPECT_THROW(vector / scalar, std::invalid_argument);
}

TEST(Vector, equal_operator) {
	CB::Vector a(3.f, -4.7f);
	CB::Vector b(3.f, -4.7f);

	EXPECT_TRUE(a == b);
}

TEST(Vector, not_equal_operator) {
	CB::Vector a(3.f, -4.7f);
	CB::Vector b(3.1f, -4.7f);

	EXPECT_TRUE(a != b);
}


