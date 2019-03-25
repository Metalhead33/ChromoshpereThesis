#ifndef NORMALIZE_HPP
#define NORMALIZE_HPP
/*
Copyright 2019 Metalhead33

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include <limits>
template <typename T> constexpr float normalize(T value)
{
	return value < 0
		? -static_cast<float>(value) / static_cast<float>(std::numeric_limits<T>::min()) * -1.0f
		:  static_cast<float>(value) / static_cast<float>(std::numeric_limits<T>::max());
}
template <typename T> constexpr T denormalizeAs(float value)
{
	return value >= 0.0f ?
		static_cast<T>(static_cast<float>(std::numeric_limits<T>::max()) * value)
		: static_cast<T>(static_cast<float>(std::numeric_limits<T>::min()) * (value*-1.0f));
}

#endif // NORMALIZE_HPP
