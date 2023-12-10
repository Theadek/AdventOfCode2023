#include<iostream>
#include<fstream>
#include<string>
#include<vector>

namespace Advent2023_10 {

	enum class Dir {
		north,
		south,
		west,
		east
	};

	Dir GetNewDir(Dir wasGoingTo, char c) {
		switch (wasGoingTo) {
		case Dir::north:
			if (c == '|') return Dir::north;
			if (c == 'F') return Dir::east;
			if (c == '7') return Dir::west;
		case Dir::south:
			if (c == '|') return Dir::south;
			if (c == 'L') return Dir::east;
			if (c == 'J') return Dir::west;
		case Dir::west:
			if (c == '-') return Dir::west;
			if (c == 'L') return Dir::north;
			if (c == 'F') return Dir::south;
		case Dir::east:
			if (c == '-') return Dir::east;
			if (c == 'J') return Dir::north;
			if (c == '7') return Dir::south;
		}
		return wasGoingTo; // if 'S'
	}

	int GetLoopSize(std::vector<std::string>& pipes, int sX, int sY) {
		//find starting direction
		int length = 0;
		int curX = sX, curY = sY;
		Dir dir = Dir::north;
		bool found = false;
		if (sX > 0) {
			if (pipes[sX - 1][sY] == '|') {
				dir = Dir::north;
				curX = sX - 1;
				found = true;
			}
			else if (pipes[sX - 1][sY] == 'F') {
				dir = Dir::east;
				curX = sX - 1;
				found = true;
			}
			else if (pipes[sX - 1][sY] == '7') {
				dir = Dir::west;
				curX = sX - 1;
				found = true;
			}
		}
		if (sX < pipes.size() - 1 && !found) {
			if (pipes[sX + 1][sY] == '|') {
				dir = Dir::south;
				curX = sX + 1;
				found = true;
			}
			else if (pipes[sX + 1][sY] == 'L') {
				dir = Dir::east;
				curX = sX + 1;
				found = true;
			}
			else if (pipes[sX - 1][sY] == 'J') {
				dir = Dir::west;
				curX = sX + 1;
				found = true;
			}
		}
		if (sY > 0 && !found) {
			if (pipes[sX][sY-1] == '-') {
				dir = Dir::west;
				curY = sY - 1;
				found = true;
			}
			else if (pipes[sX][sY-1] == 'L') {
				dir = Dir::north;
				curY = sY - 1;
				found = true;
			}
			else if (pipes[sX][sY-1] == 'F') {
				dir = Dir::south;
				curY = sY - 1;
				found = true;
			}
		}
		if (sY < pipes[sX].length() - 1 && !found) {
			if (pipes[sX][sY+1] == '-') {
				dir = Dir::east;
				curY = sY + 1;
				found = true;
			}
			else if (pipes[sX][sY+1] == 'J') {
				dir = Dir::north;
				curY = sY + 1;
				found = true;
			}
			else if (pipes[sX][sY+1] == '7') {
				dir = Dir::south;
				curY = sY + 1;
				found = true;
			}
		}
		length = 1;

		while (pipes[curX][curY] != 'S') {
			switch (dir) {
			case Dir::north:
				curX--;
				break;
			case Dir::south:
				curX++;
				break;
			case Dir::west:
				curY--;
				break;
			case Dir::east:
				curY++;
				break;
			}
			dir = GetNewDir(dir, pipes[curX][curY]);
			length++;
		}

		return length;
	}

	int LeftRight(Dir prev, Dir now) {
		switch (prev) {
		case Dir::north:
			if (now == Dir::north) return 0;
			if (now == Dir::west) return -1;
			if (now == Dir::east) return 1;
		case Dir::south:
			if (now == Dir::south) return 0;
			if (now == Dir::east) return -1;
			if (now == Dir::west) return 1;
		case Dir::west:
			if (now == Dir::west) return 0;
			if (now == Dir::south) return -1;
			if (now == Dir::north) return 1;
		case Dir::east:
			if (now == Dir::east) return 0;
			if (now == Dir::north) return -1;
			if (now == Dir::south) return 1;
		}
		return 0; // if 'S'
	}

