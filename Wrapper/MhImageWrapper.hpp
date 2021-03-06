#ifndef MHIMAGEWRAPPER_HPP
#define MHIMAGEWRAPPER_HPP
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
#include "../Io/FIO.hpp"

struct MemoryBuffer
{
	void* ptr;
	size_t size;
};

namespace Mh {

	enum class ImageFormat : int {
	UNKNOWN = 0, //! unknown type
	BITMAP = 1,  //! standard image			: 1-, 4-, 8-, 16-, 24-,
			//! 32-bit
	UINT16 = 2, //! array of unsigned short	: unsigned 16-bit
	INT16 = 3,  //! array of short			: signed 16-bit
	UINT32 = 4, //! array of unsigned long	: unsigned 32-bit
	INT32 = 5,  //! array of long			: signed 32-bit
	FLOAT = 6,  //! array of float			: 32-bit IEEE floating
			//! point
	DOUBLE = 7, //! array of double			: 64-bit IEEE floating
			//! point
	COMPLEX =
		8,       //! array of FICOMPLEX		: 2 x 64-bit IEEE floating point
	RGB16 = 9,   //! 48-bit RGB image			: 3 x 16-bit
	RGBA16 = 10, //! 64-bit RGBA image		: 4 x 16-bit
	RGBF = 11,   //! 96-bit RGB float image	: 3 x 32-bit IEEE floating point
	RGBAF = 12 //! 128-bit RGBA float image	: 4 x 32-bit IEEE floating point
	};
	enum class ImageFileType : int {
	UNKNOWN = -1,
	BMP = 0,
	ICO = 1,
	JPEG = 2,
	JNG = 3,
	KOALA = 4,
	LBM = 5,
	IFF = LBM,
	MNG = 6,
	PBM = 7,
	PBMRAW = 8,
	PCD = 9,
	PCX = 10,
	PGM = 11,
	PGMRAW = 12,
	PNG = 13,
	PPM = 14,
	PPMRAW = 15,
	RAS = 16,
	TARGA = 17,
	TIFF = 18,
	WBMP = 19,
	PSD = 20,
	CUT = 21,
	XBM = 22,
	XPM = 23,
	DDS = 24,
	GIF = 25,
	HDR = 26,
	FAXG3 = 27,
	SGI = 28,
	EXR = 29,
	J2K = 30,
	JP2 = 31,
	PFM = 32,
	PICT = 33,
	RAW = 34,
	WEBP = 35,
	JXR = 36
	};
	enum class RescaleFilter : int {
	FILTER_BOX		  = 0,	// Box, pulse, Fourier window, 1st order (constant) b-spline
	FILTER_BICUBIC	  = 1,	// Mitchell & Netravali's two-param cubic filter
	FILTER_BILINEAR   = 2,	// Bilinear filter
	FILTER_BSPLINE	  = 3,	// 4th order (cubic) b-spline
	FILTER_CATMULLROM = 4,	// Catmull-Rom spline, Overhauser spline
	FILTER_LANCZOS3	  = 5	// Lanczos3 filter
	};

	DEFINE_CLASS( ImageWrapper )
	class ImageWrapper {
	  private:
	DEFINE_STRUCT( ImageWrapper_imp )
	sImageWrapper_imp pimpl;

