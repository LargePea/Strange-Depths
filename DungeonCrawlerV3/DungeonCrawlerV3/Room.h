#pragma once

#include <array>
#include <iterator>
#include "Image.h"

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
		Treasure,
		Empty,
		Shop,
		Exit
	};

	static Room* _currentRoom;
	static const int _shopApperance = 5;
	static int _roomsCompleted;
	static int _roomDifficulty;
	static Image* _progress;

	std::array<RoomType, 4> _nextRooms;
	std::array<int, 3> _roomGenerationWeights{ 7, 1, 2 };
	int _totalGenerationWeight;

protected:
	static bool _exitUnlocked;

	template<size_t Size>
	int GenerateTotalWeights(std::_Array_iterator<int, Size> it, std::_Array_iterator<int, Size> ed) {
		if (it == ed)
			return 0;

		return *it + GenerateTotalWeights(it + 1, ed);
	}

	Room();

public:
	Room(const Room& other);

	Room& operator=(Room other);

	virtual ~Room() = default;

	static void Init();

	void Move(Direction moveDirection);

	static inline Room* GetCurrentRoom() { return _currentRoom; }

	static inline int GetRoomsCompleted() { return _roomsCompleted; }

	static inline int GetCurrentDifficulty() { return _roomDifficulty; }

	static inline Image* GetProgress() { return _progress; }

	static void ResetRooms();

	inline std::array<RoomType, 4> GetNextRooms() { return _nextRooms; }

private:

	void GenerateNextPossibleRooms();

	void GenerateRoomWeights();

protected:
	void IncreaseRoomDifficulty();
};