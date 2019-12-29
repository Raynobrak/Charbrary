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

#include "Stopwatch.h"

namespace CB {

	Stopwatch::Stopwatch() {
		start();
	}

	void Stopwatch::start() {
		start_ = now();
	}

	void Stopwatch::reset() {
		start();
	}

	void Stopwatch::stop() {
		end_ = now();
	}

	long Stopwatch::elapsedSeconds() {
		stop();
		return std::chrono::duration_cast<std::chrono::seconds>(end_ - start_).count();
	}

	long Stopwatch::elapsedMilliseconds() {
		stop();
		return std::chrono::duration_cast<std::chrono::milliseconds>(end_ - start_).count();
	}

	long Stopwatch::elapsedMicroseconds() {
		stop();
		return std::chrono::duration_cast<std::chrono::microseconds>(end_ - start_).count();
	}

	long Stopwatch::elapsedNanoseconds() {
		stop();
		return std::chrono::duration_cast<std::chrono::nanoseconds>(end_ - start_).count();
	}

	Stopwatch::time_point Stopwatch::now() const {
		return std::chrono::system_clock::now();
	}
}