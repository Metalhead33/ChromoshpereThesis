#ifndef IMAGEMETADATACONTAINER_HPP
#define IMAGEMETADATACONTAINER_HPP
#include "../Wrapper/MhImageWrapper.hpp"
#include <QIcon>

class ImageMetadataContainer
{
private:
	QIcon icon;
	Mh::ImageWrapper iconGreyscale;
	float sharpnessMin, sharpnessMax, sharpnessAvg;
	unsigned width, height;
	std::string fullPath;
	std::string localPath;
	bool isValid;
public:
	ImageMetadataContainer(ImageMetadataContainer&& mv);
	ImageMetadataContainer(const Mh::ImageWrapper& original, const std::string& npath, const std::string &npath2);
	ImageMetadataContainer(Mh::ImageWrapper&& original, std::string&& npath, std::string &&npath2);
	const QIcon &getIcon() const;
	const Mh::ImageWrapper& getGreyscaleIcon() const;
	float getSharpnessMin() const;
	float getSharpnessMax() const;
	float getSharpnessAvg() const;
	unsigned getWidth() const;
	unsigned getHeight() const;
	const std::string& getFullPath() const;
	const std::string& getLocalPath() const;
	float calculateDifference(const ImageMetadataContainer& other) const;
	bool isItValid() const;
};

#endif // IMAGEMETADATACONTAINER_HPP
