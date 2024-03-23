#include "pch.h"
#include "IMath.h"

int IMath::DigitCount(long long n)
{
    return n == 0 ? 1 : ((int)log10(abs(n)) + 1);
}

int IMath::BitCount(long long n)
{
    return n == 0 ? 1 : ((int)log2(abs(n)) + 1);
}