	  public:
	~ImageWrapper( ) = default;
	ImageWrapper( );
	ImageWrapper( const ImageWrapper &cpy );
	ImageWrapper( ImageWrapper &&mov );
	ImageWrapper( void *bits, int width, int height, int pitch,
			  unsigned bpp, unsigned red_mask, unsigned green_mask,
			  unsigned blue_mask, bool topdown = false );
	ImageWrapper( void *bits, int width, int height, int pitch,
			  unsigned bpp, bool topdown = false );
	void operator=( const ImageWrapper &cpy );
	void operator=( ImageWrapper &&mov );
	ImageWrapper( int width, int height, int bpp, unsigned red_mask = 0,
			  unsigned green_mask = 0, unsigned blue_mask = 0 );
	ImageWrapper( ImageFormat typus, int width, int height, int bpp = 8,
			  unsigned red_mask = 0, unsigned green_mask = 0,
			  unsigned blue_mask = 0 );
	ImageWrapper( const char *path );
	ImageWrapper( ImageFileType typus, const char *path );
	ImageWrapper( Abstract::FIO &handle );
	ImageWrapper( ImageFileType typus, Abstract::FIO &handle );
	// Save the image
	bool save( ImageFileType format, const char *path ) const;
	bool save( ImageFileType format, Abstract::FIO &handle ) const;
	// Image Attribute getters
	ImageFormat getFormat( ) const;
	unsigned getColorsUsed( ) const;
	unsigned getBPP( ) const;
	unsigned getWidth( ) const;
	unsigned getHeight( ) const;
	unsigned getLine( ) const;
	unsigned getPitch( ) const;
	unsigned getDIBSize( ) const;
	unsigned getMemorySize( ) const;
	unsigned getRedMask( ) const;
	unsigned getGreenMask( ) const;
	unsigned getBlueMask( ) const;
	// Image access getters
	bool hasPixels( ) const;
	bool hasThumbnail( ) const;
	ImageWrapper copyThumbnail( ) const;
	bool setThumbnail( const ImageWrapper &cpy ) const;
	bool removeThumbnail( void ) const;
	void *getBytes( ) const;
	void *getScanline( int scanline ) const;
	// Conversions
	bool convertTo4Bits( ) const;
	bool convertTo8Bits( ) const;
	bool convertToGreyscale( ) const;
	bool convertTo16Bits555( ) const;
	bool convertTo16Bits565( ) const;
	bool convertTo24Bits( ) const;
	bool convertTo32Bits( ) const;
	bool quantizeXiaolinWu( ) const;
	bool quantizeNeuQuant( ) const;
	bool quantizeCarlsten( ) const;
	bool threshold( unsigned char hold ) const;
	bool ditherFS( ) const;
	bool ditherBayer4x4( ) const;
	bool ditherBayer8x8( ) const;
	bool ditherBayer16x16( ) const;
	bool ditherCluster6x6( ) const;
	bool ditherCluster8x8( ) const;
	bool ditherCluster16x16( ) const;
	bool convertToStandardType( ) const;
	bool convertToFloat( ) const;
	bool convertToRGBF( ) const;
	bool convertToRGBAF( ) const;
	bool convertToUINT16( ) const;
	bool convertToRGB16( ) const;
	bool convertToRGBA16( ) const;
	bool tonemapDrago03( double gamma = 2.2, double exposure = 0.0 ) const;
	bool tonemapReinhard05( double intensity = 0.0,
				double contrast = 0.0 ) const;
	bool tonemapReinhard05Ex( double intensity = 0.0, double contrast = 0.0,
				  double adaptation = 1.0,
				  double color_correction = 0.0 ) const;
	bool tonemapFattal02( double color_saturation = 0.5,
				  double attenuation = 0.85 ) const;
	// Other transformations
	bool rotate(double angle) const;
	bool rotateEx(double angle, double x_shift, double y_shift, double x_origin, double y_origin, bool use_mask) const;
	bool rescale(int new_with, int new_height, RescaleFilter filter) const;
	bool createThumbmail(int pixelCnt) const;
	bool crop(int left, int top, int right, int bottom) const;
	bool adjustGamma(double gamma) const;
	bool adjustBrightness(double percentage) const;
	bool adjustContrast(double percentage) const;
	bool invert(void) const;
	bool adjustColors(double brightness, double contrast, double gamma, bool invert) const;
	static bool paste(const ImageWrapper& to, const ImageWrapper& from, int left, int top, int alpha);
	bool pasteFrom(const ImageWrapper& from, int left, int top, int alpha);
	bool pasteTo(const ImageWrapper& to, int left, int top, int alpha);
	// Cloning
	ImageWrapper copyThumbmail(int pixelCnt) const;
	ImageWrapper copy(int left, int top, int right, int bottom) const;
	ImageWrapper cloneAs4Bits( ) const;
	ImageWrapper cloneAs8Bits( ) const;
	ImageWrapper cloneAsGreyscale( ) const;
	ImageWrapper cloneAs16Bits555( ) const;
	ImageWrapper cloneAs16Bits565( ) const;
	ImageWrapper cloneAs24Bits( ) const;
	ImageWrapper cloneAs32Bits( ) const;
	ImageWrapper cloneQuantizeXiaolinWu( ) const;
	ImageWrapper cloneQuantizeNeuQuant( ) const;
	ImageWrapper cloneQuantizeCarlsten( ) const;
	ImageWrapper cloneThreshold( unsigned char hold ) const;
	ImageWrapper cloneDitherFS( ) const;
	ImageWrapper cloneDitherBayer4x4( ) const;
	ImageWrapper cloneDitherBayer8x8( ) const;
	ImageWrapper cloneDitherBayer16x16( ) const;
	ImageWrapper cloneDitherCluster6x6( ) const;
	ImageWrapper cloneDitherCluster8x8( ) const;
	ImageWrapper cloneDitherCluster16x16( ) const;
	ImageWrapper cloneAsStandardType( ) const;
	ImageWrapper cloneAsFloat( ) const;
	ImageWrapper cloneAsRGBF( ) const;
	ImageWrapper cloneAsRGBAF( ) const;
	ImageWrapper cloneAsUINT16( ) const;
	ImageWrapper cloneAsRGB16( ) const;
	ImageWrapper cloneAsRGBA16( ) const;
	ImageWrapper cloneTonemapDrago03( double gamma = 2.2, double exposure = 0.0 ) const;
	ImageWrapper cloneTonemapReinhard05( double intensity = 0.0,
				double contrast = 0.0 ) const;
	ImageWrapper cloneTonemapReinhard05Ex( double intensity = 0.0, double contrast = 0.0,
				  double adaptation = 1.0,
				  double color_correction = 0.0 ) const;
	ImageWrapper cloneTonemapFattal02( double color_saturation = 0.5,
				  double attenuation = 0.85 ) const;
	std::vector<char> saveToMemory(ImageFileType filetype) const;
	};

} // namespace Mh
#endif // MHIMAGEWRAPPER_HPP
