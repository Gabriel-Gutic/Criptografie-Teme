#pragma once


class Coefficient
{
public:
	Coefficient(const std::initializer_list<Integer>& list = { 0 });
	Coefficient(const Integer& term, int power);
	Coefficient(const Coefficient& other) = default;
	Coefficient& operator=(const Coefficient& other) = default;
	~Coefficient() = default;

	int GetDegree() const;
	int GetCount() const;
	const std::vector<Integer>& GetTerms() const;

	Integer Evaluate(Integer a, Integer n) const;

	Coefficient operator-() const;
	friend Coefficient operator+(const Coefficient& c1, const Coefficient& c2);
	friend Coefficient operator-(const Coefficient& c1, const Coefficient& c2);
	friend Coefficient operator*(const Coefficient& c1, const Coefficient& c2);
	friend Coefficient operator%(const Coefficient& c, int n);
	friend bool operator==(const Coefficient& c, const Integer& n);

	friend std::ostream& operator<<(std::ostream& os, const Coefficient& c);
private:
	std::vector<Integer> m_Terms;
};