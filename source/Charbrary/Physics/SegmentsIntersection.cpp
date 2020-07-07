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

#include "SegmentsIntersection.h"

namespace CB {
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_) : type(type_) {}
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_, const vec_t& point_) : type(type_), point(point_) {}
	SegmentsIntersection::SegmentsIntersection(IntersectionType type_, const std::pair<vec_t, vec_t>& segment) : type(type_), resultingSegment(segment) {}
}
