#pragma once
#include <vector>
#include <map>

class Car
{
public:
	enum class Direction
	{
		FORWARD,
		STILL,
		BACKWARD,
	};

	bool TurnOnEngine();
	bool TurnOffEngine();
	bool SetGear(int gear);
	bool SetSpeed(int speed);

	bool IsTurnedOn() const;
	Direction GetDirection() const;
	int GetGear() const;
	int GetSpeed() const;

private:
	bool m_isEngineOn = false;
	int m_gear = 0;
	int m_speed = 0;
};