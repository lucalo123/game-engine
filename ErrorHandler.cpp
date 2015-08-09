#include <iostream>
#include <cstdlib>
#include <SDL.h>

#include "ErrorHandler.h"


npe::ErrorHandler::ErrorHandler()
{
}
void npe::ErrorHandler::Message(std::string message)
{
	std::cout << "Errormessage: " << message.c_str() << "\nPress key to continue..." << std::endl;
	int input;
	std::cin >> input;
	SDL_Quit();
	exit(1);
}