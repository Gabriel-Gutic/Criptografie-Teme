#pragma once
#include "Integer.h"


class Prime
{
public:
	static bool Divisions(const Integer& n);
	static bool Fermat(const Integer& n, int nr_incercari);
	static bool MillerRabin(const Integer& n, int nr_incercari);
};