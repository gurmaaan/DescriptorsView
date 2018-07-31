#include "floatservice.h"

FloatService::FloatService()
{

}

bool FloatService::equal(double d1, double d2, double epsilon)
{
    return qAbs(d1 - d2) < epsilon;
}

bool FloatService::equal(double d1, int i1, double epsilon)
{
    return ( qAbs(d1 - (double)i1) < epsilon);
}
