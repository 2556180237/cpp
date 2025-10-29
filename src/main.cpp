#include <iostream>
#include <filesystem>
#include <cstdlib>
#include "Matrix.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"

static void openImage(const std::string& path) {
	#ifdef _WIN32
		std::string cmd = "cmd /c start \"\" \"" + path + "\"";
	#elif __APPLE__
		std::string cmd = "open \"" + path + "\"";
	#else
		std::string cmd = "xdg-open \"" + path + "\"";
	#endif
	std::system(cmd.c_str());
}

int main() {
	// RGB сцена: дом (точно как в эталоне)
	{
		RGBMatrix rgb(2000, 2000, {0, 0, 0});
		RGBColor rgbColor(102, 205, 255);
		Rectangle sky({0, 0}, 2000, 1500, rgbColor);
		rgbColor.changeColor(0, 153, 0);
		Rectangle grass({0, 1500}, 2000, 2000, rgbColor);
		rgbColor.changeColor(255, 255, 0);
		Circle sun({50, 50}, 300, rgbColor);
		Triangle ray1({360, 50}, {550, 30}, {550, 70}, rgbColor);
		Triangle ray2({270, 270}, {420, 360}, {390, 400}, rgbColor);
		Triangle ray3({50, 360}, {30, 550}, {70, 550}, rgbColor);
		rgbColor.changeColor(102, 51, 0);
		Rectangle wall({600, 900}, 1000, 800, rgbColor);
		rgbColor.changeColor(0, 0, 0);
		Rectangle flue({1300, 550}, 100, 200, rgbColor);
		rgbColor.changeColor(51, 0, 0);
		Triangle roof({560, 900}, {1100, 500}, {1640, 900}, rgbColor);
		rgbColor.changeColor(204, 102, 0);
		Rectangle door({1400, 1350}, 150, 300, rgbColor);
		rgbColor.changeColor(0, 0, 0);
		Circle knob({1535, 1500}, 6, rgbColor);
		rgbColor.changeColor(102, 163, 255);
		Rectangle window1({700, 950}, 300, 350, rgbColor);
		Rectangle window2({1200, 950}, 300, 350, rgbColor);

		rgb.draw(sky);
		rgb.draw(grass);
		rgb.draw(sun);
		rgb.draw(ray1);
		rgb.draw(ray2);
		rgb.draw(ray3);
		rgb.draw(wall);
		rgb.draw(flue);
		rgb.draw(roof);
		rgb.draw(door);
		rgb.draw(knob);
		rgb.draw(window1);
		rgb.draw(window2);
		rgb.display();
	}

	// BW сцена: гриб (как в эталоне)
	{
		int bgColor = 255;
		int capColor = 179;
		int stipeColor = 128;
		int bottomColor = 52;
		BWMatrix bw(2000, 2000, 255);
		BWColor bwColor(capColor);
		Circle cap({1000, 1000}, 700, bwColor);
		bwColor.changeColor(bgColor);
		Rectangle background({0, 700}, 2000, 1000, bwColor);
		Rectangle background2({800, 1300}, 400, 200, bwColor);
		bwColor.changeColor(stipeColor);
		Triangle stipe({1000, 350}, {1200, 1500}, {800, 1500}, bwColor);
		bwColor.changeColor(capColor);
		Rectangle background3({800, 350}, 400, 350, bwColor);
		bwColor.changeColor(bottomColor);
		Circle bottom({1000, 1500}, 200, bwColor);

		bw.draw(cap);
		bw.draw(background);
		bw.draw(bottom);
		bw.draw(background2);
		bw.draw(stipe);
		bw.draw(background3);
		bw.display();
	}

	// Подготовка результата: папка result и PNG
	try {
		std::filesystem::create_directory("result");
		if (std::filesystem::exists("house.png")) {
			std::filesystem::copy_file("house.png", "result/house.png", std::filesystem::copy_options::overwrite_existing);
		}
		if (std::filesystem::exists("mushroom.png")) {
			std::filesystem::copy_file("mushroom.png", "result/mushroom.png", std::filesystem::copy_options::overwrite_existing);
		}
		std::filesystem::copy_file("house.ppm", "result/house.ppm", std::filesystem::copy_options::overwrite_existing);
		std::filesystem::copy_file("mushroom.pgm", "result/mushroom.pgm", std::filesystem::copy_options::overwrite_existing);
	} catch (const std::exception& e) {
		std::cerr << "Result export error: " << e.what() << "\n";
	}

	// Автооткрытие изображений на Windows/macOS/Linux
	if (std::filesystem::exists("result/house.png")) openImage("result/house.png");
	else openImage("result/house.ppm");
	if (std::filesystem::exists("result/mushroom.png")) openImage("result/mushroom.png");
	else openImage("result/mushroom.pgm");

	std::cout << "Images saved to ./result and opened in default viewer.\n";
	return 0;
}
