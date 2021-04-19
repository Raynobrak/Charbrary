#pragma once

#include "charbrary_and_catch2.h"

TEST_CASE("default construct circle", "[Circle]") {
	ch::Circle circle;
	
	REQUIRE(circle.pos.x == 0.f);
	REQUIRE(circle.pos.y == 0.f);
	REQUIRE(circle.radius == 0.f);
}

TEST_CASE("construct circle from position and radius", "[Circle]") {
	ch::Circle circle({ 13.f, 49.f }, 42.5f);

	REQUIRE(circle.pos.x == 13.f);
	REQUIRE(circle.pos.y == 49.f);
	REQUIRE(circle.radius == 42.5f);
}

TEST_CASE("compute circle diameter", "[Circle]") {
	ch::Circle circle({ 0.f,0.f }, 4);
	REQUIRE(circle.diameter() == 8.f);
}

TEST_CASE("compute circle circumference", "[Circle]") {
	ch::Circle circle({ 0.f,0.f }, 7);
	REQUIRE(circle.circumference() == Approx(43.98229715f));
}

TEST_CASE("compute circle area", "[Circle]") {
	ch::Circle circle({ 0.f,0.f }, 7);
	REQUIRE(circle.area() == Approx(153.9380400f));
}

TEST_CASE("compute the smallest enclosing aabb of a circle", "[Circle]") {
	ch::Circle circle({ 5.f,3.f }, 2.f);
	ch::AABB expected(3.f, 1.f, 4.f, 4.f);
	REQUIRE(circle.enclosingAABB() == expected);
}

TEST_CASE("compute the distance to another circle", "[Circle]") {
	ch::Circle circle({ 0.f,0.f }, 5.f);
	ch::Circle up({ -10.f, 0.f }, 3.f);

	REQUIRE(circle.distanceTo(up) == 2.f);

	ch::Circle other(circle.pos + ch::vec_from_polar_coordinates(123, 20.f), 18.f);

	REQUIRE(circle.distanceTo(other) == -3.f);
}

TEST_CASE("circle contains a point", "[Circle]") {
	ch::Circle circle({ 5.f,3.f }, 2.f);
	ch::vec_t point(6.f, 2.f);

	REQUIRE(circle.contains(point));
}

TEST_CASE("circle doesn't contain a point", "[Circle]") {
	ch::Circle circle({ 5.f,3.f }, 2.f);
	ch::vec_t point(6.f, -5.f);

	REQUIRE_FALSE(circle.contains(point));
}

TEST_CASE("circle intersects other circle when their center is contained within each other", "[Circle]") {
	ch::Circle first({ 5.f,3.f }, 2.f);
	ch::Circle second({ 6.f,2.f }, 1.f);

	REQUIRE(first.intersects(second));
	REQUIRE(second.intersects(first));
}

TEST_CASE("circle intersects other circle when their center are not within each other", "[Circle]") {
	ch::Circle first({ 5.f,3.f }, 3.f);
	ch::Circle second({ 10.f,3.f }, 3.f);

	REQUIRE(first.intersects(second));
	REQUIRE(second.intersects(first));
}

TEST_CASE("circles don't intersect", "[Circle]") {
	ch::Circle first({ 5.f,3.f }, 2.f);
	ch::Circle second({ 10.f,5.f }, 1.f);

	REQUIRE_FALSE(first.intersects(second));
	REQUIRE_FALSE(second.intersects(first));
}

TEST_CASE("circle intersects itself", "[Circle]") {
	ch::Circle circle({ 5.f,3.f }, 2.f);
	REQUIRE(circle.intersects(circle));
}

TEST_CASE("circle strictly contains another circle and not the opposite", "[Circle]") {
	ch::Circle container({ 5.f,3.f }, 2.f);
	ch::Circle contained({ 6.f,3.f }, 0.5f);
	REQUIRE(container.strictlyContains(contained));
	REQUIRE_FALSE(contained.strictlyContains(container));
}

TEST_CASE("2 circles intersect but none of the 2 is strictly contained within the other", "[Circle]") {
	ch::Circle first({ 5.f,3.f }, 2.f);
	ch::Circle second({ 6.f,3.f }, 2.f);
	REQUIRE_FALSE(first.strictlyContains(second));
	REQUIRE_FALSE(second.strictlyContains(first));
}


TEST_CASE("circle strictly contains itself", "[Circle]") {
	ch::Circle container({ 5.f,3.f }, 2.f);
	REQUIRE(container.strictlyContains(container));
}

TEST_CASE("circle assignment operator", "[Circle]") {
	ch::Circle c({ 1.f,1.f }, 1.f);
	ch::Circle expected({ 434.f,4622.f }, 398523.f);
	c = expected;
	REQUIRE(c == expected);
}

TEST_CASE("circle equality operator", "[Circle]") {
	ch::Circle left({ 1.f,1.f }, 1.f);
	ch::Circle right({ 1.f,1.f }, 1.f);
	REQUIRE(left == right);
}

TEST_CASE("circle inequality operator", "[Circle]") {
	ch::Circle left({ 1.2f,1.f }, 1.f);
	ch::Circle right({ 1.f,1.f }, 1.f);
	REQUIRE_FALSE(left == right);
}