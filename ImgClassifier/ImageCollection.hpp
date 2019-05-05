#ifndef IMAGECOLLECTION_HPP
#define IMAGECOLLECTION_HPP
#include "ImageMetadataContainer.hpp"
#include <list>

class ImageCollection
{
public:
	typedef std::list<std::vector<ImageMetadataContainer>> ClasterType;
	typedef ClasterType::iterator ClasterIterator;
	typedef ClasterType::const_iterator ClasterConstIterator;
private:
	ClasterType clasters;
	std::string path;
public:
	ImageCollection(const std::string& npath);
	void pruneBasedOnFmax();
	void pruneBasedOnFavg();
	static Mh::ImageWrapper composeClaster(ClasterIterator it);
	uint32_t purgeBasedOnFmax(float fmax);
	uint32_t purgeBasedOnFavg(float favg);
	void createClasters(float maximalDifference);
};

#endif // IMAGECOLLECTION_HPP
