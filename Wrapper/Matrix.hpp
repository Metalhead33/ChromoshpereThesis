#ifndef MATRIX_HPP
#define MATRIX_HPP
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
#include <cstring>
#include <initializer_list>
template < typename T, int _width, int _height > struct Matrix {
	// Data
	typedef Matrix< T, _height, _width > TransposedMatrix;
	typedef std::initializer_list< T > Initializer;
	static const int width = _width;
	static const int height = _height;
	static const int linearSize = _width * _height;
	static const size_t sizeInBytes = _width * _height * sizeof( T );
	T data[_width * _height];
	// Constructor
	Matrix( ) { std::memset( data, 0, sizeInBytes ); }
	Matrix( const Matrix &cpy ) { std::memcpy( data, cpy.data, sizeInBytes ); }
	Matrix( const T *cpy ) { std::memcpy( data, cpy, sizeInBytes ); }
	Matrix( const Initializer &cpy ) {
	std::memset( data, 0, sizeInBytes );
	int i = 0;
	auto it = cpy.begin( );
	for ( ; i < linearSize && it != cpy.end( ); ++i, ++it ) {
		data[i] = *it;
	}
	}
	T *operator[]( int id ) { return &data[id * width]; }
	const T *operator[]( int id ) const { return &data[id * width]; }
	void operator+=( const Matrix &b ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		( *this )[y][x] += b[y][x];
	}
	}
	void operator+=( const T &b ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		( *this )[y][x] += b;
	}
	}
	void operator-=( const Matrix &b ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		( *this )[y][x] -= b[y][x];
	}
	}
	void operator-=( const T &b ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		( *this )[y][x] -= b;
	}
	}
	void operator*=( const Matrix &b ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		( *this )[y][x] *= b[y][x];
	}
	}
	void operator*=( const T &b ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		( *this )[y][x] *= b;
	}
	}
	void operator/=( const Matrix &b ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		( *this )[y][x] /= b[y][x];
	}
	}
	void operator/=( const T &b ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		( *this )[y][x] /= b;
	}
	}
	void operator%=( const Matrix &b ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		( *this )[y][x] %= b[y][x];
	}
	}
	void operator%=( const T &b ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		( *this )[y][x] %= b;
	}
	}
	Matrix &operator++( ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		++( *this )[y][x];
	}
	return *this;
	}
	Matrix operator++( int ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		++( *this )[y][x];
	}
	return *this;
	}
	Matrix &operator--( ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		++( *this )[y][x];
	}
	return *this;
	}
	Matrix operator--( int ) {
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		++( *this )[y][x];
	}
	return *this;
	}

	Matrix operator+( const Matrix &b ) const {
	Matrix tmp = *this;
	tmp += b;
	return tmp;
	}
	Matrix operator+( const T &b ) const {
	Matrix tmp = *this;
	tmp += b;
	return tmp;
	}
	Matrix operator-( const Matrix &b ) const {
	Matrix tmp = *this;
	tmp -= b;
	return tmp;
	}
	Matrix operator-( const T &b ) const {
	Matrix tmp = *this;
	tmp -= b;
	return tmp;
	}
	Matrix operator*( const Matrix &b ) const {
	Matrix tmp = *this;
	tmp *= b;
	return tmp;
	}
	Matrix operator*( const T &b ) const {
	Matrix tmp = *this;
	tmp *= b;
	return tmp;
	}
	Matrix operator/( const Matrix &b ) const {
	Matrix tmp = *this;
	tmp /= b;
	return tmp;
	}
	Matrix operator/( const T &b ) const {
	Matrix tmp = *this;
	tmp /= b;
	return tmp;
	}
	Matrix operator%( const Matrix &b ) const {
	Matrix tmp = *this;
	tmp %= b;
	return tmp;
	}
	Matrix operator%( const T &b ) const {
	Matrix tmp = *this;
	tmp %= b;
	return tmp;
	}

	Matrix operator!( ) const {
	Matrix tmp = *this;
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		tmp[y][x] = !( tmp[y][x] );
	}
	return tmp;
	}
	Matrix operator&&( const Matrix &b ) const {
	Matrix tmp = *this;
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		tmp[y][x] = ( *this )[y][x] && b[y][x];
	}
	return tmp;
	}
	Matrix operator||( const Matrix &b ) const {
	Matrix tmp = *this;
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		tmp[y][x] = ( *this )[y][x] && b[y][x];
	}
	return tmp;
	}

	TransposedMatrix transpose( ) const {
	TransposedMatrix tmp;
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		tmp[x][y] = ( *this )[y][x];
	}
	return tmp;
	}
	T scalarMul( const Matrix &b ) const {
	T tmp;
	memset( &tmp, 0, sizeof( T ) );
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y )
		tmp += ( *this )[y][x] * b[y][x];
	}
	return tmp;
	}
	T convolve( const Matrix &b ) const {
	return scalarMul( b ) / T( linearSize );
	}
	T sum( ) const {
	T tmp;
	memset( &tmp, 0, sizeof( T ) );
	for ( int x = 0; x < width; ++x ) {
		for ( int y = 0; y < height; ++y ) {
		tmp += ( *this )[y][x];
		}
	}
	return tmp;
	}
	T avg( ) const { return sum( ) / T( linearSize ); }
};

typedef Matrix< float, 3, 3 > fmat3x3;
typedef Matrix< float, 5, 5 > fmat5x5;
typedef Matrix< float, 7, 7 > fmat7x7;

#endif // MATRIX_HPP