	Dir RotateDir(Dir dir, bool right) {
		switch (dir) {
		case Dir::north:
			if (right) return Dir::east;
			else return Dir::west;
		case Dir::south:
			if (right) return Dir::west;
			else return Dir::east;
		case Dir::west:
			if (right) return Dir::north;
			else return Dir::south;
		case Dir::east:
			if (right) return Dir::south;
			else return Dir::north;
		}
		return Dir::north; // if 'S'
	}

	char GetCrypt(char c, Dir goodDir) {
		switch (c) {
		case '|':
			if (goodDir == Dir::east) return '<';
			else return '>';
		case '-':
			if (goodDir == Dir::north) return 'V';
			else return 'A';
		case 'L':
			if (goodDir == Dir::west || goodDir == Dir::south) return 'I';
			else return 'X';
		case 'J':
			if (goodDir == Dir::east || goodDir == Dir::south) return 'I';
			else return 'X';
		case '7':
			if (goodDir == Dir::east || goodDir == Dir::north) return 'I';
			else return 'X';
		case 'F':
			if (goodDir == Dir::west || goodDir == Dir::north) return 'I';
			else return 'X';
		}
	}

	char ChangeS(std::vector<std::string>& pipes, int sX, int sY) {
		int bit = 0; //EWSN = 8421
		if (sX > 0) {
			if (pipes[sX - 1][sY] == '|' || pipes[sX - 1][sY] == 'F' || pipes[sX - 1][sY] == '7') {
				bit += 1;
			}
		}
		if (sX < pipes.size() - 1) {
			if (pipes[sX + 1][sY] == '|' || pipes[sX + 1][sY] == 'L' || pipes[sX + 1][sY] == 'J') {
				bit += 2;
			}
		}
		if (sY > 0) {
			if (pipes[sX][sY - 1] == '-' || pipes[sX][sY - 1] == 'L' || pipes[sX][sY - 1] == 'F') {
				bit += 4;
			}
		}
		if (sY < pipes[sX].length() - 1) {
			if (pipes[sX][sY + 1] == '-' || pipes[sX][sY + 1] == 'J' || pipes[sX][sY + 1] == '7') {
				bit += 8;
			}
		}

		switch (bit) {
		case 3:
			return '|';
		case 5:
			return 'J';
		case 6:
			return '7';
		case 9:
			return 'L';
		case 10:
			return 'F';
		case 12:
			return '-';
		}

	}

