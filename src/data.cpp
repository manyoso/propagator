#include "data.h"

#include "tms.h"

Data* Data::contradiction()
{
    static Data* s_instance = 0;
    if (!s_instance) {
        s_instance = new Data;
        s_instance->m_type = Data::Contradiction;
    }
    return s_instance;
}

Data::Data()
    : m_type(Data::Nothing)
    , m_certainty(0)
{
}

Data::Data(bool b)
    : m_type(Data::Boolean)
    , m_certainty(1)
{
    m_data = b ? "true" : "false";
}

Data::Data(int n)
    : m_type(Data::Number)
    , m_certainty(1)
{
    m_data = QString::number(n);
}

Data::Data(double n)
    : m_type(Data::Number)
    , m_certainty(1)
{
    m_data = QString::number(n);
}

Data::Data(const QString& s)
    : m_type(Data::String)
    , m_certainty(1)
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
    // Merge with one side a 'Nothing'
    if (isNothing())
        return info;
    if (info.isNothing())
        return this;

    // FIXME: Add support for uncertainty and partial information
    return *contradiction();
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

double Data::certainty() const
{
    return m_certainty;
}

bool Data::isContingent() const
{
    return m_premises.count() > 0;
}

bool Data::isJustified() const
{
    if (!isContingent())
        return true;

    bool justified = true;
    QList<QString> worldViewPremises = WorldView::instance()->premises();
    foreach (QString premise, m_premises)
        justified = !worldViewPremises.contains(premise) ? false : justified;
    return justified;
}

QList<QString> Data::premises() const
{
    return m_premises;
}

void Data::addPremise(const QString& premise)
{
    if (!m_premises.contains(premise))
        m_premises.append(premise);
}

void Data::removePremise(const QString& premise)
{
    m_premises.removeAll(premise);
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
