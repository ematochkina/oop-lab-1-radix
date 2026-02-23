#include <iostream>
#include "Translator.h"

using namespace std;

void PrintUseageFormat()
{
	cout << "Usage: radix.exe <source notation> <destination notation> <value>\n";
}

void ProcessTranslatorErrorStatus(TranslatorStatus translatorStatus)
{
	switch (translatorStatus)
	{
	case TranslatorStatus::RadixOutOfRange:
		std::cout << "The radix must be an integer in the range from " << MinNotation
				  << " to " << MaxNotation << " inclusive\n";
		break;
	case TranslatorStatus::HasInvalidCharacter:
		std::cout << "The value has invalid characters in source notation\n";
		break;
	case TranslatorStatus::ValueNotSpecified:
		std::cout << "No value specified\n";
		break;
	case TranslatorStatus::WasOverflow: 
		std::cout << "Converting value to decimal with overflow\n";
		break;
	case TranslatorStatus::Success:
		break;
	default:
		break;
	}
}

int main(int argc, char* argv[])
{
	if (argc != 4)
	{
		cout << "Invalid arguments count\n";
		PrintUseageFormat();
		return 1;
	}

	TranslatorStatus sourceTranslatorStatus = TranslatorStatus::Success;
	const int source = StringToInt(argv[1], 10, sourceTranslatorStatus);
	const bool wasSourceError = IsErrorStatus(sourceTranslatorStatus);
	if (wasSourceError)
	{
		cout << "Invalid source notation:\n";
		ProcessTranslatorErrorStatus(sourceTranslatorStatus);
	}

	TranslatorStatus valueTranslatorStatus = TranslatorStatus::Success;
	const int valueDec = wasSourceError ? 0 : StringToInt(argv[3], source, valueTranslatorStatus);
	const bool wasValueToDecError = IsErrorStatus(valueTranslatorStatus);
	if (wasValueToDecError)
	{
		cout << "Invalid value:\n";
		ProcessTranslatorErrorStatus(valueTranslatorStatus);
	}

	TranslatorStatus destinationTranslatorStatus = TranslatorStatus::Success;
	const int destination = StringToInt(argv[2], 10, destinationTranslatorStatus);
	const bool wasDestinationError = IsErrorStatus(destinationTranslatorStatus);
	if (wasDestinationError)
	{
		cout << "Invalid destination notation:\n";
		ProcessTranslatorErrorStatus(destinationTranslatorStatus);
	}

	if (wasSourceError || wasDestinationError || wasValueToDecError)
	{
		return 1;
	}

	const std::string valueDest = IntToString(valueDec, destination, valueTranslatorStatus);
	if (IsErrorStatus(valueTranslatorStatus))
	{
		cout << "Invalid value:\n";
		ProcessTranslatorErrorStatus(valueTranslatorStatus);
		return 1;
	}

	cout << valueDest << std::endl;
	return 0;
}