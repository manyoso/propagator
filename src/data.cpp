#include "data.h"

Data::Data()
    : m_type(Data::Nothing)
{
}

Data::Data(bool b)
    : m_type(Data::Boolean)
{
    m_data = b ? "true" : "false";
}

Data::Data(int n)
    : m_type(Data::Number)
{
    m_data = QString::number(n);
}

Data::Data(double n)
    : m_type(Data::Number)
{
    m_data = QString::number(n);
}

Data::Data(const QString& s)
    : m_type(Data::String)
{
    m_data = s;
}

Data::~Data()
{
}

Data::Type Data::type() const
{
    return m_type;
}

bool Data::toBool() const
{
    return m_type == Data::Boolean && m_data == "true" ? true : false;
}

double Data::toNumber() const
{
    return m_data.toDouble();
}

QString Data::toString() const
{
    return m_data;
}

Data Data::merge(const Data& info)
{
    if (m_type == Data::Nothing)
        return info;
    if (info.m_type == Data::Nothing)
        return this;
    return Data();
}

bool Data::isNothing() const
{
    return m_type == Data::Nothing;
}

bool Data::isBoolean() const
{
    return m_type == Data::Boolean;
}

bool Data::isNumber() const
{
    return m_type == Data::Number;
}

bool Data::isString() const
{
    return m_type == Data::String;
}

bool Data::isContradiction() const
{
    return m_type == Data::Contradiction;
}

bool Data::operator==(const Data &other) const
{
    return m_type == other.m_type && m_data == other.m_data;
}

bool Data::operator!=(const Data &other) const
{
    return m_type != other.m_type || m_data != other.m_data;
}

QDebug operator<<(QDebug debug, const Data &data)
{
    debug.nospace() << qPrintable(data.toString());
    return debug.space();
}
