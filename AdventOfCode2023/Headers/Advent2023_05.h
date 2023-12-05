#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

namespace Advent2023_05 {

	struct Range {
		long long start, range;
		Range(long long start, long long range) : start(start), range(range) {}
	};

	class Rule {
		public:
			long long from, to, offset;

		Rule(long long from, long long to, long long offset) : from(from), to(to), offset(offset) {}

		bool MapTo(long long& value) {
			if (value >= from && value <= to) {
				value += offset;
				return true;
			}
			else {
				return false;
			}
		}

		void MapToRange(Range& range, std::vector<Range>& unprocessed, std::vector<Range>& processed) {
			if ((range.start + range.range - 1 < from) ||
				 range.start > to) {
				unprocessed.push_back(range);
				return;
			}

			if (range.start < from) {
				Range pre_from(range.start, from - range.start);
				unprocessed.push_back(pre_from);
				range.range -= pre_from.range;
				range.start = from;
			}

			if (range.start + range.range - 1 > to) {
				Range to_from(to + 1, range.start + range.range -  1 - to);
				unprocessed.push_back(to_from);
				range.range -= to_from.range;
			}

			range.start += offset;
			processed.push_back(range);
		}
	};



}

void Solve2023_05() {

	std::vector<Advent2023_05::Rule> rules[7];
	std::vector<long long> seeds;

	std::fstream file("Input/Input_05.txt");

	std::string buffor;
	long long value1, value2, value3;

	file >> buffor; //skip "seeds:"
	while (!file.eof()) {
		file >> buffor;
		if (buffor[0] >= '0' && buffor[0] <= '9') {
			seeds.push_back(std::stoll(buffor));
		}
		else {
			file >> buffor; //skip "map:"
			break;
		}
	}

	//---part 2 input parse---
	std::vector<Advent2023_05::Range> ranges;
	for (int i = 0; i < seeds.size(); i += 2) {
		ranges.emplace_back(seeds[i], seeds[i + 1]);
	}
	//---end part 2 parse---

	int rules_index = 0;

	while (!file.eof()) {
		file >> buffor;
		if (buffor[0] >= '0' && buffor[0] <= '9') {
			value1 = std::stoll(buffor);
			file >> value2 >> value3;
			Advent2023_05::Rule tmp_rule(value2, value2 + value3 - 1, value1 - value2);
			rules[rules_index].push_back(tmp_rule);
		}
		else {
			file >> buffor; //skip "map:"
			rules_index++;
		}
	}
	file.close();

	// ---process part 1---
	for (int rule_group = 0; rule_group < 7; rule_group++) {							// for every mapping
		for (auto& seed : seeds) {														// for every seed
			for (int rule_no = 0; rule_no < rules[rule_group].size(); rule_no++) {		// for every rule in map
				if (rules[rule_group][rule_no].MapTo(seed)) {
					break;
				}
			}
		}
	}

	std::cout << "Advent2023_05_1: " << *std::min_element(seeds.begin(), seeds.end()) << "\n";

	//---part 2---

	// ---process part 2---

	std::vector<Advent2023_05::Range> unprocessed;
	std::vector<Advent2023_05::Range> processed;
	unprocessed.clear();
	processed.clear();

	for (int rule_group = 0; rule_group < 7; rule_group++) {						// for every rule in map
		for (int rule_no = 0; rule_no < rules[rule_group].size(); rule_no++) {		// for every mapping
			for (auto& range : ranges) {											// for every range
				rules[rule_group][rule_no].MapToRange(range, unprocessed, processed);
			}
			ranges = unprocessed;
			unprocessed.clear();
		}
		ranges.insert(ranges.begin(), processed.begin(), processed.end());
		processed.clear();
	}

	long long answer = ranges[0].start;
	for (int i = 1; i < ranges.size(); i++) {
		if (ranges[i].start < answer) answer = ranges[i].start;
	}

	std::cout << "Advent2023_05_2: "  << answer << "\n";
}

