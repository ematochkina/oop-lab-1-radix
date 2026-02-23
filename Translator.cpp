#include "Translator.h"
#include <array>
#include <iostream>
#include <limits>
#include <vector>
#include <algorithm>
#include <cctype>

namespace
{

const int code9 = static_cast<int>('9');
const int codeA = static_cast<int>('A');

struct DigitsView
{
	bool hasInvalidSymbols = false;
	std::vector<size_t> digits;
	bool isSigned = false;
	bool isNegative = false;

	bool IsEmpty() const
	{
		return digits.empty();
	}
};

bool IsRadixOutOfRange(int radix)
{
	return radix < MinNotation || radix > MaxNotation;
}

bool IsDigitSymbol(char symbol)
{
	return symbol >= '0' && symbol <= '9';
}

bool IsUpperAlphabetSymbol(char symbol)
{
	return symbol >= 'A' && symbol <= 'Z';
}

size_t CharToDigitByRadix(char element, int radix, bool& outOfRange)
{
	element = std::toupper(element);

	const size_t value = IsDigitSymbol(element) 
		? element - '0' 
		: IsUpperAlphabetSymbol(element) 
		? (element - 'A') + 10
		: MaxNotation;
	outOfRange = value >= radix;

	return outOfRange ? 0 : value;
}

char DigitToChar(size_t digit)
{
	return digit < 10 ? '0' + digit : 'A' + (digit - 10);
}

DigitsView GetDigitsView(const std::string& str, int radix)
{
	DigitsView info;
	if (str.empty())
	{
		return info;
	}

	const size_t len = str.length();
	info.isNegative = str[0] == '-';
	info.isSigned = info.isNegative || str[0] == '+';
	if (info.isSigned && len == 1)
	{
		return info;
	}

	info.digits.reserve(len);
	for (size_t i = info.isSigned ? 1 : 0; i < len; i++)
	{
		const size_t digit = CharToDigitByRadix(str[i], radix, info.hasInvalidSymbols);
		if (info.hasInvalidSymbols)
		{
			return info;
		}

		info.digits.push_back(digit);
	}
	return info;
}

int DigitsToValue(const std::vector<size_t>& digits, bool isNegative, int radix, bool& wasOverflow)
{
	wasOverflow = false;
	const int lowBorder = isNegative
		? std::numeric_limits<int>::min()
		: -std::numeric_limits<int>::max();
	const int lowBorderDivRadix = lowBorder / radix;
	int value = 0;
	for (int digit : digits)
	{
		if (value < lowBorderDivRadix)
		{
			wasOverflow = true;
			return 0;
		}
		value *= radix;

		if (value < lowBorder + digit)
		{
			wasOverflow = true;
			return 0;
		}
		value -= digit;
	}

	return isNegative ? value : std::abs(value);
}

} // namespace

bool IsErrorStatus(TranslatorStatus translatorStatus)
{
	return translatorStatus != TranslatorStatus::Success;
}

int StringToInt(const std::string& str, int radix, TranslatorStatus& translatorStatus)
{
	translatorStatus = TranslatorStatus::Success;

	if (IsRadixOutOfRange(radix))
	{
		translatorStatus = TranslatorStatus::RadixOutOfRange;
		return 0;
	}

	DigitsView valueDigitsView = GetDigitsView(str, radix);
	if (valueDigitsView.hasInvalidSymbols)
	{
		translatorStatus = TranslatorStatus::HasInvalidCharacter;
		return 0;
	}

	if (valueDigitsView.IsEmpty())
	{
		translatorStatus = TranslatorStatus::ValueNotSpecified;
		return 0;
	}

	bool wasOverflow = false;
	const int value = DigitsToValue(valueDigitsView.digits, valueDigitsView.isNegative, radix, wasOverflow);
	if (wasOverflow)
	{
		translatorStatus = TranslatorStatus::WasOverflow;
		return 0;
	}
	
	return value;
}

std::string IntToString(int n, int radix, TranslatorStatus& translatorStatus)
{
	translatorStatus = TranslatorStatus::Success;

	if (IsRadixOutOfRange(radix))
	{
		translatorStatus = TranslatorStatus::RadixOutOfRange;
		return "";
	}

	const bool isNegative = n < 0;
	std::string str;
	do
	{
		const int remainder = std::abs(n % radix);
		str.push_back(DigitToChar(remainder));
		n /= radix;
	} while (n != 0);

	if (isNegative)
	{
		str.push_back('-');
	}

	std::reverse(str.begin(), str.end());

	return str;
}