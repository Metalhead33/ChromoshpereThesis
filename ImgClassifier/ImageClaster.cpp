#include "ImageClaster.hpp"
#include "../Io/PhysFsFileHandle.hpp"
#include "ProfileImage.hpp"

ImageClaster::ImageClaster(QObject *parent)
	: QAbstractItemModel(parent)
{
}
ImageClaster::ImageClaster(ImageClaster& mov, QObject *parent)
	: QAbstractItemModel(parent), container(std::move(mov.container))
{
	;
}

ImageMetadataContainer& ImageClaster::getImage(size_t row)
{
	return container[row % container.size()];
}
const ImageMetadataContainer& ImageClaster::getImage(size_t row) const
{
	return container[row % container.size()];
}

QModelIndex ImageClaster::index(int row, int column, const QModelIndex &parent) const
{
	if(column != 1) return QModelIndex();
	if(!parent.isValid()) {
	if(row <= container.size()) return createIndex(row,column,nullptr);
	else return QModelIndex();
	} else return QModelIndex();
}

QModelIndex ImageClaster::parent(const QModelIndex &index) const
{
	// FIXME: Implement me!
}

int ImageClaster::rowCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	else return container.size() + 1;

	// FIXME: Implement me!
}

int ImageClaster::columnCount(const QModelIndex &parent) const
{
	if (parent.isValid())
		return 0;
	else return 1;
}

QVariant ImageClaster::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();
	if(index.row() >= container.size()) return QVariant();
	switch (role) {
		case Qt::DisplayRole:
		return QString::fromStdString(container[index.row()].getLocalPath());
	case Qt::DecorationRole:
		return container[index.row()].getIcon();
	case Qt::ToolTipRole:
	return QString::fromStdString(container[index.row()].getLocalPath());
	case Qt::SizeHintRole:
		return QSize(container[index.row()].getGreyscaleIcon().getWidth(),
				container[index.row()].getGreyscaleIcon().getHeight());
	default:
		return QVariant();
	}
	return QVariant();
}
void ImageClaster::insertImage(int row, ImageMetadataContainer &&mov)
{
	beginInsertRows(QModelIndex(),row,row);
	container.insert(&container[row],mov);
	endInsertRows();
}
void ImageClaster::insertImage(ImageMetadataContainer&& mov)
{
	beginInsertRows(QModelIndex(),container.size(),container.size());
	container.push_back(mov);
	endInsertRows();
}
void ImageClaster::removeImage(int row)
{
	if(row >= container.size()) return;
	beginRemoveRows(QModelIndex(),row,row);
	container.erase(&container[row]);
	endRemoveRows();
}
bool ImageClaster::isValid() const
{
	if(container.size()) return container[0].isItValid();
	else return false;
}
QIcon ImageClaster::getIcon() const
{
	if(container.size()) return container[0].getIcon();
	else return QIcon();
}
float ImageClaster::getBestFmax() const
{
	float bestFmax = 0.0f;
	for(auto zit = std::begin(container); zit != std::end(container);++zit) {
		if(zit->getSharpnessMax() >= bestFmax) {
		bestFmax = zit->getSharpnessMax();
		}
	}
	return bestFmax;
}
float ImageClaster::getBestFavg() const
{
	float bestFavg = 0.0f;
	for(auto zit = std::begin(container); zit != std::end(container);++zit) {
		if(zit->getSharpnessAvg() >= bestFavg) {
		bestFavg = zit->getSharpnessMax();
		}
	}
	return bestFavg;
}
void ImageClaster::pruneBasedOnFmax()
{
	float bestFmax = 0.0f;
	size_t bestIndex = 0;
	size_t currentIndex = 0;
	for(auto zit = std::begin(container); zit != std::end(container);++zit) {
		if(zit->getSharpnessMax() >= bestFmax) {
		bestFmax = zit->getSharpnessMax();
		bestIndex = currentIndex;
		}
		++currentIndex;
	}
	if(bestIndex) {
	beginRemoveRows(QModelIndex(),0,bestIndex-1);
	container.remove(0,bestIndex-1);
	endRemoveRows();
	}
	if(container.size() > 1)
	{
		beginRemoveRows(QModelIndex(),1,container.size()-2);
		container.remove(1,container.size()-1);
		endRemoveRows();
	}
}
void ImageClaster::pruneBasedOnFavg()
{
	float bestFavg = 0.0f;
	size_t bestIndex = 0;
	size_t currentIndex = 0;
	for(auto zit = std::begin(container); zit != std::end(container);++zit) {
		if(zit->getSharpnessAvg() >= bestFavg) {
		bestFavg = zit->getSharpnessMax();
		bestIndex = currentIndex;
		}
		++currentIndex;
	}
	if(bestIndex) {
	beginRemoveRows(QModelIndex(),0,bestIndex-1);
	container.remove(0,bestIndex-1);
	endRemoveRows();
	}
	if(container.size() > 1)
	{
		beginRemoveRows(QModelIndex(),1,container.size()-2);
		container.remove(1,container.size()-1);
		endRemoveRows();
	}
}
Mh::ImageWrapper ImageClaster::composeClaster()
{
	if(!container.size()) return Mh::ImageWrapper();
	Mh::ImageWrapper tmp;
	auto thandle = PhysFS::FileHandle::openRead(container[0].getFullPath());
	Mh::ImageWrapper tmpWrap(Mh::ImageFileType::JPEG,*thandle);
	for(int i = 1; i < container.size();++i)
	{
		auto thandleB = PhysFS::FileHandle::openRead(container[i].getFullPath());
		Mh::ImageWrapper tmpWrapB(Mh::ImageFileType::JPEG,*thandleB);
		tmpWrap = sharpnessComposite(tmpWrap,tmpWrapB);
	}
	return tmp;
}
void ImageClaster::absorbClaster(ImageClaster &other)
{
	beginRemoveRows(QModelIndex(),container.size(),container.size()+other.container.size()-1);
	for(auto it = std::begin(other.container); it != std::end(other.container);++it)
	{
		container.push_back(std::move(*it));
	}
	endRemoveRows();
}
