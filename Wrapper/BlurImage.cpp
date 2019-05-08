#include "BlurImage.hpp"
#include "Matrix.hpp"
#include "PixelWrapper.hpp"
#include <stdexcept>
#include <vector>
#include "../Wrapper/RgbType.hpp"
typedef PixelWrapper< float > GreyscalePixels;
static const char *GreyscaleOnlyError =
	"Only greyscale floating-point images are supported!";


Mh::ImageWrapper processGreyscale(const  Mh::ImageWrapper& image, const std::vector<float>& kernel, bool vertical)
{
	if ( image.getFormat( ) != Mh::ImageFormat::FLOAT )
	throw std::runtime_error( GreyscaleOnlyError );
	Mh::ImageWrapper img( Mh::ImageFormat::FLOAT, image.getWidth( ),
			  image.getHeight( ), 32 );
	GreyscalePixels input( static_cast< float * >( image.getBytes( ) ),
			   image.getWidth( ), image.getHeight( ) );
	GreyscalePixels output( static_cast< float * >( img.getBytes( ) ),
				img.getWidth( ), img.getHeight( ) );
	std::vector<float> internalKernel(kernel.size());
	memset(internalKernel.data(),0,sizeof(float)*internalKernel.size());
	memset( output.pixels, 0, sizeof( float ) * output.width * output.height );
	const int kend = ( kernel.size() / 2 );
	const int kbegin = kend * -1;
	for ( int y = 0; y < input.height; ++y ) {
	for ( int x = 0; x < input.width; ++x ) {
		int kval = 0;
		for ( int h = kbegin; h <= kend; ++h,++kval ) {
		if ( vertical )
			internalKernel[kval] = input[y + h][x];
		else
			internalKernel[kval] += input[y][x + h];
		}
		float sum = 0.0f;
		for(size_t i = 0; i < internalKernel.size();++i)
		{
			sum += internalKernel[i]*kernel[i];
		}
		output[y][x] = sum;
	}
	}
	return img;
}
Mh::ImageWrapper processColoured(const  Mh::ImageWrapper& image, const std::vector<float>& kernel, bool vertical)
{
	struct rgbf {
		float r,g,b;
	};
	Mh::ImageWrapper img( image.getFormat(), image.getWidth( ),
			  image.getHeight( ), image.getBPP() );
	PixelWrapper<PixelRgb8> input( image.getBytes( ),
			   image.getWidth( ), image.getHeight( ) );
	PixelWrapper<PixelRgb8> output( img.getBytes( ),
				img.getWidth( ), img.getHeight( ) );
	std::vector<rgbf> internalKernel(kernel.size());
	memset(internalKernel.data(),0,sizeof(rgbf)*internalKernel.size());
	memset( output.pixels, 0, sizeof( float ) * output.width * output.height );
	const int kend = ( kernel.size() / 2 );
	const int kbegin = kend * -1;
	for ( int y = 0; y < input.height; ++y ) {
	for ( int x = 0; x < input.width; ++x ) {
		int kval = 0;
		for ( int h = kbegin; h <= kend; ++h,++kval ) {
		if ( vertical ) {
			const PixelRgb8& ref = input[y + h][x];
			internalKernel[kval].r = float(ref.r)/255.0f;
			internalKernel[kval].g = float(ref.g)/255.0f;
			internalKernel[kval].b = float(ref.b)/255.0f;
			}
		else {
			const PixelRgb8& ref = input[y][x + h];
			internalKernel[kval].r = float(ref.r)/255.0f;
			internalKernel[kval].g = float(ref.g)/255.0f;
			internalKernel[kval].b = float(ref.b)/255.0f;
			}
		}
		rgbf sum{0.0f,0.0f,0.0f};
		for(size_t i = 0; i < internalKernel.size();++i)
		{
			sum.r += internalKernel[i].r*kernel[i];
			sum.g += internalKernel[i].g*kernel[i];
			sum.b += internalKernel[i].b*kernel[i];
		}
		PixelRgb8& ref = output[y][x];
		ref.r = uint8_t(sum.r*255.0f);
		ref.g = uint8_t(sum.r*255.0f);
		ref.b = uint8_t(sum.r*255.0f);
	}
	}
	return img;
}


void optimizedBlur( const GreyscalePixels &input, GreyscalePixels &output,
			int blurRadius, bool Yaxis );
void blur3x3( const GreyscalePixels &input, GreyscalePixels &output,
		  const fmat3x3 &convolutionKernel );
