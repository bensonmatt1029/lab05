/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"
#include <random>

#include <iostream>

using namespace std;

 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
   random_device rd;                         // obtain a random number from hardware
   mt19937 gen(rd());                        // seed the generator
   uniform_int_distribution<> distr(75.0, 95.0); // define the range
   uniform_int_distribution<> distr2(-10.0, -4.0);
   uniform_int_distribution<> distr3(-2.0, 2.0);


   status = PLAYING;
   fuel = 5000.0;
   angle.setUp();
   pos.setX(99.0);
   pos.setY(distr(gen));
   velocity.setDX(distr2(gen));
   velocity.setDY(distr3(gen));
   
   
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   // use angle and thrust for ddx and ddy.
   // Find out how angle affect thrust
   // determine if we can use getters to replace the conditional by get(isMain())

   Acceleration acc;
   if (angle.getRadians() != 0.0 && thrust.isMain()) // fix conditional, or move, or remove.
   {
      acc.set(angle, thrust.mainEngineThrust());
      acc.setDDY(acc.getDDY() + gravity);
      fuel -= 10;
      //acc = Acceleration(thrust.mainEngineThrust(), thrust.mainEngineThrust() + gravity);
   }
   else
      acc = Acceleration(0.0, gravity);
  
   return acc;
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   
   pos.add(acceleration, velocity, time); // update position
   velocity.add(acceleration, time); // update velocity

}
