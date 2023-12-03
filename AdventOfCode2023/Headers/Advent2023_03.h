#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>

namespace Advent2023_03 {
	bool IsNumber(char& c) {
		return (c >= '0' && c <= '9');
	}
	bool IsSymbol(char& c) {
		if (IsNumber(c)) return false;
		if (c == '.') return false;
		return true;
	}
	int GetFirstNumber(std::string& line, int index) {
		while (index >= 0) {
			if (IsNumber(line[index])) {
				index--;
			}
			else {
				return index + 1;
			}
		}
		return 0;
	}
}

void Solve2023_03() {

	std::vector<std::string> schematic;
	std::map<int, int> numberLocations; // key = 1000 * i + j

	std::fstream file("Input/Input_03.txt");
	while (!file.eof()) {
		std::string buffor;
		file >> buffor;
		schematic.push_back(buffor);
	}
	file.close();

	int sum = 0;
	for (int i = 0; i < schematic.size(); i++) {
		std::string line = schematic[i];
		int index = 0;

		while (index < line.length()) {
			if (!Advent2023_03::IsNumber(line[index])) {
				index++;
				continue;
			}
			else {
				int foundIndex = index;
				int lastIndex = index++;
				for (; index < line.length(); index++) {
					if (Advent2023_03::IsNumber(line[index])) {
						lastIndex = index;
					}
					else {
						index++;
						break;
					}
				}
				bool foundSymbol = false;
				bool canLookUp = i > 0;
				bool canLookDown = i < schematic.size() - 1;
				char c = ',';
				for (int j = foundIndex; j <= lastIndex; j++) {
					bool canLookLeft = j > 0;
					bool canLookRight = j < line.length() - 1;
					if (canLookUp && canLookLeft) {
						c = schematic[i - 1][j - 1];
						if (Advent2023_03::IsSymbol(c)) {
							foundSymbol = true;
							break;
						}
					}
					if (canLookUp) {
						c = schematic[i - 1][j];
						if (Advent2023_03::IsSymbol(c)) {
							foundSymbol = true;
							break;
						}
					}
					if (canLookUp && canLookRight) {
						c = schematic[i - 1][j + 1];
						if (Advent2023_03::IsSymbol(c)) {
							foundSymbol = true;
							break;
						}
					}
					if (canLookDown && canLookLeft) {
						c = schematic[i + 1][j - 1];
						if (Advent2023_03::IsSymbol(c)) {
							foundSymbol = true;
							break;
						}
					}
					if (canLookDown) {
						c = schematic[i + 1][j];
						if (Advent2023_03::IsSymbol(c)) {
							foundSymbol = true;
							break;
						}
					}
					if (canLookDown && canLookRight) {
						c = schematic[i + 1][j + 1];
						if (Advent2023_03::IsSymbol(c)) {
							foundSymbol = true;
							break;
						}
					}
					if (canLookLeft) {
						c = schematic[i][j - 1];
						if (Advent2023_03::IsSymbol(c)) {
							foundSymbol = true;
							break;
						}
					}
					if (canLookRight) {
						c = schematic[i][j + 1];
						if (Advent2023_03::IsSymbol(c)) {
							foundSymbol = true;
							break;
						}
					}

				}
				if (foundSymbol) {
					std::string tmp = line.substr(foundIndex, lastIndex - foundIndex + 1);
					int value = std::stoi(tmp);
					//numberLocations.insert(i * 1000 + foundIndex, value);
					numberLocations[i * 1000 + foundIndex] = value;
					sum += value;
				}
			}


		}
	}

	std::cout << "Advent2023_03_1: " << sum << "\n";

	//---part 2---

	sum = 0;

	for (int i = 0; i < schematic.size(); i++) {
		std::string line = schematic[i];

		for (int j = 0; j < line.length(); j++) {
			if (line[j] == '*') {
				bool canLookUp = j > 0;
				bool canLookDown = i < schematic.size() - 1;
				bool canLookLeft = j > 0;
				bool canLookRight = j < line.length() - 1;
				int neighbors = 0;
				int gearRatio = 1;
				if (canLookLeft) {
					if (Advent2023_03::IsNumber(line[j - 1])) {
						neighbors++;
						gearRatio *= numberLocations[i * 1000 + Advent2023_03::GetFirstNumber(line, j - 1)];
					}
				}
				if (canLookRight) {
					if (Advent2023_03::IsNumber(line[j + 1])) {
						neighbors++;
						gearRatio *= numberLocations[i * 1000 + j + 1];
					}
				}
				if (canLookUp) {
					bool neighborFound = false;
					if (canLookLeft) {
						if (Advent2023_03::IsNumber(schematic[i - 1][j - 1])) {
							neighbors++;
							neighborFound = true;
							gearRatio *= numberLocations.at((i-1) * 1000 + Advent2023_03::GetFirstNumber(schematic[i - 1], j - 1));

							if (!Advent2023_03::IsNumber(schematic[i - 1][j]) && Advent2023_03::IsNumber(schematic[i - 1][j + 1])) {
								neighbors++;
								gearRatio *= numberLocations[(i - 1) * 1000 + j + 1];
							}
						}
					}
					if (!neighborFound) {
						if (Advent2023_03::IsNumber(schematic[i - 1][j])) {
							neighbors++;
							neighborFound = true;
							gearRatio *= numberLocations[(i - 1) * 1000 + j];
						}
					}
					if (!neighborFound && canLookRight) {
						if (Advent2023_03::IsNumber(schematic[i - 1][j + 1])) {
							neighbors++;
							neighborFound = true;
							gearRatio *= numberLocations[(i - 1) * 1000 + j + 1];
						}
					}
				}
				if (canLookDown) {
					bool neighborFound = false;
					if (canLookLeft) {
						if (Advent2023_03::IsNumber(schematic[i + 1][j - 1])) {
							neighbors++;
							neighborFound = true;
							gearRatio *= numberLocations[(i+1) * 1000 + Advent2023_03::GetFirstNumber(schematic[i + 1], j - 1)];

							if (!Advent2023_03::IsNumber(schematic[i + 1][j]) && Advent2023_03::IsNumber(schematic[i + 1][j + 1])) {
								neighbors++;
								gearRatio *= numberLocations[(i + 1) * 1000 + j + 1];
							}
						}
					}
					if (!neighborFound) {
						if (Advent2023_03::IsNumber(schematic[i + 1][j])) {
							neighbors++;
							neighborFound = true;
							gearRatio *= numberLocations[(i + 1) * 1000 + j];
						}
					}
					if (!neighborFound && canLookRight) {
						if (Advent2023_03::IsNumber(schematic[i + 1][j + 1])) {
							neighbors++;
							neighborFound = true;
							gearRatio *= numberLocations[(i + 1) * 1000 + j + 1];
						}
					}
				}


				if (neighbors == 2) {
					sum += gearRatio;
				}
			}
		}
	}

	std::cout << "Advent2023_03_2: " << sum << "\n";
}

