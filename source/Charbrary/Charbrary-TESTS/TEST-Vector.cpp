#pragma once

#include "pch.h"

#include "../Physics/Vector.h"
#include "../Physics/Vector.cpp"

#define FLOAT_EPSILON std::numeric_limits<float>::epsilon()

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

TEST(Vector, polar_coordinates_0degrees) {
	CB::Vector v = CB::Vector::fromPolarCoordinates(0.f, 10.f);

	EXPECT_FLOAT_EQ(v.x, 10.f);
	EXPECT_FLOAT_EQ(v.y, 0.f);
}

TEST(Vector, polar_coordinates_90degrees) {
	CB::Vector v = CB::Vector::fromPolarCoordinates(90.f, 2.f);

	EXPECT_NEAR(v.x, 0.f, FLOAT_EPSILON);
	EXPECT_NEAR(v.y, 2.f, FLOAT_EPSILON);
}

TEST(Vector, polar_coordinates_negative_angle) {
	CB::Vector v = CB::Vector::fromPolarCoordinates(-120.f, 1.f);

	EXPECT_NEAR(v.x, -0.5f, FLOAT_EPSILON);
	EXPECT_NEAR(v.y, -sqrtf(3.f)/2.f, FLOAT_EPSILON);
}

TEST(Vector, magnitudeSquared) {
	CB::Vector v(3.f, 4.f);

	EXPECT_FLOAT_EQ(v.magnitudeSquared(), 25.f);
}

TEST(Vector, magnitude) {
	CB::Vector v(-4.f, 3.f);

	EXPECT_FLOAT_EQ(v.magnitude(), 5.f);
}

TEST(Vector, normalize) {
	CB::Vector v(3.f, 4.f);
	CB::Vector expected(0.6f, 0.8f);

	EXPECT_EQ(v.normalize(), expected);
}

TEST(Vector, normalize_div0) {
	CB::Vector v(0.f, 0.f);

	EXPECT_EQ(v.normalize(), v);
}

TEST(Vector, abs) {
	CB::Vector v(-456.f, 201.f);
	CB::Vector expected(456.f, 201.f);

	EXPECT_EQ(v.abs(), expected);
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

TEST(Vector, dotProduct) {
	CB::Vector first(1.f, -4.f);
	CB::Vector second(3.f, 2.f);

	float expected = -5.f;

	EXPECT_FLOAT_EQ(CB::Vector::dotProduct(first, second), expected);
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


