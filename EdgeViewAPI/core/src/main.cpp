#include <QCoreApplication>
#include "EdgeViewAPIServer.hpp"

int main(int argc, char *argv[])
{
    EdgeViewAPIServer *server = new EdgeViewAPIServer(argc, argv);
    server->start();
    return server->exec();
}
