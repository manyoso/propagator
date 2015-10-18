#ifndef cell_h
#define cell_h

#include "data.h"

#include <QtCore>

class Cell : public QObject {
    Q_OBJECT
public:
    Cell();
    Cell(const Data& data);
    Cell(const Cell& cell);
    virtual ~Cell();

    Data data() const;
    void setData(const Data& data);

signals:
    void dataChanged();

private:
    Data m_data;
};

Q_DECLARE_METATYPE(Cell)

#endif // cell_h
