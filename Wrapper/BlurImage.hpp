#ifndef BLURIMAGE_HPP
#define BLURIMAGE_HPP
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
#include "MhImageWrapper.hpp"
enum class BlurType : unsigned char {
	box_blur_3x3,
	box_blur_5x5,
	box_blur_7x7
};

Mh::ImageWrapper processGreyscale(const  Mh::ImageWrapper& image, const std::vector<float>& kernel, bool vertical);
Mh::ImageWrapper processColoured(const  Mh::ImageWrapper& image, const std::vector<float>& kernel, bool vertical);

void greyscaleBlurImage( Mh::ImageWrapper &image,
		BlurType blurType ); // Destroys the original image!
Mh::ImageWrapper
greyscaleBlurAndCopy( const Mh::ImageWrapper &image,
		 BlurType blurType ); // Des NOT destroy the original image!
Mh::ImageWrapper rgbBlurAndCopy( const Mh::ImageWrapper &image, int blurRadius );

Mh::ImageWrapper greyscaleSharpenAndCopy( const Mh::ImageWrapper &image, int sharpRadius );
Mh::ImageWrapper rgbSharpenAndCopy( const Mh::ImageWrapper &image, int sharpRadius );

void greyscaleBlurImage( Mh::ImageWrapper &image,
		int blurRadius ); // Destroys the original image!
Mh::ImageWrapper
greyscaleBlurAndCopy( const Mh::ImageWrapper &image,
		 int blurRadius ); // Des NOT destroy the original image!

#endif // BLURIMAGE_HPP
