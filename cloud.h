/***********************************************************************
 * Header File:
 *    CLOUD
 * Author:
 *    Matt Benson
 * Summary:
 *    Everything we need to know about the cloud
 ************************************************************************/


#pragma once
#include "Position.h"
#include "uiDraw.h"

class Cloud
{
public:
   // constructors
   Cloud(double x = 0.0, double y = 0.0, double size = 20.0)
      : pos(x, y), size(size) { }

   // setters
   void setPosition(double x, double y) { pos.setMeters(x, y); }
   void setSize(double s) { size = s; }

   // getters
   Position getPosition() const { return pos; }
   double getSize() const { return size; }

   // draw the clouds
   void draw(ogstream& gout) const;

private:
   Position pos;    // position of clouds
   double size;     // cloud size
};