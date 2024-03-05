#include "pch.h"
#include "Int2.h"

Int2::Int2(long long x, long long y)
	:m_X(x), m_Y(y)
{
}

long long Int2::GetX() const
{
	return m_X;
}

long long Int2::GetY() const
{
	return m_Y;
}

std::string Int2::ToString() const
{
	std::stringstream ss;
	ss << "(" << m_X << ", " << m_Y << ")";
	return ss.str();
}

Int2 operator+(const Int2& v1, const Int2& v2)
{
	return Int2(v1.m_X + v2.m_X, v1.m_Y + v2.m_Y);
}

Int2 operator-(const Int2& v1, const Int2& v2)
{
	return Int2(v1.m_X - v2.m_X, v1.m_Y - v2.m_Y);
}

Int2 operator*(long long scalar, const Int2& v)
{
	return Int2(scalar * v.m_X, scalar * v.m_Y);
}

Int2 operator*(const Int2& v, long long scalar)
{
	return Int2(scalar * v.m_X, scalar * v.m_Y);
}

std::ostream& operator<<(std::ostream& output, const Int2& v)
{
	output << v.ToString();
	return output;
}
