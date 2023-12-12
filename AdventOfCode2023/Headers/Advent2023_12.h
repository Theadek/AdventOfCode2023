#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2023_12 {
	bool CheckMatching(std::string& line, std::string& test, int lineStart) {
		for (int i = 0; i < test.length(); i++) {
			if (line[i + lineStart] != test[i] && line[i + lineStart] != '?') {
				return false;
			}
		}
		return true;
	}

	long long GetAnswer(std::string& line, std::vector<long long>& numbers) {
		std::string buffor = "";
		std::vector<std::vector<long long>> tab;
		std::vector<long long> tab_tmp(line.length(), 0);
		for (int i = 0; i < numbers.size(); i++) {
			tab.push_back(tab_tmp);
		}

		// last number
		int start = 0, stop = line.length() - numbers[numbers.size()-1];
		for (int i = 0; i < numbers.size() - 1; i++) {
			start += numbers[i] + 1;
		}
		buffor = std::string(numbers[numbers.size() - 1], '#');
		for (int i = 0; i <= stop - start; i++) {			//per tab[0][i]
			int index = stop - i;
			if (i != 0) {
				if (line[line.length() - i] == '#') {		//should be '.' or '?'
					for (int x = index; x >= 0; x--) {
						if (line[x] != '#')
							tab[numbers.size() - 1][x] = tab[numbers.size() - 1][index + 1];
						else
							break;
					}
					break;
				}
			}
			if (CheckMatching(line, buffor, index)) {
				tab[numbers.size() - 1][index]++;
			}
			if (i != 0) {
				if (line[index] != '#') {
					tab[numbers.size() - 1][index] += tab[numbers.size() - 1][index + 1];
				}
			}

		}

		// rest
		for (int number = numbers.size() - 2; number >= 0; number--) {
			start = 0;
			for (int i = 0; i < number; i++) {
				start += numbers[i] + 1;
			}
			stop = line.length() - numbers[number];
			for (int i = number + 1; i < numbers.size(); i++) {
				stop -= (numbers[i] + 1);
			}
			buffor = std::string(numbers[number], '#');
			buffor += ".";
			for (int i = 0; i <= stop - start; i++) {				//per tab[number][i]
				int index = stop - i;
				if (CheckMatching(line, buffor, index)) {
					tab[number][index] += tab[number + 1][index + numbers[number] + 1];
				}
				if (i != 0) {
					if (line[index] != '#') {
						tab[number][index] += tab[number][index + 1];
					}
				}
			}

		}

		return tab[0][0];
	}

}

void Solve2023_12() {

	std::string buffor1, buffor2;
	std::fstream file("Input/Input_12.txt");

	std::vector<std::string> lines;
	std::vector<std::vector<long long>> numbers;

	while (!file.eof()) {
		file >> buffor1 >> buffor2;
		lines.push_back(buffor1);

		std::vector<long long> num;
		int index = 0;
		index = buffor2.find(',');
		while (index != -1) {
			num.push_back(std::stoi(buffor2.substr(0, index)));
			buffor2 = buffor2.substr(index + 1, buffor2.length() - index - 1);
			index = buffor2.find(',');
		}
		num.push_back(std::stoi(buffor2));
		numbers.push_back(num);
	}
	file.close();

	unsigned long long sum = 0;
	for (int i = 0; i < lines.size(); i++) {
		long long val = Advent2023_12::GetAnswer(lines[i], numbers[i]);
		sum += val;
	}
	std::cout << "Advent2023_12_1: " << sum << "\n";


	sum = 0;
	for (int i = 0; i < lines.size(); i++) {
		std::string line = "";
		std::vector<long long> number;
		for (int j = 0; j < 5; j++) {
			line += lines[i];
			if(j!=4)line += '?';
			number.insert(number.end(), numbers[i].begin(), numbers[i].end());
		}
		unsigned long long ans = Advent2023_12::GetAnswer(line, number);
		sum += ans;

	}

	std::cout << "Advent2023_12_2: " << sum << "\n";


}

