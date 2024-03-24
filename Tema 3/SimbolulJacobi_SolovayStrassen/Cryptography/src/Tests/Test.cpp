#include "pch.h"
#include "Test.h"

void Test::Assert(std::string_view message)
{
	std::cout << "Test Failed: " << message << std::endl;
	__debugbreak();
}
