#include "Translator.h"
#include <array>
#include <iostream>
#include <limits>

namespace
{

const std::array<char, 36> alphabet = {
	'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
	'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
	'U', 'V', 'W', 'X', 'Y', 'Z'
};

const int minNotation = 2;
const int maxNotation = alphabet.size();

}

int StringToInt(const std::string& str, int radix, bool& wasError)
{
	wasError = true;

	if (str.empty())
	{
		std::cout << "No value specified\n";
		return 0;
	}

	if (radix < minNotation || radix > maxNotation)
	{
		std::cout << "The radix must be an integer in the range from 2 to 36 inclusive\n"
				  << "Invalid source notation\n";
		return 0;
	}

	const bool isNegative = str[0] == '-';
	const bool hasSign = isNegative || str[0] == '+';
	const size_t symbolCount = str.length();
	if (hasSign && symbolCount == 1)
	{
		std::cout << "No value specified\n";
		return 0;
	}

	const int lowBorder = isNegative
		? std::numeric_limits<int>::min()
		: -std::numeric_limits<int>::max();
	const int lowBorderDivRadix = lowBorder / radix;
	int value = 0;
	for (size_t i = hasSign ? 1 : 0; i < symbolCount; i++)
	{
		auto it = std::find(alphabet.begin(), alphabet.end(), std::toupper(str[i]));
		const int digit = it == std::end(alphabet) 
			? -1 
			: static_cast<int>(it - std::begin(alphabet));
		if (digit < 0 || digit >= radix)
		{
			std::cout << "Invalid character \'" << str[i] << "\'"
					  << " in \'" << str << "\'"
					  << " in " << radix << "-notation\n";
			return 0;
		}

		if (value < lowBorderDivRadix)
		{
			std::cout << "Converting value to decimal with overflow\n";
			return 0;
		}
		value *= radix;
		
		if (value < lowBorder + digit)
		{
			std::cout << "Converting value to decimal with overflow\n";
			return 0;
		}
		value -= digit;
	}

	wasError = false;
	return isNegative ? value : std::abs(value);
}

std::string IntToString(int n, int radix, bool& wasError)
{
	wasError = true;

	if (radix < minNotation || radix > maxNotation)
	{
		std::cout << "The radix must be an integer in the range from 2 to 36 inclusive\n"
				  << "Invalid destination notation\n";
		return "";
	}

	const bool isNegative = n < 0;
	std::string str = "";
	do
	{
		const int remainder = std::abs(n % radix);
		str = alphabet[remainder] + str;
		n /= radix;
	} while (n != 0);
	

	wasError = false;
	return isNegative ? '-' + str : str;
}