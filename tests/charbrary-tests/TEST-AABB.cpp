#pragma once

#include "charbrary_and_catch2.h"

#include <array>

TEST_CASE("AABB, ctor_vectors") {
	CB::AABB aabb(CB::vec_t(3.f, 5.f), CB::vec_t(9.f, -8.f));

	REQUIRE(aabb.pos.x == 3.f);
	REQUIRE(aabb.pos.y == 5.f);
	REQUIRE(aabb.size.x == 9.f);
	REQUIRE(aabb.size.y == -8.f);
}

TEST_CASE("AABB, ctor_floats") {
	CB::AABB aabb(3.f, 5.f, 9.f, -8.f);

	REQUIRE(aabb.pos.x == 3.f);
	REQUIRE(aabb.pos.y == 5.f);
	REQUIRE(aabb.size.x == 9.f);
	REQUIRE(aabb.size.y == -8.f);
}

TEST_CASE("AABB, ctor_default") {
	CB::AABB aabb;

	REQUIRE(aabb.pos.x == 0.f);
	REQUIRE(aabb.pos.y == 0.f);
	REQUIRE(aabb.size.x == 0.f);
	REQUIRE(aabb.size.y == 0.f);
}

TEST_CASE("AABB, move") {
	CB::AABB aabb(1.f, 8.f, 5.f, 5.f);

	aabb.move({ -7.f,2.f });

	CB::AABB expected(-6.f, 10.f, 5.f, 5.f);

	REQUIRE(aabb == expected);
}

TEST_CASE("AABB, center") {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t expected(8.f, 15.f);

	REQUIRE(aabb.center() == expected);
}

TEST_CASE("AABB, corner_tl") {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t expected(3.f, 5.f);

	REQUIRE(aabb.corner(CB::Corner::TopLeft) == expected);
}

TEST_CASE("AABB, corner_tr") {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t expected(13.f, 5.f);

	REQUIRE(aabb.corner(CB::Corner::TopRight) == expected);
}

TEST_CASE("AABB, corner_bl") {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t expected(3.f, 25.f);

	REQUIRE(aabb.corner(CB::Corner::BottomLeft) == expected);
}

TEST_CASE("AABB, corner_br") {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t expected(13.f, 25.f);

	REQUIRE(aabb.corner(CB::Corner::BottomRight) == expected);
}

TEST_CASE("AABB, corner_invalid") {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);

	REQUIRE_THROWS_AS(aabb.corner(static_cast<CB::Corner>(434923)), std::invalid_argument);
}
 
TEST_CASE("AABB, corners") {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);

	auto corners = aabb.corners();

	REQUIRE(corners[0] == aabb.corner(CB::Corner::TopLeft));
	REQUIRE(corners[1] == aabb.corner(CB::Corner::TopRight));
	REQUIRE(corners[2] == aabb.corner(CB::Corner::BottomLeft));
	REQUIRE(corners[3] == aabb.corner(CB::Corner::BottomRight));
}

TEST_CASE("AABB, detectCollision_no_collision") {
	CB::AABB current(0.f, 0.f, 10.f, 10.f);
	CB::AABB other(50.f, 50.f, 30.f, 30.f);

	REQUIRE(current.detectCollision(other).normal == CB::NULL_VEC);
}

TEST_CASE("AABB, detectCollision_left") {
	CB::AABB current(0.f, 0.f, 10.f, 10.f);
	CB::AABB other(-1.f, 1.f, 3.f, 3.f);

	REQUIRE(current.detectCollision(other).normal == CB::LEFT_VEC);
}

TEST_CASE("AABB, detectCollision_right") {
	CB::AABB current(0.f, 0.f, 10.f, 10.f);
	CB::AABB other(8.f, 5.f, 40.f, 40.f);

	REQUIRE(current.detectCollision(other).normal == CB::RIGHT_VEC);
}

TEST_CASE("AABB, detectCollision_up") {
	CB::AABB current(10.f, 10.f, 4.f, 4.f);
	CB::AABB other(9.f, 9.f, 4.f, 2.f);

	REQUIRE(current.detectCollision(other).normal == CB::UP_VEC);
}

TEST_CASE("AABB, detectCollision_down") {
	CB::AABB current(0.f, 0.f, 10.f, 10.f);
	CB::AABB other(5.f, 9.f, 10.f, 10.f);

	REQUIRE(current.detectCollision(other).normal == CB::DOWN_VEC);
}

