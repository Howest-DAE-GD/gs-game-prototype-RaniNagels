#pragma once
#include <iostream>
#include <fstream>
#include <sstream>

class Streams
{
public:
	Streams();

private:
	int value;

	void PrintTitle(const std::string& title);
	void PrintIOstream();
	void PrintFstream();
	void PrintSstream();
};

