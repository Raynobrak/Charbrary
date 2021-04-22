#pragma once

#include "charbrary_and_catch2.h"

TEST_CASE("Compute smallest enclosing circle", "[Collision functions]") {
	ch::AABB aabb(20.f, 10.f, 16.f, 12.f);
	ch::Circle circle({ 28.f, 16.f }, 10.f);
	REQUIRE(ch::collision::enclosingCircle(aabb) == circle);
}

TEST_CASE("Compute inscribed circle touching left and right", "[Collision functions]") {
	ch::AABB aabb({ 18.f,4.f }, { 20.f, 24.f });
	ch::Circle circle({ 28.f,16.f }, 10.f);
	REQUIRE(ch::collision::inscribedCircle(aabb) == circle);
}

TEST_CASE("Compute inscribed circle touching up and down", "[Collision functions]") {
	ch::AABB aabb({ 16.f,6.f }, { 24.f, 20.f });
	ch::Circle circle({ 28.f,16.f }, 10.f);
	REQUIRE(ch::collision::inscribedCircle(aabb) == circle);
}

TEST_CASE("compute the smallest enclosing aabb of a circle", "[Collision functions]") {
	ch::Circle circle({ 28.f,16.f }, 10.f);
	ch::AABB expected(18.f, 6.f, 20.f, 20.f);
	REQUIRE(ch::collision::enclosingAABB(circle) == expected);
}

TEST_CASE("compute inscribed aabb of circle", "[Collision functions]") {
	ch::Circle circle({ 54.f, 30.f }, 5.656854249f);
	ch::AABB aabb(50.f, 26.f, 8.f, 8.f);

	auto inscribed = ch::collision::inscribedAABB(circle);
	REQUIRE(inscribed.pos.x == Approx(aabb.pos.x));
	REQUIRE(inscribed.pos.y == Approx(aabb.pos.y));
	REQUIRE(inscribed.size.x == Approx(aabb.size.x));
	REQUIRE(inscribed.size.y == Approx(aabb.size.y));
}

TEST_CASE("aabb contains a point", "[Collision functions]") {
	ch::AABB aabb(6.f, 7.f, 10.f, 20.f);
	ch::vec_t point(6.f, 26.f);

	REQUIRE(ch::collision::aabb_contains(aabb, point));
}

TEST_CASE("aabb doesn't contain a point", "[Collision functions]") {
	ch::AABB aabb(6.f, 7.f, 10.f, 20.f);
	ch::vec_t point(5.f, 14.f);

	REQUIRE_FALSE(ch::collision::aabb_contains(aabb, point));
}

TEST_CASE("aabb does not contain another aabb", "[Collision functions]") {
	ch::AABB first(6.f, 4.f, 10.f, 30.f);
	ch::AABB second(5.f, 6.f, 4.f, 3.f);

	REQUIRE_FALSE(ch::collision::aabb_contains(first, second));
}

TEST_CASE("aabb contains another aabb but the opposite is not true", "[Collision functions]") {
	ch::AABB container(2.f, 3.f, 50.f, 20.f);
	ch::AABB contained(10.f, 10.f, 5.f, 5.f);

	REQUIRE(ch::collision::aabb_contains(container, contained));
	REQUIRE_FALSE(ch::collision::aabb_contains(contained, container));
}

TEST_CASE("aabb contains itself", "[Collision functions]") {
	ch::AABB aabb(6.f, 4.f, 10.f, 30.f);

	REQUIRE(ch::collision::aabb_contains(aabb, aabb));
}

TEST_CASE("aabb doesn't contain a circle", "[Collision functions]") {
	ch::AABB container(16.f, 8.f, 24.f, 20.f);
	ch::Circle circle({ 28.f, 16.f }, 10.f);

	REQUIRE_FALSE(ch::collision::aabb_contains(container, circle));
}

TEST_CASE("aabb contains a circle", "[Collision functions]") {
	ch::AABB container(16.f, 6.f, 24.f, 25.f);
	ch::Circle circle({ 28.f, 16.f }, 10.f);

	REQUIRE(ch::collision::aabb_contains(container, circle));
}

TEST_CASE("circle contains a point", "[Collision functions]") {
	ch::Circle circle({ 5.f,3.f }, 2.f);
	ch::vec_t point(6.f, 2.f);

	REQUIRE(ch::collision::circle_contains(circle, point));
}

