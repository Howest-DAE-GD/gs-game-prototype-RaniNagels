#include "pch.h"
#include "Streams.h"

Streams::Streams()
	: value{}
{
}

void Streams::PrintTitle(const std::string& title)
{
	std::string deco{ " ============= " };
	std::cout << deco << title << deco << std::endl;
}

void Streams::PrintIOstream()
{
	PrintTitle("IOSTREAM");
	std::cout << "This string is printed\ngive integer value: ";
	std::cin >> value;
}

void Streams::PrintFstream()
{
	PrintTitle("FSTREAM");
	std::cout << "  -> reading from and writing to files\n";
	// more later
}

void Streams::PrintSstream()
{
	PrintTitle("SSTREAM");
	std::cout << "  -> manipulating string data without direclty interacting with files, consoles ...\n";
	
	std::ostringstream ostream;		// initialize

	ostream.str("");				// Set string content
	std::cout << ostream.str();		// Get string content

	ostream << 45.56424218 << '\n';	// Add the number to the string
	ostream.precision(2);			// Set 2 digits IN TOTAL
	ostream.setf(std::ios::fixed);	// Change to 2 digits AFTER decimal
	ostream << 309.2649236 << '\n';	// Add the number 309.26 to the string!

	std::cout << ostream.str();		// Print content
	ostream.clear();				// clear the ostream
}
