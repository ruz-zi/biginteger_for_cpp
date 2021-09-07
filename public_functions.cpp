#include "Big_Integer.hpp"

std::string Bigint::to_string() const
{
	std::string _str = _negative ? "-" : "";
	value_t *_ptr = _data + _size;
	while (_ptr != _data)
		_str += std::to_string(*--_ptr);
	return _str;
}

void Bigint::swap(Bigint& __x)
{
	Bigint _tmp;
	_tmp._assign(__x);
	__x._assign(*this);
	_assign(_tmp);
}