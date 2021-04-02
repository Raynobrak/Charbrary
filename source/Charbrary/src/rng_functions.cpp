#include <random>
#include <chrono>

#include "rng_functions.h"

namespace ch {

	/**
	 * \brief Returns a reference to a static instance of the random engine.
	 */
	std::default_random_engine& get_random_engine() {
		static std::default_random_engine rng{ static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()) };
		return rng;
	}

	int rnd_int(int lowerInc, int upperInc) {
		std::uniform_int_distribution<int> distribution(lowerInc, upperInc);
		return distribution(get_random_engine());
	}

	float rnd_float(float min, float max) {
		std::uniform_real_distribution<float> distribution(min, max);
		return distribution(get_random_engine());
	}

	float rnd_normal_float() {
		return rnd_float(-1.f, 1.f);
	}

	float rnd_angle_deg() {
		return rnd_float(0.f, 360.f);
	}

	float rnd_angle_rad() {
		static constexpr float PI_2 = 2.f * 3.1415926f;
		return rnd_float(0.f, PI_2);
	}

	vec_t rnd_sfvector(float minX, float maxX, float minY, float maxY) {
		return vec_t(rnd_float(minX, maxX), rnd_float(minY, maxY));
	}

	vec_t rnd_unit_sfvector() {
		float randomRadianAngle = rnd_angle_rad();
		return vec_t(std::cosf(randomRadianAngle), std::sinf(randomRadianAngle));
	}

	vec_t rnd_point_on_rect(vec_t topLeftCorner, vec_t size) {
		auto bottomRightCorner = topLeftCorner + size;
		return rnd_sfvector(topLeftCorner.x, topLeftCorner.y, bottomRightCorner.x, bottomRightCorner.y);
	}

	vec_t rnd_point_on_rect(vec_t center, float width, float height) {
		return center + vec_t(rnd_normal_float() * (width / 2.f), rnd_normal_float() * (height / 2.f));
	}

	vec_t rnd_point_on_circle(float circleRadius, vec_t circleCenter) {
		return circleCenter + rnd_unit_sfvector() * rnd_float(0.f, circleRadius);
	}

	vec_t rnd_point_on_torus(float innerRadius, float outerRadius, vec_t torusCenter) {
		return torusCenter + rnd_unit_sfvector() * rnd_float(innerRadius, outerRadius);
	}
}
