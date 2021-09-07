#include "Big_Integer.hpp"

const Bigint& Bigint::operator-() const
{
	Bigint _res(*this);
	_res._negative ^= 1;
	return _res;
}

Bigint& Bigint::operator+=(const Bigint& __x)
{
	return *this;
}
Bigint& Bigint::operator-=(const Bigint& __x)
{
	return *this;
}
Bigint& Bigint::operator*=(const Bigint& __x)
{
	return *this;
}
Bigint& Bigint::operator/=(const Bigint& __x)
{
	return *this;
}
Bigint& Bigint::operator&=(const Bigint& __x)
{
	return *this;
}
Bigint& Bigint::operator|=(const Bigint& __x)
{
	return *this;
}
Bigint& Bigint::operator^=(const Bigint& __x)
{
	return *this;
}