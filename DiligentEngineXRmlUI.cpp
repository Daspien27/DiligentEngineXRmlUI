// DiligentEngineXRmlUI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Application.h"
#include <iostream>

namespace ReturnCodes {
	constexpr int RETURN_ERROR = -1;
	constexpr int RETURN_SUCCESS = 0;
};

int main() {

	try {
		application app{ create_application_build_params() };
		app.run();
	}
	catch (const std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		return ReturnCodes::RETURN_ERROR;
	}

	return ReturnCodes::RETURN_SUCCESS;
}