#include "collision_functions.h"

namespace ch {
	namespace collision {
		Circle enclosingCircle(const AABB& aabb) {
			return Circle(aabb.center(), aabb.diagonalLength() / 2.f);
		}

		Circle inscribedCircle(const AABB& aabb) {
			return Circle(aabb.center(), std::min(aabb.size.x, aabb.size.y) / 2.f);
		}

		AABB enclosingAABB(const Circle& circle) {
			return AABB(circle.pos.x - circle.radius, circle.pos.y - circle.radius, circle.radius * 2, circle.radius * 2);
		}

		AABB enclosingAABB(const LineSegment& lineSegment) {
			return AABB({ lineSegment.minX(), lineSegment.minY() }, lineSegment.absoluteSize());
		}

		AABB inscribedAABB(const Circle& circle) {
			float halfSide = sqrtf(circle.radius * circle.radius / 2.f);
			auto halfSize = vec_t(halfSide, halfSide);
			return AABB(circle.pos - halfSize, halfSize * 2.f);
		}

		bool aabb_contains(const AABB& aabb, const vec_t& point) {
			return
				point.x >= aabb.pos.x &&
				point.y >= aabb.pos.y &&
				point.x <= aabb.pos.x + aabb.size.x &&
				point.y <= aabb.pos.y + aabb.size.y;
		}

		bool aabb_contains(const AABB& first, const AABB& other) {
			if (first.area() >= other.area()) {
				AABB zone = first;
				zone.size -= other.size;

				return aabb_contains(zone, other.pos);
			}
			return false;
		}

		bool aabb_contains(const AABB& aabb, const Circle& circle) {
			return aabb_contains(aabb, enclosingAABB(circle));
		}

		bool circle_contains(const Circle& circle, const vec_t& point) {
			return vec_magnitude_squared(circle.pos - point) < circle.radius * circle.radius;
		}

		bool circle_contains(const Circle& first, const Circle& other) {
			if (other.radius <= first.radius) {
				return vec_magnitude_squared(first.pos - other.pos) <= (first.radius - other.radius) * (first.radius - other.radius);
			}
			return false;
		}

		bool circle_contains(const Circle& circle, const AABB& aabb) {
			return
				circle_contains(circle, aabb.corner(ch::Corner::TopLeft)) &&
				circle_contains(circle, aabb.corner(ch::Corner::TopRight)) &&
				circle_contains(circle, aabb.corner(ch::Corner::BottomLeft)) &&
				circle_contains(circle, aabb.corner(ch::Corner::BottomRight));
		}

		bool aabb_intersects(const AABB& a, const AABB& b) {
			AABB extended = b;

			extended.size += a.size;
			extended.pos -= a.size;

			return aabb_contains(extended, a.pos);
		}

		bool aabb_intersects(const AABB& aabb, const Circle& circle) {
			// First check : are the circle and the box close enough to be colliding ?
			if (!aabb_intersects(aabb, enclosingAABB(circle))) {
				return false;
			}

			// Second check : does the circle contain any of the box corners ?
			if (circle_contains(circle, aabb.corner(ch::Corner::TopLeft)) ||
				circle_contains(circle, aabb.corner(ch::Corner::TopRight)) ||
				circle_contains(circle, aabb.corner(ch::Corner::BottomLeft)) ||
				circle_contains(circle, aabb.corner(ch::Corner::BottomRight)))
					return true;

			// Last check : does the aabb contain any of the extremums of the circle ?
			if (aabb_contains(aabb, circle.pos + LEFT_VEC * circle.radius) ||
				aabb_contains(aabb, circle.pos + RIGHT_VEC * circle.radius) ||
				aabb_contains(aabb, circle.pos + UP_VEC * circle.radius) ||
				aabb_contains(aabb, circle.pos + DOWN_VEC * circle.radius))
					return true;

			return false;
		}

		bool circle_intersects(const Circle& circle, const Circle& other) {
			return vec_magnitude_squared(circle.pos - other.pos) < (circle.radius + other.radius) * (circle.radius + other.radius);
		}

		bool circle_intersects(const Circle& circle, const AABB& aabb) {
			return aabb_intersects(aabb, circle);
		}

		float circles_distance(const Circle& a, const Circle& b) {
			return vec_magnitude(a.pos - b.pos) - a.radius - b.radius;
		}
		
		AABBCollision aabb_collision_info(const AABB& first, const AABB& other) {
			if (!aabb_intersects(first, other)) {
				return AABBCollision{ NULL_VEC, NULL_VEC };
			}

			auto currentCorners = first.corners();
			auto otherCorners = other.corners();

			auto otherCenter = other.center();

			float closestCornerDistanceSquared = std::numeric_limits<float>::infinity();

			Corner closestCorner = Corner::MAX_VALUE;

			for (size_t i = 0; i < static_cast<size_t>(Corner::MAX_VALUE); ++i) {
				float distanceToOtherCenterSquared = vec_magnitude(currentCorners[i] - otherCenter);

				if (distanceToOtherCenterSquared < closestCornerDistanceSquared) {
					closestCornerDistanceSquared = distanceToOtherCenterSquared;
					closestCorner = static_cast<Corner>(i);
				}
			}

			Corner oppositeCorner = diagonally_opposed_corner(closestCorner);

			auto c1 = currentCorners[static_cast<size_t>(closestCorner)];
			auto c2 = otherCorners[static_cast<size_t>(oppositeCorner)];
			vec_t delta = c1 - c2;
			delta = vec_abs(delta);

			AABBCollision collision;
			collision.delta = delta;

			if (delta.x > delta.y) {
				if (closestCorner == Corner::TopLeft || closestCorner == Corner::TopRight)
					collision.normal = UP_VEC;
				else
					collision.normal = DOWN_VEC;
			}
			else {
				if (closestCorner == Corner::TopLeft || closestCorner == Corner::BottomLeft)
					collision.normal = LEFT_VEC;
				else
					collision.normal = RIGHT_VEC;
			}

			return collision;
		}

