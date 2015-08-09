#pragma once
#include <string>
namespace npe {
	class ErrorHandler
	{
		std::string _message;
	public:
		ErrorHandler();
		static void Message(std::string message);
	};
}
