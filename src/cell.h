#ifndef cell_h
#define cell_h

#include <QtCore>

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
