#include "Big_Integer.hpp"

std::string Bigint::to_string() const
{
	assert(_size >= 1);
	register size_t _i;
	value_t *_ptr = _data + _size;
	std::string _str = (_negative ? "-" : "");
	
	_str += std::to_string(*--_ptr);
	while (_ptr-- != _data)
		for (_i = BASE / 10; _i > 0; _i /= 10)
			_str += *_ptr / _i % 10 + '0';
	return _str;
}

void Bigint::swap(Bigint& __x)
{
	Bigint _tmp;
	_tmp._assign(__x);
	__x._assign(*this);
	_assign(_tmp);
}