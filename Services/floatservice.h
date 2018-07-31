#ifndef FLOATSERVICE_H
#define FLOATSERVICE_H

#include <QObject>

class FloatService
{
public:
    FloatService();
    static bool equal(double d1, double d2, double epsilon = 0.0001);
    static bool equal(double d1, int i1, double epsilon = 0.0001);
};

#endif // FLOATSERVICE_H