TEST_CASE("circle doesn't contain a point", "[Collision functions]") {
	ch::Circle circle({ 5.f,3.f }, 2.f);
	ch::vec_t point(6.f, -5.f);

	REQUIRE_FALSE(ch::collision::circle_contains(circle, point));
}

TEST_CASE("circle strictly contains another circle and not the opposite", "[Collision functions]") {
	ch::Circle container({ 5.f,3.f }, 2.f);
	ch::Circle contained({ 6.f,3.f }, 0.5f);
	REQUIRE(ch::collision::circle_contains(container, contained));
	REQUIRE_FALSE(ch::collision::circle_contains(contained, container));
}

TEST_CASE("circle strictly contains itself", "[Collision functions]") {
	ch::Circle container({ 5.f,3.f }, 2.f);
	REQUIRE(ch::collision::circle_contains(container, container));
}

TEST_CASE("2 circles intersect but none of the 2 is strictly contained within the other", "[Collision functions]") {
	ch::Circle first({ 5.f,3.f }, 2.f);
	ch::Circle second({ 6.f,3.f }, 2.f);

	REQUIRE(ch::collision::circle_intersects(first, second));
	REQUIRE_FALSE(ch::collision::circle_contains(first, second));
	REQUIRE_FALSE(ch::collision::circle_contains(second, first));
}

TEST_CASE("circle contains an AABB and not the opposite", "[Collision functions]") {
	ch::Circle circle({ 5.f,3.f }, 3.f);
	ch::AABB aabb(3.f, 1.f, 4.f, 4.f);
	REQUIRE(ch::collision::circle_contains(circle, aabb));
	REQUIRE_FALSE(ch::collision::aabb_contains(aabb, circle));
}

TEST_CASE("circle doesn't contain an AABB but they both intersect", "[Collision functions]") {
	ch::Circle circle({ 6.f,3.f }, 2.f);
	ch::AABB aabb(3.f, 1.f, 4.f, 3.f);
	REQUIRE_FALSE(ch::collision::circle_contains(circle, aabb));
	REQUIRE_FALSE(ch::collision::aabb_contains(aabb, circle));
	REQUIRE(ch::collision::circle_intersects(circle, aabb));
}

TEST_CASE("aabbs intersect", "[Collision functions]") {
	ch::AABB first(6.f, 7.f, 10.f, 20.f);
	ch::AABB second(18.f, 10.f, 30.f, 40.f);

	REQUIRE_FALSE(ch::collision::aabb_intersects(first, second));
	REQUIRE_FALSE(ch::collision::aabb_intersects(second, first));
}

TEST_CASE("aabbs don't intersect", "[Collision functions]") {
	ch::AABB first(6.f, 4.f, 10.f, 5.f);
	ch::AABB second(7.f, 5.f, 5.f, 2.f);

	REQUIRE(ch::collision::aabb_intersects(first, second));
	REQUIRE(ch::collision::aabb_intersects(second, first));
}

TEST_CASE("aabb intersects itself", "[Collision functions]") {
	ch::AABB aabb(6.f, 4.f, 10.f, 5.f);

	REQUIRE(ch::collision::aabb_intersects(aabb, aabb));
}

TEST_CASE("crossing aabbs intersect", "[Collision functions]") {
	ch::AABB first(6.f, 4.f, 10.f, 30.f);
	ch::AABB second(1.f, 10.f, 30.f, 10.f);

	REQUIRE(ch::collision::aabb_intersects(first, second));
	REQUIRE(ch::collision::aabb_intersects(second, first));
}

TEST_CASE("aabb and circle intersect (circle center in top-left quadrant)", "[Collision functions]") {
	ch::AABB aabb(4.f, 3.f, 5.f, 2.f);
	ch::Circle circle({ 2.f,4.f }, 3.f);

	REQUIRE(ch::collision::circle_intersects(circle, aabb));
	REQUIRE(ch::collision::aabb_intersects(aabb, circle));
}

TEST_CASE("aabb and circle intersect (circle center inside the x-range of the AABB)", "[Collision functions]") {
	ch::AABB aabb(4.f, 3.f, 5.f, 2.f);
	ch::Circle circle({ 5.f,5.f }, 3.f);

	REQUIRE(ch::collision::circle_intersects(circle, aabb));
	REQUIRE(ch::collision::aabb_intersects(aabb, circle));
}

