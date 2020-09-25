#pragma once

#include "charbrary_and_catch2.h"

TEST_CASE("vector_maths_functions, polar_coordinates_0degrees") {
	CB::vec_t v = CB::vec_from_polar_coordinates(0.f, 10.f);

	REQUIRE(v.x == 10.f);
	REQUIRE(v.y == 0.f);
}

TEST_CASE("vector_maths_functions, polar_coordinates_90degrees") {
	CB::vec_t v = CB::vec_from_polar_coordinates(90.f, 2.f);

	REQUIRE(v.x == Approx(0.f).margin(0.01f)); // See https://github.com/catchorg/Catch2/issues/1444 for why a margin was used here.
	REQUIRE(v.y == Approx(2.f));
}

TEST_CASE("vector_maths_functions, polar_coordinates_negative_angle") {
	CB::vec_t v = CB::vec_from_polar_coordinates(-120.f, 1.f);

	REQUIRE(v.x == Approx(-0.5f));
	REQUIRE(v.y == Approx(-sqrtf(3.f) / 2.f));
}

TEST_CASE("vector_maths_functions, magnitude_squared") {
	CB::vec_t v(3.f, 4.f);

	REQUIRE(CB::vec_magnitude_squared(v) == 25.f);
}

TEST_CASE("vector_maths_functions, magnitude") {
	CB::vec_t v(-4.f, 3.f);

	REQUIRE(CB::vec_magnitude(v) == 5.f);
}

TEST_CASE("vector_maths_functions, normalize") {
	CB::vec_t v(3.f, 4.f);
	CB::vec_t expected(0.6f, 0.8f);

	REQUIRE(CB::vec_normalize(v) == expected);
}

TEST_CASE("vector_maths_functions, normalize_div0") {
	CB::vec_t v(0.f, 0.f);

	REQUIRE(CB::vec_normalize(v) == v);
}

TEST_CASE("vector_maths_functions, abs") {
	CB::vec_t v(-456.f, 201.f);
	CB::vec_t expected(456.f, 201.f);

	REQUIRE(CB::vec_abs(v) == expected);
}

TEST_CASE("vector_maths_functions, rotate_0degrees") {
	CB::Vector v(12.f, 31.f);
	CB::Vector after = CB::vec_rotate(v, 0.f);

	REQUIRE(v.x == Approx(after.x));
	REQUIRE(v.y == Approx(after.y));
}

TEST_CASE("vector_maths_functions, rotate_45degrees") {
	CB::vec_t v(0.1f, 0.1f);
	CB::vec_t after = CB::vec_rotate(v, 45.f);

	REQUIRE(after.x == Approx(0.f));
	REQUIRE(after.y == Approx(sqrtf(2.f) / 10.f));
}

TEST_CASE("vector_maths_functions, rotate_minus180degrees") {
	CB::vec_t v(0.3f, 0.2f);
	CB::vec_t after = CB::vec_rotate(v, -180.f);

	REQUIRE(after.x == Approx(-v.x));
	REQUIRE(after.y == Approx(-v.y));
}

TEST_CASE("vector_maths_functions, rotate_360degrees") {
	CB::vec_t v(0.4f, 0.1f);
	CB::vec_t after = CB::vec_rotate(v, 360.f);

	REQUIRE(v.x == Approx(after.x));
	REQUIRE(v.y == Approx(after.y));
}

TEST_CASE("vector_maths_functions, dot_product") {
	CB::vec_t first(1.f, -4.f);
	CB::vec_t second(3.f, 2.f);

	float expected = -5.f;

	REQUIRE(CB::vec_dot_product(first, second) == expected);
}