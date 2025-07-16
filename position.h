/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    Matt Benson
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/

#pragma once
#include <iostream> 
#include <cmath>

class Velocity;        // for Position::add()
class Acceleration;    // for Position::add()
class TestPosition;    // for the unit tests

 /*********************************************
  * Position
  * A single position on the field in Meters
  *********************************************/
class Position
{
public:
   friend ::TestPosition;

   // constructors
   Position() : x(0), y(0) {}
   Position(double x, double y);
   Position(const Position& pt) : x(pt.x), y(pt.y) {}
   Position& operator = (const Position& pt);

   // getters
   double getMetersX()       const { return x; }
   double getMetersY()       const { return y; }
   double getPixelsX()       const { return x / metersFromPixels; }
   double getPixelsY()       const { return y / metersFromPixels; }
   double getZoom()          const { return metersFromPixels; }

   // setters
   void setZoom(double z) { metersFromPixels = z; }
   void setMeters(double xMeters, double yMeters) { x = xMeters, y = yMeters; }
   void setMetersX(double xMeters) { x = xMeters; }
   void setMetersY(double yMeters) { y = yMeters; }
   void setPixelsX(double xPixels) { x = xPixels * metersFromPixels; }
   void setPixelsY(double yPixels) { y = yPixels * metersFromPixels; }
   double addMetersX(double x) { return this->x += x; }
   double addMetersY(double y) { return this->y += y; }
   double addPixelsX(double x) { return this->x += (x * metersFromPixels); }
   double addPixelsY(double y) { return this->y += (y * metersFromPixels); }
   void add(const Acceleration& a, const Velocity& v, double t);
   void reverse() {}
   static Position rotate(const Position& posCenter, double angle, double xOffset, double yOffset);


private:
   double x;                 // horizontal position
   double y;                 // vertical position
   static double metersFromPixels;
};

// stream I/O useful for debugging
std::ostream& operator << (std::ostream& out, const Position& pt);
std::istream& operator >> (std::istream& in, Position& pt);


/*********************************************
 * PT
 * Trivial point
 *********************************************/
struct PT
{
   double x;
   double y;
};

/*********************************************
 * COMPUTE DISTANCE
 * Find the distance between two positions
 *********************************************/
inline double computeDistance(const Position& pos1, const Position& pos2)
{
   double x = pos1.getMetersX() - pos2.getMetersX();
   double y = pos1.getMetersY() - pos2.getMetersY();
   return sqrt(x * x + y * y);
}