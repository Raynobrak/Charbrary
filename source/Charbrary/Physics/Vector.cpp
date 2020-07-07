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

#include "Vector.h"
#include <stdexcept>

namespace CB {
	Vector::Vector(float X, float Y) : x(X), y(Y) {}

	Vector & Vector::operator+=(const Vector & add) {
		x += add.x;
		y += add.y;
		return *this;
	}

	Vector & Vector::operator-=(const Vector & substract) {
		*this += -substract;
		return *this;
	}

	Vector & Vector::operator*=(const float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector & Vector::operator/=(const float divisor) {
		if (divisor == 0) {
			throw std::invalid_argument("Invalid argument : Cannot divide vector by 0");
		}
		x /= divisor;
		y /= divisor;
		return *this;
	}

	void Vector::operator=(const Vector & other) {
		x = other.x;
		y = other.y;
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

	Vector operator*(const Vector & base, const float scalar) {
		return Vector(base.x * scalar, base.y * scalar);
	}

	Vector operator*(const float scalar, const Vector & base) {
		return base * scalar;
	}

	Vector operator/(const Vector & base, const float divisor) {
		if (divisor == 0) {
			throw std::invalid_argument("Invalid argument : Cannot divide vector by 0");
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

