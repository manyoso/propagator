#include "cell.h"

#include <QtCore>

Cell::Cell()
{ }

Cell::Cell(const Data& data)
    : m_data(data)
{ }

Cell::Cell(const Cell& cell)
    : QObject()
{
    m_data = cell.m_data;
}

Cell::~Cell()
{ }

Data Cell::data() const
{
    return m_data;
}

void Cell::setData(const Data& data)
{
    if (m_data != data) {
        m_data = data;
        emit dataChanged();
    }
}
