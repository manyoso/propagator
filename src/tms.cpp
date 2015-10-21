#include "tms.h"

WorldView* WorldView::instance()
{
    static WorldView* s_instance = 0;
    if (!s_instance)
        s_instance = new WorldView;
    return s_instance;
}

QList<QString> WorldView::premises() const
{
    return m_premises;
}

void WorldView::setPremises(const QList<QString>& premises)
{
    m_premises = premises;
}

bool WorldView::hasPremise(const QString& premise) const
{
    return m_premises.contains(premise);
}

void WorldView::addPremise(const QString& premise)
{
    if (!m_premises.contains(premise))
        m_premises.append(premise);
}

void WorldView::removePremise(const QString& premise)
{
    m_premises.removeAll(premise);
}

void WorldView::clear()
{
    m_premises.clear();
}
