#include "rng_functions.h"

#include <random>
#include <chrono>

namespace ch {
	namespace rand {

		/**
		 * \brief Returns a reference to a static instance of the random engine.
		 */
		std::default_random_engine& get_random_engine() {
			static std::default_random_engine rng{ static_cast<unsigned int>(std::chrono::system_clock::now().time_since_epoch().count()) };
			return rng;
		}

		int rand_int(int lowerInc, int upperInc) {
			std::uniform_int_distribution<int> distribution(lowerInc, upperInc);
			return distribution(get_random_engine());
		}

		float rand_float(float min, float max) {
			std::uniform_real_distribution<float> distribution(min, max);
			return distribution(get_random_engine());
		}

		bool rand_bit() {
			return rand_int(0, 1) == 0;
		}

		bool rand_bit(float probability) {
			return rand_float(0.f, 1.f) <= probability;
		}

		float rnd_normal_float() {
			return rand_float(-1.f, 1.f);
		}

		float rnd_angle_deg() {
			return rand_float(0.f, 360.f);
		}

		float rnd_angle_rad() {
			static constexpr float PI_2 = 2.f * 3.1415926f;
			return rand_float(0.f, PI_2);
		}

		vec_t rand_vector(float minX, float maxX, float minY, float maxY) {
			return vec_t(rand_float(minX, maxX), rand_float(minY, maxY));
		}

		vec_t rand_unit_vector() {
			float randomRadianAngle = rnd_angle_rad();
			return vec_t(std::cosf(randomRadianAngle), std::sinf(randomRadianAngle));
		}

		vec_t rand_point_on_rect(vec_t topLeftCorner, vec_t size) {
			auto bottomRightCorner = topLeftCorner + size;
			return rand_vector(topLeftCorner.x, topLeftCorner.y, bottomRightCorner.x, bottomRightCorner.y);
		}

		vec_t rand_point_on_rect(vec_t center, float width, float height) {
			return center + vec_t(rnd_normal_float() * (width / 2.f), rnd_normal_float() * (height / 2.f));
		}

		vec_t rand_point_on_circle(float circleRadius, vec_t circleCenter) {
			return circleCenter + rand_unit_vector() * rand_float(0.f, circleRadius);
		}

		vec_t rand_point_on_torus(float innerRadius, float outerRadius, vec_t torusCenter) {
			return torusCenter + rand_unit_vector() * rand_float(innerRadius, outerRadius);
		}
	}
}
