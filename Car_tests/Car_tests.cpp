#define CATCH_CONFIG_MAIN
#include "../Car/Car.h"
#include "../Car/CarControl.h"
#include "../catch2/catch.hpp"
#include <sstream>

SCENARIO("Car is operated correctly")
{
	GIVEN("A car")
	{
		Car car;

		WHEN("Car is fresh")
		{
			THEN("The engine is off")
			{
				REQUIRE(!car.IsTurnedOn());
			}

			THEN("Car is at zeroth gear")
			{
				REQUIRE(car.GetGear() == 0);
			}

			THEN("Car has zero speed")
			{
				REQUIRE(car.GetSpeed() == 0);
			}

			THEN("Car is not moving")
			{
				REQUIRE(car.GetDirection() == Car::Direction::STILL);
			}

			THEN("Car can't change gear")
			{
				REQUIRE(!car.SetGear(1));
				REQUIRE(car.GetGear() == 0);
				REQUIRE(!car.SetGear(-1));
				REQUIRE(car.GetGear() == 0);
			}

			THEN("Car can't change speed")
			{
				REQUIRE(!car.SetSpeed(10));
				REQUIRE(car.GetSpeed() == 0);
			}

			THEN("The engine can't be turned off")
			{
				REQUIRE(!car.TurnOffEngine());
				REQUIRE(!car.IsTurnedOn());
			}

			THEN("The engine can be turned on")
			{
				REQUIRE(car.TurnOnEngine());
				REQUIRE(car.IsTurnedOn());
			}

			WHEN("The engine is turned on")
			{
				car.TurnOnEngine();

				THEN("Car is at zeroth gear")
				{
					REQUIRE(car.GetGear() == 0);
				}

				THEN("Car has zero speed")
				{
					REQUIRE(car.GetSpeed() == 0);
				}

				THEN("Car is not moving")
				{
					REQUIRE(car.GetDirection() == Car::Direction::STILL);
				}

				THEN("The engine can be turned off")
				{
					REQUIRE(car.TurnOffEngine());
					REQUIRE(!car.IsTurnedOn());
				}

				THEN("The engine can't be turned on")
				{
					REQUIRE(!car.TurnOnEngine());
					REQUIRE(car.IsTurnedOn());
				}

				THEN("Car can set first gear")
				{
					REQUIRE(car.SetGear(1));
					REQUIRE(car.GetGear() == 1);
				}

				THEN("Car can set reverse gear")
				{
					REQUIRE(car.SetGear(-1));
					REQUIRE(car.GetGear() == -1);
				}

				THEN("Neutral gear can be set")
				{
					REQUIRE(car.SetGear(0));
					REQUIRE(car.GetGear() == 0);
				}

				WHEN("Reverse gear is set")
				{
					car.SetGear(-1);

					THEN("The engine can't be turned off")
					{
						REQUIRE(!car.TurnOffEngine());
						REQUIRE(car.IsTurnedOn());
					}

					THEN("Neutral gear can be set")
					{
						REQUIRE(car.SetGear(0));
						REQUIRE(car.GetGear() == 0);
					}

					THEN("Reverse gear can be set")
					{
						REQUIRE(car.SetGear(-1));
						REQUIRE(car.GetGear() == -1);
					}

					THEN("First gear can be set")
					{
						REQUIRE(car.SetGear(1));
						REQUIRE(car.GetGear() == 1);
					}

					THEN("Speed from 0 to 20 can be set")
					{
						REQUIRE(car.SetSpeed(20));
						REQUIRE(car.GetSpeed() == 20);
						REQUIRE(car.SetSpeed(0));
						REQUIRE(car.GetSpeed() == 0);
					}

					THEN("Speed exceeding limit can't be set")
					{
						REQUIRE(!car.SetSpeed(21));
						REQUIRE(car.GetSpeed() == 0);
					}

					WHEN("It speeds up")
					{
						car.SetSpeed(10);

						THEN("It is moving backward")
						{
							REQUIRE(car.GetDirection() == Car::Direction::BACKWARD);
						}

						THEN("First gear can't be set")
						{
							REQUIRE(!car.SetGear(1));
							REQUIRE(car.GetGear() == -1);
						}

						THEN("Reverse gear can't be set")
						{
							REQUIRE(!car.SetGear(-1));
						}

						THEN("Neutral gear can be set")
						{
							REQUIRE(car.SetGear(0));
							REQUIRE(car.GetGear() == 0);
						}

						WHEN("Neutral gear is set")
						{
							car.SetGear(0);

							THEN("It has the same speed")
							{
								REQUIRE(car.GetSpeed() == 10);
							}

							THEN("It is still moving backwards")
							{
								REQUIRE(car.GetDirection() == Car::Direction::BACKWARD);
							}

							THEN("It can't speed up")
							{
								REQUIRE(!car.SetSpeed(15));
								REQUIRE(car.GetSpeed() == 10);
							}

							THEN("It can slow down")
							{
								REQUIRE(car.SetSpeed(5));
								REQUIRE(car.GetSpeed() == 5);
								REQUIRE(car.GetDirection() == Car::Direction::BACKWARD);
							}
						}
					}
				}

				WHEN("First gear is set")
				{
					car.SetGear(1);

					THEN("The engine can't be turned off")
					{
						REQUIRE(!car.TurnOffEngine());
						REQUIRE(car.IsTurnedOn());
					}

					THEN("Speed from 0 to 30 can be set")
					{
						REQUIRE(car.SetSpeed(30));
						REQUIRE(car.GetSpeed() == 30);
						REQUIRE(car.SetSpeed(0));
						REQUIRE(car.GetSpeed() == 0);
					}

					THEN("Speed exceeding limit can't be set")
					{
						REQUIRE(!car.SetSpeed(31));
						REQUIRE(car.GetSpeed() == 0);
						REQUIRE(!car.SetSpeed(-10));
						REQUIRE(car.GetSpeed() == 0);
					}

					THEN("First gear can be set")
					{
						REQUIRE(car.SetGear(1));
						REQUIRE(car.GetGear() == 1);
					}

					WHEN("It speeds up")
					{
						car.SetSpeed(20);

						THEN("It is moving forward")
						{
							REQUIRE(car.GetDirection() == Car::Direction::FORWARD);
						}

						THEN("Reverse gear can't be set")
						{
							REQUIRE(!car.SetGear(-1));
							REQUIRE(car.GetGear() == 1);
						}

						THEN("Neutral gear can be set")
						{
							REQUIRE(car.SetGear(0));
							REQUIRE(car.GetGear() == 0);
						}

						WHEN("Neutral gear is set")
						{
							car.SetGear(0);

							THEN("It has the same speed")
							{
								REQUIRE(car.GetSpeed() == 20);
							}

							THEN("It is still moving forward")
							{
								REQUIRE(car.GetDirection() == Car::Direction::FORWARD);
							}

							THEN("It can't speed up")
							{
								REQUIRE(!car.SetSpeed(25));
								REQUIRE(car.GetSpeed() == 20);
							}

							THEN("It can slow down")
							{
								REQUIRE(car.SetSpeed(10));
								REQUIRE(car.GetSpeed() == 10);
							}
						}
					}
				}

				WHEN("Second gear is set")
				{
					car.SetGear(1);
					car.SetSpeed(20);
					car.SetGear(2);

					THEN("Speed from 20 to 50 can be set")
					{
						REQUIRE(car.SetSpeed(20));
						REQUIRE(car.GetSpeed() == 20);
						REQUIRE(car.SetSpeed(50));
						REQUIRE(car.GetSpeed() == 50);
					}

					THEN("Speed exceeding limit can't be set")
					{
						REQUIRE(!car.SetSpeed(19));
						REQUIRE(car.GetSpeed() == 20);
						REQUIRE(!car.SetSpeed(51));
						REQUIRE(car.GetSpeed() == 20);
					}
				}

				WHEN("Third gear is set")
				{
					car.SetGear(1);
					car.SetSpeed(20);
					car.SetGear(2);
					car.SetSpeed(30);
					car.SetGear(3);

					THEN("Speed from 30 to 60 can be set")
					{
						REQUIRE(car.SetSpeed(30));
						REQUIRE(car.GetSpeed() == 30);
						REQUIRE(car.SetSpeed(60));
						REQUIRE(car.GetSpeed() == 60);
					}

					THEN("Speed exceeding limit can't be set")
					{
						REQUIRE(!car.SetSpeed(29));
						REQUIRE(car.GetSpeed() == 30);
						REQUIRE(!car.SetSpeed(61));
						REQUIRE(car.GetSpeed() == 30);
					}
				}

				WHEN("Fourth gear is set")
				{
					car.SetGear(1);
					car.SetSpeed(20);
					car.SetGear(2);
					car.SetSpeed(30);
					car.SetGear(3);
					car.SetSpeed(40);
					car.SetGear(4);

					THEN("Speed from 40 to 90 can be set")
					{
						REQUIRE(car.SetSpeed(40));
						REQUIRE(car.GetSpeed() == 40);
						REQUIRE(car.SetSpeed(90));
						REQUIRE(car.GetSpeed() == 90);
					}

					THEN("Speed exceeding limit can't be set")
					{
						REQUIRE(!car.SetSpeed(39));
						REQUIRE(car.GetSpeed() == 40);
						REQUIRE(!car.SetSpeed(91));
						REQUIRE(car.GetSpeed() == 40);
					}
				}

				WHEN("Fifth gear is set")
				{
					car.SetGear(1);
					car.SetSpeed(20);
					car.SetGear(2);
					car.SetSpeed(30);
					car.SetGear(3);
					car.SetSpeed(40);
					car.SetGear(4);
					car.SetSpeed(50);
					car.SetGear(5);

					THEN("Speed from 50 to 150 can be set")
					{
						REQUIRE(car.SetSpeed(50));
						REQUIRE(car.GetSpeed() == 50);
						REQUIRE(car.SetSpeed(150));
						REQUIRE(car.GetSpeed() == 150);
					}

					THEN("Speed exceeding limit can't be set")
					{
						REQUIRE(!car.SetSpeed(49));
						REQUIRE(car.GetSpeed() == 50);
						REQUIRE(!car.SetSpeed(151));
						REQUIRE(car.GetSpeed() == 50);
					}
				}
			}
		}
	}
}

