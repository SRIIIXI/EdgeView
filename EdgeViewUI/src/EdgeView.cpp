#include "EdgeView.hpp"

EdgeViewApplication* edgeViewPtr = nullptr;

EdgeViewApplication::EdgeViewApplication(int argc, char *argv[])
    :QGuiApplication(argc, argv)
{
    edgeViewPtr = this;
}

EdgeViewApplication::~EdgeViewApplication()
{
}
