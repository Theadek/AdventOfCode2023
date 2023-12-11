#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

namespace Advent2023_11 {

	struct Node {
		long long x, y;
		Node() {
			x = 0, y = 0;
		}
		Node(long long x, long long y) : x(x), y(y) {}

		inline bool operator < (const Node& node) const {
			if (x == node.x) {
				return y < node.y;
			}
			else {
				return x < node.x;
			}
		}

		inline Node operator - (const Node& node) const {
			return Node(x - node.x, y - node.y);
		}

	};

	void ExpandWorld(std::vector<Node>& galaxies, int sizeX, int sizeY, long long add) {
		int index = galaxies.size() - 1;
		for (int i = sizeX-1; i >= 0 ; i--) {
			while (index >= 0) {
				if (galaxies[index].x == i) {
					break;
				}
				else if (galaxies[index].x < i) {
					for (int j = index + 1; j < galaxies.size(); j++) {
						galaxies[j].x += add;
					}
					break;
				}
				else {
					index--;
				}
			}
		}

		for (int i = sizeY-1; i >= 0 ; i--) {
			bool found = false;
			for (int j = 0; j < galaxies.size(); j++) {
				if (galaxies[j].y == i) {
					found = true;
					break;
				}
			}
			if (!found) {
				for (int j = 0; j < galaxies.size(); j++) {
					if (galaxies[j].y > i) {
						galaxies[j].y += add;
					}
				}
			}
		}
	}

	long long FindPathLength(Node A, Node B) {
		Node C = A - B;
		return std::abs(C.x) + std::abs(C.y);
	}
}

void Solve2023_11() {

	std::vector<std::string> world;
	std::vector<Advent2023_11::Node> galaxies;
	std::vector<Advent2023_11::Node> galaxies2;
	std::string buffor;

	std::fstream file("Input/Input_11.txt");

	while (!file.eof()) {
		file >> buffor;
		world.push_back(buffor);
	}
	file.close();

	for (int i = 0; i < world.size(); i++) {
		for (int j = 0; j < world[i].length(); j++) {
			if (world[i][j] == '#') {
				galaxies.emplace_back(i, j);
			}
		}
	}

	std::sort(galaxies.begin(), galaxies.end());
	galaxies2 = galaxies;


	Advent2023_11::ExpandWorld(galaxies, world.size(), world[0].length(), 1);
	long long sum = 0;
	for (int i = 0; i < galaxies.size() - 1; i++) {
		for (int j = i + 1; j < galaxies.size(); j++) {
			sum += Advent2023_11::FindPathLength(galaxies[i], galaxies[j]);
		}
	}
	std::cout << "Advent2023_11_1: " << sum << "\n";

	Advent2023_11::ExpandWorld(galaxies2, world.size(), world[0].length(), 999999);
	sum = 0;
	for (int i = 0; i < galaxies2.size() - 1; i++) {
		for (int j = i + 1; j < galaxies2.size(); j++) {
			sum += Advent2023_11::FindPathLength(galaxies2[i], galaxies2[j]);
		}
	}
	std::cout << "Advent2023_11_2: " << sum << "\n";
}

