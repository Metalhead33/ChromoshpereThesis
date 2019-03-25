#ifndef CLAMP_HPP
#define CLAMP_HPP
#include <algorithm>
#if __cplusplus > 201402L
  // C__17 code here
#else
namespace std {

template <typename T> const T& clamp(const T& YourNumber, const T& lower, const T& upper)
{
	return min(upper,max(lower,YourNumber));
}

}
#endif

#endif // CLAMP_HPP
