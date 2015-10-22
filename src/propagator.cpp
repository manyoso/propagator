#include "propagator.h"

#include <QtCore>

Propagator::Propagator(const QList<Cell*>& inputs, const QList<Cell*>& outputs)
    : m_inputs(inputs)
    , m_outputs(outputs)
{
    foreach(Cell* c, m_inputs) {
        QObject::connect(c, &Cell::dataChanged,
                         this, &Propagator::run);
    }
}

Propagator::~Propagator()
{ }

void Add::run()
{
    int result = 0;
    foreach (Cell* c, m_inputs) {
      int data = c->data().toNumber();
      result += data;
    }
    foreach (Cell* c, m_outputs) {
      c->setData(result);
    }
}
