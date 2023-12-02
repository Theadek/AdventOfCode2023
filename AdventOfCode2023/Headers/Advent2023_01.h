#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2023_01 {

	int CheckWords(std::string& line, int index) {
		// 3 - one, two, six
		// 4 - four, five, nine		- zero
		// 5 - three, seven, eight

		bool fiveAble, fourAble, threeAble;

		if (line.length() - index >= 5) {
			fiveAble = fourAble = threeAble = true;
		}
		else if (line.length() - index == 4) {
			fiveAble = false;
			fourAble = threeAble = true;
		}
		else if (line.length() - index == 3) {
			fiveAble = fourAble = false;
			threeAble = true;
		}
		else {
			fiveAble = fourAble = threeAble = false;
		}

		if (fiveAble) {
			std::string test = line.substr(index, 5);
			if (test.compare("three") == 0) return 3;
			if (test.compare("seven") == 0) return 7;
			if (test.compare("eight") == 0) return 8;
		}
		if (fourAble) {
			std::string test = line.substr(index, 4);
			if (test.compare("zero") == 0) return 0;
			if (test.compare("four") == 0) return 4;
			if (test.compare("five") == 0) return 5;
			if (test.compare("nine") == 0) return 9;
		}
		if (threeAble) {
			std::string test = line.substr(index, 3);
			if (test.compare("one") == 0) return 1;
			if (test.compare("two") == 0) return 2;
			if (test.compare("six") == 0) return 6;
		}
		return -1;
	}

}

void Solve2023_01() {

	std::fstream file("Input/Input_01.txt");
	int sum = 0;

	while (!file.eof()) {
		int decimal = -1, unit = -1;
		std::string s;
		file >> s;

		for (size_t i = 0; i < s.length(); i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				if (decimal == -1) {
					decimal = s[i] - '0';
					unit = s[i] - '0';
				}
				else {
					unit = s[i] - '0';
				}
			}
		}
		sum += decimal * 10 + unit;
	}
	file.close();

	std::cout << "Advent2023_01_1:" << sum << "\n";

	//---part 2---

	file.open("Input/Input_01.txt");

	sum = 0;

	while (!file.eof()) {
		int decimal = -1, unit = -1;
		std::string s;
		file >> s;

		for (size_t i = 0; i < s.length(); i++) {
			if (s[i] >= '0' && s[i] <= '9') {
				if (decimal == -1) {
					decimal = s[i] - '0';
					unit = s[i] - '0';
				}
				else {
					unit = s[i] - '0';
				}
			}
			else {
				int value = Advent2023_01::CheckWords(s, i);
				if (value != -1) {
					if (decimal == -1) {
						decimal = value;
						unit = value;
					}
					else {
						unit = value;
					}
				}
			}
		}
		sum += decimal * 10 + unit;
	}

	file.close();
	std::cout << "Advent2023_01_2:" << sum << "\n";
}

