#include "Room.h"
#include "EnemyRoom.h"
#include "TreasureRoom.h"
#include "ShopRoom.h"
#include <random>
#include <iostream>

Room* Room::_currentRoom;
int Room::_roomsCompleted;
int Room::_roomDifficulty;
bool Room::_exitUnlocked;
Image* Room::_progress;

Room::Room() {
	++_roomsCompleted;
	if (_progress == nullptr) _progress = new Image(std::vector<std::string>{"Current Room: " + std::to_string(_roomsCompleted)}, 2, { 50, 35 });
	else *_progress = std::move(Image(std::vector<std::string>{"Current Room: " + std::to_string(_roomsCompleted)}, 2, { 50, 35 }));
	GenerateNextPossibleRooms();
}

void Room::Init() {
	if (_currentRoom != nullptr) delete _currentRoom;
	_currentRoom = new Room();
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
	switch (GetNextRooms()[(int)moveDirection])
	{
	case RoomType::Enemy:
		if (_currentRoom != nullptr) delete _currentRoom;
		_currentRoom = new EnemyRoom();
		break;
	case RoomType::Treasure:
		if (_currentRoom != nullptr) delete _currentRoom;
		_currentRoom = new TreasureRoom();
		break;
	case RoomType::Empty:
		if (_currentRoom != nullptr) delete _currentRoom;
		_currentRoom = new Room();
		break;
	case RoomType::Shop:
		if (_currentRoom != nullptr) delete _currentRoom;
		_currentRoom = new ShopRoom();
		break;
	case RoomType::Exit:
		//TO:DO win game
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
		if (_exitUnlocked) _nextRooms.fill(RoomType::Exit);
		else _nextRooms.fill(RoomType::Shop);
		return;
	}

	for (int i = 0; i < _nextRooms.size(); ++i) {
		int generatedNumber = distributor(engine);

		for (int j = 0; j < _roomGenerationWeights.size(); ++j) {
			if (generatedNumber <= _roomGenerationWeights[j]) {
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