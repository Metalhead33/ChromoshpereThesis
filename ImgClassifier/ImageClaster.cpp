#include "ImageClaster.hpp"

ImageClaster::ImageClaster(QObject *parent)
	: QAbstractItemModel(parent)
{
}

QVariant ImageClaster::headerData(int section, Qt::Orientation orientation, int role) const
{
	return QVariant();
	// FIXME: Implement me!
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
