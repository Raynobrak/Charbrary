#pragma once

#include "charbrary_and_catch2.h"

TEST_CASE("default construct circle", "[Circle]") {
	CB::Circle circle;
	
	REQUIRE(circle.pos.x == 0.f);
	REQUIRE(circle.pos.y == 0.f);
	REQUIRE(circle.radius == 0.f);
}

TEST_CASE("construct circle from position and radius", "[Circle]") {
	CB::Circle circle({ 13.f, 49.f }, 42.5f);

	REQUIRE(circle.pos.x == 13.f);
	REQUIRE(circle.pos.y == 49.f);
	REQUIRE(circle.radius == 42.5f);
}

TEST_CASE("compute circle diameter", "[Circle]") {
	CB::Circle circle({ 0.f,0.f }, 4);
	REQUIRE(circle.diameter() == 8.f);
}

TEST_CASE("compute circle circumference", "[Circle]") {
	CB::Circle circle({ 0.f,0.f }, 7);
	REQUIRE(circle.circumference() == Approx(43.98229715f));
}

TEST_CASE("compute circle area", "[Circle]") {
	CB::Circle circle({ 0.f,0.f }, 7);
	REQUIRE(circle.area() == Approx(153.9380400f));
}

TEST_CASE("compute the smallest enclosing aabb of a circle", "[Circle]") {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	CB::AABB expected(3.f, 1.f, 4.f, 4.f);
	REQUIRE(circle.enclosingAABB() == expected);
}

TEST_CASE("circle contains a point", "[Circle]") {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	CB::vec_t point(6.f, 2.f);

	REQUIRE(circle.contains(point));
}

TEST_CASE("circle doesn't contain a point", "[Circle]") {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	CB::vec_t point(6.f, -5.f);

	REQUIRE_FALSE(circle.contains(point));
}

TEST_CASE("circle intersects other circle when their center is contained within each other", "[Circle]") {
	CB::Circle first({ 5.f,3.f }, 2.f);
	CB::Circle second({ 6.f,2.f }, 1.f);

	REQUIRE(first.intersects(second));
	REQUIRE(second.intersects(first));
}

TEST_CASE("circle intersects other circle when their center are not within each other", "[Circle]") {
	CB::Circle first({ 5.f,3.f }, 3.f);
	CB::Circle second({ 10.f,3.f }, 3.f);

	REQUIRE(first.intersects(second));
	REQUIRE(second.intersects(first));
}

TEST_CASE("circles don't intersect", "[Circle]") {
	CB::Circle first({ 5.f,3.f }, 2.f);
	CB::Circle second({ 10.f,5.f }, 1.f);

	REQUIRE_FALSE(first.intersects(second));
	REQUIRE_FALSE(second.intersects(first));
}

TEST_CASE("circle intersects itself", "[Circle]") {
	CB::Circle circle({ 5.f,3.f }, 2.f);
	REQUIRE(circle.intersects(circle));
}

TEST_CASE("circle strictly contains another circle and not the opposite", "[Circle]") {
	CB::Circle container({ 5.f,3.f }, 2.f);
	CB::Circle contained({ 6.f,3.f }, 0.5f);
	REQUIRE(container.strictlyContains(contained));
	REQUIRE_FALSE(contained.strictlyContains(container));
}

TEST_CASE("2 circles intersect but none of the 2 is strictly contained within the other", "[Circle]") {
	CB::Circle first({ 5.f,3.f }, 2.f);
	CB::Circle second({ 6.f,3.f }, 2.f);
	REQUIRE_FALSE(first.strictlyContains(second));
	REQUIRE_FALSE(second.strictlyContains(first));
}


TEST_CASE("circle strictly contains itself", "[Circle]") {
	CB::Circle container({ 5.f,3.f }, 2.f);
	REQUIRE(container.strictlyContains(container));
}

TEST_CASE("circle assignment operator", "[Circle]") {
	CB::Circle c({ 1.f,1.f }, 1.f);
	CB::Circle expected({ 434.f,4622.f }, 398523.f);
	c = expected;
	REQUIRE(c == expected);
}

TEST_CASE("circle equality operator", "[Circle]") {
	CB::Circle left({ 1.f,1.f }, 1.f);
	CB::Circle right({ 1.f,1.f }, 1.f);
	REQUIRE(left == right);
}

TEST_CASE("circle inequality operator", "[Circle]") {
	CB::Circle left({ 1.2f,1.f }, 1.f);
	CB::Circle right({ 1.f,1.f }, 1.f);
	REQUIRE_FALSE(left == right);
}