#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_set>
#include<limits.h>


namespace Advent2023_17 {

	struct Node {
		uint64_t value;
		uint64_t goDir[4][3];
		/*
				3
			   2+0
				1
		*/

		Node(uint64_t value, uint64_t n = UINT64_MAX) : value(value) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					goDir[i][j] = n;
				}
			}
		}

	};

	struct NodeUltra {
		uint64_t value;
		uint64_t goDir[4][10];
		/*
				3
			   2+0
				1
		*/

		NodeUltra(uint64_t value, uint64_t n = UINT64_MAX) : value(value) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 10; j++) {
					goDir[i][j] = n;
				}
			}
		}

		void Zero() {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 10; j++) {
					goDir[i][j] = 0;
				}
			}
		}
	};

	struct Pair {
		unsigned int x, y;
		Pair() {
			x = 0, y = 0;
		}
		Pair(unsigned int x, unsigned int y) : x(x), y(y) {}

		bool operator==(const Pair& otherPair) const {
			return otherPair.x == x && otherPair.y == y;
		}

		struct HashFunction {
			size_t operator()(const Pair& pair) const {
				size_t xHash = std::hash<unsigned int>()(pair.x);
				size_t yHash = std::hash<unsigned int>()(pair.y) << 1;
				return xHash ^ yHash;
			}
		};
	};

	Pair GetNeightborPair(Pair& from, size_t dir) {
		size_t x = from.x, y = from.y;
		switch (dir) {
		case 0:
			y++;
			break;
		case 1:
			x++;
			break;
		case 2:
			y--;
			break;
		case 3:
			x--;
			break;
		}

		return Pair(x, y);
	}

	Node* GetNeighborNode(std::vector<std::vector<Node>>& heatMap, Pair& from, size_t dir) {
		size_t x = from.x, y = from.y;
		switch (dir) {
		case 0:
			y++;
			break;
		case 1:
			x++;
			break;
		case 2:
			y--;
			break;
		case 3:
			x--;
			break;
		}
		if (x < 0 || x >= heatMap[0].size() || y < 0 || y >= heatMap.size())return nullptr;

		return &heatMap[x][y];
	}

	NodeUltra* GetNeighborNodeUltra(std::vector<std::vector<NodeUltra>>& heatMap, Pair& from, size_t dir) {
		size_t x = from.x, y = from.y;
		switch (dir) {
		case 0:
			y++;
			break;
		case 1:
			x++;
			break;
		case 2:
			y--;
			break;
		case 3:
			x--;
			break;
		}
		if (x < 0 || x >= heatMap[0].size() || y < 0 || y >= heatMap.size())return nullptr;

		return &heatMap[x][y];
	}


	void Step(std::vector<std::vector<Node>>& heatMap, std::unordered_set<Pair, Pair::HashFunction>& toCheck) {
		Pair pair = toCheck.extract(toCheck.begin()).value();
		//std::cout << pair.y << "\t" << pair.x << "\n";
		Node* node = &heatMap[pair.x][pair.y];
		Node* neighbors[4];
		for (int i = 0; i < 4; i++) {
			neighbors[i] = GetNeighborNode(heatMap, pair, i);
		}

		for (size_t i = 0; i < 4; i++) {		// i - direction
			for (size_t j = 0; j < 3; j++) {	// j - power
				if (node->goDir[i][j] == UINT64_MAX)continue;

				Node* tmp;
				int dir;
				// go left
				dir = (i + 4 -1) % 4;
				tmp = neighbors[dir];
				if (tmp != nullptr) {
					int value = tmp->value + node->goDir[i][j];
					if (tmp->goDir[dir][0] > value) {
						tmp->goDir[dir][0] = value;
						toCheck.insert(GetNeightborPair(pair, dir));
					}
				}
				// go right
				dir = (i + 4 + 1) % 4;
				tmp = neighbors[dir];
				if (tmp != nullptr) {
					int value = tmp->value + node->goDir[i][j];
					if (tmp->goDir[dir][0] > value) {
						tmp->goDir[dir][0] = value;
						toCheck.insert(GetNeightborPair(pair, dir));
					}
				}
				// go straight
				if (j == 2)continue;
				tmp = neighbors[i];
				if (tmp != nullptr) {
					int value = tmp->value + node->goDir[i][j];
					if (tmp->goDir[i][j+1] > value) {
						tmp->goDir[i][j+1] = value;
						toCheck.insert(GetNeightborPair(pair, i));
					}
				}

			}
		}
	}

	void StepUltra(std::vector<std::vector<NodeUltra>>& heatMap, std::unordered_set<Pair, Pair::HashFunction>& toCheck) {
		Pair pair = toCheck.extract(toCheck.begin()).value();
		//std::cout << pair.y << "\t" << pair.x << "\n";
		NodeUltra* node = &heatMap[pair.x][pair.y];
		NodeUltra* neighbors[4];
		for (int i = 0; i < 4; i++) {
			neighbors[i] = GetNeighborNodeUltra(heatMap, pair, i);
		}

		for (size_t i = 0; i < 4; i++) {		// i - direction
			for (size_t j = 0; j < 10; j++) {	// j - power
				if (node->goDir[i][j] == UINT64_MAX)continue;

				NodeUltra* tmp;
				int dir;

				if (j >= 3) {
					// go left
					dir = (i + 4 - 1) % 4;
					tmp = neighbors[dir];
					if (tmp != nullptr) {
						int value = tmp->value + node->goDir[i][j];
						if (tmp->goDir[dir][0] > value) {
							tmp->goDir[dir][0] = value;
							toCheck.insert(GetNeightborPair(pair, dir));
						}
					}
					// go right
					dir = (i + 4 + 1) % 4;
					tmp = neighbors[dir];
					if (tmp != nullptr) {
						int value = tmp->value + node->goDir[i][j];
						if (tmp->goDir[dir][0] > value) {
							tmp->goDir[dir][0] = value;
							toCheck.insert(GetNeightborPair(pair, dir));
						}
					}
				}

				// go straight
				if (j == 9)continue;
				tmp = neighbors[i];
				if (tmp != nullptr) {
					int value = tmp->value + node->goDir[i][j];
					if (tmp->goDir[i][j + 1] > value) {
						tmp->goDir[i][j + 1] = value;
						toCheck.insert(GetNeightborPair(pair, i));
					}
				}

			}
		}
	}

	void InitializeUltra(std::vector<std::vector<NodeUltra>>& heatMap, std::unordered_set<Pair, Pair::HashFunction>& toCheck) {
		NodeUltra* node = &heatMap[0][0];
		NodeUltra* tmp;

		tmp = &heatMap[0][1];
		tmp->goDir[0][0] = tmp->value;
		toCheck.emplace(0, 1);

		tmp = &heatMap[1][0];
		tmp->goDir[1][0] = tmp->value;
		toCheck.emplace(1, 0);
	}
}

