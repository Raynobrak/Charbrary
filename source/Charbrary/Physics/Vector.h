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

#pragma once

namespace CB {
	typedef float VECTOR_T;
	typedef VECTOR_T Scalar;

	class Vector {
	public:

		VECTOR_T x;

		VECTOR_T y;

		Vector(VECTOR_T X = (VECTOR_T)0, VECTOR_T Y = (VECTOR_T)0);

		Scalar magnitudeSquared() const;

		Scalar magnitude() const;

		Vector normalize() const;

		Vector abs() const;

		Scalar dotProductWith(const Vector& other);


		Vector& operator+=(const Vector& add);

		Vector& operator-=(const Vector& substract);

		Vector& operator*=(const Scalar& scalar);

		Vector& operator/=(const Scalar& divisor);

		void operator=(const Vector& other);
	private:

		bool hasAMagnitudeOf0() const;
	};


	Vector operator+(const Vector& left, const Vector& right);

	Vector operator-(const Vector& left, const Vector& right);

	Vector operator-(const Vector& right);

	Vector operator*(const Vector& base, const Scalar scalar);


	Vector operator*(const Scalar scalar, const Vector& base);


	Vector operator/(const Vector& base, const Scalar divisor);

	bool operator==(const Vector& left, const Vector& right);

	bool operator!=(const Vector& left, const Vector& right);
}