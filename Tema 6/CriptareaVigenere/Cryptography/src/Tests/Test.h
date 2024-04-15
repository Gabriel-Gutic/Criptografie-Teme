#pragma once


class Test
{
public:
	virtual void Run() = 0;

	void Assert(std::string_view message);
};