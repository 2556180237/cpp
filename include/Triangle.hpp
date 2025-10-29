#pragma once
#include "Shape.hpp"

class Triangle : public Shape {
public:
	Triangle(Point a, Point b, Point c, const BWColor& color);
	Triangle(Point a, Point b, Point c, const RGBColor& color);
private:
	static float area(Point a, Point b, Point c);
	void fill(Point a, Point b, Point c);
};
