#include<iostream>
#include<fstream>
#include<string>
#include<vector>

void Solve2023_06() {

	std::fstream file("Input/Input_06.txt");

	std::string buffor;
	std::vector<int> time, distance;
	std::string bigTimeStr = "", bigDistanceStr = "";
	long long bigTime, bigDistance;

	file >> buffor; // skip "Time:"
	while (!file.eof()) {
		file >> buffor;
		if (buffor[0] >= '0' && buffor[0] <= '9') {
			time.push_back(std::stoi(buffor));
			bigTimeStr.append(buffor);
		}
		else {
			break;
		}
	}
	bigTime = std::stoll(bigTimeStr);
	while (!file.eof()) {
		int tmpValue;
		file >> tmpValue;
		distance.push_back(tmpValue);
		bigDistanceStr.append(std::to_string(tmpValue));
	}
	bigDistance = std::stoll(bigDistanceStr);
	file.close();

	int result1 = 1;
	for (int race = 0; race < time.size(); race++) {
		int answer = 0;
		for (int startingValue = (time[race] + 1) / 2 ; startingValue < time[race]; startingValue++) {
			int value = startingValue * (time[race] - startingValue);
			if (value > distance[race]) {
				answer++;
			}
			else {
				break;
			}
		}
		if (time[race] % 2 == 0) {
			answer = answer * 2 - 1;
		}
		else {
			answer *= 2;
		}
		result1 *= answer;
	}
	std::cout << "Advent2023_06_1: " << result1 << "\n";

	//---part 2---

	int result2 = 0;

	for (long long startingValue = (bigTime + 1) / 2; startingValue < bigTime; startingValue++) {
		long long value = startingValue * (bigTime - startingValue);
		if (value > bigDistance) {
			result2++;
		}
		else {
			break;
		}
	}
	if (bigTime % 2 == 0) {
		result2 = result2 * 2 - 1;
	}
	else {
		result2 *= 2;
	}

	std::cout << "Advent2023_06_2: " << result2 << "\n";
}

