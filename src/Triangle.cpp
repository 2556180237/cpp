#include "Triangle.hpp"
#include <algorithm>
#include <cmath>

Triangle::Triangle(Point a, Point b, Point c, const BWColor& color)
	: Shape(color) {
	fill(a, b, c);
}

Triangle::Triangle(Point a, Point b, Point c, const RGBColor& color)
	: Shape(color) {
	fill(a, b, c);
}

float Triangle::area(Point a, Point b, Point c) {
	return 0.5f * std::abs(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

void Triangle::fill(Point a, Point b, Point c) {
	int minX = std::min({a.x, b.x, c.x});
	int maxX = std::max({a.x, b.x, c.x});
	int minY = std::min({a.y, b.y, c.y});
	int maxY = std::max({a.y, b.y, c.y});
	float S = area(a, b, c);
	if (S == 0.0f) return;
	const float eps = 1e-3f;
	for (int y = minY; y <= maxY; ++y) {
		for (int x = minX; x <= maxX; ++x) {
			Point p{x, y};
			float s1 = area(a, b, p);
			float s2 = area(b, c, p);
			float s3 = area(c, a, p);
			if (std::abs((s1 + s2 + s3) - S) <= eps) {
				m_points.push_back(p);
			}
		}
	}
}
