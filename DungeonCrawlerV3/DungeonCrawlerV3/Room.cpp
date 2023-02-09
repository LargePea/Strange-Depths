#include "Room.h"
#include "EnemyRoom.h"

#include <random>
#include <iostream>

Room Room::_currentRoom;
int Room::_roomsCompleted;
int Room::_roomDifficulty;

Room::Room() {
	_currentRoom = *this;
	++_roomsCompleted;
	_totalGenerationWeight = GenerateTotalRoomWeights();
	GenerateNextPossibleRooms();
}

Room::Room(const Room& other) : _totalGenerationWeight(other._totalGenerationWeight) {
	_nextRooms = other._nextRooms;
}

Room& Room::operator=(Room other) {
	_nextRooms = other._nextRooms;
	_totalGenerationWeight = other._totalGenerationWeight;
	return *this;
}

void Room::MoveToNextRoom(Direction moveDirection) {
	//TO:DO Create the different types of rooms
	RoomType roomTypeToGenerate = _nextRooms[(int)moveDirection];

	switch (roomTypeToGenerate)
	{
	case RoomType::Enemy:
		EnemyRoom();
		break;
	case RoomType::Tresure:
		break;
	case RoomType::Empty:
		break;
	case RoomType::Shop:
		break;
	default:
		break;
	}
}

int Room::GenerateTotalRoomWeights(int i) {
	if (i == _roomGenerationWeights.size())
		return 0;

	return _roomGenerationWeights[i] + GenerateTotalRoomWeights(i + 1);
}

void Room::GenerateNextPossibleRooms() {
	static std::default_random_engine engine;
	static std::uniform_int_distribution<int> distributor(1, 7);


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

void Room::IncreaseRoomDifficulty() {
	++_roomDifficulty;
	++_roomGenerationWeights[(int)RoomType::Enemy];

	if (_roomDifficulty % 2) ++_roomGenerationWeights[(int)RoomType::Tresure];

	_totalGenerationWeight = GenerateTotalRoomWeights();
}