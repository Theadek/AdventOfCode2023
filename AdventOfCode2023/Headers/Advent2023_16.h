#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_set>

namespace Advent2023_16 {

	struct Node {
		int place;
		char sign;
		int visitedDirection;
		Node(int place, char sign) : place(place), sign(sign) {
			visitedDirection = 0;
		};
	};

	struct WorkUnit {
		int x, y;
		int direction;
		WorkUnit(int x, int y, int direction) : x(x), y(y), direction(direction) {}
		// right,	down,	left,	up
		// 1		2		4		8
	};

	void Work(std::vector<std::vector<Node>>& contraptionX, std::vector<std::vector<Node>>& contraptionY, std::vector<WorkUnit>& units, std::unordered_set<int>& visited , int& sizeX, int& sizeY) {
		WorkUnit unit = units.back();
		units.pop_back();
		//Find First Symbol
		Node* tmp = nullptr;
		bool found = false;
		switch (unit.direction) {
		case 1:
			for (int i = 0; i < contraptionX[unit.x].size(); i++) {
				if (unit.y < contraptionX[unit.x][i].place) {
					tmp = &contraptionX[unit.x][i];
					if ((tmp->visitedDirection & unit.direction) != 0) {
						//visited already
						return;
					}
					//place visited
					for (int j = unit.y + 1; j <= tmp->place; j++) {
						visited.emplace(unit.x * 1000 + j);
					}
					tmp->visitedDirection |= unit.direction;
					found = true;
					break;
				}
			}
			if (!found) {
				for (int j = unit.y + 1; j <= sizeX - 1; j++) {
					visited.emplace(unit.x * 1000 + j);
				}
				return;
			}
			break;
		case 2:
			for (int i = 0; i < contraptionY[unit.y].size(); i++) {
				if (unit.x < contraptionY[unit.y][i].place) {
					tmp = &contraptionY[unit.y][i];
					if ((tmp->visitedDirection & unit.direction) != 0) {
						//visited already
						return;
					}
					//place visited
					for (int j = unit.x + 1; j <= tmp->place; j++) {
						visited.emplace(j * 1000 + unit.y);
					}
					tmp->visitedDirection |= unit.direction;
					found = true;
					break;
				}
			}
			if (!found) {
				for (int j = unit.x + 1; j <= sizeY - 1; j++) {
					visited.emplace(j * 1000 + unit.y);
				}
				return;
			}
			break;
		case 4:
			for (int i = contraptionX[unit.x].size() - 1; i >= 0; i--) {
				if (unit.y > contraptionX[unit.x][i].place) {
					tmp = &contraptionX[unit.x][i];
					if ((tmp->visitedDirection & unit.direction) != 0) {
						//visited already
						return;
					}
					//place visited
					for (int j = unit.y - 1; j >= tmp->place; j--) {
						visited.emplace(unit.x * 1000 + j);
					}
					tmp->visitedDirection |= unit.direction;
					found = true;
					break;
				}
			}
			if (!found) {
				for (int j = unit.y - 1; j >= 0; j--) {
					visited.emplace(unit.x * 1000 + j);
				}
				return;
			}
			break;
		case 8:
			for (int i = contraptionY[unit.y].size() - 1; i >= 0; i--) {
				if (unit.x > contraptionY[unit.y][i].place) {
					tmp = &contraptionY[unit.y][i];
					if ((tmp->visitedDirection & unit.direction) != 0) {
						//visited already
						return;
					}
					//place visited
					for (int j = unit.x - 1; j >= tmp->place; j--) {
						visited.emplace(j * 1000 + unit.y);
					}
					tmp->visitedDirection |= unit.direction;
					found = true;
					break;
				}
			}
			if (!found) {
				for (int j = unit.x - 1; j >= 0; j--) {
					visited.emplace(j * 1000 + unit.y);
				}
				return;
			}
			break;
		}

		if (tmp == nullptr)return;

		switch (tmp->sign) {
		case '-':
			if (unit.direction == 1 || unit.direction == 4) units.emplace_back(unit.x, tmp->place, unit.direction);
			else {
				units.emplace_back(tmp->place, unit.y, 1);
				units.emplace_back(tmp->place, unit.y, 4);
			}
			break;
		case '|':
			if (unit.direction == 2 || unit.direction == 8) units.emplace_back(tmp->place, unit.y, unit.direction);
			else {
				units.emplace_back(unit.x, tmp->place, 2);
				units.emplace_back(unit.x, tmp->place, 8);
			}
			break;
		case '/':
			if (unit.direction == 1) units.emplace_back(unit.x, tmp->place, 8);
			else if (unit.direction == 2) units.emplace_back(tmp->place, unit.y, 4);
			else if (unit.direction == 4) units.emplace_back(unit.x, tmp->place, 2);
			else if (unit.direction == 8) units.emplace_back(tmp->place, unit.y, 1);
			break;
		case '\\':
			if (unit.direction == 1) units.emplace_back(unit.x, tmp->place, 2);
			else if (unit.direction == 2) units.emplace_back(tmp->place, unit.y, 1);
			else if (unit.direction == 4) units.emplace_back(unit.x, tmp->place, 8);
			else if (unit.direction == 8) units.emplace_back(tmp->place, unit.y, 4);
			break;
		}

	}

