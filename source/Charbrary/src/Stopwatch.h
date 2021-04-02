#pragma once

#include <chrono>

namespace ch {

	/**
	 * \brief Represents a stopwatch.
	 *
	 * A utility class that encapsulates time measurement in a very simple interface.
	 */
	class Stopwatch {
	public:
		using time_point = std::chrono::time_point<std::chrono::system_clock>;

		/**
		 * \brief Constructs a new Stopwatch and starts it
		 */
		Stopwatch();

		/**
		 * \brief Starts measuring time.
		 */
		void start();

		/**
		 * \brief reset() is a convenient alias for the start() method.
		 */
		void reset();

		/**
		 * \brief Stops measuring time.
		 * \note Stopping the watch is not necessary to get the elapsed time. 
		 */
		void stop();

		/**
		 * \brief Returns the elapsed time in seconds.
		 * \note Stopping the watch is not necessary to get the elapsed time.
		 */
		long elapsedSeconds();

		/**
		 * \brief Returns the elapsed time in milliseconds.
		 * \note Stopping the watch is not necessary to get the elapsed time.
		 */
		long elapsedMilliseconds();

		/**
		 * \brief Returns the elapsed time in microseconds.
		 * \note Stopping the watch is not necessary to get the elapsed time.
		 */
		long elapsedMicroseconds();

		/**
		 * \brief Returns the elapsed time in nanoseconds.
		 * \note Stopping the watch is not necessary to get the elapsed time.
		 */
		long elapsedNanoseconds();

	private:

		/**
		 * \brief Returns a time_point representing the current moment.
		 */
		time_point now() const;

		time_point start_; /**< Time at which the stopwatch started measuring */
		time_point end_; /**< Time at which the stopwatch stopped measuring */
	};
}