TEST_CASE("Car control works correctly")
{
	Car car;
	std::istringstream input;
	std::ostringstream output;
	CarControl control(car, input, output);

	SECTION("Command 'Help' works correctly")
	{
		input.str("Help\nExit\n");
		const std::string result = "EngineOn - turn on engine\n"
								   "EngineOff - turn off engine\n"
								   "SetSpeed <number> - set speed\n"
								   "SetGear <number> - set gear\n"
								   "Info - get info about car\n";
		control.HandleCommand();
		REQUIRE(output.str() == result);
	}

	SECTION("Command 'Info' works correctly")
	{
		SECTION("Newly created car info is printed correctly")
		{
			input.str("Info\nExit\n");
			const std::string result = "Car state:\n"
									   "Engine: off\n"
									   "Direction: standing still\n"
									   "Speed: 0\n"
									   "Gear: 0\n";
			control.HandleCommand();
			REQUIRE(output.str() == result);
		}

		SECTION("Modified car info is printed correctly")
		{
			car.TurnOnEngine();
			car.SetGear(1);
			car.SetSpeed(15);
			input.str("Info\nExit\n");
			const std::string result = "Car state:\n"
									   "Engine: on\n"
									   "Direction: forward\n"
									   "Speed: 15\n"
									   "Gear: 1\n";
			control.HandleCommand();
			REQUIRE(output.str() == result);
		}
	}

	SECTION("Turning engine on works correctly")
	{
		input.str("EngineOn\nExit\n");
		const std::string result = "Engine turned on\n";
		control.HandleCommand();
		REQUIRE(output.str() == result);
		REQUIRE(car.IsTurnedOn());
	}

	SECTION("Turning engine off works correctly")
	{
		input.str("EngineOn\nSetGear -1\nSetSpeed 20\nEngineOff\nSetSpeed 0\nSetGear 0\nEngineOff\nExit\n");
		const std::string result = "Engine turned on\n"
								   "Set gear -1 succeed\n"
								   "Set speed 20 succeed\n"
								   "Error: can't turn off engine\n"
								   "Set speed 0 succeed\n"
								   "Set gear 0 succeed\n"
								   "Engine turned off\n";
		while (control.HandleCommand())
		{
		};
		REQUIRE(output.str() == result);
		REQUIRE(!car.IsTurnedOn());
	}

	SECTION("Setting gear works correctly")
	{
		input.str("EngineOn\nSetGear 1\nExit\n");
		const std::string result = "Engine turned on\n"
								   "Set gear 1 succeed\n";
		while (control.HandleCommand())
		{
		};
		REQUIRE(output.str() == result);
		REQUIRE(car.GetGear() == 1);
	}

	SECTION("Setting speed works correctly")
	{
		input.str("EngineOn\nSetGear 1\nSetSpeed 20\nExit\n");
		const std::string result = "Engine turned on\n"
								   "Set gear 1 succeed\n"
								   "Set speed 20 succeed\n";
		while (control.HandleCommand())
		{
		};
		REQUIRE(output.str() == result);
		REQUIRE(car.GetSpeed() == 20);
	}
}