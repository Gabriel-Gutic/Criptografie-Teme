#pragma once
#include "Coefficient.h"


class Polynomial
{
public:
	Polynomial(const std::initializer_list<Coefficient>& list = { Coefficient() });
	Polynomial(const Coefficient& coef, int power);
	Polynomial(const Polynomial& other) = default;
	Polynomial& operator=(const Polynomial& other) = default;
	~Polynomial() = default;

	int GetDegree() const;
	int GetCount() const;
	const std::vector<Coefficient>& GetCoefficients() const;
	std::vector<Coefficient>& GetCoefficients();

	Polynomial Remainder(int power) const;

	// (x + a) ^ n
	static Polynomial NewtonCoefficients(int power);

	friend Polynomial operator%(const Polynomial& P, int n);

	friend Polynomial operator-(const Polynomial& P1, const Polynomial& P2);

	friend std::ostream& operator<<(std::ostream& os, const Polynomial& P);
private:
	std::vector<Coefficient> m_Coefficients;
};