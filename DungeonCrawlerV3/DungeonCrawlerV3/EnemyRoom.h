#pragma once

#include "Room.h"
#include "Enemy.h"
#include <array>

class EnemyRoom : public Room {
friend class Room;

private:
	enum class EnemyType {
		Slime,
		Skeleton,
		Banshee,
		Ogre
	};

	std::array<int, 4> _enemyWeightMap{6,5,2,1};
	int _totalEnemyWeights;
	Enemy _roomEnemy;

protected:
	EnemyRoom();

public:
	~EnemyRoom() override = default;

private:
	Enemy GenerateEnemy();

	void GenerateEnemyWeights();
};