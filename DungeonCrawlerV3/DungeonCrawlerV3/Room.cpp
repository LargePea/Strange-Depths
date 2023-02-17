#include "Room.h"
#include "EnemyRoom.h"
#include "TreasureRoom.h"
#include <random>
#include <iostream>

Room Room::_currentRoom;
int Room::_roomsCompleted;
int Room::_roomDifficulty;

Room::Room() {
	++_roomsCompleted;
	GenerateNextPossibleRooms();
}

Room::Room(const Room& other) : 
	_totalGenerationWeight(other._totalGenerationWeight), _roomGenerationWeights(other._roomGenerationWeights) {
	_nextRooms = other._nextRooms;
}

Room& Room::operator=(Room other) {
	_nextRooms = other._nextRooms;
	_totalGenerationWeight = other._totalGenerationWeight;
	_roomGenerationWeights = other._roomGenerationWeights;
	return *this;
}

void Room::Move(Direction moveDirection) {
	std::cout << "moved: " << (int)moveDirection << std::endl;
	switch (GetNextRooms()[(int)moveDirection])
	{
	case RoomType::Enemy:
		_currentRoom = EnemyRoom();
		break;
	case RoomType::Treasure:
		_currentRoom = TreasureRoom();
		break;
	case RoomType::Empty:
		_currentRoom = Room();
		break;
	case RoomType::Shop:
		_currentRoom = Room();
		break;
	default:
		break;
	}
}

void Room::GenerateNextPossibleRooms() {
	static std::default_random_engine engine;

	GenerateRoomWeights();
	std::uniform_int_distribution<int> distributor(1, _totalGenerationWeight);


	if (_roomsCompleted % _shopApperance == 0) {
		_nextRooms.fill(RoomType::Shop);
		return;
	}

	for (int i = 0; i < _nextRooms.size(); ++i) {
		int generatedNumber = distributor(engine);

		for (int j = 0; j < _roomGenerationWeights.size(); ++j) {
			if (generatedNumber < _roomGenerationWeights[j]) {
				_nextRooms[i] = (RoomType)j;
				break;
			}

			generatedNumber -= _roomGenerationWeights[j];
		}
	}
}

void Room::GenerateRoomWeights() {
	_roomGenerationWeights[(int)RoomType::Enemy] += _roomDifficulty;
	_roomGenerationWeights[(int)RoomType::Treasure] += _roomDifficulty / 2;
	_totalGenerationWeight = GenerateTotalWeights(_roomGenerationWeights.begin(), _roomGenerationWeights.end());
}

void Room::IncreaseRoomDifficulty() {
	++_roomDifficulty;
}