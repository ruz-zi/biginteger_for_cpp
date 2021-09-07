#include "Big_Integer.hpp"

const std::string& Bigint::to_string() const
{
	std::string _str = _negative ? "-" : "";
	value_t *_ptr = _data + _size;
	while (_ptr != _data)
		_str += std::to_string(*--_ptr);
	return _str;
}