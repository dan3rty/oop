#include "CPerson.h"
#include "CPoliceCar.h"
#include "CPoliceMan.h"
#include "CRacer.h"
#include "CTaxi.h"
#include <iostream>

int main()
{
	std::shared_ptr<IPoliceCar> policeCar = std::make_shared<CPoliceCar>(5, MakeOfTheCar::FORD);
	std::shared_ptr<IPoliceMan> johnSmith = std::make_shared<CPoliceMan>("John Smith", "NWPD");
	std::shared_ptr<IPoliceMan> jimClark = std::make_shared<CPoliceMan>("Jim Clark", "SEPD");

	std::shared_ptr<ITaxi> taxi = std::make_shared<CTaxi>(2, MakeOfTheCar::TOYOTA);
	std::shared_ptr<IPerson> rajaGhandi = std::make_shared<CPerson>("Raja Ghandi");
	std::shared_ptr<IRacer> michaelSchumacher = std::make_shared<CRacer>("Michael Schumacher", 12);

	std::cout << "John: I hate my freaking police work." << std::endl
			  << "*John gets in the car*" << std::endl;
	policeCar->AddPassenger(johnSmith);

	std::cout << "Jim: Hey, buddy! Looks like we're working together today! That's adorable!" << std::endl
			  << "John: ..." << std::endl
			  << "*Jim gets in the car*" << std::endl
			  << std::endl;
	policeCar->AddPassenger(jimClark);

	std::cout << "Policemen in the car:" << std::endl;
	for (std::size_t i = 0; i < policeCar->GetPassengerCount(); i++)
	{
		auto const& policeman = policeCar->GetPassenger(i);
		std::cout << "  Name: " << policeman.GetName() << std::endl
				  << "  Department: " << policeman.GetDepartmentName() << std::endl;
	}
	std::cout << std::endl;

	std::cout << "John: You know, Jim, I'm in such a fucked-up mood, I want to blow the brains out of the first person I see." << std::endl
			  << "Jim: What the hell are you talking about?! That's it! I'm out!" << std::endl
			  << "*Jim gets out of the car and slams the door*" << std::endl
			  << std::endl;
	policeCar->RemovePassenger(1);

	std::cout << "*Meanwhile...*" << std::endl
			  << "Michael: What takes you so long? We have 15 minutes left!" << std::endl
			  << "Raja (heavy indian accent): Do not worry good sir, we'll be there in no time!" << std::endl
			  << std::endl;
	taxi->AddPassenger(rajaGhandi);
	taxi->AddPassenger(michaelSchumacher);

	std::cout << "Jim: Toyota, pull to the curb!" << std::endl
			  << "*Taxi stops*" << std::endl
			  << "Jim: DRIVER, LEAVE THE VEHICLE WITH YOUR HANDS UP, NO SUDDEN MOVEMENTS, I CAN ONLY BE COMMENDED FOR KILLING A NIGGER!" << std::endl
			  << "Raja (heavy indian accent): OH WHAT THE HELL MAN!! OKAY, OKAY, CHILL!" << std::endl
			  << "*Raja gets out of the car, Jim hops in and locks the doors*" << std::endl
			  << std::endl;
	taxi->RemovePassenger(0);
	taxi->AddPassenger(jimClark);

	std::cout << "Michael: WHAT IN THE GODDAMN IS HAPPENING OUT THERE?!! I'M GONNA BE LATE!" << std::endl
			  << "Jim: Wha.. Are you Michael Schumacher?! You're my favorite racer! Don't worry, we'll get there in time. Faster your belt!" << std::endl
			  << "Michael: You're fucking crazy, man..." << std::endl
			  << std::endl;

	std::cout << "Raja (heavy indian accent): I left my chicken kari in the car!" << std::endl
			  << "*Raja tries to get in the car*" << std::endl;
	try
	{
		taxi->AddPassenger(rajaGhandi);
	}
	catch (std::logic_error const& e)
	{
		std::cout << "*Raja can't get in the car! Cause: " << e.what() << "*" << std::endl
				  << "Raja (heavy indian accent): OH NOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO!!!" << std::endl
				  << std::endl;
	}

	std::cout << "The end." << std::endl;

	return EXIT_SUCCESS;
}