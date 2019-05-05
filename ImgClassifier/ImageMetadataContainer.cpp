#include "ImageMetadataContainer.hpp"
#include "ProfileImage.hpp"
#include "../Wrapper/PixelWrapper.hpp"
#include <numeric>

const int THUMBNAIL_SIZE = 16384;
const int BLUR_RADIUS = 15;
typedef PixelWrapper<float> GreyscalePixelWrapper;

ImageMetadataContainer::ImageMetadataContainer(ImageMetadataContainer&& mv)
	: icon(std::move(mv.icon)), iconGreyscale(std::move(mv.iconGreyscale)),
	  sharpnessMin(mv.sharpnessMin), sharpnessMax(mv.sharpnessMax), sharpnessAvg(mv.sharpnessAvg),
	  width(mv.width), height(mv.height), path(std::move(mv.path)), isValid(mv.isValid)
{
	mv.isValid = false;
}
ImageMetadataContainer::ImageMetadataContainer(const Mh::ImageWrapper& original, const std::string& npath)
	: icon(original.copyThumbmail(THUMBNAIL_SIZE)), width(original.getWidth()), height(original.getWidth()), path(npath),isValid(true)
{
	produceSharpnessProfile(original,BLUR_RADIUS,&sharpnessMin,&sharpnessMax,&sharpnessAvg);
	iconGreyscale = icon.cloneAsFloat();
}
ImageMetadataContainer::ImageMetadataContainer(Mh::ImageWrapper&& original, std::string&& npath)
	: width(original.getWidth()), height(original.getWidth()), path(npath),isValid(true)
{
	produceSharpnessProfile(original,BLUR_RADIUS,&sharpnessMin,&sharpnessMax,&sharpnessAvg);
	icon = std::move(original);
	icon.createThumbmail(THUMBNAIL_SIZE);
	iconGreyscale = icon.cloneAsFloat();
}

const Mh::ImageWrapper& ImageMetadataContainer::getIcon() const
{
	return icon;
}
const Mh::ImageWrapper &ImageMetadataContainer::getGreyscaleIcon() const
{
	return iconGreyscale;
}
float ImageMetadataContainer::getSharpnessMin() const
{
	return sharpnessMin;
}
float ImageMetadataContainer::getSharpnessMax() const
{
	return sharpnessMax;
}
float ImageMetadataContainer::getSharpnessAvg() const
{
	return sharpnessAvg;
}
unsigned ImageMetadataContainer::getWidth() const
{
	return width;
}
unsigned ImageMetadataContainer::getHeight() const
{
	return height;
}
const std::string& ImageMetadataContainer::getPath() const
{
	return path;
}
float ImageMetadataContainer::calculateDifference(const ImageMetadataContainer& other) const
{
	if(!icon.hasPixels() || !other.icon.hasPixels()) return std::numeric_limits<float>::infinity();
	GreyscalePixelWrapper wrapThis(icon.getBytes(),icon.getWidth(),icon.getHeight());
	GreyscalePixelWrapper wrapOther(other.icon.getBytes(),other.icon.getWidth(),other.icon.getHeight());
	float diff = 0.0f;
	for(int i = 0; i < wrapThis.height; ++i)
	{
		for(int j = 0; j < wrapThis.width; ++j)
		{
			const float a = wrapThis[i][j];
			const float b = wrapOther[i][j];
			diff += std::max(a,b) - std::min(a,b);
		}
	}
	return diff;
}
bool ImageMetadataContainer::isItValid() const
{
	return isValid;
}
