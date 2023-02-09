#pragma once

#include "Room.h"
#include "Banshee.h"
#include "Ogre.h"
#include "Skeleton.h"
#include "Slime.h"

class EnemyRoom : public Room {
friend class Room;

private:
	Enemy _roomEnemy;

protected:
	EnemyRoom();

private:
	Enemy GenerateEnemy();
};