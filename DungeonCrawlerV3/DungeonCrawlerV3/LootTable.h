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
	LootTable() = default;
	LootTable(std::initializer_list<std::pair<Item*, float>> startingLoot);

	~LootTable() = default;

	template<size_t Size>
	void CreateLoot(std::array<Item*, Size>& createdLoot, bool maxLoot = false) {
		static std::default_random_engine numberGenerator;
		static std::uniform_real_distribution<float> itemDistribution(1, _totalTableWeight);
		static std::uniform_int_distribution<int> amountGeneratedDistribution(1, Size);

		//dont bother generating loot if there's nothing to generate
		if (_lootList.size() == 0) return;

		int amountToGenerate = maxLoot ? Size : amountGeneratedDistribution(numberGenerator);
		for (int i = 0; i < amountToGenerate; i++)
		{
			float generatedNumber = itemDistribution(numberGenerator);

			//generate loot based on weight
			for (auto& loot : _lootList) {
				if (generatedNumber <= loot.second) {
					createdLoot[i] = loot.first;
					break;
				}
				generatedNumber -= loot.second;
			}
		}
	}

	void PrintTable() {
		for (auto& loot : _lootList) {
			std::cout << loot.first->GetName() << loot.second << "\n";
		}

		std::cout << std::flush;
	}
};