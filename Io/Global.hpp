#pragma once
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
#include <cstdint>
#include <exception>
#include <experimental/propagate_const>
#include <iostream>
#include <memory>
#include <thread>

#define MIN( a, b )                                                            \
	( ( ( a ) < ( b ) ) ? ( a ) : ( b ) ) // min: Choose smaller of two scalars.
#define MAX( a, b )                                                            \
	( ( ( a ) > ( b ) ) ? ( a ) : ( b ) ) // max: Choose greater of two scalars.
#define CLAMP( a, mi, ma )                                                     \
	min( max( a, mi ), ma ) // clamp: Clamp value into set range.

#ifndef _MSC_VER
#define __enforce_inlining __attribute__( ( always_inline ) )
#elif
#define __enforce_inlining __forceinline
#endif

// From util.h - Written by Daniël Sonck
#define DEFINE_PTR( a )                                                        \
	typedef a *p##a;                                                           \
	typedef std::shared_ptr< a > s##a;                                         \
	typedef std::weak_ptr< a > w##a;                                           \
	typedef std::unique_ptr< a > u##a;                                         \
	typedef std::experimental::propagate_const< std::unique_ptr< a > > pimpl##a;

#define DEFINE_PTR2( s, a )                                                    \
	typedef s::a *p##a;                                                        \
	typedef std::shared_ptr< s::a > s##a;                                      \
	typedef std::weak_ptr< s::a > w##a;                                        \
	typedef std::unique_ptr< a > u##a;

#define DEFINE_CLASS( klass )                                                  \
	class klass;                                                               \
	DEFINE_PTR( klass )

#define DEFINE_STRUCT( klass )                                                 \
	struct klass;                                                              \
	DEFINE_PTR( klass )

typedef std::shared_ptr< std::thread > ThreadPointer;

// End of former util.h

// Some useful defines
#define EXCEPTION( A, B )                                                      \
	struct A : public std::exception {                                         \
	const char *what( ) const throw( ) { return B; }                       \
	};

#if defined( DEBUG ) || defined( NDEBUG ) || defined( _DEBUG ) ||              \
	defined( DEBUG_BUILD )
#define IF_DEBUG( ... ) __VA_ARGS__
#else
#define IF_DEBUG( ... )
#endif /* DEBUG */
