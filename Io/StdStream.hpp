/*
 * File:   StdStream.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 23., 17:46
 */

#ifndef STDSTREAM_HPP
#define STDSTREAM_HPP
/*
Copyright 2019 Metalhead33

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#include "FIO.hpp"
#include <cstdio>
#include <string>
class StdStream : public Abstract::FIO {
  public:
	StdStream( );
	StdStream( const std::string &newpath, bool ro = false );
	~StdStream( );
	virtual int64_t read( void *data, int64_t size );
	virtual int64_t seek( int64_t position );
	virtual int64_t tell( );
	virtual int64_t size( );
	virtual int64_t write( const void *data, int64_t size );
	virtual char getc( );
	std::string GetPath( );
	void close( );
	bool IsActive( );
	bool open( const std::string &newpath, bool ro = false );

	static Abstract::sFIO createReader( const std::string &newpath );
	static Abstract::sFIO createWriter( const std::string &newpath );

	virtual Abstract::byteBuffer loadIntoBuffer( );
	virtual std::string stringize( );

  private:
	std::string path;
	FILE *chandle;
	bool active;
};
#endif /* STDSTREAM_HPP */
