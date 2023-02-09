#include "EnemyRoom.h"
#include "Banshee.h"
#include "Ogre.h"
#include "Skeleton.h"
#include "Slime.h"
#include <random>

EnemyRoom::EnemyRoom() :
	Room(), _totalEnemyWeights(0) {

}

Enemy EnemyRoom::GenerateEnemy() {
	static std::default_random_engine engine;

	GenerateEnemyWeights();
	std::uniform_int_distribution<int> distribution(1, _totalEnemyWeights);

	//Roll for enemy
	int generatedNumber = distribution(engine);

	for (int i = 0; i < _enemyWeightMap.size(); ++i) {
		if (generatedNumber < _enemyWeightMap[i]) {
			switch ((EnemyType)i)
			{
			case EnemyType::Slime:
				return Slime();
			case EnemyType::Skeleton:
				return Skeleton();
			case EnemyType::Banshee:
				return Banshee();
			case EnemyType::Ogre:
				return Ogre();
			default:
				break;
			}
		}
		generatedNumber -= _enemyWeightMap[i];
	}

	//if all fails create slime as a fallback
	return Slime();
}

void EnemyRoom::GenerateEnemyWeights() {
	_enemyWeightMap[(int)EnemyType::Skeleton] += GetCurrentDifficulty();
	_enemyWeightMap[(int)EnemyType::Banshee] += GetCurrentDifficulty() / 2;
	_enemyWeightMap[(int)EnemyType::Ogre] += GetCurrentDifficulty() / 3;

	_totalEnemyWeights = GenerateTotalWeights(_enemyWeightMap.begin(), _enemyWeightMap.end());
}