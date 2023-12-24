#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<unordered_map>

namespace Advent2023_20 {

	struct Source {
		std::string from;
		bool isHigh;
		Source(std::string from, bool isHigh) : from(from), isHigh(isHigh) {}
	};

	struct Signal {
		std::string from;
		std::string to;
		bool isHigh;
		Signal(std::string from, std::string to, bool isHigh) : from(from), to(to), isHigh(isHigh) {}
	};

	class Node {
	public:
		std::string name;
		std::vector<std::string> output;

		Node() = delete;
		Node (std::string name, std::vector<std::string>& output) {
			this->name = name;
			this->output = output;
		}

		virtual void SendSignal(std::string& name, bool isHigh, std::vector<Signal>& signals) = 0;
	};

	class Broadcaster : public Node {
	public:
		Broadcaster(std::string name, std::vector<std::string>& output) : Node(name, output) {}

		void SendSignal(std::string& name, bool isHigh, std::vector<Signal>& signals) override {
			for (int i = 0; i < output.size(); i++) {
				signals.emplace_back(this->name, output[i], isHigh);
			}
		}
	};

	class FlipFlop : public Node {
	public:
		bool isOn;

		FlipFlop(std::string name, std::vector<std::string>& output) : Node(name, output) {
			isOn = false;
		}

		void SendSignal(std::string& name, bool isHigh, std::vector<Signal>& signals) override {
			if (!isHigh) {
				isOn = !isOn;
				for (int i = 0; i < output.size(); i++) {
					signals.emplace_back(this->name, output[i], isOn);
				}
			}
		}
	};

	class Conjuction : public Node {
	public:
		std::vector<Source> sources;

		Conjuction(std::string name, std::vector<std::string>& output) : Node(name, output) {
			sources = std::vector<Source>();
		}

		void AddSource(std::string source) {
			sources.emplace_back(source, false);
		}

		bool IsAllLow() {
			for (int i = 0; i < sources.size(); i++) {
				if (sources[i].isHigh) return false;
			}
			return true;
		}

		void SendSignal(std::string& name, bool isHigh, std::vector<Signal>& signals) override {
			for (int i = 0; i < sources.size(); i++) {
				if (sources[i].from == name) {
					sources[i].isHigh = isHigh;
					break;
				}
			}
			bool allHigh = true;
			for (int i = 0; i < sources.size(); i++) {
				if (!sources[i].isHigh) {
					allHigh = false;
					break;
				}
			}
			for (int i = 0; i < output.size(); i++) {
				signals.emplace_back(this->name, output[i], !allHigh);
			}
		}
	};

	void PressButton(std::unordered_map<std::string, Advent2023_20::Node*>& nodes, std::vector<Signal>& toSimulate, int& lowSignals, int& highSignals) {
		while (!toSimulate.empty()) {
			std::vector<Signal> tmpSignals;

			for (auto& signal : toSimulate) {
				if (signal.isHigh) {
					highSignals++;
				}
				else {
					lowSignals++;
				}

				if (auto search = nodes.find(signal.to); search != nodes.end()) {
					search->second->SendSignal(signal.from, signal.isHigh, tmpSignals);
				}
			}
			toSimulate = tmpSignals;
		}
	}


}

