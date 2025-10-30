#pragma once
#include <vector>
#include <array>
#include <string>
#include "Shape.hpp"

class Matrix {
public:
	virtual ~Matrix() = default;
	virtual void draw(const Shape& shape) = 0;
	virtual void display(const std::string& filename) = 0;
    virtual void display() = 0;
    virtual void savePng(const std::string& filename) = 0;
protected:
	Matrix(int width, int height) : m_width(width), m_height(height) {}
	int m_width;
	int m_height;
};

class BWMatrix : public Matrix {
public:
	BWMatrix(int width, int height, unsigned char background)
		: Matrix(width, height), m_pixels(width * height, background) {}
	void draw(const Shape& shape) override;
	void display(const std::string& filename) override;
    void display() override;
    void savePng(const std::string& filename) override;
	unsigned char& at(int x, int y) { 
		return m_pixels[y * m_width + x]; 
	}
private:
	std::vector<unsigned char> m_pixels;
};

class RGBMatrix : public Matrix {
public:
	RGBMatrix(int width, int height, std::array<unsigned char,3> background)
		: Matrix(width, height), m_pixels(width * height, background) {}
	
	void draw(const Shape& shape) override;
	
	void display(const std::string& filename) override; 
    
	void display() override; 
    
	void savePng(const std::string& filename) override;
	
	std::array<unsigned char,3>& at(int x, int y) { 
		return m_pixels[y * m_width + x]; 
	}
	
	private:
		std::vector<std::array<unsigned char,3>> m_pixels;
};
