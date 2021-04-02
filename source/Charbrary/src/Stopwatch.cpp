#include "Stopwatch.h"

namespace ch {

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