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
	CBVEC::CBVEC(float X, float Y) : x(X), y(Y) {}

	CBVEC & CBVEC::operator+=(const CBVEC & add) {
		x += add.x;
		y += add.y;
		return *this;
	}

	CBVEC & CBVEC::operator-=(const CBVEC & substract) {
		*this += -substract;
		return *this;
	}

	CBVEC & CBVEC::operator*=(const float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	CBVEC & CBVEC::operator/=(const float divisor) {
		if (divisor == 0) {
			throw std::invalid_argument("Invalid argument : Cannot divide vector by 0");
		}
		x /= divisor;
		y /= divisor;
		return *this;
	}

	void CBVEC::operator=(const CBVEC & other) {
		x = other.x;
		y = other.y;
	}

	CBVEC operator+(const CBVEC & left, const CBVEC & right) {
		return CBVEC(left.x + right.x, left.y + right.y);
	}

	CBVEC operator-(const CBVEC & left, const CBVEC & right) {
		return CBVEC(left.x - right.x, left.y - right.y);
	}

	CBVEC operator-(const CBVEC & right) {
		return CBVEC(-right.x, -right.y);
	}

	CBVEC operator*(const CBVEC & base, const float scalar) {
		return CBVEC(base.x * scalar, base.y * scalar);
	}

	CBVEC operator*(const float scalar, const CBVEC & base) {
		return base * scalar;
	}

	CBVEC operator/(const CBVEC & base, const float divisor) {
		if (divisor == 0) {
			throw std::invalid_argument("Invalid argument : Cannot divide vector by 0");
		}
		return CBVEC(base.x / divisor, base.y / divisor);
	}

	bool operator==(const CBVEC & left, const CBVEC & right) {
		return left.x == right.x && left.y == right.y;
	}

	bool operator!=(const CBVEC & left, const CBVEC & right) {
		return !(left == right);
	}
}

