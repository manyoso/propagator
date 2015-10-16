#include "cell.h"

#include <QtCore>

Cell::Cell()
{ }

Cell::Cell(const QVariant& data)
    : m_data(data)
{ }

Cell::~Cell()
{ }

QVariant Cell::data() const
{
    return m_data;
}

void Cell::setData(const QVariant& data)
{
    if (m_data != data) {
        m_data = data;
        emit dataChanged();
    }
}
