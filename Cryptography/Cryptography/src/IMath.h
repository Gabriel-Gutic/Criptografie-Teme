#pragma once
#include "Integer.h"


class IMath
{
public:
	static int DigitCount(long long n);
	static int BitCount(long long n);
	static Integer Cmmdc(const Integer& a, const Integer& b);
};