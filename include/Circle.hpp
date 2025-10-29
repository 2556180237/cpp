#pragma once
#include "Shape.hpp"

class Circle : public Shape {
public:
	Circle(Point center, int radius, const BWColor& color);
	Circle(Point center, int radius, const RGBColor& color);
private:
	void fill(Point c, int r);
};
