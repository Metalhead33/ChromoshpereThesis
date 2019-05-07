#ifndef IMAGECLASTER_HPP
#define IMAGECLASTER_HPP
#include <QAbstractItemModel>
#include "ImageMetadataContainer.hpp"

class ImageClaster : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit ImageClaster(QObject *parent = nullptr);

	// Header:
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	// Basic functionality:
	QModelIndex index(int row, int column,
					  const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &index) const override;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
	std::vector<ImageMetadataContainer> container;
};

#endif // IMAGECLASTER_HPP
