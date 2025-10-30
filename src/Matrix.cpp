#include "Matrix.hpp"
#include "PngCodec.hpp"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <vector>
#include <cstring>

static inline bool inBounds(int x, int y, int w, int h) {
	return x >= 0 && y >= 0 && x < w && y < h;
}

// PNG encoding is implemented in separate PngCodec module

// Legacy inline PNG writer removed, using PngCodec module now

void BWMatrix::draw(const Shape& shape) {
	unsigned char c = shape.getColor()->getBWColor();
	for (const auto& p : shape.getPoints()) {
		if (inBounds(p.x, p.y, m_width, m_height)) {
			at(p.x, p.y) = c;
		}
	}
}

void BWMatrix::display(const std::string& filename) {
#ifdef NO_LEGACY_PPM
    (void)filename; // disabled by NO_LEGACY_PPM
    return;
#else
    std::ofstream out(filename, std::ios::out);
    // P2 — ASCII PGM
    out << "P2\n" << m_width << ' ' << m_height << "\n255\n";
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            out << static_cast<int>(m_pixels[y * m_width + x]) << ' ';
        }
        out << '\n';
    }
#endif
}

void BWMatrix::display() {
#ifdef NO_LEGACY_PPM
    return;
#else
    this->display("mushroom.pgm");
#endif
}

void BWMatrix::savePng(const std::string& filename) {
    PngCodec::Image image(m_width, m_height);
    
    // Convert grayscale to RGB
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            unsigned char gray = m_pixels[y * m_width + x];
            image.r(x, y) = gray;
            image.g(x, y) = gray;
            image.b(x, y) = gray;
        }
    }
    
    if (!PngCodec::encode(filename, image)) {
        std::cerr << "Error: Could not save PNG to " << filename << "\n";
    }
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
#ifdef NO_LEGACY_PPM
    (void)filename; // disabled by NO_LEGACY_PPM
    return;
#else
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
#endif
}

void RGBMatrix::display() {
#ifdef NO_LEGACY_PPM
    return;
#else
    this->display("house.ppm");
#endif
}

void RGBMatrix::savePng(const std::string& filename) {
    PngCodec::Image image(m_width, m_height);
    
    // Copy RGB data
    for (int y = 0; y < m_height; ++y) {
        for (int x = 0; x < m_width; ++x) {
            const auto& px = m_pixels[y * m_width + x];
            image.r(x, y) = px[0];
            image.g(x, y) = px[1];
            image.b(x, y) = px[2];
        }
    }
    
    if (!PngCodec::encode(filename, image)) {
        std::cerr << "Error: Could not save PNG to " << filename << "\n";
    }
}
