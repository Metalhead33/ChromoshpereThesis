#include "ImageMetadataContainer.hpp"
#include "ProfileImage.hpp"
#include "../Wrapper/PixelWrapper.hpp"
#include <numeric>
#include <QImage>
#include <QPixmap>

const int THUMBNAIL_SIZE = 16384;
const int BLUR_RADIUS = 15;
typedef PixelWrapper<float> GreyscalePixelWrapper;

ImageMetadataContainer::ImageMetadataContainer(ImageMetadataContainer&& mv)
	: icon(std::move(mv.icon)), iconGreyscale(std::move(mv.iconGreyscale)),
	  sharpnessMin(mv.sharpnessMin), sharpnessMax(mv.sharpnessMax), sharpnessAvg(mv.sharpnessAvg),
	  width(mv.width), height(mv.height), fullPath(std::move(mv.fullPath)), localPath(std::move(mv.localPath)), isValid(mv.isValid)
{
	mv.isValid = false;
}
ImageMetadataContainer::ImageMetadataContainer(const Mh::ImageWrapper& original, const std::string& npath, const std::string& npath2)
	: width(original.getWidth()), height(original.getWidth()), fullPath(npath), localPath(npath2),
	  isValid(true)
{
	Mh::ImageWrapper tIcon = original.copyThumbmail(THUMBNAIL_SIZE);
	produceSharpnessProfile(original,BLUR_RADIUS,&sharpnessMin,&sharpnessMax,&sharpnessAvg);
	iconGreyscale = tIcon.cloneAsFloat();
	tIcon.convertTo24Bits();
	auto jpEgV = tIcon.saveToMemory(Mh::ImageFileType::JPEG);
	QPixmap img;
	img.loadFromData(reinterpret_cast<uchar*>(jpEgV.data()),jpEgV.size());
	icon = QIcon(img);
}
ImageMetadataContainer::ImageMetadataContainer(Mh::ImageWrapper&& original, std::string&& npath, std::string&& npath2)
	: width(original.getWidth()), height(original.getWidth()), fullPath(npath), localPath(npath2), isValid(true)
{
	produceSharpnessProfile(original,BLUR_RADIUS,&sharpnessMin,&sharpnessMax,&sharpnessAvg);
	Mh::ImageWrapper tIcon = std::move(original);
	tIcon.createThumbmail(THUMBNAIL_SIZE);
	iconGreyscale = tIcon.cloneAsFloat();
	tIcon.convertTo24Bits();
	auto jpEgV = tIcon.saveToMemory(Mh::ImageFileType::JPEG);
	QPixmap img;
	img.loadFromData(reinterpret_cast<uchar*>(jpEgV.data()),jpEgV.size());
	icon = QIcon(img);
}

const QIcon &ImageMetadataContainer::getIcon() const
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
const std::string& ImageMetadataContainer::getFullPath() const
{
	return fullPath;
}
const std::string& ImageMetadataContainer::getLocalPath()  const
{
	return localPath;
}
float ImageMetadataContainer::calculateDifference(const ImageMetadataContainer& other) const
{
	if(!iconGreyscale.hasPixels() || !other.iconGreyscale.hasPixels()) return std::numeric_limits<float>::infinity();
	GreyscalePixelWrapper wrapThis(iconGreyscale.getBytes(),iconGreyscale.getWidth(),iconGreyscale.getHeight());
	GreyscalePixelWrapper wrapOther(other.iconGreyscale.getBytes(),other.iconGreyscale.getWidth(),other.iconGreyscale.getHeight());
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
