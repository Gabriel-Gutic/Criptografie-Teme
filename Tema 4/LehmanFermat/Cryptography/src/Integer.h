#pragma once


class Integer
{
public:
	static Integer Zero;
	static Integer One;
	static Integer Nan;
public:
	Integer(long long n = 0);
	Integer(std::string_view n);
	Integer(const Integer& other) = default; 
	Integer& operator=(const Integer& other) = default;
	~Integer() = default;

	bool IsPositive() const;
	bool IsNegative() const;
	bool IsNan() const;

	int DigitCount() const;
	std::string ToString() const;
	Integer Abs() const;
	Integer Sqrt() const;
	Integer Log2() const;
	Integer Log10() const;
	Integer MultiplyByPower10(int power) const;

	static Integer Pow(const Integer& n, const Integer& p);
	// a ^ b (mod n)
	static Integer Pow(const Integer& a, const Integer& b, const Integer& n);

	Integer operator-() const;
	friend Integer operator+(const Integer& a, const Integer& b);
	friend Integer operator-(const Integer& a, const Integer& b);
	friend Integer operator*(const Integer& a, const Integer& b);

	static std::pair<Integer, Integer> Euler(const Integer& a, const Integer& b);
	friend Integer operator/(const Integer& a, const Integer& b);
	friend Integer operator%(const Integer& a, const Integer& b);

	Integer& operator+=(const Integer& a);
	Integer& operator-=(const Integer& a);
	Integer& operator*=(const Integer& a);
	Integer& operator/=(const Integer& a);
	Integer& operator%=(const Integer& a);
	Integer& operator++();
	Integer operator++(int);
	Integer& operator--();
	Integer operator--(int);

	friend bool operator==(const Integer& a, const Integer& b);
	friend bool operator!=(const Integer& a, const Integer& b);
	friend bool operator<=(const Integer& a, const Integer& b);
	friend bool operator>=(const Integer& a, const Integer& b);
	friend bool operator<(const Integer& a, const Integer& b);
	friend bool operator>(const Integer& a, const Integer& b);

	char operator[](int index) const;

	friend std::ostream& operator<<(std::ostream& os, const Integer& n);
	friend std::istream& operator>>(std::istream& is, Integer& n);
private:
	static Integer GetNan();
private:
	// 0 = positive
	// 1 = negative
	bool m_Sign; 
	std::vector<char> m_Digits;
};