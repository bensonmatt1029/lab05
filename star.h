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
#include <random>
#include <vector>

/*****************************************************
 * STAR
 * A star that twinkles
 *****************************************************/
class Star
{
private:
   Position position   = Position(300, 300); // Default value to keep above ground
   unsigned char phase = 0;                  // NOTE - increment by one for each new star
   
public:
   // Default Constructor
   Star() {}

   Position getPosition()     { return position; }
   unsigned char getPhase()   { return phase; }
   void incrementPhase()      { phase++; }
   std::vector<Position> genRandomPositions();
};
