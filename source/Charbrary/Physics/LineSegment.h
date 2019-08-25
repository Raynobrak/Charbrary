/* Copyright 2019 Lucas Charbonnier

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License. */

#pragma once

#include "Vector.h"
#include "AABB.h"

#include "LineSegmentsCollision.h"

namespace CB {

	class LineSegment {

	public:

		Vector start;
		Vector end;

	public:

		LineSegment();

		LineSegment(const Vector& start_, const Vector& end_);

		float slope() const;

		float length() const;

		float lengthSquared() const;

		Vector absoluteSize() const;

		Vector dirFromStart() const;

		float minX() const;
		float minY() const;
		float maxX() const;
		float maxY() const;

		AABB enclosingAABB() const;

		SegmentsIntersection checkForIntersection(const LineSegment& other) const;

		static float YIntercept(const Vector& anyPoint, float slope);

		void operator=(const LineSegment& model);
	};

	bool operator==(const LineSegment& left, const LineSegment& right);

	bool operator!=(const LineSegment& left, const LineSegment& right);
}