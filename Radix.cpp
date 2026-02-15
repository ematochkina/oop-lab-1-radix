#include <iostream>
#include "Translator.h"

using namespace std;

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: radix.exe <source notation> <destination notation> <value>\n";
		return 1;
	}

	bool wasTo10TranslatorError = false;
	bool wasSourceError = false;
	int value10 = 0;
	const int source = StringToInt(argv[1], 10, wasSourceError);
	if (wasSourceError)
	{
		cout << "The radix must be an integer in the range from 2 to 36 inclusive\n" 
			<< "Invalid source notation\n";
	}
	else
	{
		value10 = StringToInt(argv[3], source, wasTo10TranslatorError);
	}

	bool wasDestinationError = false;
	const int destination = StringToInt(argv[2], 10, wasDestinationError);
	if (wasDestinationError)
	{
		cout << "The radix must be an integer in the range from 2 to 36 inclusive\n" 
			<< "Invalid destination notation\n";
	}

	if (wasSourceError || wasDestinationError || wasTo10TranslatorError)
	{
		return 1;
	}

	bool wasFrom10TranslatorError = false;
	const std::string valueView = IntToString(value10, destination, wasFrom10TranslatorError);
	if (wasFrom10TranslatorError)
	{
		return 1;
	}

	cout << valueView << std::endl;
	return 0;
}