TEST_CASE("circle intersects other circle when their center is contained within each other", "[Collision functions]") {
	ch::Circle first({ 5.f,3.f }, 2.f);
	ch::Circle second({ 6.f,2.f }, 1.f);

	REQUIRE(ch::collision::circle_intersects(first, second));
	REQUIRE(ch::collision::circle_intersects(second, first));
}

TEST_CASE("circle intersects other circle when their center are not within each other", "[Collision functions]") {
	ch::Circle first({ 5.f,3.f }, 3.f);
	ch::Circle second({ 10.f,3.f }, 3.f);

	REQUIRE(ch::collision::circle_intersects(first, second));
	REQUIRE(ch::collision::circle_intersects(second, first));
}

TEST_CASE("circles don't intersect", "[Collision functions]") {
	ch::Circle first({ 5.f,3.f }, 2.f);
	ch::Circle second({ 10.f,5.f }, 1.f);

	REQUIRE_FALSE(ch::collision::circle_intersects(first, second));
	REQUIRE_FALSE(ch::collision::circle_intersects(second, first));
}

TEST_CASE("circle intersects itself", "[Collision functions]") {
	ch::Circle circle({ 5.f,3.f }, 2.f);
	REQUIRE(ch::collision::circle_intersects(circle, circle));
}

TEST_CASE("compute the distance to another circle", "[Collision functions]") {
	ch::Circle circle({ 0.f,0.f }, 5.f);
	ch::Circle up({ -10.f, 0.f }, 3.f);

	REQUIRE(ch::collision::circles_distance(circle, up) == 2.f);
}

TEST_CASE("compute the distance to another circle when they overlap (negative distance)", "[Collision functions]") {
	ch::Circle circle({ 0.f,0.f }, 5.f);
	ch::Circle other(circle.pos + ch::vec_from_polar_coordinates(123, 20.f), 18.f);

	REQUIRE(ch::collision::circles_distance(circle, other) == -3.f);
}

TEST_CASE("getting collision information when there is no collision between 2 aabbs", "[AABB]") {
	ch::AABB current(0.f, 0.f, 10.f, 10.f);
	ch::AABB other(50.f, 50.f, 30.f, 30.f);

	REQUIRE(ch::collision::aabb_collision_info(current, other).normal == ch::NULL_VEC);
}

TEST_CASE("aabb collides with the left side of the first aabb", "[Collision functions]") {
	ch::AABB current(0.f, 0.f, 10.f, 10.f);
	ch::AABB other(-1.f, 1.f, 3.f, 3.f);

	REQUIRE(ch::collision::aabb_collision_info(current, other).normal == ch::LEFT_VEC);
}

TEST_CASE("aabb collides with the right side of the first aabb", "[Collision functions]") {
	ch::AABB current(0.f, 0.f, 10.f, 10.f);
	ch::AABB other(8.f, 5.f, 40.f, 40.f);

	REQUIRE(ch::collision::aabb_collision_info(current, other).normal == ch::RIGHT_VEC);
}

TEST_CASE("aabb collides with the top side of the first aabb", "[Collision functions]") {
	ch::AABB current(10.f, 10.f, 4.f, 4.f);
	ch::AABB other(9.f, 9.f, 4.f, 2.f);

	REQUIRE(ch::collision::aabb_collision_info(current, other).normal == ch::UP_VEC);
}

TEST_CASE("aabb collides with the bottom side of the first aabb", "[Collision functions]") {
	ch::AABB current(0.f, 0.f, 10.f, 10.f);
	ch::AABB other(5.f, 9.f, 10.f, 10.f);

	REQUIRE(ch::collision::aabb_collision_info(current, other).normal == ch::DOWN_VEC);
}

TEST_CASE("compute the depth of the collision along the collision normal", "[Collision functions]") {
	ch::AABBCollision collision{ ch::LEFT_VEC, {-140.f,20.f} };

	REQUIRE(collision.absolutePenetrationDepthAlongNormal() == 140.f);

	collision.normal = ch::RIGHT_VEC;
	REQUIRE(collision.absolutePenetrationDepthAlongNormal() == 140.f);

	collision.normal = ch::UP_VEC;
	REQUIRE(collision.absolutePenetrationDepthAlongNormal() == 20.f);

	collision.normal = ch::DOWN_VEC;
	REQUIRE(collision.absolutePenetrationDepthAlongNormal() == 20.f);
}

