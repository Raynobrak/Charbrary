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

#include <string>

namespace CB {

	class Vector {

	public:
		float x;

		float y;

	public:
		Vector(float X = 0.f, float Y = 0.f);

		float magnitudeSquared() const;

		float magnitude() const;

		Vector normalize() const;

		Vector abs() const;

		Vector& operator+=(const Vector& add);

		Vector& operator-=(const Vector& substract);

		Vector& operator*=(const float scalar);

		Vector& operator/=(const float divisor);

		void operator=(const Vector& other);

		static float dotProduct(const Vector& a, const Vector& b);
	};


	Vector operator+(const Vector& left, const Vector& right);

	Vector operator-(const Vector& left, const Vector& right);

	Vector operator-(const Vector& right);

	Vector operator*(const Vector& base, const float scalar);

	Vector operator*(const float scalar, const Vector& base);

	Vector operator/(const Vector& base, const float divisor);

	bool operator==(const Vector& left, const Vector& right);

	bool operator!=(const Vector& left, const Vector& right);
}