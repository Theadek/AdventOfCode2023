#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<cmath>

namespace Advent2023_13 {
	class MMap {
	private:
		std::vector<int> horizontalMap;
		std::vector<int> verticalMap;

		static bool IsPowerOf2(int x) {
			while (x != 1) {
				if (x % 2 != 0)return false;
				x /= 2;
			}
			return true;
		}

	public:

		MMap() {}

		MMap(std::vector<std::string>& map_buffor) {
			for (int i = 0; i < map_buffor.size(); i++) {
				int tmp = 0;
				int index = 2;
				for (int j = 0; j < map_buffor[i].length(); j++) {
					if (map_buffor[i][j] == '#')tmp += index;
					index *= 2;
				}
				horizontalMap.push_back(tmp);
			}

			for (int j = 0; j < map_buffor[0].length(); j++) {
				int tmp = 0;
				int index = 2;
				for (int i = 0; i < map_buffor.size(); i++) {
					if (map_buffor[i][j] == '#')tmp += index;
					index *= 2;
				}
				verticalMap.push_back(tmp);
			}
		}

		int Solve1() {
			for (int i = 1; i < horizontalMap.size(); i++) {
				int iter = std::min(i, (int)(horizontalMap.size() - i));
				bool found = true;
				for (int j = 0; j < iter; j++) {
					if (horizontalMap[i + j] != horizontalMap[i - j - 1]) {
						found = false;
						break;
					}
				}
				if (found) {
					return i * 100;
				}
			}
			for (int i = 1; i < verticalMap.size(); i++) {
				int iter = std::min(i, (int)(verticalMap.size() - i));
				bool found = true;
				for (int j = 0; j < iter; j++) {
					if (verticalMap[i + j] != verticalMap[i - j - 1]) {
						found = false;
						break;
					}
				}
				if (found) {
					return i;
				}
			}
			return 0;
		}

		int Solve2() {
			for (int i = 1; i < horizontalMap.size(); i++) {
				int iter = std::min(i, (int)(horizontalMap.size() - i));
				bool found = true;
				bool smudge = false;
				for (int j = 0; j < iter; j++) {
					if (horizontalMap[i + j] != horizontalMap[i - j - 1]) {
						if (!smudge) {
							int diff = std::abs(horizontalMap[i + j] - horizontalMap[i - j - 1]);
							if (IsPowerOf2(diff)) {
								smudge = true;
								continue;
							}
						}
						found = false;
						break;

					}
				}
				if (found && smudge) {
					return i * 100;
				}
			}
			for (int i = 1; i < verticalMap.size(); i++) {
				int iter = std::min(i, (int)(verticalMap.size() - i));
				bool found = true;
				bool smudge = false;
				for (int j = 0; j < iter; j++) {
					if (verticalMap[i + j] != verticalMap[i - j - 1]) {
						if (!smudge) {
							int diff = std::abs(verticalMap[i + j] - verticalMap[i - j - 1]);
							if (IsPowerOf2(diff)) {
								smudge = true;
								continue;
							}
						}
						found = false;
						break;
					}
				}
				if (found && smudge) {
					return i;
				}
			}

			return 0;
		};
	};

}

void Solve2023_13() {

	std::vector<int> horizontalMap;
	std::vector<int> verticalMap;


	std::vector<std::string> map_buffor;
	std::string buffor;

	int sum = 0;
	int sum2 = 0;

	std::fstream file("Input/Input_13.txt");
	while (!file.eof()) {
		std::getline(file, buffor);
		if (buffor == "" || file.eof()) {
			Advent2023_13::MMap mMap(map_buffor);
			sum += mMap.Solve1();
			sum2 += mMap.Solve2();
			map_buffor.clear();
		}
		else {
			map_buffor.push_back(buffor);
		}

	}
	file.close();

	std::cout << "Advent2023_13_1: " << sum << "\n";
	std::cout << "Advent2023_13_2: " << sum2 << "\n";
}

