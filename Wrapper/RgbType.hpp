#ifndef RGBTYPE_HPP
#define RGBTYPE_HPP
#include <cstdint>
#ifdef _WIN32
#define __BYTE_ORDER __LITTLE_ENDIAN
#else
#include <endian.h>
#endif

#pragma pack( push )
#pragma pack( 1 )
struct BgrPix {
	uint8_t b;
	uint8_t g;
	uint8_t r;
};
#pragma pack( pop )

#pragma pack( push )
#pragma pack( 1 )
struct RgbPix {
	uint8_t r;
	uint8_t g;
	uint8_t b;
};
#pragma pack( pop )

#if __BYTE_ORDER == __LITTLE_ENDIAN
typedef BgrPix PixelRgb8;
#elif __BYTE_ORDER == __BIG_ENDIAN
typedef RgbPix PixelRgb8;
#else
#error Unknown endianness!
#endif

#endif // RGBTYPE_HPP
