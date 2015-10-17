#ifndef cell_h
#define cell_h

#include <QtCore>

class Information {
public:
    enum Type {
        Nothing,
        Value
    };

    virtual Type type() const;
    virtual bool equivalent(const Information& info) const = 0;
    virtual Information* merge(Information* info) = 0;
    virtual bool contradiction() const = 0;
};

class Nothing : public Information {
public:
    virtual Type type() const
    { return Information::Nothing; }

    virtual bool equivalent(const Information& info) const
    { return info.type() == Information::Nothing; }

    virtual Information* merge(Information* info)
    { return info; }

    virtual bool contradiction() const
    { return false; }
};

class Value : public Information {
public:
    virtual Type type() const
    { return Information::Value; }

    virtual bool equivalent(const Information& info) const
    {
        if (info.type() != Information::Value)
            return false;

        const Value* v = static_cast<const Value*>(&info);
        return v->value() == m_value;
    }

    virtual Information* merge(Information* info)
    {
        m_contradictory = !equivalent(*info);
        return this;
    }

    virtual bool contradiction() const
    { return m_contradictory; }

    QVariant value() const
    { return m_value; }

    void setValue(const QVariant& value)
    { m_value = value; }

private:
    QVariant m_value;
    bool m_contradictory;
};

class Cell : public QObject {
    Q_OBJECT
public:
    Cell();
    Cell(const QVariant& data);
    Cell(const Cell& cell);
    virtual ~Cell();

    QVariant data() const;
    void setData(const QVariant& data);

signals:
    void dataChanged();

private:
    QVariant m_data;
};

Q_DECLARE_METATYPE(Cell)

#endif // cell_h
