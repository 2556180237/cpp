#pragma once
#include "Shape.hpp"

class Rectangle : public Shape {
public:
	Rectangle(Point topLeft, int width, int height, const BWColor& color);
	Rectangle(Point topLeft, int width, int height, const RGBColor& color);
private:
	void fill(Point p, int w, int h);
};
