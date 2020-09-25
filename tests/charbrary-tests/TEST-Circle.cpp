#pragma once

#include "charbrary_and_catch2.h"

TEST_CASE("Circle, default_constructor") {
	CB::Circle circle;
	
	REQUIRE(circle.pos.x == 0.f);
	REQUIRE(circle.pos.y == 0.f);
	REQUIRE(circle.radius == 0.f);
}

TEST_CASE("Circle, pos_radius_constructor") {
	CB::Circle circle({ 13.f, 49.f }, 42.5f);

	REQUIRE(circle.pos.x == 13.f);
	REQUIRE(circle.pos.y == 49.f);
	REQUIRE(circle.radius == 42.5f);
}

TEST_CASE("Circle, diameter") {
	CB::Circle circle({ 0.f,0.f }, 4);
	REQUIRE(circle.diameter() == 8.f);
}

TEST_CASE("Circle, circumference") {
	CB::Circle circle({ 0.f,0.f }, 7);
	REQUIRE(circle.circumference() == Approx(43.98229715f));
}

TEST_CASE("Circle, area") {
	CB::Circle circle({ 0.f,0.f }, 7);
	REQUIRE(circle.area() == Approx(153.9380400f));
}

TEST_CASE("Circle, enclosingAABB") {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	CB::AABB expected(3.f, 1.f, 4.f, 4.f);
	REQUIRE(circle.enclosingAABB() == expected);
}

TEST_CASE("Circle, contains_true") {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	CB::vec_t point(6.f, 2.f);

	REQUIRE(circle.contains(point));
}

TEST_CASE("Circle, contains_false") {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	CB::vec_t point(6.f, -5.f);

	REQUIRE_FALSE(circle.contains(point));
}

TEST_CASE("Circle, intersects_true_center_inside") {
	CB::Circle first({ 5.f,3.f }, 2.f);
	CB::Circle second({ 6.f,2.f }, 1.f);

	REQUIRE(first.intersects(second));
	REQUIRE(second.intersects(first));
}

TEST_CASE("Circle, intersects_true_center_outside") {
	CB::Circle first({ 5.f,3.f }, 3.f);
	CB::Circle second({ 10.f,3.f }, 3.f);

	REQUIRE(first.intersects(second));
	REQUIRE(second.intersects(first));
}

TEST_CASE("Circle, intersects_false") {
	CB::Circle first({ 5.f,3.f }, 2.f);
	CB::Circle second({ 10.f,5.f }, 1.f);

	REQUIRE_FALSE(first.intersects(second));
	REQUIRE_FALSE(second.intersects(first));
}

TEST_CASE("Circle, intersects_overlapping") {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	REQUIRE(circle.intersects(circle));
}

TEST_CASE("Circle, strictlyContains_true") {
	CB::Circle container({ 5.f,3.f }, 2.f);
	CB::Circle contained({ 6.f,3.f }, 0.5f);
	REQUIRE(container.strictlyContains(contained));
	REQUIRE_FALSE(contained.strictlyContains(container));
}

TEST_CASE("Circle, strictlyContains_false") {
	CB::Circle container({ 5.f,3.f }, 2.f);
	CB::Circle contained({ 6.f,3.f }, 2.f);
	REQUIRE_FALSE(container.strictlyContains(contained));
	REQUIRE_FALSE(contained.strictlyContains(container));
}


TEST_CASE("Circle, strictlyContains_overlapping") {
	CB::Circle container({ 5.f,3.f }, 2.f);
	REQUIRE(container.strictlyContains(container));
}

TEST_CASE("Circle, assign_operator") {
	CB::Circle c({ 1.f,1.f }, 1.f);
	CB::Circle expected({ 434.f,4622.f }, 398523.f);
	c = expected;
	REQUIRE(c == expected);
}

TEST_CASE("Circle, equality_operator") {
	CB::Circle left({ 1.f,1.f }, 1.f);
	CB::Circle right({ 1.f,1.f }, 1.f);
	REQUIRE(left == right);
}

TEST_CASE("Circle, inequality_operator") {
	CB::Circle left({ 1.2f,1.f }, 1.f);
	CB::Circle right({ 1.f,1.f }, 1.f);
	REQUIRE_FALSE(left == right);
}