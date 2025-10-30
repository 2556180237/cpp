#include "Circle.hpp"
#include <cmath>
Circle::Circle(Point center, int radius, const BWColor& color)
	: Shape(color) {
	fill(center, radius);
}

Circle::Circle(Point center, int radius, const RGBColor& color)
	: Shape(color) {
	fill(center, radius);
}
void Circle::fill(Point c, int r) {
	if (r <= 0) return;
	int xmin = c.x - r;
	int xmax = c.x + r;
	int ymin = c.y - r;
	int ymax = c.y + r;
	int rr = r * r;
	for (int y = ymin; y <= ymax; ++y) {
		for (int x = xmin; x <= xmax; ++x) {
			long dx = x - c.x;
			long dy = y - c.y;
			if (dx * dx + dy * dy <= rr) {
				m_points.push_back({x, y});
			}
		}
	}
}
