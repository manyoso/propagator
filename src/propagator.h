#ifndef propagator_h
#define propagator_h

#include <QtCore>

#include "cell.h"

class Propagator : public Cell {
    Q_OBJECT
public slots:
    virtual void run() { }

protected:
    Propagator(const QList<Cell*>& inputs, const QList<Cell*>& outputs);
    virtual ~Propagator();
    QList<Cell*> m_inputs;
    QList<Cell*> m_outputs;
};

class Add : public Propagator {
public:
    Add(const QList<Cell*>& inputs, const QList<Cell*>& outputs)
        : Propagator(inputs, outputs) { run(); }

    virtual void run();
};

#endif // propagator_h
