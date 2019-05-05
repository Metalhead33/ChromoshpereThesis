#include "ImageCollection.hpp"
#include "../Io/PhysFsFileHandle.hpp"
#include "ProfileImage.hpp"

inline bool endsWith(const std::string& s, const std::string& suffix)
{
	return s.rfind(suffix) == (s.size()-suffix.size());
}

ImageCollection::ImageCollection(const std::string& npath)
	: path(npath)
{
	auto paths = PhysFS::FileHandle::enumerateFilesFullpath(npath);
	for(auto it = std::begin(paths); it != std::end(paths); ++it)
	{
		if( endsWith(*it,".jpg") || endsWith(*it,".JPG") || endsWith(*it,".jpeg") || endsWith(*it,".JPEG"))
		{
			auto thandle = PhysFS::FileHandle::openRead(*it);
			Mh::ImageWrapper tmpWrap(Mh::ImageFileType::JPEG,*thandle);
			std::vector<ImageMetadataContainer> images;
			images.push_back(ImageMetadataContainer(std::move(tmpWrap),std::move(*it)));
			clasters.push_back(std::move(images));
		}
	}
}
uint32_t ImageCollection::purgeBasedOnFmax(float fmax)
{
	for(auto it = std::begin(clasters); it != std::end(clasters);)
	{
		if( (*it)[0].getSharpnessMax() >= fmax) it = clasters.erase(it);
		else ++it;
	}
}
uint32_t ImageCollection::purgeBasedOnFavg(float favg)
{
	for(auto it = std::begin(clasters); it != std::end(clasters);)
	{
		if(!it->size()) it = clasters.erase(it);
		else if( (*it)[0].getSharpnessAvg() >= favg) it = clasters.erase(it);
		else ++it;
	}
}
Mh::ImageWrapper ImageCollection::composeClaster(ClasterIterator it)
{
	Mh::ImageWrapper tmp;
	if(it->size() > 1)
	{
		auto thandle = PhysFS::FileHandle::openRead((*it)[0].getPath());
		Mh::ImageWrapper tmpWrap(Mh::ImageFileType::JPEG,*thandle);
		for(size_t i = 1; i < it->size();++i)
		{
			auto thandleB = PhysFS::FileHandle::openRead((*it)[i].getPath());
			Mh::ImageWrapper tmpWrapB(Mh::ImageFileType::JPEG,*thandleB);
			tmpWrap = sharpnessComposite(tmpWrap,tmpWrapB);
		}
	}
	return tmp;
}
void ImageCollection::pruneBasedOnFmax()
{
	for(auto it = std::begin(clasters); it != std::end(clasters);++it)
	{
		float bestFmax = 0.0f;
		size_t bestIndex = 0;
		size_t currentIndex = 0;
		for(auto zit = std::begin(*it); zit != std::end(*it);++zit) {
			if(zit->getSharpnessMax() >= bestFmax) {
			bestFmax = zit->getSharpnessMax();
			bestIndex = currentIndex;
			}
			++currentIndex;
		}
		std::vector<ImageMetadataContainer> tmp;
		tmp.push_back(std::move( (*it)[bestIndex]));
		*it = std::move(tmp);
	}
}
void ImageCollection::pruneBasedOnFavg()
{
	for(auto it = std::begin(clasters); it != std::end(clasters);++it)
	{
		float bestFavg = 0.0f;
		size_t bestIndex = 0;
		size_t currentIndex = 0;
		for(auto zit = std::begin(*it); zit != std::end(*it);++zit) {
			if(zit->getSharpnessAvg() >= bestFavg) {
			bestFavg = zit->getSharpnessAvg();
			bestIndex = currentIndex;
			}
			++currentIndex;
		}
		std::vector<ImageMetadataContainer> tmp;
		tmp.push_back(std::move( (*it)[bestIndex]));
		*it = std::move(tmp);
	}
}
void ImageCollection::createClasters(float maximalDifference)
{
	for(auto it = std::begin(clasters); it != std::end(clasters);++it)
	{
		for(auto xit = std::begin(clasters); xit != std::end(clasters);++xit)
		{
			if(it != xit && (*it)[0].isItValid() && (*xit)[0].isItValid() )
			{
				if( (*it)[0].getWidth() == (*xit)[0].getWidth() &&
					(*it)[0].getHeight() == (*xit)[0].getHeight() &&
						(*it)[0].calculateDifference((*xit)[0]) <= maximalDifference)
				{
					it->push_back((*xit)[0]);
				}
			}
		}
	}
	for(auto it = std::begin(clasters); it != std::end(clasters);)
	{
		if( (*it)[0].isItValid() ) ++it;
		else it = clasters.erase(it);
	}
}