void Solve2023_20() {

	std::unordered_map<std::string, Advent2023_20::Node*> nodes;

	Advent2023_20::Broadcaster* p_broadcaster = nullptr;
	std::vector<Advent2023_20::FlipFlop*> flipFlops;
	std::vector<Advent2023_20::Conjuction*> conjuctions;


	std::fstream file("Input/Input_20.txt");
	std::string buffor;

	while (!file.eof()) {
		file >> buffor;
		if (buffor[0] == '%') {
			std::string name = buffor.substr(1, buffor.length() - 1);
			file >> buffor >> buffor;
			std::vector<std::string> outputs;
			while (true) {
				if (buffor[buffor.length() - 1] == ',') {
					outputs.push_back(buffor.substr(0, buffor.length() - 1));
					file >> buffor;
				}
				else {
					outputs.push_back(buffor);
					break;
				}
			}
			Advent2023_20::FlipFlop* flipFlop = new Advent2023_20::FlipFlop(name, outputs);
			nodes.insert({ name, flipFlop });
			flipFlops.push_back(flipFlop);
		}
		else if (buffor[0] == '&') {
			std::string name = buffor.substr(1, buffor.length() - 1);
			file >> buffor >> buffor;
			std::vector<std::string> outputs;
			while (true) {
				if (buffor[buffor.length() - 1] == ',') {
					outputs.push_back(buffor.substr(0, buffor.length() - 1));
					file >> buffor;
				}
				else {
					outputs.push_back(buffor);
					break;
				}
			}
			Advent2023_20::Conjuction* conjuction = new Advent2023_20::Conjuction(name, outputs);
			nodes.insert({ name, conjuction });
			conjuctions.push_back(conjuction);
		}
		else {
			std::string name = buffor.substr(1, buffor.length() - 1);
			file >> buffor >> buffor;
			std::vector<std::string> outputs;
			while (true) {
				if (buffor[buffor.length() - 1] == ',') {
					outputs.push_back(buffor.substr(0, buffor.length() - 1));
					file >> buffor;
				}
				else {
					outputs.push_back(buffor);
					break;
				}
			}
			p_broadcaster = new Advent2023_20::Broadcaster("broadcaster", outputs);
			nodes.insert({ "broadcaster", p_broadcaster });
		}
	}
	file.close();

	for (int i = 0; i < conjuctions.size(); i++) {
		for (int j = 0; j < flipFlops.size(); j++) {
			for (int k = 0; k < flipFlops[j]->output.size() ; k++) {
				if (conjuctions[i]->name == flipFlops[j]->output[k]) {
					conjuctions[i]->AddSource(flipFlops[j]->name);
					break;
				}
			}

		}
		for (int j = 0; j < conjuctions.size(); j++) {
			if (i == j)continue;
			for (int k = 0; k < conjuctions[j]->output.size(); k++) {
				if (conjuctions[i]->name == conjuctions[j]->output[k]) {
					conjuctions[i]->AddSource(conjuctions[j]->name);
					break;
				}
			}
		}
	}

	//---part 1---

	std::vector<Advent2023_20::Signal> toSimulate;

	int lowSignals = 0, highSignals = 0;

	int iter;
	for (iter = 1; iter <= 1000; iter++) {
		toSimulate.emplace_back("", "broadcaster", false);
		Advent2023_20::PressButton(nodes, toSimulate, lowSignals, highSignals);

		bool allGood = true;
		for (int j = 0; j < flipFlops.size(); j++) {
			if (flipFlops[j]->isOn) {
				allGood = false;
				break;
			}
		}
		if (!allGood) {
			continue;
		}

		for (int j = 0; j < conjuctions.size(); j++) {
			if (!conjuctions[j]->IsAllLow()) {
				allGood = false;
				break;
			}
		}
		if (!allGood) {
			continue;
		}
		else {
			//multiply result till under 1000
			int multiply = 1000 / iter;
			iter *= multiply;
			lowSignals *= multiply;
			highSignals *= multiply;
			break;
		}
	}

	for (; iter < 1000; iter++) {
		toSimulate.emplace_back("", "broadcaster", false);
		Advent2023_20::PressButton(nodes, toSimulate, lowSignals, highSignals);
	}

	std::cout << "Advent2023_20_1: " << lowSignals * highSignals << "\n";

	//---part 2---

	for (int j = 0; j < flipFlops.size(); j++) {
		flipFlops[j]->isOn = false;
	}
	for (int j = 0; j < conjuctions.size(); j++) {
		for (int k = 0; k < conjuctions[j]->sources.size(); k++) {
			conjuctions[j]->sources[k].isHigh = false;
		}
	}



	std::cout << "Advent2023_20_2: " << "missing answer!" << "\n";

	for (auto& node : nodes) {
		delete node.second;
	}
}

