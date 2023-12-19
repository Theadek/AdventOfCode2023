#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

namespace Advent2023_18 {
	struct Node {
		int from, to;
		bool isDouble;

		Node(int from, int to, bool isDouble) : from(from), to(to), isDouble(isDouble) {}

		inline bool operator<(const Node& node) const {
			return from < node.from;
		}
	};

	struct Line {
		int64_t column;
		int64_t from, to;
		bool excludeTop, excludeBottom;
		bool good;

		Line(int64_t column, int64_t from, int64_t to, bool excludeTop, bool excludeBottom) :
			column(column), from(from), to(to), excludeTop(excludeTop), excludeBottom(excludeBottom) {
			good = true;
		}

		inline bool operator<(const Line& line) const {
			if (column == line.column) {
				return from < line.from;
			}
			return column < line.column;
		}
	};

	struct Pair {
		int x, y;
		Pair(int x, int y) : x(x), y(y) {}
	};

}

void Solve2023_18() {

	std::string directions = "RDLU";

	//---part 1---
	std::vector<std::string> commands;
	std::vector<int> numbers;
	std::string buffor;
	std::vector<std::vector<Advent2023_18::Node>> trenches;

	//---part 2---
	std::vector<std::string> commands2;
	std::vector<int64_t> numbers2;
	std::vector<Advent2023_18::Line> trenches2;
	int64_t answer2 = 0;

	//---process input file---

	std::fstream file("Input/Input_18.txt");
	while (!file.eof()) {
		//p1
		file >> buffor;
		commands.push_back(buffor);
		file >> buffor;
		numbers.push_back(std::stoi(buffor));
		//p2
		file >> buffor;
		int64_t tmpNumber = std::stoll(buffor.substr(2, buffor.size() - 4), nullptr, 16);
		answer2 += tmpNumber; // add board frame
		numbers2.push_back(tmpNumber);
		buffor = buffor.substr(buffor.size() - 2, 1);
		buffor = directions[std::stoi(buffor)];
		commands2.push_back(buffor);
	}
	file.close();

	//---part 1 get max up/down---
	int max = 0, current = 0, min = 0;
	for (size_t i = 0; i < commands.size(); i++) {
		if (commands[i] == "U") {
			current += numbers[i];
			if (max < current)
				max = current;
		}
		if (commands[i] == "D") {
			current -= numbers[i];
			if (min > current)
				min = current;
		}
	}
	int size = max - min + 1;
	int currentY = max;
	int currentX = 0;

	//---part 1 prepare Node vector---
	trenches = std::vector<std::vector<Advent2023_18::Node>>(size);
	for (int i = 0; i < commands.size(); i++) {
		if (commands[i] == "R") {
			trenches[currentY].emplace_back(currentX, currentX + numbers[i], true);
			currentX += numbers[i];
		}
		else if (commands[i] == "L") {
			trenches[currentY].emplace_back(currentX - numbers[i], currentX, true);
			currentX -= numbers[i];
		}
		else if (commands[i] == "D") {
			for (size_t j = 0; j < numbers[i] - 1; j++) {
				trenches[++currentY].emplace_back(currentX, currentX, false);
			}
			currentY++;
		}
		else if (commands[i] == "U") {
			for (size_t j = 0; j < numbers[i] - 1; j++) {
				trenches[--currentY].emplace_back(currentX, currentX, false);
			}
			currentY--;
		}
	}

	// sort all trenches
	for (size_t i = 0; i < trenches.size(); i++) {
		std::sort(trenches[i].begin(), trenches[i].end());
	}

	// get board size
	int minimum_x = 0;
	int maximum_x = 0; //todo delete?
	for (size_t i = 0; i < trenches.size(); i++) {
		if (minimum_x > trenches[i][0].from)
			minimum_x = trenches[i][0].from;
		if (maximum_x > trenches[i][trenches[i].size() - 1].to)
			maximum_x = trenches[i][trenches[i].size() - 1].to;

	}

	// draw board
	if (false) {
		for (size_t i = 0; i < trenches.size(); i++) {
			int current_index = minimum_x;
			for (size_t j = 0; j < trenches[i].size(); j++) {

				for (size_t k = 0; k < trenches[i][j].from - current_index; k++) {
					std::cout << " ";
				}

				for (size_t k = 0; k < trenches[i][j].to - trenches[i][j].from + 1; k++) {
					std::cout << "#";
				}
				current_index = trenches[i][j].to + 1;
			}
			std::cout << "\n";
		}
	}



	// count
	int answer = 0;
	for (size_t i = 0; i < trenches.size(); i++) {
		bool open = true;
		int lines = 0;
		for (size_t j = 0; j < trenches[i].size(); j++) {
			if (trenches[i][j].isDouble) lines += 2;
			else lines += 1;
		}
		for (size_t j = 0; j < trenches[i].size() - 1; j++) {

			// if is double a loop
			//
			// ###      # #
			// # #  or  # #
			// # #      ###
			//

			if (trenches[i][j].isDouble) {
				bool leftUp = false;
				bool rightUp = false;
				if (i > 0) {
					for (int x = 0; x < trenches[i - 1].size(); x++) {
						if (trenches[i - 1][x].to == trenches[i][j].from) leftUp = true;
						if (trenches[i - 1][x].from == trenches[i][j].to) rightUp = true;
					}
				}
				if ((leftUp == rightUp)) {
					open = !open;
				}
			}


			if (open) {
				answer += trenches[i][j + 1].from - trenches[i][j].to - 1;
			}

			open = !open;

			if (trenches[i][j].isDouble) lines -= 2;
			else lines -= 1;
		}
		answer += trenches[i].size();
		for (size_t j = 0; j < trenches[i].size(); j++) {
			answer += trenches[i][j].to - trenches[i][j].from;
		}
	}

	std::cout << "Advent2023_18_1: " << answer << "\n";

	//---part 2---

	//prepare line vector
	int64_t currentX2 = 0, currentY2 = 0;
	for (size_t i = 0; i < numbers2.size(); i++) {
		if (commands2[i] == "R") {
			currentX2 += numbers2[i];
		}
		else if (commands2[i] == "L") {
			currentX2 -= numbers2[i];
		}
		else if (commands2[i] == "D") {
			int64_t column = currentX2, top = currentY2, down = currentY2 + numbers2[i];
			bool exTop, exBot;
			if (i == 0) {
				if (commands2[commands2.size() - 1] == "R")
					exTop = false;
				else
					exTop = true;
			}
			else {
				if (commands2[i - 1] == "R")
					exTop = false;
				else
					exTop = true;

			}
			if (i == numbers2.size() - 1) {
				if (commands2[0] == "R")
					exBot = true;
				else
					exBot = false;
			}
			else {
				if (commands2[i + 1] == "R")
					exBot = true;
				else
					exBot = false;
			}
			trenches2.emplace_back(column, top, down, exTop, exBot);
			currentY2 += numbers2[i];
		}
		else { // =="U"
			int64_t column = currentX2, top = currentY2 - numbers2[i], down = currentY2;
			bool exTop, exBot;
			if (i == 0) {
				if (commands2[commands2.size() - 1] == "R")
					exBot = false;
				else
					exBot = true;
			}
			else {
				if (commands2[i - 1] == "R")
					exBot = false;
				else
					exBot = true;

			}
			if (i == numbers2.size() - 1) {
				if (commands2[0] == "R")
					exTop = true;
				else
					exTop = false;
			}
			else {
				if (commands2[i + 1] == "R")
					exTop = true;
				else
					exTop = false;
			}
			trenches2.emplace_back(column, top, down, exTop, exBot);
			currentY2 -= numbers2[i];
		}
		//"U"
	}
	//sort line vector

	std::sort(trenches2.begin(), trenches2.end());

	//count line vector

	for (int line = 0; line < trenches2.size() - 1; line++) {
		if (!trenches2[line].good) continue;

		std::vector<Advent2023_18::Pair> toCheck;
		int x = trenches2[line].from;
		int y = trenches2[line].to;
		if (trenches2[line].excludeTop) x++;
		if (trenches2[line].excludeBottom) y--;
		toCheck.emplace_back(x, y);
		while (!toCheck.empty()) {
			x = toCheck.back().x;
			y = toCheck.back().y;
			for (int i = line + 1; i < trenches2.size(); i++) {
				if (trenches2[i].column == trenches2[line].column) continue;
				if (trenches2[i].to < x || trenches2[i].from > y) continue;

				if (trenches2[i].from <= x) {
					if (trenches2[i].to >= y) {
						answer2 += (y - x + 1) * (trenches2[i].column - trenches2[line].column - 1);
						toCheck.pop_back();
					}
					else {
						answer2 += (trenches2[i].to - x + 1) * (trenches2[i].column - trenches2[line].column - 1);
						toCheck[toCheck.size() - 1].x = trenches2[i].to + 1;
					}
				}
				else {
					if (trenches2[i].to >= y) {
						answer2 += (y - trenches2[i].from + 1) * (trenches2[i].column - trenches2[line].column - 1);
						toCheck[toCheck.size() - 1].y = trenches2[i].from - 1;
					}
					else {
						answer2 += (trenches2[i].to - trenches2[i].from + 1) * (trenches2[i].column - trenches2[line].column - 1);
						toCheck[toCheck.size() - 1].y = trenches2[i].from - 1;
						toCheck.emplace_back(trenches2[i].to + 1, y);
					}
				}

				trenches2[i].good = false;
				break;

			}
		}

	}

	std::cout << "Advent2023_18_2: " << answer2 << "\n";
}

