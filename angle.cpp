/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;


/************************************
  * ANGLE : NORMALIZE
  ************************************/
double Angle::normalize(double radians) const
{
    double twoPi = 2 * M_PI;

    return (radians)-floor((radians) / (twoPi)) * (twoPi);
}

/************************************
  * ANGLE : SETRADIANS
  * Sets radians with range of 0 - 2PI
  ************************************/
void Angle::setRadians(double radians)
{
    if (radians <= 0 || radians >= (2 * M_PI))
    {
        this->radians = normalize(radians);
    }
    else
    {
        this->radians = radians;
    }
}

/**********************************************
  * ANGLE : SETDEGREES
  * Converts degrees to radians, sets radians
  *********************************************/
void Angle::setDegrees(double degrees)
{
    double r = (2 * M_PI) * (degrees / 360);
    setRadians(r);
}

/**********************************************************
  * ANGLE : ADD
  * Adds the given value to radians, within range (0, 2PI)
  *********************************************************/
Angle& Angle::add(double delta)
{
    radians += delta;

    if (radians <= 0 || radians >= (2 * M_PI))
    {
        radians = normalize(radians);
    }

    return *this;
}