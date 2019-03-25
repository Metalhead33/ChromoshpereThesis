#ifndef PIXELWRAPPER_HPP
#define PIXELWRAPPER_HPP
#include "Clamp.hpp"

template <typename PixelType> struct PixelWrapper {
	// Typedefs
	typedef PixelType PIXEL;
	typedef PIXEL* pixelPointer;
	typedef PIXEL* const constantPixelPointer;
	struct RowWrapper {
		constantPixelPointer rowPointer;
		const int width;
		const float floatWith;
		// Direct indexing
		PIXEL& operator[](int index) { return rowPointer[std::clamp(index,0,width-1)]; }
		const PIXEL& operator[](int index) const { return rowPointer[std::clamp(index,0,width-1)]; }
		PIXEL& accessPixel(int index) { return rowPointer[std::clamp(index,0,width-1)]; }
		const PIXEL& accessPixel(int index) const { return rowPointer[std::clamp(index,0,width-1)]; }
		// Floating point indexing
		PIXEL& operator[](float index)
		{
			return accessPixel(int(std::clamp(index,0.0f,1.0f)*floatWith));
		}
		const PIXEL& operator[](float index) const
		{
			return accessPixel(int(std::clamp(index,0.0f,1.0f)*floatWith));
		}
		PIXEL& accessPixel(float index)
		{
			return accessPixel(int(std::clamp(index,0.0f,1.0f)*floatWith));
		}
		const PIXEL& accessPixel(float index) const
		{
			return accessPixel(int(std::clamp(index,0.0f,1.0f)*floatWith));
		}
		// Constructor
		RowWrapper(constantPixelPointer ptr, const int width, const float floatWith)
			: rowPointer(ptr), width(width), floatWith(floatWith)
		{
			;
		}
	};
	// Variables
	constantPixelPointer pixels;
	const int width; // the width of every single row
	const int height; // the height of every single column
	const float floatWith; // width minus one, but converted to float
	const float floatHeight; // height minus one, but converted to float

	// Not const
	RowWrapper operator[](int y) { return RowWrapper(&pixels[std::clamp(y,0,height-1) * width],width,floatWith) ; }
	RowWrapper getRow(int y) { return RowWrapper(&pixels[std::clamp(y,0,height-1) * width],width,floatWith) ; }
	RowWrapper operator[](float y) { getRow(int(std::clamp(y,0.0f,1.0f)*floatHeight)); }
	RowWrapper getRow(float y) { getRow(int(std::clamp(y,0.0f,1.0f)*floatHeight)); }
	// Const
	const RowWrapper operator[](int y) const { return RowWrapper(&pixels[std::clamp(y,0,height-1) * width],width,floatWith) ; }
	const RowWrapper getRow(int y) const { return RowWrapper(&pixels[std::clamp(y,0,height-1) * width],width,floatWith) ; }
	const RowWrapper operator[](float y) const { getRow(int(std::clamp(y,0.0f,1.0f)*floatHeight)); }
	const RowWrapper getRow(float y) const { getRow(int(std::clamp(y,0.0f,1.0f)*floatHeight)); }
	// Access pixel directly
	PIXEL& accessPixel(int x, int y)
	{
		return pixels[(std::clamp(y,0,height) * width) + std::clamp(x,0,width)];
	}
	PixelWrapper(pixelPointer ptr, int width, int height)
		: pixels(ptr), width(width), height(height),
		  floatWith(float(width-1)), floatHeight(float(height-1))
	{
		;
	}
};

#endif // PIXELWRAPPER_HPP
