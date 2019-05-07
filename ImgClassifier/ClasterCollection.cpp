#include "ClasterCollection.hpp"

ClasterCollection::ClasterCollection(QObject *parent)
	: QAbstractItemModel(parent)
{
}

QModelIndex ClasterCollection::index(int row, int column, const QModelIndex &parent) const
{
	// FIXME: Implement me!
}

QModelIndex ClasterCollection::parent(const QModelIndex &index) const
{
	// FIXME: Implement me!
}

int ClasterCollection::rowCount(const QModelIndex &parent) const
{
	if (!parent.isValid())
		return 0;

	// FIXME: Implement me!
}

int ClasterCollection::columnCount(const QModelIndex &parent) const
{
	if (!parent.isValid())
		return 0;

	// FIXME: Implement me!
}

QVariant ClasterCollection::data(const QModelIndex &index, int role) const
{
	if (!index.isValid())
		return QVariant();

	// FIXME: Implement me!
	return QVariant();
}
