#pragma once

#include "vector_type_definition.h"

namespace CB {
	constexpr float FLT_PI = 3.14159265359f;

	static const CB::vec_t LEFT_VEC = { -1.f, 0.f };
	static const CB::vec_t RIGHT_VEC = { 1.f, 0.f };
	static const CB::vec_t UP_VEC = { 0.f, 1.f };
	static const CB::vec_t DOWN_VEC = { 0.f, -1.f };

	static const CB::vec_t NULL_VEC = { 0.f,0.f };
}