#pragma once
#include "Car.h"
#include <fstream>
#include <functional>

class CarControl
{
public:
	CarControl(Car& car, std::istream& input, std::ostream& output);
	bool HandleCommand();

private:
	bool EngineOn();
	bool EngineOff();
	bool SetGear(const int args);
	bool SetSpeed(const int args);
	bool Info() const;
	bool Help() const;
	bool Exit() const;

private:
	using Handler = std::function<bool(int args)>;

	using ActionMap = std::map<std::string, Handler>;

	Car& m_car;
	std::istream& m_input;
	std::ostream& m_output;

	const ActionMap m_actionMap;

	static std::string DirectionToString(Car::Direction direction);
};