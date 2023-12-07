#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

namespace Advent2023_07 {

	enum class Type {
		Five,
		Four,
		Full,
		Three,
		TPair,
		Pair,
		High
	};

	struct Hand {
	public:
		int bid;
		std::string cards;


		Type type;

		Hand(std::string cards, int bid) : cards(cards), bid(bid)
		{
			static const std::string order = "23456789TJQKA";
			int occurrences[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
			for (char& c : cards) {
				occurrences[order.find(c)]++;
			}
			int pairs = 0;
			bool threes = false, fours = false, fives = false;
			for (int i = 0; i < 13; i++) {
				switch (occurrences[i]) {
				case 2:
					pairs++;
					break;
				case 3:
					threes = true;
					break;
				case 4:
					fours = true;
					break;
				case 5:
					fives = true;
					break;
				default:
					break;
				}
				if (fives) {
					type = Type::Five;
				}
				else if (fours) {
					type = Type::Four;
				}
				else if (threes) {
					if (pairs == 0) {
						type = Type::Three;
					}
					else {
						type = Type::Full;
					}
				}
				else if (pairs == 2) {
					type = Type::TPair;
				}
				else if (pairs == 1) {
					type = Type::Pair;
				}
				else {
					type = Type::High;
				}
			}
		}

		static int GetCardValue(char card) {
			static const std::string order = "23456789TJQKA";
			return order.find(card);
		}

		static int CompareCard(char card1, char card2) {
			// return -1 if card1 is better
			// return  0 if equal
			// return  1 if card2 is better
			int value1 = GetCardValue(card1);
			int value2 = GetCardValue(card2);
			if (value1 > value2) return -1;
			if (value1 < value2) return 1;
			return 0;
		}

		inline bool operator < (const Hand& hand) const {
			//return true if hand1 < hand2
			if (type == hand.type) {
				for (int i = 0; i < 5; i++) {
					int compRes = CompareCard(cards[i], hand.cards[i]);
					if (compRes == 0) {
						continue;
					}
					if (compRes == -1) return false;
					return true;
				}
			}
			else {
				return type > hand.type;
			}
		}

	};

	struct HandAdv {
	public:
		int bid;
		std::string cards;


		Type type;

		HandAdv(std::string cards, int bid) : cards(cards), bid(bid)
		{
			static const std::string order = "J23456789TQKA";
			int occurrences[13] = { 0,0,0,0,0,0,0,0,0,0,0,0,0 };
			for (char& c : cards) {
				occurrences[order.find(c)]++;
			}
			int pairs = 0;
			bool threes = false, fours = false, fives = false;
			for (int i = 1; i < 13; i++) {
				switch (occurrences[i]) {
				case 2:
					pairs++;
					break;
				case 3:
					threes = true;
					break;
				case 4:
					fours = true;
					break;
				case 5:
					fives = true;
					break;
				default:
					break;
				}
			}
			if (fives || occurrences[0] == 5) {
				type = Type::Five;
			}
			else if (fours) {
				if (occurrences[0] == 1) {
					type = Type::Five;
				}
				else {
					type = Type::Four;
				}
			}
			else if (threes) {
				if (pairs == 0) {
					if (occurrences[0] == 2) {
						type = Type::Five;
					}
					else if (occurrences[0] == 1) {
						type = Type::Four;
					}
					else {
						type = Type::Three;
					}
				}
				else {
					type = Type::Full;
				}
			}
			else if (pairs == 2) {
				if (occurrences[0] == 1) {
					type = Type::Full;
				}
				else {
					type = Type::TPair;
				}
			}
			else if (pairs == 1) {
				if (occurrences[0] == 3) {
					type = Type::Five;
				}
				else if (occurrences[0] == 2) {
					type = Type::Four;
				}
				else if (occurrences[0] == 1) {
					type = Type::Three;
				}
				else {
					type = Type::Pair;
				}
			}
			else {
				if (occurrences[0] == 4) {
					type = Type::Five;
				}
				else if (occurrences[0] == 3) {
					type = Type::Four;
				}
				else if (occurrences[0] == 2) {
					type = Type::Three;
				}
				else if (occurrences[0] == 1) {
					type = Type::Pair;
				}
				else {
					type = Type::High;
				}
			}
		}

		static int GetCardValue(char card) {
			static const std::string order = "J23456789TQKA";
			return order.find(card);
		}

		static int CompareCard(char card1, char card2) {
			// return -1 if card1 is better
			// return  0 if equal
			// return  1 if card2 is better
			int value1 = GetCardValue(card1);
			int value2 = GetCardValue(card2);
			if (value1 > value2) return -1;
			if (value1 < value2) return 1;
			return 0;
		}

		inline bool operator < (const HandAdv& hand) const {
			//return true if hand1 < hand2
			if (type == hand.type) {
				for (int i = 0; i < 5; i++) {
					int compRes = CompareCard(cards[i], hand.cards[i]);
					if (compRes == 0) {
						continue;
					}
					if (compRes == -1) return false;
					return true;
				}
			}
			else {
				return type > hand.type;
			}
		}

	};
}

void Solve2023_07() {

	std::fstream file("Input/Input_07.txt");
	std::vector<Advent2023_07::Hand> hands;
	std::vector<Advent2023_07::HandAdv> handsAdv;

	std::string hand;
	int bid;

	while (!file.eof()) {
		file >> hand >> bid;
		hands.emplace_back(hand, bid);
		handsAdv.emplace_back(hand, bid);
	}

	file.close();

	std::sort(hands.begin(), hands.end());
	int sum = 0;
	for (int i = 0; i < hands.size();i++) {
		sum += (i + 1) * hands[i].bid;
	}
	std::cout << "Advent2023_07_1: " << sum << "\n";

	std::sort(handsAdv.begin(), handsAdv.end());
	sum = 0;
	for (int i = 0; i < handsAdv.size(); i++) {
		sum += (i + 1) * handsAdv[i].bid;
	}
	std::cout << "Advent2023_07_2: " << sum << "\n";
}

