#include <QtCore>

#include "cell.h"
#include "propagator.h"

static bool s_error = false;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("propagator");
    QCoreApplication::setApplicationVersion("0.1");

    qRegisterMetaType<Cell>();

    Cell a(1);
    Cell b(1);
    Cell answer;
    Addition add(QList<Cell*>() << &a << &b, QList<Cell*>() << &answer);

    qDebug()
      << "answer:" << answer.data() << "\n"
      << "  certainty:" << answer.data().certainty() << "\n"
      << "  isContingent:" << answer.data().isContingent() << "\n"
      << "  isJustified:" << answer.data().isJustified();

    return s_error ? EXIT_FAILURE : EXIT_SUCCESS;
}
