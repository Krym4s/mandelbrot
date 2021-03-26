#include <iostream>
#include "Optimzation0.h"

int main() {
    WindowOptions options = {};
    SetWindowOptions (&options, 800, 800, 0, 0, 0.002);

    ComplexPoint interestingPoint = {};
    SetPoint (&interestingPoint, 0, 0);

    ShowMandelbrotSet (&options, &interestingPoint);
    return 0;
}
