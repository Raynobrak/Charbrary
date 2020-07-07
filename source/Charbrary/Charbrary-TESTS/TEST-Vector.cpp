#pragma once

#include "pch.h"

#include "../Physics/vector_type_definition.h"

#ifndef USE_SFML_VECTORS
#include "../Physics/Vector.cpp"
#endif USE_SFML_VECTORS

#include "../Physics/VectorMaths.h"
#include "../Physics/VectorMaths.cpp"

#define FLOAT_EPSILON std::numeric_limits<float>::epsilon()

TEST(Vector, ctor) {
	CB::vec_t v(54.f, -23.f);

	EXPECT_FLOAT_EQ(v.x, 54.f);
	EXPECT_FLOAT_EQ(v.y, -23.f);
}

TEST(Vector, ctor_default) {
	CB::vec_t v;

	EXPECT_FLOAT_EQ(v.x, 0.f);
	EXPECT_FLOAT_EQ(v.y, 0.f);
}

TEST(Vector, polar_coordinates_0degrees) {
	CB::vec_t v = CB::fromPolarCoordinates(0.f, 10.f);

	EXPECT_FLOAT_EQ(v.x, 10.f);
	EXPECT_FLOAT_EQ(v.y, 0.f);
}

TEST(Vector, polar_coordinates_90degrees) {
	CB::vec_t v = CB::fromPolarCoordinates(90.f, 2.f);

	EXPECT_NEAR(v.x, 0.f, FLOAT_EPSILON);
	EXPECT_NEAR(v.y, 2.f, FLOAT_EPSILON);
}

TEST(Vector, polar_coordinates_negative_angle) {
	CB::vec_t v = CB::fromPolarCoordinates(-120.f, 1.f);

	EXPECT_NEAR(v.x, -0.5f, FLOAT_EPSILON);
	EXPECT_NEAR(v.y, -sqrtf(3.f)/2.f, FLOAT_EPSILON);
}

TEST(Vector, magnitudeSquared) {
	CB::vec_t v(3.f, 4.f);

	EXPECT_FLOAT_EQ(CB::magnitudeSquared(v), 25.f);
}

TEST(Vector, magnitude) {
	CB::vec_t v(-4.f, 3.f);

	EXPECT_FLOAT_EQ(CB::magnitude(v), 5.f);
}

TEST(Vector, normalize) {
	CB::vec_t v(3.f, 4.f);
	CB::vec_t expected(0.6f, 0.8f);

	EXPECT_EQ(CB::normalize(v), expected);
}

TEST(Vector, normalize_div0) {
	CB::vec_t v(0.f, 0.f);

	EXPECT_EQ(CB::normalize(v), v);
}

TEST(Vector, abs) {
	CB::vec_t v(-456.f, 201.f);
	CB::vec_t expected(456.f, 201.f);

	EXPECT_EQ(CB::abs(v), expected);
}

TEST(Vector, rotate_0degrees) {
	CB::vec_t v(12.f, 31.f);
	CB::vec_t after = CB::rotate(v, 0.f);

	EXPECT_EQ(v, after);
}

TEST(Vector, rotate_45degrees) {
	CB::vec_t v(0.1f, 0.1f);
	CB::vec_t after = CB::rotate(v, 45.f);

	EXPECT_NEAR(after.x, 0.f, FLOAT_EPSILON);
	EXPECT_NEAR(after.y, sqrtf(2.f) / 10.f, FLOAT_EPSILON);
}

TEST(Vector, rotate_minus180degrees) {
	CB::vec_t v(0.3f, 0.2f);
	CB::vec_t after = CB::rotate(v, -180.f);

	EXPECT_NEAR(after.x, -v.x, FLOAT_EPSILON);
	EXPECT_NEAR(after.y, -v.y, FLOAT_EPSILON);
}

TEST(Vector, rotate_360degrees) {
	CB::vec_t v(0.4f, 0.1f);
	CB::vec_t after = CB::rotate(v, 360.f);

	EXPECT_NEAR(v.x, after.x, FLOAT_EPSILON);
	EXPECT_NEAR(v.y, after.y, FLOAT_EPSILON);
}

TEST(Vector, add_assign_operator) {
	CB::vec_t first(-1.f, 20.f);
	CB::vec_t second(3.f, -30);

	CB::vec_t expected(2.f, -10.f);

	EXPECT_EQ(first += second, expected);
}

TEST(Vector, substract_assign_operator) {
	CB::vec_t first(-1.f, 20.f);
	CB::vec_t second(3.f, -30);

	CB::vec_t expected(-4.f, 50.f);

	EXPECT_EQ(first -= second, expected);
}

TEST(Vector, multiply_assign_operator) {
	CB::vec_t vector(3.f, -5.f);
	float scalar = 1.5f;

	CB::vec_t expected(4.5f, -7.5f);

	EXPECT_EQ(vector *= scalar, expected);
}

TEST(Vector, divide_assign_operator) {
	CB::vec_t vector(3.f, -5.f);
	float scalar = 2.f;

	CB::vec_t expected(1.5f, -2.5f);

	EXPECT_EQ(vector /= scalar, expected);
}

TEST(Vector, divide_assign_operator_div0_exception) {
	CB::vec_t vector(3.f, -5.f);
	float scalar = 0.f;

	EXPECT_THROW(vector /= scalar, std::invalid_argument);
}

TEST(Vector, assign_operator) {
	CB::vec_t vector(-456.f, 201.f);

	CB::vec_t expected(13.f, -8.f);

	vector = expected;

	EXPECT_EQ(vector, expected);
}

TEST(Vector, dotProduct) {
	CB::vec_t first(1.f, -4.f);
	CB::vec_t second(3.f, 2.f);

	float expected = -5.f;

	EXPECT_FLOAT_EQ(CB::dotProduct(first, second), expected);
}

TEST(Vector, add_operator) {
	CB::vec_t first(-1.f, 20.f);
	CB::vec_t second(3.f, -30);

	CB::vec_t expected(2.f, -10.f);

	EXPECT_EQ(first + second, expected);
}

TEST(Vector, substract_operator) {
	CB::vec_t first(-1.f, 20.f);
	CB::vec_t second(3.f, -30);

	CB::vec_t expected(-4.f, 50.f);

	EXPECT_EQ(first - second, expected);
}

TEST(Vector, unary_minus_operator) 	{
	CB::vec_t v(45.f, -39.f);
	CB::vec_t expected(-45.f, 39.f);

	EXPECT_EQ(-v, expected);
}

TEST(Vector, multiply_operator) {
	CB::vec_t vector(3.f, -5.f);
	float scalar = 1.5f;

	CB::vec_t expected(4.5f, -7.5f);

	EXPECT_EQ(vector * scalar, expected);
}

TEST(Vector, divide_operator) {
	CB::vec_t vector(3.f, -5.f);
	float scalar = 2.f;

	CB::vec_t expected(1.5f, -2.5f);

	EXPECT_EQ(vector / scalar, expected);
}

TEST(Vector, divide_operator_div0_exception) {
	CB::vec_t vector(3.f, -5.f);
	float scalar = 0.f;

	EXPECT_THROW(vector / scalar, std::invalid_argument);
}

TEST(Vector, equal_operator) {
	CB::vec_t a(3.f, -4.7f);
	CB::vec_t b(3.f, -4.7f);

	EXPECT_TRUE(a == b);
}

TEST(Vector, not_equal_operator) {
	CB::vec_t a(3.f, -4.7f);
	CB::vec_t b(3.1f, -4.7f);

	EXPECT_TRUE(a != b);
}


