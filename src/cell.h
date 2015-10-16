#ifndef cell_h
#define cell_h

#include <QtCore>

class Cell : public QObject {
    Q_OBJECT
public:
    Cell();
    Cell(const QVariant& data);
    virtual ~Cell();

    QVariant data() const;
    void setData(const QVariant& data);

signals:
    void dataChanged();

private:
    QVariant m_data;
};

#endif // cell_h
