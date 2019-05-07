#ifndef CLASTERCOLLECTION_HPP
#define CLASTERCOLLECTION_HPP
#include <QAbstractItemModel>
#include "ImageClaster.hpp"

class ClasterCollection : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit ClasterCollection(QObject *parent = nullptr);

	// Basic functionality:
	QModelIndex index(int row, int column,
					  const QModelIndex &parent = QModelIndex()) const override;
	QModelIndex parent(const QModelIndex &index) const override;

	int rowCount(const QModelIndex &parent = QModelIndex()) const override;
	int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

private:
	QVector<ImageClaster> clasters;
};

#endif // CLASTERCOLLECTION_HPP
