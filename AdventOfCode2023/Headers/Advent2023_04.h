#include<iostream>
#include<fstream>
#include<string>
#include<vector>

void Solve2023_04() {

	std::vector<std::vector<int>> winning, yours;
	std::vector<int> bonus;

	std::fstream file("Input/Input_04.txt");
	std::string buffor;
	file >> buffor >> buffor; // skip Card #:

	while (!file.eof()) {
		std::vector<int> winningTmp;
		while (!file.eof()) {
			file >> buffor;
			if (buffor.compare("|") == 0) {
				break;
			}
			else {
				winningTmp.push_back(std::stoi(buffor));
			}
		}
		winning.push_back(winningTmp);

		std::vector<int> yoursTmp;
		while (!file.eof()) {
			file >> buffor;
			if (buffor.compare("Card") == 0) {
				file >> buffor; //skip #:
				break;
			}
			else {
				yoursTmp.push_back(std::stoi(buffor));
			}
		}
		yours.push_back(yoursTmp);
		bonus.push_back(0);
	}

	file.close();

	int sum = 0;
	int copies = winning.size();

	for (int i = 0; i < winning.size(); i++) {
		int score = 1;
		int copiesWon = 0;
		for (int j = 0; j < winning[i].size(); j++) {
			for (int k = 0; k < yours[i].size(); k++) {
				if (winning[i][j] == yours[i][k]) {
					score *= 2;
					copiesWon++;
					break;
				}
			}
		}
		sum += std::floor(score / 2);

		bonus[i] = copiesWon;
	}

	std::cout << "Advent2023_04_1: " << sum << "\n";

	//---part 2---

	for (int i = winning.size() - 1; i >= 0; i--) {
		int copiesWon = bonus[i];
		for (int j = 0; j < copiesWon; j++) {
			bonus[i] += bonus[i + j + 1];
		}
		copies += bonus[i];
	}

	std::cout << "Advent2023_04_2: " << copies << "\n";
}

