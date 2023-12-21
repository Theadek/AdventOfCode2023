#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>

namespace Advent2023_19 {

	struct Part {
		int xmas[4];
		Part(int x, int m, int a, int s) {
			xmas[0] = x;
			xmas[1] = m;
			xmas[2] = a;
			xmas[3] = s;
		}
	};

	struct Range {
		uint64_t xmas_min_max[8];
		Range() {
			for (int i = 0; i < 4; i++) {
				xmas_min_max[i * 2] = 1;
				xmas_min_max[i * 2 + 1] = 4000;
			}
		}

		uint64_t GetScope() {
			uint64_t answer = 1;
			for (int i = 0; i < 4; i++) {
				answer *= (xmas_min_max[i * 2 + 1] - xmas_min_max[i * 2] + 1);
			}
			return answer;
		}
	};

	struct Rule {
		bool isLessThan;
		int xmasIndex;
		uint64_t value;
		std::string result;

		Rule(int xmasIndex, bool isLessThan, int value, std::string result) :
			xmasIndex(xmasIndex), isLessThan(isLessThan), value(value), result(result) {}

		bool ProcessValue(int xmas[4], std::string& res) {
			if (isLessThan) {
				if (xmas[xmasIndex] < value) {
					res = result;
					return true;
				}
				return false;
			}
			else {
				if (xmas[xmasIndex] > value) {
					res = result;
					return true;
				}
				return false;
			}
		}

		Range ProcessRange(Range range) {
			if (isLessThan) {
				range.xmas_min_max[xmasIndex * 2 + 1] = std::min(value -1, range.xmas_min_max[xmasIndex * 2 + 1]);
			}
			else {
				range.xmas_min_max[xmasIndex * 2] = std::max(value + 1, range.xmas_min_max[xmasIndex * 2]);
			}
			return range;
		}

		Range ProcessRangeInv(Range range) {
			if (isLessThan) {
				range.xmas_min_max[xmasIndex * 2] = std::max(value, range.xmas_min_max[xmasIndex * 2]);
			}
			else {
				range.xmas_min_max[xmasIndex * 2 + 1] = std::min(value, range.xmas_min_max[xmasIndex * 2 + 1]);
			}
			return range;
		}

		bool IsValidRange(Range& range) {
			return range.xmas_min_max[xmasIndex * 2] < range.xmas_min_max[xmasIndex * 2 + 1];
		}

	};



	struct Workflow {
		std::vector<Rule> rules;
		std::string finalRes;

		Workflow() {
			rules = std::vector<Rule>();
		}

		void AddRule(Rule& rule) {
			rules.push_back(rule);
		}

		int ProcessWorkflow(std::unordered_map<std::string, Workflow>& workflows, Part& part){
			std::string next = "";
			for (int i = 0; i < rules.size(); i++) {
				if (rules[i].ProcessValue(part.xmas, next)) {
					if (next == "A") {
						return part.xmas[0] + part.xmas[1] + part.xmas[2] + part.xmas[3];
					}
					if (next == "R") {
						return 0;
					}
					return workflows[next].ProcessWorkflow(workflows, part);
				}
			}
			if (finalRes == "A") {
				return part.xmas[0] + part.xmas[1] + part.xmas[2] + part.xmas[3];
			}
			if (finalRes == "R") {
				return 0;
			}
			return workflows[finalRes].ProcessWorkflow(workflows, part);

		}

		uint64_t PredictWorkflow(std::unordered_map<std::string, Workflow>& workflows, Range range) {
			uint64_t answer = 0;
			for (int i = 0; i < rules.size(); i++) {
				Range rangeLeft = rules[i].ProcessRange(range);
				if (rules[i].IsValidRange(rangeLeft)) {
					if (rules[i].result == "A") {
						answer += rangeLeft.GetScope();
					}
					else if (rules[i].result != "R") {
						answer += workflows[rules[i].result].PredictWorkflow(workflows, rangeLeft);
					}
				}

				range = rules[i].ProcessRangeInv(range);
				if (!rules[i].IsValidRange(range)) {
					return answer;
				}
			}

			if (finalRes == "A") {
				answer += range.GetScope();
			}
			else if (finalRes != "R") {
				answer += workflows[finalRes].PredictWorkflow(workflows, range);
			}

			return answer;
		}
	};


}

void Solve2023_19() {

	std::fstream file("Input/Input_19.txt");
	std::string buffor;
	std::vector<Advent2023_19::Part> parts;
	std::unordered_map<std::string, Advent2023_19::Workflow> workflows;
	Advent2023_19::Workflow* in;

	while (!file.eof()) {
		std::getline(file, buffor);
		if (buffor == "")break;

		int index = buffor.find('{');
		std::string name = buffor.substr(0, index);
		buffor = buffor.substr(index + 1, buffor.length() - index - 1);

		Advent2023_19::Workflow workflowTmp = Advent2023_19::Workflow();
		while (true) {
			index = buffor.find(':');
			if (index == -1) {
				std::string finalRes = buffor.substr(0, buffor.length() - 1);
				workflowTmp.finalRes = finalRes;
				break;
			}
			else {
				int xmasIndex;
				switch (buffor[0]) {
				case 'x':
					xmasIndex = 0;
					break;
				case 'm':
					xmasIndex = 1;
					break;
				case 'a':
					xmasIndex = 2;
					break;
				case 's':
					xmasIndex = 3;
					break;
				}
				bool isLessThan = buffor[1] == '<';
				int value = std::stoi(buffor.substr(2, index - 2));
				buffor = buffor.substr(index + 1, buffor.length() - index - 1);
				index = buffor.find(',');
				std::string res = buffor.substr(0, index);
				buffor = buffor.substr(index + 1, buffor.length() - index - 1);
				Advent2023_19::Rule rule = Advent2023_19::Rule(xmasIndex, isLessThan, value, res);
				workflowTmp.AddRule(rule);
			}

		}
		workflows.insert({ name, workflowTmp });
	}
	in = &workflows["in"];
	while (!file.eof()) {
		std::getline(file, buffor);

		int x, m, a, s;

		int index = buffor.find(',');
		x = std::stoi(buffor.substr(3, index - 3));
		buffor = buffor.substr(index + 1, buffor.length() - index - 1);

		index = buffor.find(',');
		m = std::stoi(buffor.substr(2, index - 2));
		buffor = buffor.substr(index + 1, buffor.length() - index - 1);

		index = buffor.find(',');
		a = std::stoi(buffor.substr(2, index - 2));
		buffor = buffor.substr(index + 1, buffor.length() - index - 1);

		s = std::stoi(buffor.substr(2, buffor.length() - 3));

		parts.emplace_back(x, m, a, s);
	}
	file.close();

	int answer = 0;
	for (int i = 0; i < parts.size(); i++) {
		answer += in->ProcessWorkflow(workflows, parts[i]);
	}
	std::cout << "Advent2023_19_1: " << answer << "\n";

	//---part 2---

	Advent2023_19::Range range;
	uint64_t answer2 = in->PredictWorkflow(workflows, range);
	std::cout << "Advent2023_19_2: " << answer2 << "\n";
}

