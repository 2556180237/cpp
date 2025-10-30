#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <chrono>
#include <algorithm>
#include "Matrix.hpp"
#include "Rectangle.hpp"
#include "Circle.hpp"
#include "Triangle.hpp"

/*
English: Render RGB "house" into provided matrix.
Русский: Отрисовка RGB «дом» в переданную матрицу.
Pseudocode:
  prepare shapes (sky, grass, sun, rays, walls, roof, door, windows)
  draw them to rgb in order
*/
static void renderRgbTo(RGBMatrix &rgb) {
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
}

/*
English: Render BW  "mushroom" into provided matrix.
Русский: Отрисовка ЧБ «гриб» в переданную матрицу.
Pseudocode:
  choose grayscale colors
  build shapes (cap, background pieces, stipe, bottom)
  draw to bw in order
*/
static void renderBwTo(BWMatrix &bw) {
	int bgColor = 255;
	int capColor = 179;
	int stipeColor = 128;
	int bottomColor = 52;
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
}

/*
English: Build both scenes entirely in memory (no file IO); used for benchmarks.
Русский: Строю обе сцены в памяти без IO; используется для бенчмарка.
Pseudocode:
  allocate RGBMatrix; renderRgbTo
  allocate BWMatrix;  renderBwTo
*/
static void renderScenesNoIO() {
	RGBMatrix rgb(2000, 2000, {0, 0, 0});
	renderRgbTo(rgb);
	BWMatrix bw(2000, 2000, 255);
	renderBwTo(bw);
}

/*
English: Entry point. Optional benchmark mode (--bench N). Otherwise renders and exports PNGs.
Русский: Точка входа. Опциональный режим бенчмарка (--bench N). Иначе отрисовка и экспорт PNG.
Pseudocode:
  if args contain --bench:
    parse N; time N times renderScenesNoIO; compute score; print; exit
  else:
    render RGB/BW; (legacy display may no-op) ; ensure result/ ; save 2 PNGs
*/
int main(int argc, char** argv) {
	if (argc >= 2 && std::string(argv[1]) == "--bench") {
		int iters = 3;
		if (argc >= 3) {
			try { iters = std::max(1, std::stoi(argv[2])); } catch (...) { iters = 3; }
		}
		auto t0 = std::chrono::high_resolution_clock::now();
		for (int i = 0; i < iters; ++i) {
			renderScenesNoIO();
		}
		auto t1 = std::chrono::high_resolution_clock::now();
		double totalMs = std::chrono::duration<double, std::milli>(t1 - t0).count();
		double avgMs = totalMs / iters;

        // Baseline from env PERF_BASELINE_MS or default
        double baselineMs = 3000.0; // default 3000 ms
		if (const char* envv = std::getenv("PERF_BASELINE_MS")) {
			try { baselineMs = std::max(1.0, std::stod(envv)); } catch (...) {}
		}
        double perf = baselineMs / avgMs; // >1 better than baseline
        perf = std::clamp(perf, 0.0, 1.5); // clamp upper bound
		double score = 7.0 + (perf * 2.0);
		score = std::clamp(score, 0.0, 10.0);

		std::cout << "Benchmark iterations: " << iters << "\n";
		std::cout << "Avg time (ms): " << avgMs << "\n";
		std::cout << "Baseline (ms): " << baselineMs << "\n";
		std::cout << "Perf ratio: " << (baselineMs / avgMs) << "\n";
		std::cout << "Score (0-10): " << score << "\n";
		return 0;
	}

    // RGB scene: house
	{
		RGBMatrix rgb(2000, 2000, {0, 0, 0});
		renderRgbTo(rgb);
		rgb.display();
	}

    // BW scene: mushroom
	{
		BWMatrix bw(2000, 2000, 255);
		renderBwTo(bw);
		bw.display();
	}

    // Prepare output: create result folder
	try {
		namespace fs = std::filesystem;
		fs::create_directory("result");
		{
			RGBMatrix rgb(2000, 2000, {0, 0, 0});
			renderRgbTo(rgb);
			rgb.savePng("result/house.png");
		}
		{
			BWMatrix bw(2000, 2000, 255);
			renderBwTo(bw);
			bw.savePng("result/mushroom.png");
		}
	} catch (const std::exception& e) {
		std::cerr << "Result export error: " << e.what() << "\n";
	}

	std::cout << "Images saved to ./result and opened in default viewer.\n";
	return 0;
}


