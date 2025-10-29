#include "Rectangle.hpp"

Rectangle::Rectangle(Point topLeft, int width, int height, const BWColor& color)
	: Shape(color) {
	fill(topLeft, width, height);
}

Rectangle::Rectangle(Point topLeft, int width, int height, const RGBColor& color)
	: Shape(color) {
	fill(topLeft, width, height);
}

void Rectangle::fill(Point p, int w, int h) {
	if (w <= 0 || h <= 0) return;
	for (int y = p.y; y < p.y + h; ++y) {
		for (int x = p.x; x < p.x + w; ++x) {
			m_points.push_back({x, y});
		}
	}
}
