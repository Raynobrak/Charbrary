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

	/*
	/**
	 * \brief Represents a 2D vector.
	 * 
	 * Represents a 2D vector whose components are axis-aligned. This class can be used
	 * to represent physical properties such as
	 * - acceleration
	 * - velocity
	 * - position
	 * - size
	 * - force
	 * - etc...
	 * 
	 * The components are public and can be directly like so
	 * 
	 * Common vector operations such as computing the magnitude, normalizing or
	 * computing the dot product are encapsulated in member functions.
	 * 
	 * Most operators are overloaded to simplify vector calculus.
	 */
	class Vector {
	public:	
		float x; /**< Horizontal component of the vector. */
		float y; /**< Vertical component of the vector. */
	public:
		/**
		 * \brief Constructs a new Vector from it's X and Y values.
		 * \param X Horizontal component
		 * \param Y Vertical component
		 * 
		 * By default, X and Y will be equal to 0. So constructing a vector without any
		 * parameters is absolutely valid.
		 */
		Vector(float X = 0.f, float Y = 0.f);

		/**
		 * \brief Overload of the addition-assignment operator.
		 * 
		 * The vector given as parameter will be added onto the current vector. Their
		 * components will be added respectively.
		 * 
		 * \param add The vector that will be added to the current vector.
		 * \return A reference to the current vector.
		 */
		Vector& operator+=(const Vector& add);

		/**
		 * \brief Overload of the substraction-assignment operator.
		 * 
		 * The components of the current vector will be respectively substracted by the
		 * components of the vector given as parameter.
		 * 
		 * \param add The vector that the current vector will be substracted by.
		 * \return A reference to the current vector.
		 */
		Vector& operator-=(const Vector& substract);

		/**
		 * \brief Overload of the multiplication-assignment operator.
		 * 
		 * Amplifies (or "scales") the current vector by a scalar. Each component will be
		 * multiplied by the given scalar.
		 * 
		 * \param scalar Scalar by which the current vector will be amplified.
		 * \return A reference to the current vector.
		 */
		Vector& operator*=(const float scalar);

		/**
		 * \brief Overload of the division-assignment operator.
		 * 
		 * Divides the current vector by a real number. Each component will be
		 * divided by the given number.
		 * 
		 * \param divisor Number by which the current vector will be divided.
		 * \return A reference to the current vector.
		 */
		Vector& operator/=(const float divisor);

		/**
		 * \brief Overload of the assignment operator.
		 */
		void operator=(const Vector& other);	
	};

	/**
	 * \brief Overload of the addition operator.
	 * 
	 * The vectors are summed by respectively adding their components.
	 * 
	 * \return The sum as a new Vector.
	 */
	Vector operator+(const Vector& left, const Vector& right);

	/**
	 * \brief Overload of the substraction operator.
	 * 
	 * The components of left are respectively substracted by the ones from right.
	 * 
	 * \return The result as a new Vector.
	 */
	Vector operator-(const Vector& left, const Vector& right);

	/**
	 * \brief Overload of the unary minus operator.
	 * 
	 * Applies the unary minus operator to each component of the vector.
	 * 
	 * \return The result as a new Vector.
	 */
	Vector operator-(const Vector& right);

	/**
	 * \brief Overload of the multiplication operator.
	 * 
	 * Amplifies (or "scales") base by a scalar. Each component will be
	 * multiplied by the given scalar.
	 * 
	 * \param scalar Scalar (real number) by which the current vector will be amplified.
	 * \return The result as a new vector.
	 */
	Vector operator*(const Vector& base, const float scalar);

	/**
	 * \brief Overload of the multiplication operator.
	 * 
	 * Amplifies (or "scales") base by a scalar. Each component will be
	 * multiplied by the given scalar.
	 * 
	 * \param scalar Scalar (real number) by which the current vector will be amplified.
	 * \return The result as a new vector.
	 */
	Vector operator*(const float scalar, const Vector& base);

	/**
	 * \brief Overload of the multiplication operator.
	 * 
	 * Amplifies (or "scales") base by a scalar. Each component will be
	 * multiplied by the given scalar.
	 * 
	 * \param scalar Scalar (real number) by which the current vector will be amplified.
	 * \return The result as a new vector.
	 */
	Vector operator/(const Vector& base, const float divisor);

	/**
	 * \brief Overload of the equality operator.
	 * \return True if the 2 vectors are equal, false otherwise.
	 */
	bool operator==(const Vector& left, const Vector& right);

	/**
	 * \brief Overload of the inequality operator.
	 * \return true if the 2 vectors are different, false otherwise.
	 */
	bool operator!=(const Vector& left, const Vector& right);
}