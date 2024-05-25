/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich & Daniel & Matt
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
   random_device rd;                              // obtain a random number
   mt19937 gen(rd());                             // seed the generator
   uniform_int_distribution<> distr(75.0, 95.0);  // define the range
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
   // We couldn't get this portion to work.
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   Acceleration acc(0.0, gravity);

   // No fuel
   if (fuel <= 0.0)
      return acc;

   double thrustForce = thrust.mainEngineThrust();
   double angleRadians = angle.getRadians();

   // Main thruster
   if (thrust.isMain())
   {
      double thrustDDX = -sin(angleRadians) * thrustForce;
      double thrustDDY =  cos(angleRadians) * thrustForce;
      acc              = Acceleration(thrustDDX, gravity + thrustDDY);
      fuel            -= 10;
   }

   // Counter Clockwise thruster
   else if (thrust.isCounter())
   {
      acc.setDDY(gravity);
      angle.setRadians(angle.getRadians() - 0.1);
      fuel -= 1.0;
   }

   // Clockwise thruster
   else if (thrust.isClock())
   {
      acc.setDDY(gravity);
      angle.setRadians(angle.getRadians() + 0.1);
      fuel -= 1.0;
   }

   // input_none
   else
   {
      acc = Acceleration(0.0, gravity);
   }

   return acc;
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   
   pos.add(acceleration, velocity, time); // update position
   velocity.add(acceleration, time);      // update velocity
}

