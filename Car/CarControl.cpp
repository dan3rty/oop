#include "CarControl.h"
#include <iostream>
#include <sstream>

CarControl::CarControl(Car& car, std::istream& input, std::ostream& output)
	: m_car(car)
	, m_input(input)
	, m_output(output)
	, m_actionMap({ { "EngineOn", [this](const int args) { return EngineOn(); } },
		  { "EngineOff", [this](const int args) { return EngineOff(); } },
		  { "SetGear", [this](const int args) { return SetGear(args); } },
		  { "SetSpeed", [this](const int args) { return SetSpeed(args); } },
		  { "Info", [this](const int args) { return Info(); } },
		  { "Help", [this](const int args) { return Help(); } },
		  { "Exit", [this](const int args) { return Exit(); } } })
{
}

bool CarControl::HandleCommand()
{
	std::string commandLine;
	std::getline(m_input, commandLine);

	std::istringstream stream(commandLine);

	std::string action;
	int args;
	std::getline(stream, action, ' ');
	args = stream >> args ? args : 0;

	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(args);
	}

	std::cout << "Unkown command" << std::endl;

	return true;
}

bool CarControl::EngineOn()
{
	m_car.TurnOnEngine();
	m_output << "Engine turned on" << std::endl;

	return true;
}

bool CarControl::EngineOff()
{
	if (m_car.TurnOffEngine())
	{
		m_output << "Engine turned off" << std::endl;
	}
	else
	{
		m_output << "Error: can't turn off engine" << std::endl;
	}

	return true;
}

bool CarControl::Help() const
{
	m_output << "EngineOn - turn on engine" << std::endl
			 << "EngineOff - turn off engine" << std::endl
			 << "SetSpeed <number> - set speed" << std::endl
			 << "SetGear <number> - set gear" << std::endl
			 << "Info - get info about car" << std::endl;

	return true;
}

bool CarControl::SetGear(const int args)
{
	if (!m_car.SetGear(args))
	{
		m_output << "Error: can't set gear to " << args << std::endl;
		return true;
	}

	m_output << "Set gear " << args << " succeed" << std::endl;

	return true;
}

bool CarControl::SetSpeed(const int args)
{
	if (!m_car.SetSpeed(args))
	{
		m_output << "Error: can't set speed to " << args << std::endl;
		return true;
	}

	m_output << "Set speed " << args << " succeed" << std::endl;

	return true;
}

bool CarControl::Info() const
{
	m_output << "Car state:" << std::endl
			 << "Engine: " << (m_car.IsTurnedOn() ? "on" : "off") << std::endl
			 << "Direction: " << DirectionToString(m_car.GetDirection()) << std::endl
			 << "Speed: " << m_car.GetSpeed() << std::endl
			 << "Gear: " << m_car.GetGear() << std::endl;

	return true;
}

bool CarControl::Exit() const
{
	return false;
}

std::string CarControl::DirectionToString(Car::Direction direction)
{
	switch (direction)
	{
	case Car::Direction::FORWARD:
		return "forward";
	case Car::Direction::STILL:
		return "standing still";
	case Car::Direction::BACKWARD:
		return "backward";
	default:
		return {};
	}
}
