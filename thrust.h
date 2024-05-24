/***********************************************************************
 * Header File:
 *    Thrust : Represents activation of thrusters
 * Author:
 *    Br. Helfrich
 * Summary:
 *    down, clockwise, and counterclockwise
 ************************************************************************/

#pragma once

#include "uiInteract.h"  // for Interface

class TestLander;
class TestThrust;

 /*****************************************************
  * THRUST
  * Represents activation of thrusters
  *****************************************************/
class Thrust
{
   friend TestLander;
   friend TestThrust;
   
public:
   // Thrust is initially turned off
   Thrust() : mainEngine(false), clockwise(false), counterClockwise(false) {}

   // Get rotation in radians per second
   double rotation() const
   {
      if (clockwise && counterClockwise) return 0.0;
      else if (clockwise) return 0.1;
      else if (counterClockwise) return -0.1;
      else return 0.0; 
   }

   // get main engine thrust in  m / s ^ 2
   double mainEngineThrust() const
   {
      return 45000.00 / 15103.00;
   }

   // reflect what is firing
   bool isMain()    const { return mainEngine; }
   bool isClock()   const { return clockwise; }
   bool isCounter() const { return counterClockwise; }

   
   // 0 or 1
   // set the thrusters
   void set(const Interface * pUI)
   {
      mainEngine = true;
      clockwise = true;
      counterClockwise = true;

      if (pUI->isDown() < 1 ) 
      {
         mainEngine = false;
      }
      if (pUI->isLeft() < 1)
      {
         clockwise = false;
      }
      if (pUI->isRight() < 1)
      {
         counterClockwise = false;
      }
      
   }

private:
   bool mainEngine;
   bool clockwise;
   bool counterClockwise;
};
