#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2023_02 {

}

void Solve2023_02() {

	std::fstream file("Input/Input_02.txt");

	const int numberOfLines = 5;
	const int redCubes = 12;
	const int greenCubes = 13;
	const int blueCubes = 14;


	int index = 1;
	int value;
	std::string color;
	file >> color >> color; //skip Game #:

	int sum = 0;
	bool badGame = false;
	bool lastOne = false;

	while (!file.eof()) {
		file >> value >> color;

		if (color[color.length() - 1] != ',' && color[color.length() - 1] != ';') {
			lastOne = true;
		}
		else {
			color = color.substr(0, color.length() - 1);
		}

		if (color.compare("red") == 0) {
			if (value > redCubes) badGame = true;
		}
		else if (color.compare("green") == 0) {
			if (value > greenCubes) badGame = true;
		}
		else if (color.compare("blue") == 0) {
			if (value > blueCubes) badGame = true;
		}

		if (lastOne) {
			if (!badGame) sum += index;
			badGame = false;
			lastOne = false;
			index++;
			file >> color >> color; // skip Game #:
		}

	}

	file.close();

	std::cout << "Advent2023_02_1: " << sum << "\n";

	//---part 2---

	file.open("Input/Input_02.txt");

	file >> color >> color; //skip Game #:

	sum = 0;
	int red = 0, blue = 0, green = 0;

	lastOne = false;

	while (!file.eof()) {
		file >> value >> color;

		if (color[color.length() - 1] != ',' && color[color.length() - 1] != ';') {
			lastOne = true;
		}
		else {
			color = color.substr(0, color.length() - 1);
		}

		if (color.compare("red") == 0) {
			if (value > red) red = value;
		}
		else if (color.compare("green") == 0) {
			if (value > green) green = value;
		}
		else if (color.compare("blue") == 0) {
			if (value > blue) blue = value;
		}

		if (lastOne) {
			sum += (red * green * blue);

			red = green = blue = 0;
			lastOne = false;
			file >> color >> color; // skip Game #:
		}
	}

	file.close();

	std::cout << "Advent2023_02_2: " << sum << "\n";
}

