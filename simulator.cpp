/**********************************************************************
 * LAB 06
 * Bro Helfrich & Daniel & Matt
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"     // everything should have a point
#include "angle.h"        // angle of the lander
#include "uiInteract.h"   // for INTERFACE
#include "uiDraw.h"       // for RANDOM and DRAW*
#include "ground.h"       // for GROUND
#include "test.h"         // for the unit tests
#include <cmath>          // for SQRT
#include <cassert>        // for ASSERT
#include "star.h"         // for stars
#include "lander.h"       // for lander
#include "acceleration.h" // for acceleration
#include <vector>
#include <iostream>
using namespace std;

/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   // set up the simulator
   Simulator(const Position& posUpperRight)
      : ground(posUpperRight), lander(posUpperRight)
   {
      // Create stars
      for (int i = 0; i < 50; i++)
      {
         Star star;
         star.reset(posUpperRight.getX(), posUpperRight.getY());
         stars.push_back(star);
      }
   }

   // display stuff on the screen
   void display();

   // update the simulator for each frame
   void update(const Interface* pUI);

private:
   Ground ground;
   Lander lander;
   Thrust thrust;
   std::vector<Star> stars; // List of stars in the simulation
};

/**********************************************************
 * DISPLAY
 * Draw on the screen
 **********************************************************/
void Simulator::display()
{
   ogstream gout;

   // draw the ground
   ground.draw(gout);

   // draw the lander
   lander.draw(thrust, gout);

   // draw 50 stars
   for (auto& star : stars)
   {
      star.draw(gout);
   }
}

/**********************************************************
 * UPDATE
 * Update the simulator state for each frame
 **********************************************************/
void Simulator::update(const Interface* pUI)
{
   // update the thrust based on user input
   thrust.set(pUI);

   // Get the gravity from the ground
   double gravity = -1.0;

   // Calculate the acceleration based on input and gravity
   Acceleration acceleration = lander.input(thrust, gravity);

   // Check for collision with the ground
   if (ground.hitGround(lander.getPosition(), lander.getWidth()))
   {
      if (lander.getSpeed() < lander.getMaxSpeed())
      {
         lander.land();
      }
      else
      {
         lander.crash();
      }
   }

   // Draw the game
   display();
}

/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator* pSimulator = (Simulator*)p;

   // Update the simulator state
   pSimulator->update(pUI);
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();

   // Initialize OpenGL
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action
   ui.run(callBack, (void*)&simulator);

   return 0;
}