void blur5x5( const GreyscalePixels &input, GreyscalePixels &output,
		  const fmat5x5 &convolutionKernel );
void blur7x7( const GreyscalePixels &input, GreyscalePixels &output,
		  const fmat7x7 &convolutionKernel );

static const fmat3x3 BOX_BLUR_3X3 = {
	0.111111111111111f, 0.111111111111111f, 0.111111111111111f,
	0.111111111111111f, 0.111111111111111f, 0.111111111111111f,
	0.111111111111111f, 0.111111111111111f, 0.111111111111111f};
static const fmat5x5 BOX_BLUR_5X5 = {
	0.04f, 0.04f, 0.04f, 0.04f, 0.04f, 0.04f, 0.04f, 0.04f, 0.04f,
	0.04f, 0.04f, 0.04f, 0.04f, 0.04f, 0.04f, 0.04f, 0.04f, 0.04f,
	0.04f, 0.04f, 0.04f, 0.04f, 0.04f, 0.04f, 0.04f};
static const fmat7x7 BOX_bLUR_7X7 = {
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f, 0.020408163265306f, 0.020408163265306f,
	0.020408163265306f};

void greyscaleBlurImage( Mh::ImageWrapper &image, int blurRadius ) {
	image = greyscaleBlurAndCopy( image, blurRadius );
}
Mh::ImageWrapper greyscaleBlurAndCopy( const Mh::ImageWrapper &image, int blurRadius ) {
	if ( image.getFormat( ) != Mh::ImageFormat::FLOAT )
	throw std::runtime_error( GreyscaleOnlyError );
	std::vector<float> blurKernel(blurRadius);
	for(auto it = std::begin(blurKernel); it != std::end(blurKernel);++it)
	{
		*it = 1.0f / float(blurKernel.size());
	}
	Mh::ImageWrapper tmp = processGreyscale(image,blurKernel,false);
	return processGreyscale(tmp,blurKernel,true);
}
Mh::ImageWrapper rgbBlurAndCopy( const Mh::ImageWrapper &image, int blurRadius ) {
	throw std::runtime_error( GreyscaleOnlyError );
	std::vector<float> blurKernel(blurRadius);
	for(auto it = std::begin(blurKernel); it != std::end(blurKernel);++it)
	{
		*it = 1.0f / float(blurKernel.size());
	}
	Mh::ImageWrapper tmp = processColoured(image,blurKernel,false);
	return processColoured(tmp,blurKernel,true);
}

Mh::ImageWrapper greyscaleSharpenAndCopy( const Mh::ImageWrapper &image, int sharpRadius ) {
	if ( image.getFormat( ) != Mh::ImageFormat::FLOAT )
	throw std::runtime_error( GreyscaleOnlyError );
	const int kend = ( sharpRadius / 2 );
	const int kbegin = kend * -1;
	std::vector<float> blurKernel(sharpRadius);
	for(auto it = std::begin(blurKernel); it != std::end(blurKernel);++it)
	{
		*it = -1.0f;
	}
	blurKernel[kbegin] = float(sharpRadius);
	Mh::ImageWrapper tmp = processGreyscale(image,blurKernel,false);
	return processGreyscale(tmp,blurKernel,true);
}
Mh::ImageWrapper rgbSharpenAndCopy( const Mh::ImageWrapper &image, int sharpRadius ) {
	const int kend = ( sharpRadius / 2 );
	const int kbegin = kend * -1;
	std::vector<float> blurKernel(sharpRadius);
	for(auto it = std::begin(blurKernel); it != std::end(blurKernel);++it)
	{
		*it = -1.0f;
	}
	blurKernel[kbegin] = float(sharpRadius);
	Mh::ImageWrapper tmp = processColoured(image,blurKernel,false);
	return processColoured(tmp,blurKernel,true);
}

