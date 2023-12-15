#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2023_15 {
	struct Lens {
	public:
		std::string name;
		int value;

		Lens(std::string name, int value) : name(name), value(value) {}
	};

	int GetHash(std::string& input) {
		int value = 0;
		for (int i = 0; i < input.length(); i++) {
			value += (long long)input[i];
			value *= 17;
			value %= 256;
		}
		return value;
	}
}

void Solve2023_15() {

	std::fstream file("Input/Input_15.txt");
	std::string buffor;
	file >> buffor;
	file.close();

	//buffor = "rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7";

	//---part 1---
	long long sum = 0;
	long long value = 0;
	for (int i = 0; i < buffor.length(); i++) {
		if (buffor[i] == ',') {
			sum += value;
			value = 0;
		}
		else {
			value += (long long)buffor[i];
			value *= 17;
			value %= 256;
		}
	}
	sum += value;

	std::cout << "Advent2023_15_1: " << sum << "\n";


	//---part 2---
	std::vector<std::vector<Advent2023_15::Lens>> boxes(256);

	std::string current = "";
	int hash = 0;
	for (int index = 0; index < buffor.length();) {
		if (buffor[index] == '=') {
			hash = Advent2023_15::GetHash(current);
			bool found = false;
			for (int i = 0; i < boxes[hash].size(); i++) {
				if (boxes[hash][i].name == current) {
					found = true;
					boxes[hash][i].value = (int)(buffor[index + 1] - '0');
					break;
				}
			}
			if (!found) {
				boxes[hash].emplace_back(current, (int)(buffor[index + 1] - '0'));
			}
			index += 3;
			current = "";
		}
		else if (buffor[index] == '-') {
			hash = Advent2023_15::GetHash(current);
			for (int i = 0; i < boxes[hash].size(); i++) {
				if (boxes[hash][i].name == current) {
					boxes[hash].erase(boxes[hash].begin() + i);
					break;
				}
			}
			index += 2;
			current = "";
		}
		else {
			current += buffor[index];
			index++;
		}
	}

	sum = 0;
	//calculate answer;
	for (int i = 0; i < boxes.size(); i++) {
		for (int j = 0; j < boxes[i].size(); j++) {
			sum += ((i + 1) * (j + 1) * (boxes[i][j].value));
		}
	}

	std::cout << "Advent2023_15_2: " << sum << "\n";
}

