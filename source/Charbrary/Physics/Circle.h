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

namespace CB {

	class Circle {

	public:

		Vector pos;

		float radius;

	public:

		Circle();

		Circle(Vector position, float radius_);

		Circle(float x, float y, float radius_);

		float diameter() const;

		float circumference() const;

		float area() const;

		AABB enclosingAABB() const;

		bool contains(const Vector& point) const;

		bool intersects(const Circle& other) const;

		bool strictlyContains(const Circle& other) const;

		void operator=(const Circle& toCopy);
	};

	bool operator==(const Circle& left, const Circle& right);

	bool operator!=(const Circle& left, const Circle& right);
}