#pragma once
#include <vector>
#include "Color.hpp"

struct Point {
	int x;
	int y;
};

class Shape {
public:
	virtual ~Shape() { delete m_color; }
	std::vector<Point> getPoints() const { return m_points; }
	const Color* getColor() const { return m_color; }
protected:
	explicit Shape(const BWColor& color) { m_color = new BWColor(color); }
	explicit Shape(const RGBColor& color) { m_color = new RGBColor(color); }
protected:
	std::vector<Point> m_points;
	Color* m_color = nullptr;
};
