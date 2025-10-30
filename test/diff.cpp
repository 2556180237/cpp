#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../include/PngCodec.hpp"

namespace fs = std::filesystem;

static bool run(const std::string &cmd) {
	int rc = std::system(cmd.c_str());
	return rc == 0;
}

/*
English (func): compareWithMetricAE — decode two PNGs, count pixel differences, write visual diff.
Русский (функция): compareWithMetricAE — декодирует два PNG, подсчитывает отличающиеся пиксели, сохраняет визуальный дифф.
Pseudocode:
  decode expected -> exp, actual -> act
  if decode fails: return false
  diffPixels = compare(exp, act)
  if diffPixels>0:
    create diff image WxH (max dims); paint black; mark mismatches red; save
  return true
*/
static bool compareWithMetricAE(const fs::path &expected,
		const fs::path &actual,
		const fs::path &diffOut,
		long long &diffPixels) {
	PngCodec::Image expImg, actImg;
	
	if (!PngCodec::decode(expected.string(), expImg)) {
		std::cerr << "Failed to decode expected image: " << expected << "\n";
		std::cerr << "File size: " << fs::file_size(expected) << " bytes\n";
		return false;
	}
	
	if (!PngCodec::decode(actual.string(), actImg)) {
		std::cerr << "Failed to decode actual image: " << actual << "\n";
		return false;
	}
	
	diffPixels = PngCodec::compare(expImg, actImg);
	
	if (diffPixels > 0) {
		PngCodec::Image diffImg(std::max(expImg.width, actImg.width), 
		                       std::max(expImg.height, actImg.height));
		for (uint32_t y = 0; y < diffImg.height; ++y) {
			for (uint32_t x = 0; x < diffImg.width; ++x) {
				diffImg.r(x, y) = 0;
				diffImg.g(x, y) = 0;
				diffImg.b(x, y) = 0;
			}
		}
		uint32_t minWidth = std::min(expImg.width, actImg.width);
		uint32_t minHeight = std::min(expImg.height, actImg.height);
		
		for (uint32_t y = 0; y < minHeight; ++y) {
			for (uint32_t x = 0; x < minWidth; ++x) {
				if (expImg.r(x, y) != actImg.r(x, y) ||
				    expImg.g(x, y) != actImg.g(x, y) ||
				    expImg.b(x, y) != actImg.b(x, y)) {
                    diffImg.r(x, y) = 255;
					diffImg.g(x, y) = 0;
					diffImg.b(x, y) = 0;
				}
			}
		}
		PngCodec::encode(diffOut.string(), diffImg);
	}
	
	return true;
}

/*
English (main): ensure folders exist, iterate pairs, compare and print result; exit code 0/1.
Русский (main): чекнуть папки, пройтись по параметрам, сравнить и вывести результат; код возврата булевый 0/1.
*/
int main() {
	fs::path examples = "examples";
	fs::path result = "result";
	if (!fs::exists(examples) || !fs::exists(result)) {
		std::cerr << "Missing directories: ensure ./examples and ./result exist\n";
		return 2;
	}

	struct Pair { const char *name; };
	std::vector<Pair> pairs = { {"house.png"}, {"mushroom.png"} };

	bool anyFail = false;
	fs::create_directories("test");
	for (const auto &p : pairs) {
		fs::path exp = examples / p.name;
		fs::path act = result / p.name;
		if (!fs::exists(exp)) {
			std::cerr << "Missing expected: " << exp << "\n";
			anyFail = true; continue;
		}
		if (!fs::exists(act)) {
			std::cerr << "Missing actual:   " << act << "\n";
			anyFail = true; continue;
		}
		fs::path diff = fs::path("test") / (std::string("diff_") + p.name);
		long long diffPixels = -1;
		if (!compareWithMetricAE(exp, act, diff, diffPixels)) {
			std::cerr << "Compare failed for: " << p.name << "\n";
			anyFail = true; continue;
		}
		if (diffPixels > 0) {
			std::cout << p.name << ": DIFFER \t(" << diffPixels << " pixels), diff -> " << diff << "\n";
			anyFail = true;
		} else {
			std::cout << p.name << ": OK\n";
		}
	}

	return anyFail ? 1 : 0;
}


