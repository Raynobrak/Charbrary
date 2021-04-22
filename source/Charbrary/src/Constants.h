#pragma once

#include "vector_type_definition.h"

namespace ch {
	constexpr float FLT_PI = 3.14159265359f;

	// The charbrary use a top-left-origin coordinate system. Below are constants for the direction of each axis.

	static const ch::vec_t LEFT_VEC = { -1.f, 0.f };
	static const ch::vec_t RIGHT_VEC = { 1.f, 0.f };
	static const ch::vec_t UP_VEC = { 0.f, -1.f };
	static const ch::vec_t DOWN_VEC = { 0.f, 1.f };

	static const ch::vec_t NULL_VEC = { 0.f,0.f };
}