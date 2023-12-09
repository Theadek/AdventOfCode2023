#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<numeric>

namespace Advent2023_08 {
	class Node {
	public:
		std::string left, right;
		Node() {
			left = "";
			right = "";
		}

		Node(std::string left, std::string right) {
			this->left = left;
			this->right = right;
		}
	};
}

void Solve2023_08() {

	std::string leftRight;
	std::map<std::string, Advent2023_08::Node> camelMap;
	std::vector<std::string> ghosts;

	std::fstream file("Input/Input_08.txt");

	file >> leftRight;

	std::string buffor;
	while (!file.eof()) {
		file >> buffor;
		std::string left, right;
		file >> left; // skip ":"
		file >> left >> right;
		left = left.substr(1, 3);
		right = right.substr(0, 3);
		Advent2023_08::Node tmpNode(left, right);
		camelMap[buffor] = tmpNode;

		if (buffor[2] == 'A') {
			ghosts.push_back(buffor);
		}
	}
	file.close();

	buffor = "AAA";
	int step = 0;

	while (buffor.compare("ZZZ") != 0) {
		if (leftRight[step % leftRight.length()] == 'L') {
			buffor = camelMap[buffor].left;
		}
		else {
			buffor = camelMap[buffor].right;
		}
		step++;
	}

	std::cout << "Advent2023_08_1: " << step << "\n";

	//---part 2---
	long long answer = 1;
	for (auto& ghost : ghosts) {
		for (int i = 0; i < 100000; i++) {
			if (leftRight[i % leftRight.length()] == 'L') {
				ghost = camelMap[ghost].left;
			}
			else {
				ghost = camelMap[ghost].right;
			}
			if (ghost[2] == 'Z') {
				answer = std::lcm(answer, i + 1); //(C++17)
				break;
			}
		}
	}

	std::cout << "Advent2023_08_2: " << answer << "\n";
}