void Solve2023_17() {

	std::vector<std::vector<Advent2023_17::Node>> heatMap;
	std::vector<std::vector<Advent2023_17::NodeUltra>> heatMapUltra;
	std::string buffor;
	std::fstream file("Input/Input_17.txt");
	while (!file.eof()) {
		file >> buffor;
		std::vector<Advent2023_17::Node> line;
		std::vector<Advent2023_17::NodeUltra> lineUltra;
		for (int i = 0; i < buffor.length(); i++) {
			line.emplace_back(buffor[i] - '0');
			lineUltra.emplace_back(buffor[i] - '0');
		}
		heatMap.push_back(line);
		heatMapUltra.push_back(lineUltra);
	}
	file.close();

	std::unordered_set<Advent2023_17::Pair, Advent2023_17::Pair::HashFunction> toCheck;
	Advent2023_17::Pair startPair(0, 0);
	toCheck.insert(startPair);

	heatMap[0][0] = Advent2023_17::Node(heatMap[0][0].value, 0);


	while (!toCheck.empty()) {
		Advent2023_17::Step(heatMap, toCheck);
	}

	uint64_t answer = UINT64_MAX;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (answer > heatMap[heatMap.size() - 1][heatMap[0].size() - 1].goDir[i][j]) {
				answer = heatMap[heatMap.size() - 1][heatMap[0].size() - 1].goDir[i][j];
			}
		}
	}
	std::cout << "Advent2023_17_1: " << answer << "\n";

	//---part 2---

	std::unordered_set<Advent2023_17::Pair, Advent2023_17::Pair::HashFunction> toCheck2;

	heatMapUltra[0][0].Zero();
	Advent2023_17::InitializeUltra(heatMapUltra, toCheck2);

	while (!toCheck2.empty()) {
		Advent2023_17::StepUltra(heatMapUltra, toCheck2);
	}

	answer = UINT64_MAX;
	for (int i = 0; i < 4; i++) {
		for (int j = 4; j < 10; j++) {
			if (answer > heatMapUltra[heatMapUltra.size() - 1][heatMapUltra[0].size() - 1].goDir[i][j]) {
				answer = heatMapUltra[heatMapUltra.size() - 1][heatMapUltra[0].size() - 1].goDir[i][j];
			}
		}
	}
	std::cout << "Advent2023_17_2: " << answer << "\n";
}