TEST_CASE("circle collide horizontally (right)", "[Collision functions]") {
	ch::Circle first({ 5.f,5.f }, 3.f);
	ch::Circle other({ 10.f,5.f }, 4.f);

	auto expectedCollision = ch::CirclesCollision{ ch::RIGHT_VEC, 2.f };

	auto collision = ch::collision::circles_collision_info(first, other);
	REQUIRE(collision.normal == expectedCollision.normal);
	REQUIRE(collision.absoluteDepth == expectedCollision.absoluteDepth);
}

TEST_CASE("circle collide horizontally (left)", "[Collision functions]") {
	ch::Circle first({ 10.f,5.f }, 4.f);
	ch::Circle other({ 5.f,5.f }, 3.f);

	auto expectedCollision = ch::CirclesCollision{ ch::LEFT_VEC, 2.f };

	auto collision = ch::collision::circles_collision_info(first, other);
	REQUIRE(collision.normal == expectedCollision.normal);
	REQUIRE(collision.absoluteDepth == expectedCollision.absoluteDepth);
}

TEST_CASE("circles collide vertically (top)", "[Collision functions]") {
	ch::Circle first({ 20.f,10.f }, 4.f);
	ch::Circle other({ 20.f, 14.f }, 2.f);

	auto expectedCollision = ch::CirclesCollision{ ch::DOWN_VEC, 2.f };

	auto collision = ch::collision::circles_collision_info(first, other);
	REQUIRE(collision.normal.x == expectedCollision.normal.x);
	REQUIRE(collision.normal.y == expectedCollision.normal.y);
	REQUIRE(collision.absoluteDepth == expectedCollision.absoluteDepth);
}

TEST_CASE("circles collide vertically (bottom)", "[Collision functions]") {
	ch::Circle first({ 20.f, 14.f }, 2.f);
	ch::Circle other({ 20.f,10.f }, 4.f);

	auto expectedCollision = ch::CirclesCollision{ ch::UP_VEC, 2.f };

	auto collision = ch::collision::circles_collision_info(first, other);
	REQUIRE(collision.normal.x == expectedCollision.normal.x);
	REQUIRE(collision.normal.y == expectedCollision.normal.y);
	REQUIRE(collision.absoluteDepth == expectedCollision.absoluteDepth);
}

TEST_CASE("circles collide vertically (30 degrees)", "[Collision functions]") {
	ch::Circle first({ 20.f, 10.f }, 4.f);
	ch::Circle other({ 24.f,12.f }, 2.f);

	auto expectedCollision = ch::CirclesCollision{ ch::vec_normalize({2.f,1.f}), 1.527864f };

	auto collision = ch::collision::circles_collision_info(first, other);
	REQUIRE(collision.normal.x == expectedCollision.normal.x);
	REQUIRE(collision.normal.y == expectedCollision.normal.y);
	REQUIRE(collision.absoluteDepth == expectedCollision.absoluteDepth);
}

TEST_CASE("circle collides AABB on the left", "[Collision functions]") {
	ch::AABB aabb(6.f, 7.f, 9.f,3.f);
	ch::Circle circle({ 5.5f,8.f }, 1.f);

	auto expectedCollision = ch::CirclesCollision{ ch::LEFT_VEC, 0.5f };

	auto collision = ch::collision::circle_aabb_collision_info(aabb, circle);
	REQUIRE(collision.normal.x == expectedCollision.normal.x);
	REQUIRE(collision.normal.y == expectedCollision.normal.y);
	REQUIRE(collision.absoluteDepth == expectedCollision.absoluteDepth);
}

TEST_CASE("circle collides AABB on the right", "[Collision functions]") {
	ch::AABB aabb(6.f, 7.f, 9.f, 3.f);
	ch::Circle circle({ 15.5f,8.f }, 1.f);

	auto expectedCollision = ch::CirclesCollision{ ch::RIGHT_VEC, 0.5f };

	auto collision = ch::collision::circle_aabb_collision_info(aabb, circle);
	REQUIRE(collision.normal.x == expectedCollision.normal.x);
	REQUIRE(collision.normal.y == expectedCollision.normal.y);
	REQUIRE(collision.absoluteDepth == expectedCollision.absoluteDepth);
}

