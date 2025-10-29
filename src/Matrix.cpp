#include "Matrix.hpp"
#include <fstream>

static inline bool inBounds(int x, int y, int w, int h) {
	return x >= 0 && y >= 0 && x < w && y < h;
}

void BWMatrix::draw(const Shape& shape) {
	unsigned char c = shape.getColor()->getBWColor();
	for (const auto& p : shape.getPoints()) {
		if (inBounds(p.x, p.y, m_width, m_height)) {
			at(p.x, p.y) = c;
		}
	}
}

void BWMatrix::display(const std::string& filename) {
	std::ofstream out(filename, std::ios::out);
	// P2 — ASCII PGM
	out << "P2\n" << m_width << ' ' << m_height << "\n255\n";
	for (int y = 0; y < m_height; ++y) {
		for (int x = 0; x < m_width; ++x) {
			out << static_cast<int>(m_pixels[y * m_width + x]) << ' ';
		}
		out << '\n';
	}
}

void BWMatrix::display() {
	this->display("mushroom.pgm");
}

void RGBMatrix::draw(const Shape& shape) {
	auto rgb = shape.getColor()->getRGBColor();
	for (const auto& p : shape.getPoints()) {
		if (inBounds(p.x, p.y, m_width, m_height)) {
			at(p.x, p.y) = rgb;
		}
	}
}

void RGBMatrix::display(const std::string& filename) {
	std::ofstream out(filename, std::ios::out);
	// P3 — ASCII PPM
	out << "P3\n" << m_width << ' ' << m_height << "\n255\n";
	for (int y = 0; y < m_height; ++y) {
		for (int x = 0; x < m_width; ++x) {
			auto& px = m_pixels[y * m_width + x];
			out << static_cast<int>(px[0]) << ' ' << static_cast<int>(px[1]) << ' ' << static_cast<int>(px[2]) << ' ';
		}
		out << '\n';
	}
}

void RGBMatrix::display() {
	this->display("house.ppm");
}
