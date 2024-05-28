/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich & Daniel & Matt
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "position.h"   // for POSITION
#include "uiDraw.h"     // for RANDOM and DRAWSTAR

/*****************************************************
 * STAR
 * A star that twinkles
 *****************************************************/
class Star
{
public:
   Star() : phase(0) {}

   // Set the location of the star field with a random phase.
   void reset(double width, double height)
   {
      pos.setX(random(0.0, width ));
      pos.setY(random(0.0, height));
      phase = random(0, 255);
   }

   // Draw this star and increment the twinkle number.
   void draw(ogstream& gout)
   {
      gout.drawStar(pos, phase++);
   }
private:
   Position pos;          // the location of the star
   unsigned char phase;   // the phase of the twinkling
};
