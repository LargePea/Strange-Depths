#pragma once

#include <iostream>
#include "Item.h"
#include <map>
#include <array>
#include <random>

class LootTable {
private:
	std::map<Item*, float> _lootList;
	float _totalTableWeight = 0;

public:
	LootTable(std::initializer_list<std::pair<Item*, float>> startingLoot);

	template<size_t Size>
	std::array<Item*, Size> CreateLoot() {
		static std::default_random_engine numberGenerator;
		static std::uniform_real_distribution<float> distribution(1, _totalTableWeight);

		std::array<Item*, Size> createdLoot;

		for (size_t i = 0; i < Size; i++)
		{
			float generatedNumber = distribution(numberGenerator);
			for (auto& loot : _lootList) {
				if (generatedNumber < loot.second) {
					createdLoot[i] = loot.first;
					break;
				}
				generatedNumber -= loot.second;
			}
		}

		return createdLoot;
	}

	void PrintTable() {
		for (auto& loot : _lootList) {
			std::cout << loot.first->GetName() << loot.second << "\n";
		}

		std::cout << std::flush;
	}
};