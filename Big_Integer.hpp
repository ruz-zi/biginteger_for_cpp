#ifndef BIG_INTEGER
#define BIG_INTEGER

#include <string>
#include <iostream>

using value_t = unsigned long long;

constexpr char		BASE_K	= 30;
constexpr value_t	BASE	= 1 << BASE_K;

class Bigint
{
public:
	Bigint();
	Bigint(long long);
	Bigint(unsigned long long);
	Bigint(const Bigint&);
	Bigint(Bigint&&);
	Bigint(const char *);
	Bigint(const std::string&);
	template <typename Tp> Bigint(const Tp&);
	template <typename Tp> Bigint(Tp&&);
	~Bigint();
	
	const bool operator<(Bigint&&) const;
	const bool operator>(Bigint&&) const;
	const bool operator<=(Bigint&&) const;
	const bool operator>=(Bigint&&) const;
	const bool operator==(Bigint&&) const;
	const bool operator!=(Bigint&&) const;
	template <typename Tp> const bool operator<(Tp&& __x) const;
	template <typename Tp> const bool operator>(Tp&& __x) const;
	template <typename Tp> const bool operator<=(Tp&& __x) const;
	template <typename Tp> const bool operator>=(Tp&& __x) const;
	template <typename Tp> const bool operator==(Tp&& __x) const;
	template <typename Tp> const bool operator!=(Tp&& __x) const;
	
	const Bigint operator=(Bigint&&);
	const Bigint operator-() const {
		Bigint ret = *this;
		ret._negative ^= 1;
		return ret;
	}
	const Bigint operator+(const Bigint&) const
	{
		Bigint result = *this;
		return result;
	}
	
private:
	value_t	*a;
	size_t	_capa;
	size_t	_size;
	bool	_negative;
	
	void copy(value_t *, value_t *, size_t);
	void alloc(size_t);
	void realloc(size_t);
	void normalize();
};

#endif