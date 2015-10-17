#ifndef information_h
#define information_h

#include <QtCore>

class Information {
public:
    enum Type {
        Nothing,
        Value
    };

    virtual Type type() const;
    virtual bool isEquivalent(const Information& info) const = 0;
    virtual Information* merge(Information* info) = 0;
    virtual bool isContradiction() const = 0;
};

class Nothing : public Information {
public:
    virtual Type type() const
    { return Information::Nothing; }

    virtual bool isEquivalent(const Information& info) const
    { return info.type() == Information::Nothing; }

    virtual Information* merge(Information* info)
    { return info; }

    virtual bool isContradiction() const
    { return false; }
};

class Value : public Information {
public:
    virtual Type type() const
    { return Information::Value; }

    virtual bool isEquivalent(const Information& info) const
    {
        if (info.type() != Information::Value)
            return false;

        const Value* v = static_cast<const Value*>(&info);
        return v->value() == m_value;
    }

    virtual Information* merge(Information* info)
    {
        m_contradictory = !isEquivalent(*info);
        return this;
    }

    virtual bool isContradictory() const
    { return m_contradictory; }

    QVariant value() const
    { return m_value; }

    void setValue(const QVariant& value)
    { m_value = value; }

private:
    QVariant m_value;
    bool m_contradictory;
};

#endif // information_h
