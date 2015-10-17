#ifndef propagator_h
#define propagator_h

#include <QtCore>

#include "cell.h"

class Propagator : public Cell {
    Q_OBJECT
public:
    Propagator(const QList<Cell*>& inputs, const QList<Cell*>& outputs);
    virtual ~Propagator();

public slots:
    virtual void run() = 0;

protected:
    QList<Cell*> m_inputs;
    QList<Cell*> m_outputs;
};

class Addition : public Propagator {
public:
    Addition(const QList<Cell*>& inputs, const QList<Cell*>& outputs)
        : Propagator(inputs, outputs) { run(); }

    virtual void run();
};

#endif // propagator_h
