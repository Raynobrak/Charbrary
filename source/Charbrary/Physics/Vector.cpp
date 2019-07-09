/*
   Copyright 2019 Lucas Charbonnier

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

	   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "Vector.h"
#pragma once
#include <cmath>
#include <stdexcept>

namespace CB {

	Vector::Vector(VECTOR_T X, VECTOR_T Y) : x(X), y(Y) {}

	Scalar Vector::magnitudeSquared() const {
		return (x * x + y * y);
	}

	Scalar Vector::magnitude() const {
		return std::sqrtf(magnitudeSquared());
	}

	Vector Vector::normalize() const {
		if (hasAMagnitudeOf0()) {
			return { 0,0 };
		}

		return *this / magnitude();
	}

	Vector Vector::abs() const {
		return Vector(std::abs(x), std::abs(y));
	}

	Scalar Vector::dotProductWith(const Vector & other) {
		return x * other.x + y * other.y;
	}

	Vector & Vector::operator+=(const Vector & add) {
		x += add.x;
		y += add.y;
		return *this;
	}

	Vector & Vector::operator-=(const Vector & substract) {
		*this += -substract;
		return *this;
	}

	Vector & Vector::operator*=(const Scalar & scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector & Vector::operator/=(const Scalar & divisor) {
		if (divisor == 0) {
			throw std::invalid_argument("Invalid argument : 'divisor' was 0, cannot divide by zero.");
		}

		x /= divisor;
		y /= divisor;
		return *this;
	}

	void Vector::operator=(const Vector & other) {
		x = other.x;
		y = other.y;
	}

	bool Vector::hasAMagnitudeOf0() const {
		return x == 0 && y == 0;
	}

	Vector operator+(const Vector & left, const Vector & right) {
		return Vector(left.x + right.x, left.y + right.y);
	}

	Vector operator-(const Vector & left, const Vector & right) {
		return Vector(left.x - right.x, left.y - right.y);
	}

	Vector operator-(const Vector & right) {
		return Vector(-right.x, -right.y);
	}

	Vector operator*(const Vector & base, const Scalar scalar) {
		return Vector(base.x * scalar, base.y * scalar);
	}

	Vector operator*(const Scalar scalar, const Vector & base) {
		return base * scalar;
	}

	Vector operator/(const Vector & base, const Scalar divisor) {
		if (divisor == 0) {
			throw std::invalid_argument("Invalid argument : 'divisor' was 0, cannot divide by zero.");
		}
		return Vector(base.x / divisor, base.y / divisor);
	}

	bool operator==(const Vector & left, const Vector & right) {
		return left.x == right.x && left.y == right.y;
	}

	bool operator!=(const Vector & left, const Vector & right) {
		return !(left == right);
	}

}

