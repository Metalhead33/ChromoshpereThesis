#ifndef IMAGEMETADATACONTAINER_HPP
#define IMAGEMETADATACONTAINER_HPP
#include "../Wrapper/MhImageWrapper.hpp"

class ImageMetadataContainer
{
private:
	Mh::ImageWrapper icon;
	Mh::ImageWrapper iconGreyscale;
	float sharpnessMin, sharpnessMax, sharpnessAvg;
	unsigned width, height;
	std::string path;
public:
	ImageMetadataContainer(const Mh::ImageWrapper& original, const std::string& npath);
	ImageMetadataContainer(Mh::ImageWrapper&& original, std::string&& npath);
	const Mh::ImageWrapper &getIcon() const;
	const Mh::ImageWrapper& getGreyscaleIcon() const;
	float getSharpnessMin() const;
	float getSharpnessMax() const;
	float getSharpnessAvg() const;
	unsigned getWidth() const;
	unsigned getHeight() const;
	const std::string& getPath() const;
	float calculateDifference(const ImageMetadataContainer& other) const;
};

#endif // IMAGEMETADATACONTAINER_HPP