TEST_CASE("AABB, scaleRelativeToCenter") {
	CB::AABB aabb(3.f, 5.f, 10.f, 20.f);
	CB::vec_t centerPosBefore = aabb.center();
	CB::vec_t expectedSize(6.f, 12.f);

	aabb.scaleRelativeToCenter(0.6f);

	REQUIRE(aabb.center() == centerPosBefore);
	REQUIRE(aabb.size == expectedSize);
}

TEST_CASE("AABB, perimeter") {
	CB::AABB aabb(0.f, 0.f, 1.f, 3.f);
	float expected = 8.f;

	REQUIRE(aabb.perimeter() == expected);
}

TEST_CASE("AABB, area") {
	CB::AABB aabb(0.f, 0.f, 2.f, 3.f);
	float expected = 6.f;

	REQUIRE(aabb.area() == expected);
}

TEST_CASE("AABB, diagonalLength") {
	CB::AABB aabb(0.f, 0.f, 3.f, 4.f);
	float expected = 5.f;

	REQUIRE(aabb.diagonalLength() == expected);
}

TEST_CASE("AABB, contains_true") {
	CB::AABB aabb(6.f, 7.f, 10.f, 20.f);
	CB::vec_t point(6.f, 26.f);

	REQUIRE(aabb.contains(point));
}

TEST_CASE("AABB, contains_false") {
	CB::AABB aabb(6.f, 7.f, 10.f, 20.f);
	CB::vec_t point(5.f, 14.f);

	REQUIRE_FALSE(aabb.contains(point));}

TEST_CASE("AABB, intersects_false") {
	CB::AABB first(6.f, 7.f, 10.f, 20.f);
	CB::AABB second(18.f, 10.f, 30.f, 40.f);

	REQUIRE_FALSE(first.intersects(second));
	REQUIRE_FALSE(second.intersects(first));
}

TEST_CASE("AABB, intersects_true_inside") {
	CB::AABB first(6.f, 4.f, 10.f, 5.f);
	CB::AABB second(7.f, 5.f, 5.f, 2.f);

	REQUIRE(first.intersects(second));
	REQUIRE(second.intersects(first));
}

TEST_CASE("AABB, intersects_true_itself") {
	CB::AABB aabb(6.f, 4.f, 10.f, 5.f);

	REQUIRE(aabb.intersects(aabb));
}

TEST_CASE("AABB, intersects_true_cross") {
	CB::AABB first(6.f, 4.f, 10.f, 30.f);
	CB::AABB second(1.f, 10.f, 30.f, 10.f);

	REQUIRE(first.intersects(second));
	REQUIRE(second.intersects(first));
}

TEST_CASE("AABB, strictlyContains_false") {
	CB::AABB first(6.f, 4.f, 10.f, 30.f);
	CB::AABB second(5.f, 6.f, 4.f, 3.f);

	REQUIRE_FALSE(first.strictlyContains(second));
}

TEST_CASE("AABB, strictlyContains_true") {
	CB::AABB container(2.f, 3.f, 50.f, 20.f);
	CB::AABB contained(10.f, 10.f, 5.f, 5.f);

	REQUIRE(container.strictlyContains(contained));
	REQUIRE_FALSE(contained.strictlyContains(container));
}

TEST_CASE("AABB, strictlyContains_true_itself") {
	CB::AABB aabb(6.f, 4.f, 10.f, 30.f);
	
	REQUIRE(aabb.strictlyContains(aabb));
}

TEST_CASE("AABB, assign_operator") {
	CB::AABB aabb(6.f, 4.f, 10.f, 30.f);
	CB::AABB expected(19.f, 25.f, 45.f, 898.f);
	aabb = expected;

	REQUIRE(aabb == expected);
}

TEST_CASE("AABB, equality_operator") {
	CB::AABB first(1.f, 2.f, 3.f, 4.f);
	CB::AABB second(1.f, 2.f, 3.f, 4.f);

	REQUIRE(first == second);
}

TEST_CASE("AABB, inequality_operator") {
	CB::AABB first(1.f, 2.f, 3.f, 4.f);
	CB::AABB second(4.f, 3.f, 2.f, 1.f);

	REQUIRE_FALSE(first == second);
}


