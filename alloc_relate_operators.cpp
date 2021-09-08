#include "Big_Integer.hpp"

Bigint& Bigint::operator=(__int128_t __x)
{
	_assign(__x);
	return *this;
}

Bigint& Bigint::operator=(const char *__s)
{
	_assign(__s);
	return *this;
}

Bigint& Bigint::operator=(const std::string& __s)
{
	_assign(__s.c_str());
	return *this;
}

Bigint& Bigint::operator=(const Bigint& __x)
{
	_assign(__x);
	return *this;
}

bool Bigint::operator==(const Bigint& __rhs) const
{
	return (_sign == __rhs._sign && _comp_abs(__rhs) == 0);
}
bool Bigint::operator!=(const Bigint& __rhs) const
{
	return !(*this == __rhs);
}
bool Bigint::operator< (const Bigint& __rhs) const
{
	if (_sign != __rhs._sign)
		return _sign;
	return _sign ? _comp_abs(__rhs) > 0 : _comp_abs(__rhs) < 0;
}
bool Bigint::operator> (const Bigint& __rhs) const
{
	return __rhs < *this;
}
bool Bigint::operator<=(const Bigint& __rhs) const
{
	return !(__rhs < *this);
}
bool Bigint::operator>=(const Bigint& __rhs) const
{
	return !(*this < __rhs);
}

