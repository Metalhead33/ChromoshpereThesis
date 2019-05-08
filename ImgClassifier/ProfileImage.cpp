#include "ProfileImage.hpp"
#include "../Wrapper/BlurImage.hpp"
#include "../Wrapper/PixelWrapper.hpp"
#include "../Wrapper/RgbType.hpp"
#include <limits>

typedef PixelWrapper< float > GreyscalePixels;
typedef PixelWrapper< PixelRgb8 > Rgb8Pixels;

/*Mh::ImageWrapper convertToWeighedGreyscale(const Mh::ImageWrapper& img) //
FreeImage does not use weighing when converting to greyscale
{
	img.convertTo24Bits();
	// We are going to assume that the image is using 8-bit RGB - ordered
RGB in Big Endian, BGR in Little Endian. Mh::ImageWrapper
tmp(Mh::ImageFormat::FLOAT,img.getWidth(),img.getHeight(),32); // Create empty
greyscale image Rgb8Pixels
origin(reinterpret_cast<PixelRgb8*>(img.getBytes()),img.getWidth(),img.getHeight());
	GreyscalePixels
profile(reinterpret_cast<float*>(tmp.getBytes()),tmp.getWidth(),tmp.getHeight());
	for(int x = 0; x < origin.width; ++x)
	{
		for(int y = 0; y < origin.height;++y)
		{
			float tmppix = 0.0f;
			tmppix += (float(origin[y][x].r) / 255.0f) * 0.2989f;
			tmppix += (float(origin[y][x].g) / 255.0f) * 0.5870f;
			tmppix += (float(origin[y][x].b) / 255.0f) * 0.1140f;
			profile[y][x] = tmppix;
		}
	}
	return tmp;
}*/

Mh::ImageWrapper produceSharpnessProfile( const Mh::ImageWrapper &img,
					  int blurRadius, float *fMin,
					  float *fMax, float *fAvg ) {
	// First check if valid
	if ( !img.hasPixels( ) )
	return Mh::ImageWrapper( );
	Mh::ImageWrapper sharpGreyscale = img;
	sharpGreyscale.convertToFloat( );
	Mh::ImageWrapper blurredGreyscale =
	greyscaleBlurAndCopy( sharpGreyscale, blurRadius );
	GreyscalePixels sharpGreyscalePixels(
	reinterpret_cast< float * >( sharpGreyscale.getBytes( ) ),
	sharpGreyscale.getWidth( ), sharpGreyscale.getHeight( ) );
	GreyscalePixels blurredGreyscalePixels(
	reinterpret_cast< float * >( blurredGreyscale.getBytes( ) ),
	blurredGreyscale.getWidth( ), blurredGreyscale.getHeight( ) );
	for ( int x = 0; x < sharpGreyscalePixels.width; ++x ) {
	for ( int y = 0; y < sharpGreyscalePixels.height; ++y ) {
		// We measure the difference between the sharp and blurred to create
		// a profile
		sharpGreyscalePixels[y][x] =
		std::max( sharpGreyscalePixels[y][x],
			  blurredGreyscalePixels[y][x] ) -
		std::min( sharpGreyscalePixels[y][x],
			  blurredGreyscalePixels[y][x] );
	}
	}
	// sharpGreyscale.convertToUINT16(); // Let's save some space // No, let's
	// NOT, because it errors out
	if ( fMin || fMax || fAvg ) {
	int imageCounted = 0;
	if ( fMin )
		*fMin = std::numeric_limits< float >::max( );
	if ( fMax )
		*fMax = std::numeric_limits< float >::min( );
	if ( fAvg )
		*fAvg = 0.0f;
	for ( int x = 0; x < sharpGreyscalePixels.width; ++x ) {
		for ( int y = 0; y < sharpGreyscalePixels.height; ++y ) {
		++imageCounted;
		if ( fAvg )
			*fAvg += sharpGreyscalePixels[y][x];
		if ( fMin )
			*fMin = std::min( *fMin, sharpGreyscalePixels[y][x] );
		if ( fMax )
			*fMax = std::max( *fMax, sharpGreyscalePixels[y][x] );
		}
		if ( fAvg )
		*fAvg /= float( imageCounted );
	}
	}
	return sharpGreyscale;
}
Mh::ImageWrapper sharpnessComposite( const Mh::ImageWrapper &originA,
					 const Mh::ImageWrapper &originB,
					 int blurRadius ) {
	// Better check if they are the same dimensions, otherwise it won't work.
	if ( ( originA.getWidth( ) != originB.getWidth( ) ) ||
	 ( originA.getHeight( ) != originB.getHeight( ) ) )
	return Mh::ImageWrapper( );
	Mh::ImageWrapper sharpnessA =
	produceSharpnessProfile( originA, blurRadius );
	Mh::ImageWrapper sharpnessB =
	produceSharpnessProfile( originB, blurRadius );
	// Create a new image
	Mh::ImageWrapper newImage( Mh::ImageFormat::BITMAP, originA.getWidth( ),
				   originA.getHeight( ), originA.getBPP( ),
				   originA.getRedMask( ), originA.getGreenMask( ),
				   originA.getBlueMask( ) );
	// Initialize the pixel pointers
	Rgb8Pixels originalPixelsA(
	reinterpret_cast< PixelRgb8 * >( originA.getBytes( ) ),
	originA.getWidth( ), originA.getHeight( ) );
	GreyscalePixels sharpnessPixelsA(
	reinterpret_cast< float * >( sharpnessA.getBytes( ) ),
	sharpnessA.getWidth( ), sharpnessA.getHeight( ) );
	Rgb8Pixels originalPixelsB(
	reinterpret_cast< PixelRgb8 * >( originB.getBytes( ) ),
	originB.getWidth( ), originB.getHeight( ) );
	GreyscalePixels sharpnessPixelsB(
	reinterpret_cast< float * >( sharpnessB.getBytes( ) ),
	sharpnessB.getWidth( ), sharpnessB.getHeight( ) );
	Rgb8Pixels newImagePixels(
	reinterpret_cast< PixelRgb8 * >( newImage.getBytes( ) ),
	newImage.getWidth( ), newImage.getHeight( ) );
	for ( int x = 0; x < newImagePixels.width; ++x ) {
	for ( int y = 0; y < newImagePixels.height; ++y ) {
		if ( sharpnessPixelsA[y][x] >= sharpnessPixelsB[y][x] )
		newImagePixels[y][x] = originalPixelsA[y][x];
		else
		newImagePixels[y][x] = originalPixelsB[y][x];
	}
	}
	return newImage;
}
