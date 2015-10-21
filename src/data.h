#ifndef data_h
#define data_h

#include <QtCore>

class Data {
public:
    enum Type {
        Nothing,
        Boolean,
        Number,
        String,
        Contradiction
    };

    Data();
    Data(bool b);
    Data(int n);
    Data(double n);
    Data(const QString& s);
    ~Data();

    Type type() const;
    bool toBool() const;
    double toNumber() const;
    QString toString() const;

    bool isNothing() const;
    bool isBoolean() const;
    bool isNumber() const;
    bool isString() const;
    bool isContradiction() const;

    double certainty() const;
    bool isContingent() const;
    bool isJustified() const;

    QList<QString> premises() const;
    void addPremise(const QString&);
    void removePremise(const QString&);

    Data merge(const Data& info);

    bool operator==(const Data &other) const;
    bool operator!=(const Data &other) const;

private:
    static Data* contradiction();

    Type m_type;
    QString m_data;
    QList<QString> m_premises;
    double m_certainty; // a number between 0 and 1
};

QDebug operator<<(QDebug debug, const Data &data);

#endif // data_h