	void CleanNodes(std::vector<std::vector<Node>>& nodes) {
		for (int i = 0; i < nodes.size(); i++) {
			for (int j = 0; j < nodes[i].size(); j++) {
				nodes[i][j].visitedDirection = 0;
			}
		}
	}
}

void Solve2023_16() {

	std::vector<std::vector<Advent2023_16::Node>> contraptionX;
	std::vector<std::vector<Advent2023_16::Node>> contraptionY;

	int contraptionSizeX;
	int contraptionSizeY;
	{
		std::vector<std::string> contraption;
		std::string buffor;
		std::fstream file("Input/Input_16.txt");
		while (!file.eof()) {
			file >> buffor;
			contraption.push_back(buffor);
		}
		file.close();

		contraptionX = std::vector<std::vector<Advent2023_16::Node>>(contraption.size());
		contraptionY = std::vector<std::vector<Advent2023_16::Node>>(contraption[0].length());

		for (int i = 0; i < contraption.size(); i++) {
			for (int j = 0; j < contraption[i].length(); j++) {
				if (contraption[i][j] != '.') {
					contraptionX[i].emplace_back(j, contraption[i][j]);
					contraptionY[j].emplace_back(i, contraption[i][j]);
				}
			}
		}
		contraptionSizeX = contraption[0].length();
		contraptionSizeY = contraption.size();
	}

	std::unordered_set<int> visited;

	std::vector<Advent2023_16::WorkUnit> workUnits;
	workUnits.emplace_back(0, -1, 1);
	while (!workUnits.empty()) {
		Advent2023_16::Work(contraptionX, contraptionY, workUnits, visited, contraptionSizeX, contraptionSizeY);
	}
	int sum = visited.size();
	std::cout << "Advent2023_16_1: " << sum << "\n";

	//---part 2---

	int bestSum = sum;

	for (int i = 1; i < contraptionSizeY; i++) {
		Advent2023_16::CleanNodes(contraptionX);
		Advent2023_16::CleanNodes(contraptionY);
		visited.clear();
		workUnits.emplace_back(i, -1, 1);
		while (!workUnits.empty()) {
			Advent2023_16::Work(contraptionX, contraptionY, workUnits, visited, contraptionSizeX, contraptionSizeY);
		}
		sum = visited.size();
		bestSum = bestSum > sum ? bestSum : sum;
	}
	for (int i = 0; i < contraptionSizeY; i++) {
		Advent2023_16::CleanNodes(contraptionX);
		Advent2023_16::CleanNodes(contraptionY);
		visited.clear();
		workUnits.emplace_back(i, contraptionSizeX, 4);
		while (!workUnits.empty()) {
			Advent2023_16::Work(contraptionX, contraptionY, workUnits, visited, contraptionSizeX, contraptionSizeY);
		}
		sum = visited.size();
		bestSum = bestSum > sum ? bestSum : sum;
	}
	for (int i = 0; i < contraptionSizeX; i++) {
		Advent2023_16::CleanNodes(contraptionX);
		Advent2023_16::CleanNodes(contraptionY);
		visited.clear();
		workUnits.emplace_back(-1, i, 2);
		while (!workUnits.empty()) {
			Advent2023_16::Work(contraptionX, contraptionY, workUnits, visited, contraptionSizeX, contraptionSizeY);
		}
		sum = visited.size();
		bestSum = bestSum > sum ? bestSum : sum;
	}
	for (int i = 0; i < contraptionSizeX; i++) {
		Advent2023_16::CleanNodes(contraptionX);
		Advent2023_16::CleanNodes(contraptionY);
		visited.clear();
		workUnits.emplace_back(contraptionSizeY, i, 8);
		while (!workUnits.empty()) {
			Advent2023_16::Work(contraptionX, contraptionY, workUnits, visited, contraptionSizeX, contraptionSizeY);
		}
		sum = visited.size();
		bestSum = bestSum > sum ? bestSum : sum;
	}

	std::cout << "Advent2023_16_2: " << bestSum << "\n";
}

