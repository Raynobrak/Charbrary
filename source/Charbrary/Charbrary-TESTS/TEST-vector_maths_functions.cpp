#pragma once

#include "pch.h"

#include "../Physics/vector_type_definition.h"
#include "../Physics/vector_maths_functions.h"

TEST(vector_maths_functions, polar_coordinates_0degrees) {
	CB::vec_t v = CB::vec_from_polar_coordinates(0.f, 10.f);

	EXPECT_FLOAT_EQ(v.x, 10.f);
	EXPECT_FLOAT_EQ(v.y, 0.f);
}

TEST(vector_maths_functions, polar_coordinates_90degrees) {
	CB::vec_t v = CB::vec_from_polar_coordinates(90.f, 2.f);

	EXPECT_NEAR(v.x, 0.f, FLOAT_EPSILON);
	EXPECT_NEAR(v.y, 2.f, FLOAT_EPSILON);
}

TEST(vector_maths_functions, polar_coordinates_negative_angle) {
	CB::vec_t v = CB::vec_from_polar_coordinates(-120.f, 1.f);

	EXPECT_NEAR(v.x, -0.5f, FLOAT_EPSILON);
	EXPECT_NEAR(v.y, -sqrtf(3.f) / 2.f, FLOAT_EPSILON);
}

TEST(vector_maths_functions, magnitude_squared) {
	CB::vec_t v(3.f, 4.f);

	EXPECT_FLOAT_EQ(CB::vec_magnitude_squared(v), 25.f);
}

TEST(vector_maths_functions, magnitude) {
	CB::vec_t v(-4.f, 3.f);

	EXPECT_FLOAT_EQ(CB::vec_magnitude(v), 5.f);
}

TEST(vector_maths_functions, normalize) {
	CB::vec_t v(3.f, 4.f);
	CB::vec_t expected(0.6f, 0.8f);

	EXPECT_EQ(CB::vec_normalize(v), expected);
}

TEST(vector_maths_functions, normalize_div0) {
	CB::vec_t v(0.f, 0.f);

	EXPECT_EQ(CB::vec_normalize(v), v);
}

TEST(vector_maths_functions, abs) {
	CB::vec_t v(-456.f, 201.f);
	CB::vec_t expected(456.f, 201.f);

	EXPECT_EQ(CB::vec_abs(v), expected);
}

TEST(vector_maths_functions, rotate_0degrees) {
	CB::Vector v(12.f, 31.f);
	CB::Vector after = CB::vec_rotate(v, 0.f);

	EXPECT_EQ(v, after);
}

TEST(vector_maths_functions, rotate_45degrees) {
	CB::vec_t v(0.1f, 0.1f);
	CB::vec_t after = CB::vec_rotate(v, 45.f);

	EXPECT_NEAR(after.x, 0.f, FLOAT_EPSILON);
	EXPECT_NEAR(after.y, sqrtf(2.f) / 10.f, FLOAT_EPSILON);
}

TEST(vector_maths_functions, rotate_minus180degrees) {
	CB::vec_t v(0.3f, 0.2f);
	CB::vec_t after = CB::vec_rotate(v, -180.f);

	EXPECT_NEAR(after.x, -v.x, FLOAT_EPSILON);
	EXPECT_NEAR(after.y, -v.y, FLOAT_EPSILON);
}

TEST(vector_maths_functions, rotate_360degrees) {
	CB::vec_t v(0.4f, 0.1f);
	CB::vec_t after = CB::vec_rotate(v, 360.f);

	EXPECT_NEAR(v.x, after.x, FLOAT_EPSILON);
	EXPECT_NEAR(v.y, after.y, FLOAT_EPSILON);
}

TEST(vector_maths_functions, dot_product) {
	CB::vec_t first(1.f, -4.f);
	CB::vec_t second(3.f, 2.f);

	float expected = -5.f;

	EXPECT_FLOAT_EQ(CB::vec_dot_product(first, second), expected);
}