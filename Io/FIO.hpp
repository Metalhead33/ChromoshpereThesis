#pragma once
/*
Copyright 2019 Metalhead33

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <cstdint>
#include "Global.hpp"
#include <vector>

namespace Abstract {

typedef std::vector<uint8_t> byteBuffer;
typedef std::vector<std::string> stringBuffer;
DEFINE_CLASS(FIO)
class FIO {
public:
	virtual ~FIO() = default;
	virtual int64_t read(void* data, int64_t size) = 0;
	virtual int64_t seek(int64_t position) = 0;
	virtual int64_t tell() = 0;
	virtual int64_t size() = 0;
	virtual int64_t write(const void* data, int64_t size) = 0;
	virtual char getc() = 0;
	virtual byteBuffer loadIntoBuffer() = 0;
	virtual std::string stringize() = 0;
private:

};

}
