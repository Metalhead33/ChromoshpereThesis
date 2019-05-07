#ifndef IMAGECLASTER_HPP
#define IMAGECLASTER_HPP
#include <QAbstractItemModel>
#include <QVector>
#include "ImageMetadataContainer.hpp"

class ImageClaster : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit ImageClaster(QObject *parent = nullptr);

	ImageClaster(ImageClaster& mov, QObject *parent = nullptr);

	// Basic functionality:
	QModelIndex index(int row, int column,
					  const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &index) const override;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	ImageMetadataContainer& getImage(size_t row);
	const ImageMetadataContainer& getImage(size_t row) const;

	void insertImage(int row, ImageMetadataContainer&& mov);
	void insertImage(ImageMetadataContainer&& mov);
	void removeImage(int row);
	bool isValid() const;
	QIcon getIcon() const;

	float getBestFmax() const;
	float getBestFavg() const;

	void pruneBasedOnFmax();
	void pruneBasedOnFavg();

	Mh::ImageWrapper composeClaster();
	void absorbClaster(ImageClaster &other);
private:
	QVector<ImageMetadataContainer> container;
};

#endif // IMAGECLASTER_HPP
