#include <QDebug>
#include "app.h"

int main(int argc, char *argv[])
{
    return App::instance()->init(argc, argv);
}
