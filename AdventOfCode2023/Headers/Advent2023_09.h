#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

namespace Advent2023_09 {
	long long PredictValue(std::vector<long long>& input) {
		std::vector<long long> interpolation = input;
		std::vector<long long> lastValue = {input[input.size()-1]};
		std::vector<long long> tmpInter;
		for (int pir = 0; pir < input.size() - 1; pir++) {
			for (int i = 0; i < interpolation.size() - 1; i++) {
				tmpInter.push_back(interpolation[i + 1] - interpolation[i]);
			}

			bool allZeros = true;
			for (int i = 0; i < tmpInter.size(); i++) {
				if (tmpInter[i] != 0) {
					allZeros = false;
					break;
				}
			}

			if (allZeros) {
				break;
			}
			else {
				lastValue.push_back(tmpInter[tmpInter.size() - 1]);
				interpolation = tmpInter;
				tmpInter.clear();
			}
		}
		long long answer = 0;
		for (int i = lastValue.size() - 1; i >= 0; i--) {
			answer += lastValue[i];
		}
		return answer;
	}
	long long PredictValueBack(std::vector<long long>& input) {
		std::vector<long long> interpolation = input;
		std::vector<long long> firstValue = {input[0]};
		std::vector<long long> tmpInter;
		for (int pir = 0; pir < input.size() - 1; pir++) {
			for (int i = 0; i < interpolation.size() - 1; i++) {
				tmpInter.push_back(interpolation[i + 1] - interpolation[i]);
			}

			bool allZeros = true;
			for (int i = 0; i < tmpInter.size(); i++) {
				if (tmpInter[i] != 0) {
					allZeros = false;
					break;
				}
			}

			if (allZeros) {
				break;
			}
			else {
				firstValue.push_back(tmpInter[0]);
				interpolation = tmpInter;
				tmpInter.clear();
			}
		}
		long long answer = 0;
		for (int i = firstValue.size() - 1; i >= 0; i--) {
			answer = firstValue[i] - answer;
		}
		return answer;
	}


}

void Solve2023_09() {

	std::vector<std::vector<long long>> OASIS;


	std::fstream file("Input/Input_09.txt");
	std::string buffor;
	long long bufforVal;
	std::getline(file, buffor);
	file.clear();
	file.seekg(0);
	int valInLine = std::count(buffor.begin(), buffor.end(), ' ') + 1 ;
	while (!file.eof()) {
		std::vector<long long> tmpVector;
		for (int i = 0; i < valInLine; i++) {
			file >> bufforVal;
			tmpVector.push_back(bufforVal);
		}
		OASIS.push_back(tmpVector);
	}
	file.close();

	long long sum = 0;
	for (int i = 0; i < OASIS.size(); i++) {
		sum += Advent2023_09::PredictValue(OASIS[i]);
	}
	std::cout << "Advent2023_09_1: " << sum << "\n";


	sum = 0;
	for (int i = 0; i < OASIS.size(); i++) {
		sum += Advent2023_09::PredictValueBack(OASIS[i]);
	}
	std::cout << "Advent2023_09_2: " << sum << "\n";
}

