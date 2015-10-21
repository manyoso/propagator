#ifndef tms_h
#define tms_h

#include <QtCore>

class WorldView {
public:
    static WorldView* instance();

    QList<QString> premises() const;
    void setPremises(const QList<QString>& premises);

    bool hasPremise(const QString&) const;

    void addPremise(const QString&);
    void removePremise(const QString&);

    void clear();

private:
    WorldView() { }
    ~WorldView() { }

    QList<QString> m_premises;
};

class TMS {
public:
    TMS();

private:
};

#endif // tms_h