		CirclesCollision circles_collision_info(const Circle& first, const Circle& other) {
			if (!circle_intersects(first, other))
				return CirclesCollision{ NULL_VEC, 0.f };

			return CirclesCollision{ vec_normalize(other.pos - first.pos), std::abs(circles_distance(first, other)) };
		}

		CircleAABBCollision circle_aabb_collision_info(const AABB& aabb, const Circle& circle) {
			static const CircleAABBCollision NO_COLLISION = CircleAABBCollision{ NULL_VEC, 0.f };

			if (!aabb_intersects(aabb, enclosingAABB(circle))) {
				return NO_COLLISION;
			}

			if ((circle.pos.x > aabb.pos.x && circle.pos.x < aabb.pos.x + aabb.size.x) ||
				(circle.pos.y > aabb.pos.y && circle.pos.y < aabb.pos.y + aabb.size.y)) {
				auto aabbColl = aabb_collision_info(aabb, enclosingAABB(circle));
				return CircleAABBCollision{ aabbColl.normal, aabbColl.absolutePenetrationDepthAlongNormal() };
			}
			else {
				auto corners = aabb.corners();
				for (const auto& corner : corners) {
					if (circle_contains(circle, corner)) {
						auto dir = vec_normalize(circle.pos - corner);
						float depth = circle.radius - vec_magnitude(circle.pos - corner);
						return CircleAABBCollision{ dir, depth };
					}
				}
			}

			return NO_COLLISION;
		}

		SegmentsIntersection line_segments_intersection_info(const LineSegment& first, const LineSegment& other) {
			if (collision::aabb_intersects(enclosingAABB(first), enclosingAABB(other))) {
				float slopeCurrent = first.slope();
				float slopeOther = other.slope();
				float YInterceptCurrent = LineSegment::YIntercept(first.start, slopeCurrent);
				float YInterceptOther = LineSegment::YIntercept(other.start, slopeOther);

				if (slopeCurrent == slopeOther) {
					if (YInterceptCurrent == YInterceptOther) {

						float minx = first.minX() < other.minX() ? first.minX() : other.minX();
						float maxx = first.maxX() > other.maxX() ? first.maxX() : other.maxX();
						float miny = first.minY() < other.minY() ? first.minY() : other.minY();
						float maxy = first.maxY() > other.maxY() ? first.maxY() : other.maxY();

						const vec_t* p1 = nullptr;
						const vec_t* p2 = nullptr;

						if (minx == maxx) {
							if (first.start.y == miny || first.start.y == maxy) {
								p1 = &first.end;
							}
							else {
								p1 = &first.start;
							}

							if (other.start.y == miny || other.start.y == maxy) {
								p2 = &other.end;
							}
							else {
								p2 = &other.start;
							}
						}
						else if (miny == maxy) {
							if (first.start.x == minx || first.start.x == maxx) {
								p1 = &first.end;
							}
							else {
								p1 = &first.start;
							}

							if (other.start.x == minx || other.start.x == maxx) {
								p2 = &other.end;
							}
							else {
								p2 = &other.start;
							}
						}
						else {
							if (first.start.x == minx || first.start.x == maxx || first.start.y == miny || first.start.y == maxy) {
								p1 = &first.end;
							}
							else {
								p1 = &first.start;
							}

							if (other.start.x == minx || other.start.x == maxx || other.start.y == miny || other.start.y == maxy) {
								p2 = &other.end;
							}
							else {
								p2 = &other.start;
							}
						}

						return SegmentsIntersection(IntersectionType::Overlapping, std::pair<vec_t, vec_t>{ *p1, *p2 });
					}
					else {
						return SegmentsIntersection(IntersectionType::None);
					}
				}
				else {
					if (YInterceptCurrent == YInterceptOther) {

						return SegmentsIntersection(IntersectionType::Crossing, vec_t(0, YInterceptCurrent));
					}
					else {
						float commonX = (YInterceptOther - YInterceptCurrent) / (slopeCurrent - slopeOther);

						if (commonX > first.minX() && commonX < first.maxX() && commonX > other.minX() && commonX < other.maxX()) {
							float commonY = slopeCurrent * commonX + YInterceptCurrent;

							return SegmentsIntersection(IntersectionType::Crossing, vec_t(commonX, commonY));
						}
						else {
							return SegmentsIntersection(IntersectionType::None);
						}
					}
				}
			}
			else {
				return SegmentsIntersection(IntersectionType::None);
			}
		}
	}
}
