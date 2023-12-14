#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2023_14 {
	void MoveNorth(std::vector<std::string>& platform) {
		for (int i = 0; i < platform[0].length(); i++) {
			int lastEmpty = 0;
			for (int j = 0; j < platform.size(); j++) {
				if (platform[j][i] == '#') {
					lastEmpty = j + 1;
				}
				else if (platform[j][i] == 'O') {
					//swap
					if (lastEmpty != j) {
						char tmp = platform[lastEmpty][i];
						platform[lastEmpty][i] = platform[j][i];
						platform[j][i] = tmp;
					}
					lastEmpty++;
				}
			}
		}
	}
	void MoveWest(std::vector<std::string>& platform) {
		for (int j = 0; j < platform.size(); j++) {
			int lastEmpty = 0;
			for (int i = 0; i < platform[j].length(); i++) {
				if (platform[j][i] == '#') {
					lastEmpty = i + 1;
				}
				else if (platform[j][i] == 'O') {
					//swap
					if (lastEmpty != i) {
						char tmp = platform[j][lastEmpty];
						platform[j][lastEmpty] = platform[j][i];
						platform[j][i] = tmp;
					}
					lastEmpty++;
				}
			}
		}
	}
	void MoveSouth(std::vector<std::string>& platform) {
		for (int i = 0; i < platform[0].length(); i++) {
			int lastEmpty = platform.size()-1;
			for (int j = platform.size()-1; j >=0 ; j--) {
				if (platform[j][i] == '#') {
					lastEmpty = j - 1;
				}
				else if (platform[j][i] == 'O') {
					//swap
					if (lastEmpty != j) {
						char tmp = platform[lastEmpty][i];
						platform[lastEmpty][i] = platform[j][i];
						platform[j][i] = tmp;
					}
					lastEmpty--;
				}
			}
		}
	}
	void MoveEast(std::vector<std::string>& platform) {
		for (int j = 0; j < platform.size(); j++) {
			int lastEmpty = platform[j].length() - 1;
			for (int i = platform[j].length() - 1; i >=0 ; i--) {
				if (platform[j][i] == '#') {
					lastEmpty = i - 1;
				}
				else if (platform[j][i] == 'O') {
					//swap
					if (lastEmpty != i) {
						char tmp = platform[j][lastEmpty];
						platform[j][lastEmpty] = platform[j][i];
						platform[j][i] = tmp;
					}
					lastEmpty--;
				}
			}
		}
	}

	void SpinCycle(std::vector<std::string>& platform) {
		MoveNorth(platform);
		MoveWest(platform);
		MoveSouth(platform);
		MoveEast(platform);
	}

	void FinishCycle(std::vector<std::string>& platform) {
		MoveWest(platform);
		MoveSouth(platform);
		MoveEast(platform);
	}

	int LoadOnNorth(std::vector<std::string>& platform) {
		int sum = 0;
		for (int i = 0; i < platform.size(); i++) {
			sum += std::count(platform[i].begin(), platform[i].end(), 'O') * (platform.size() - i);
		}
		return sum;
	}

	//--part--2

	class Platform {
	private:
		std::vector<std::vector<int>> Orows;
		std::vector<std::vector<int>> Ocolumns;
		std::vector<std::vector<int>> Hrows;
		std::vector<std::vector<int>> Hcolumns;
		int rowSize, columnSize;

		void MoveUp() {
			Orows.clear();
			Orows = std::vector<std::vector<int>>(rowSize);

			for (int i = 0; i < Ocolumns.size(); i++) {
				int currentBest = -1;
				int indexH = 0;
				for (int j = 0; j < Ocolumns[i].size(); j++) {
					for (; indexH < Hcolumns[i].size();) {
						if (Hcolumns[i][indexH] < Ocolumns[i][j]) {
							currentBest = Hcolumns[i][indexH];
							indexH++;
						}
						else {
							break;
						}
					}
					//Ocolumns[i][j] = currentBest + 1;
					Orows[currentBest + 1].push_back(i);
					currentBest++;
				}
			}
		}

		void MoveLeft() {
			Ocolumns.clear();
			Ocolumns = std::vector<std::vector<int>>(columnSize);

			for (int i = 0; i < Orows.size(); i++) {
				int currentBest = -1;
				int indexH = 0;
				for (int j = 0; j < Orows[i].size(); j++) {
					for (; indexH < Hrows[i].size();) {
						if (Hrows[i][indexH] < Orows[i][j]) {
							currentBest = Hrows[i][indexH];
							indexH++;
						}
						else {
							break;
						}
					}
					//Orows[i][j] = currentBest + 1;
					Ocolumns[currentBest + 1].push_back(i);
					currentBest++;
				}
			}
		}

		void MoveDown() {
			Orows.clear();
			Orows = std::vector<std::vector<int>>(rowSize);

			for (int i = 0; i < Ocolumns.size(); i++) {
				int currentBest = columnSize;
				int indexH = Hcolumns[i].size() - 1;
				for (int j = Ocolumns[i].size() - 1; j >= 0; j--) {
					for (; indexH >= 0 ;) {
						if (Hcolumns[i][indexH] > Ocolumns[i][j]) {
							currentBest = Hcolumns[i][indexH];
							indexH--;
						}
						else {
							break;
						}
					}
					//Ocolumns[i][j] = currentBest - 1;
					Orows[currentBest - 1].push_back(i);
					currentBest--;
				}
			}

			/*for (int i = 0; i < Orows.size(); i++) {
				std::reverse(Orows[i].begin(), Orows[i].end());
			}*/
		}

		void MoveRight() {
			Ocolumns.clear();
			Ocolumns = std::vector<std::vector<int>>(columnSize);

			for (int i = 0; i < Orows.size(); i++) {
				int currentBest = rowSize;
				int indexH = Hrows[i].size() - 1;
				for (int j = Orows[i].size() - 1; j >= 0; j--) {
					for (; indexH >= 0 ;) {
						if (Hrows[i][indexH] > Orows[i][j]) {
							currentBest = Hrows[i][indexH];
							indexH--;
						}
						else {
							break;
						}
					}
					Orows[i][j] = currentBest - 1;
					Ocolumns[currentBest - 1].push_back(i);
					currentBest--;
				}
			}

			/*for (int i = 0; i < Ocolumns.size(); i++) {
				std::reverse(Ocolumns[i].begin(), Ocolumns[i].end());
			}*/
		}


	public:
		Platform() = delete;
		Platform (std::vector<std::string>& dish) {
			rowSize = dish.size();
			columnSize = dish[0].length();
			Orows = std::vector<std::vector<int>>(rowSize);
			Ocolumns = std::vector<std::vector<int>>(columnSize);
			Hrows = std::vector<std::vector<int>>(rowSize);
			Hcolumns = std::vector<std::vector<int>>(columnSize);

			for (int i = 0; i < dish.size(); i++) {
				for (int j = 0; j < dish[i].length(); j++) {
					if (dish[i][j] == 'O') {
						Orows[i].push_back(j);
						Ocolumns[j].push_back(i);
					}
					else if (dish[i][j] == '#') {
						Hrows[i].push_back(j);
						Hcolumns[j].push_back(i);
					}
				}
			}
		}

		void Cycle() {
			// up left down right
			MoveUp();
			MoveLeft();
			MoveDown();
			MoveRight();
		}

		int LoadNorth() {
			int answer = 0;
			for (int i = 0; i < Ocolumns.size(); i++) {
				for (int j = 0; j < Ocolumns[i].size(); j++) {
					answer += rowSize - Ocolumns[i][j];
				}
			}
			return answer;
		}
	};

	bool FindCycle(std::vector<int>& answers, int& cycleLength, int& cycleOffset) {
		bool cycleExist = false;

		for (int i = 5; i < answers.size() / 2; i++) {
			bool found = true;
			for (int j = 0; j < i; j++) {
				if (answers[answers.size() - 1 - j] != answers[answers.size() - 1 - j - i]) {
					found = false;
					break;
				}
			}
			if (found) {
				cycleLength = i;
				cycleOffset = answers.size() - (2 * cycleLength);
				cycleExist = true;
			}
		}

		return cycleExist;
	}
}

void Solve2023_14() {

	std::vector<std::string> dish;
	{
		std::string buffor;
		//---input---
		std::fstream file("Input/Input_14.txt");

		while (!file.eof()) {
			file >> buffor;
			dish.push_back(buffor);
		}
		file.close();
	}
	Advent2023_14::Platform platform(dish);

	//---part 1---
	Advent2023_14::MoveNorth(dish);
	int answer = Advent2023_14::LoadOnNorth(dish);
	std::cout << "Advent2023_14_1: " << answer << "\n";

	//---part 2---
	std::vector<int> answers;
	int tmp = 0;

	int cycleOffset = 0;
	int cycleLength = 0;

	for (int i = 0; i < 1000000000; i++) {
		platform.Cycle();
		answers.push_back(platform.LoadNorth());

		if (Advent2023_14::FindCycle(answers, cycleLength, cycleOffset)) {
			break;
		}
	}
	answer = answers[cycleOffset + ((1000000000 - cycleOffset-1) % cycleLength)];
	std::cout << "Advent2023_14_2: " << answer << "\n";
}