TEST_CASE("circle collides AABB on the top", "[Collision functions]") {
	ch::AABB aabb(6.f, 7.f, 9.f, 3.f);
	ch::Circle circle({ 9.f,6.f }, 2.f);

	auto expectedCollision = ch::CirclesCollision{ ch::UP_VEC, 1.f };

	auto collision = ch::collision::circle_aabb_collision_info(aabb, circle);
	REQUIRE(collision.normal.x == expectedCollision.normal.x);
	REQUIRE(collision.normal.y == expectedCollision.normal.y);
	REQUIRE(collision.absoluteDepth == expectedCollision.absoluteDepth);
}

TEST_CASE("circle collides AABB on the bottom", "[Collision functions]") {
	ch::AABB aabb(6.f, 7.f, 9.f, 3.f);
	ch::Circle circle({ 12.f,11.f }, 2.f);

	auto expectedCollision = ch::CirclesCollision{ ch::DOWN_VEC, 1.f };

	auto collision = ch::collision::circle_aabb_collision_info(aabb, circle);
	REQUIRE(collision.normal.x == expectedCollision.normal.x);
	REQUIRE(collision.normal.y == expectedCollision.normal.y);
	REQUIRE(collision.absoluteDepth == expectedCollision.absoluteDepth);
}

TEST_CASE("circle collides top left corner of AABB", "[Collision functions]") {
	ch::AABB aabb(6.f, 7.f, 9.f, 3.f);
	ch::Circle circle({ 4.f,6.f }, 3.f);

	auto expectedCollision = ch::CirclesCollision{ ch::vec_normalize({-2.f, -1.f}), 0.763932f };

	auto collision = ch::collision::circle_aabb_collision_info(aabb, circle);
	REQUIRE(collision.normal.x == expectedCollision.normal.x);
	REQUIRE(collision.normal.y == expectedCollision.normal.y);
	REQUIRE(collision.absoluteDepth == Approx(expectedCollision.absoluteDepth));
}

TEST_CASE("circle collides top right corner of AABB", "[Collision functions]") {
	ch::AABB aabb(6.f, 7.f, 9.f, 3.f);
	ch::Circle circle({ 16.f,4.f }, 4.f);

	auto expectedCollision = ch::CirclesCollision{ ch::vec_normalize({1.f, -3.f}), 0.8377223f };

	auto collision = ch::collision::circle_aabb_collision_info(aabb, circle);
	REQUIRE(collision.normal.x == expectedCollision.normal.x);
	REQUIRE(collision.normal.y == expectedCollision.normal.y);
	REQUIRE(collision.absoluteDepth == Approx(expectedCollision.absoluteDepth));
}

TEST_CASE("circle collides bottom right corner of AABB", "[Collision functions]") {
	ch::AABB aabb(6.f, 7.f, 9.f, 3.f);
	ch::Circle circle({ 19.f,11.f }, 5.f);

	auto expectedCollision = ch::CirclesCollision{ ch::vec_normalize({4.f, 1.f}), 0.876894f };

	auto collision = ch::collision::circle_aabb_collision_info(aabb, circle);
	REQUIRE(collision.normal.x == expectedCollision.normal.x);
	REQUIRE(collision.normal.y == expectedCollision.normal.y);
	REQUIRE(collision.absoluteDepth == Approx(expectedCollision.absoluteDepth));
}

TEST_CASE("circle collides bottom left corner of AABB", "[Collision functions]") {
	ch::AABB aabb(6.f, 7.f, 9.f, 3.f);
	ch::Circle circle({ 5.f,11.f }, 2.f);

	auto expectedCollision = ch::CirclesCollision{ ch::vec_normalize({-1.f, 1.f}), 0.5857864f };

	auto collision = ch::collision::circle_aabb_collision_info(aabb, circle);
	REQUIRE(collision.normal.x == expectedCollision.normal.x);
	REQUIRE(collision.normal.y == expectedCollision.normal.y);
	REQUIRE(collision.absoluteDepth == Approx(expectedCollision.absoluteDepth));
}