	int GetEnclosed (std::vector<std::string>& pipes, int sX, int sY) {
		//find starting direction
		int length = 0;
		int curX = sX, curY = sY;
		Dir dir = Dir::north;
		bool found = false;

		if (sX > 0) {
			if (pipes[sX - 1][sY] == '|') {
				dir = Dir::north;
				curX = sX - 1;
				found = true;
			}
			else if (pipes[sX - 1][sY] == 'F') {
				dir = Dir::east;
				curX = sX - 1;
				found = true;
			}
			else if (pipes[sX - 1][sY] == '7') {
				dir = Dir::west;
				curX = sX - 1;
				found = true;
			}
		}
		if (sX < pipes.size() - 1 && !found) {
			if (pipes[sX + 1][sY] == '|') {
				dir = Dir::south;
				curX = sX + 1;
				found = true;
			}
			else if (pipes[sX + 1][sY] == 'L') {
				dir = Dir::east;
				curX = sX + 1;
				found = true;
			}
			else if (pipes[sX - 1][sY] == 'J') {
				dir = Dir::west;
				curX = sX + 1;
				found = true;
			}
		}
		if (sY > 0 && !found) {
			if (pipes[sX][sY - 1] == '-') {
				dir = Dir::west;
				curY = sY - 1;
				found = true;
			}
			else if (pipes[sX][sY - 1] == 'L') {
				dir = Dir::north;
				curY = sY - 1;
				found = true;
			}
			else if (pipes[sX][sY - 1] == 'F') {
				dir = Dir::south;
				curY = sY - 1;
				found = true;
			}
		}
		if (sY < pipes[sX].length() - 1 && !found) {
			if (pipes[sX][sY + 1] == '-') {
				dir = Dir::east;
				curY = sY + 1;
				found = true;
			}
			else if (pipes[sX][sY + 1] == 'J') {
				dir = Dir::north;
				curY = sY + 1;
				found = true;
			}
			else if (pipes[sX][sY + 1] == '7') {
				dir = Dir::south;
				curY = sY + 1;
				found = true;
			}
		}
		int saveX = curX, saveY = curY;
		Dir saveDir = dir;
		int leftRight = 0;

		while (pipes[curX][curY] != 'S') {
			switch (dir) {
			case Dir::north:
				curX--;
				break;
			case Dir::south:
				curX++;
				break;
			case Dir::west:
				curY--;
				break;
			case Dir::east:
				curY++;
				break;
			}
			Dir tmpDir = GetNewDir(dir, pipes[curX][curY]);
			leftRight += LeftRight(dir, tmpDir);
			dir = tmpDir;
		}
		curX = saveX;
		curY = saveY;
		dir = saveDir;


		bool isRight;
		if (leftRight < 0) {
			isRight = false;
		}
		else {
			isRight = true;
		}

		pipes[sX][sY] = ChangeS(pipes, sX, sY);
		pipes[sX][sY] = GetCrypt(pipes[sX][sY], RotateDir(dir, isRight));
		while (curX != sX || curY != sY) {
			pipes[curX][curY] = GetCrypt(pipes[curX][curY], RotateDir(dir, isRight));
			switch (dir) {
			case Dir::north:
				curX--;
				break;
			case Dir::south:
				curX++;
				break;
			case Dir::west:
				curY--;
				break;
			case Dir::east:
				curY++;
				break;
			}
			dir = GetNewDir(dir, pipes[curX][curY]);
		}

		int count = 0;
		for (int i = 1; i < pipes.size() - 1; i++) {
			for (int j = 1; j < pipes[i].length() - 1; j++) {
				if (pipes[i][j] == 'A' ||
					pipes[i][j] == 'V' ||
					pipes[i][j] == '>' ||
					pipes[i][j] == '<' ||
					pipes[i][j] == 'I' ||
					pipes[i][j] == 'X') {
					continue;
				}

				if (pipes[i][j - 1] == '<' || pipes[i][j - 1] == 'I') {
					pipes[i][j] = 'I';
					count++;
					continue;
				}
				if (pipes[i][j + 1] == '>' || pipes[i][j + 1] == 'I') {
					pipes[i][j] = 'I';
					count++;
					continue;
				}
				if (pipes[i - 1][j] == 'A' || pipes[i - 1][j] == 'I') {
					pipes[i][j] = 'I';
					count++;
					continue;
				}
				if (pipes[i + 1][j] == 'V' || pipes[i + 1][j] == 'I') {
					pipes[i][j] = 'I';
					count++;
					continue;
				}
			}
		}

		return count;
	}
}

void Solve2023_10() {

	std::vector<std::string> pipes;
	std::string buffor;
	std::fstream file("Input/Input_10.txt");

	int startingX = 0, startingY = 0;

	while (!file.eof()) {
		file >> buffor;
		pipes.push_back(buffor);
	}
	file.close();

	for (int i = 0; i < pipes.size(); i++) {
		std::size_t index = pipes[i].find('S');
		if (index != std::string::npos) {
			startingX = i;
			startingY = index;
			break;
		}
	}


	std::cout << "Advent2023_10_1: " << Advent2023_10::GetLoopSize(pipes, startingX, startingY) / 2 << '\n';
	std::cout << "Advent2023_10_2: " << Advent2023_10::GetEnclosed(pipes, startingX, startingY) << '\n';

}