void greyscaleBlurImage( Mh::ImageWrapper &image, BlurType blurType ) {
	if ( image.getFormat( ) != Mh::ImageFormat::FLOAT )
	throw std::runtime_error( GreyscaleOnlyError );
	std::vector< float > tmpBuff( image.getWidth( ) * image.getHeight( ) );
	GreyscalePixels input( static_cast< float * >( image.getBytes( ) ),
			   image.getWidth( ), image.getHeight( ) );
	GreyscalePixels output( tmpBuff.data( ), image.getWidth( ),
				image.getHeight( ) );
	switch ( blurType ) {
	case BlurType::box_blur_3x3:
	blur3x3( input, output, BOX_BLUR_3X3 );
	break;
	case BlurType::box_blur_5x5:
	blur5x5( input, output, BOX_BLUR_5X5 );
	break;
	case BlurType::box_blur_7x7:
	blur7x7( input, output, BOX_bLUR_7X7 );
	break;
	default:
	blur3x3( input, output, BOX_BLUR_3X3 );
	break;
	}
	memcpy( image.getBytes( ), tmpBuff.data( ),
		tmpBuff.size( ) * sizeof( float ) );
}
Mh::ImageWrapper greyscaleBlurAndCopy( const Mh::ImageWrapper &image,
				  BlurType blurType ) {
	if ( image.getFormat( ) != Mh::ImageFormat::FLOAT )
	throw std::runtime_error( GreyscaleOnlyError );
	Mh::ImageWrapper img( Mh::ImageFormat::FLOAT, image.getWidth( ),
			  image.getHeight( ), 32 );
	GreyscalePixels input( static_cast< float * >( image.getBytes( ) ),
			   image.getWidth( ), image.getHeight( ) );
	GreyscalePixels output( static_cast< float * >( img.getBytes( ) ),
				img.getWidth( ), img.getHeight( ) );
	switch ( blurType ) {
	case BlurType::box_blur_3x3:
	blur3x3( input, output, BOX_BLUR_3X3 );
	break;
	case BlurType::box_blur_5x5:
	blur5x5( input, output, BOX_BLUR_5X5 );
	break;
	case BlurType::box_blur_7x7:
	blur7x7( input, output, BOX_bLUR_7X7 );
	break;
	default:
	blur3x3( input, output, BOX_BLUR_3X3 );
	break;
	}
	return img;
}

void optimizedBlur( const GreyscalePixels &input, GreyscalePixels &output,
			int blurRadius, bool Yaxis ) {
	const int kend = ( blurRadius / 2 );
	const int kbegin = kend * -1;
	float sum = 0.0f;
	int count = 0;
	memset( output.pixels, 0, sizeof( float ) * output.width * output.height );
	for ( int y = 0; y < input.height; ++y ) {
	for ( int x = 0; x < input.width; ++x ) {
		for ( int h = kbegin; h <= kend; ++h ) {
		if ( Yaxis )
			sum += input[y + h][x];
		else
			sum += input[y][x + h];
		++count;
		}
		output[y][x] = sum / float( count );
		sum = 0.0f;
		count = 0;
	}
	}
}
void blur3x3( const GreyscalePixels &input, GreyscalePixels &output,
		  const fmat3x3 &convolutionKernel ) {
	fmat3x3 KERNEL;
	for ( int y = 0; y < input.height; ++y ) {
	for ( int x = 0; x < input.width; ++x ) {
		for ( int h = -1; h < 2; ++h ) {
		for ( int j = -1; j < 2; ++j ) {
			KERNEL[h + 1][j + 1] = input[y + h][x + j];
		}
		}
		KERNEL *= convolutionKernel;
		output[y][x] = std::clamp( KERNEL.sum( ), 0.0f, 1.0f );
	}
	}
}
void blur5x5( const GreyscalePixels &input, GreyscalePixels &output,
		  const fmat5x5 &convolutionKernel ) {
	fmat5x5 KERNEL;
	const int kend = ( KERNEL.width / 2 );
	const int kbegin = kend * -1;
	for ( int y = 0; y < input.height; ++y ) {
	for ( int x = 0; x < input.width; ++x ) {
		for ( int h = kbegin; h <= kend; ++h ) {
		for ( int j = kbegin; j <= kend; ++j ) {
			KERNEL[kend + h][kend + j] = input[y + h][x + j];
		}
		}
		KERNEL *= convolutionKernel;
		output[y][x] = std::clamp( KERNEL.sum( ), 0.0f, 1.0f );
	}
	}
}
void blur7x7( const GreyscalePixels &input, GreyscalePixels &output,
		  const fmat7x7 &convolutionKernel ) {
	fmat7x7 KERNEL;
	const int kend = ( KERNEL.width / 2 );
	const int kbegin = kend * -1;
	for ( int y = 0; y < input.height; ++y ) {
	for ( int x = 0; x < input.width; ++x ) {
		for ( int h = kbegin; h <= kend; ++h ) {
		for ( int j = kbegin; j <= kend; ++j ) {
			KERNEL[kend + h][kend + j] = input[y + h][x + j];
		}
		}
		KERNEL *= convolutionKernel;
		output[y][x] = std::clamp( KERNEL.sum( ), 0.0f, 1.0f );
	}
	}
}
