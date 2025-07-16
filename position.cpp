/***********************************************************************
 * Source File:
 *    POSITION
 * Author:
 *    Matt Benson & Daniel Malasky
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#include "position.h"
#include "velocity.h"
#include "acceleration.h"
#define _USE_MATH_DEFINES 
#include <math.h>
#include <cassert>


Position::Position(double x, double y) : x(x), y(y) { }

/******************************************
 * POINT : ASSIGNMENT
 * Assign a point. Please look ahead to
 * Week 12 C++ reading for an idea of how this works.
 * Basically, we are copying the data from posRHS
 * into this.
 *****************************************/
Position& Position::operator = (const Position& posRHS)
{
   if (this != &posRHS)
   {
      x = posRHS.x;
      y = posRHS.y;
   }
   return *this;
}

/************************************************************************
 * UPDATE POSITION
 * Update the current position based on the impulse of velocity
 * taking into account time dilation:
 *
 *   s = s_0 + vt + 1/2 at^2
 *
 *   INPUT  POSITION     The location of the item
 *          VELOCITY     The velocity of the item
 *          ACCELERATION The acceleration of the item
 *          TIME         How much time are we talking about?
 *   OUTPUT POSITION     The location, updated
 *
 *
 *  x = x + dx t + 1/2 ddx t^2
 *  y = y + dy t + 1/2 ddy t^2
 *************************************************************************/
void Position::add(const Acceleration& a, const Velocity& v, double t)
{
   x += (v.getDX() * t) + (0.5 * a.getDDX() * (t * t));
   y += (v.getDY() * t) + (0.5 * a.getDDY() * (t * t));
}

/************************************************************************
 * Position Rotate
 *
 *************************************************************************/
Position Position::rotate(const Position& posCenter, double angle, double xOffset, double yOffset)
{
   double radians = angle * (M_PI / 180.0);  // Convert angle to radians

   // Assuming Position has x and y members for position
   double newX = posCenter.getMetersX() + xOffset * cos(radians) - yOffset * sin(radians);
   double newY = posCenter.getMetersY() + xOffset * sin(radians) + yOffset * cos(radians);

   return Position(newX, newY);  // Return the rotated position
}

/******************************************
 * POSITION insertion
 *       Display coordinates on the screen
 *****************************************/
std::ostream& operator << (std::ostream& out, const Position& pt)
{
   out << "(" << pt.getMetersX() << "m , " << pt.getMetersY() << "m)";
   return out;
}

/*******************************************
* POSITION extraction
*       Prompt for coordinates
******************************************/
std::istream& operator >> (std::istream& in, Position& pt)
{
   double x;
   double y;
   in >> x >> y;

   pt.setMetersX(x);
   pt.setMetersY(y);

   return in;
}

