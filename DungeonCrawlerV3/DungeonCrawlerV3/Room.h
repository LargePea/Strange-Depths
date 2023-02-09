#pragma once

#include <array>

class Room {
public:
	enum class Direction {
		Forward,
		Right,
		Backward,
		Left
	};

private:
	enum class RoomType {
		Enemy,
		Tresure,
		Empty,
		Shop
	};

	static const int _shopApperance = 5;
	static Room _currentRoom;
	static int _roomsCompleted;
	static int _roomDifficulty;

	std::array<RoomType, 4> _nextRooms;
	std::array<int, 3> _roomGenerationWeights{7, 1, 2};
	int _totalGenerationWeight;

protected:
	Room();

public:

	Room(const Room& other);

	Room& operator=(Room other);

	~Room() = default;

	static inline Room* GetCurrentRoom() { return &_currentRoom; }

	static inline int GetRoomsCompleted() { return _roomsCompleted; }

	static inline int GetCurrentDifficulty() { return _roomDifficulty; }

	void MoveToNextRoom(Direction moveDirection);

private:
	int GenerateTotalRoomWeights(int i = 0);

	void GenerateNextPossibleRooms();

protected:
	void IncreaseRoomDifficulty();
};