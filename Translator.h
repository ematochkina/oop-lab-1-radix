#pragma once
#include <string>

const size_t MinNotation = 2;
const size_t MaxNotation = 36;

enum class TranslatorStatus
{
	RadixOutOfRange,
	HasInvalidCharacter,
	ValueNotSpecified,
	WasOverflow,
	Success
};

int StringToInt(const std::string& str, int radix, TranslatorStatus& translatorStatus);

std::string IntToString(int n, int radix, TranslatorStatus& translatorStatus);

bool IsErrorStatus(TranslatorStatus translatorStatus);