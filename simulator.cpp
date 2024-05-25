/**********************************************************************
 * LAB 06
 * Bro Helfrich & Daniel & Matt
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "angle.h"       // angle of the lander
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include "star.h"        // for stars
#include "lander.h"      // for lander
#include "acceleration.h" // for acceleration
using namespace std;



// TODO ticket 5-7
// draw function
// check logic.h for thrust and lander.h

/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   // set up the simulator
   // Simulator(const Position& posUpperRight) : ground(posUpperRight),
   //    posLander(posUpperRight.getX() / 2, posUpperRight.getY() / 2) {}
   Simulator(const Position& posUpperRight) : ground(posUpperRight),
      lander(posUpperRight) {}
   

   // display stuff on the screen
   void display();

   Angle a;
   Ground ground;
   Lander lander;
   //Position posLander;
   Star star;
   vector<Position> randomStarPositions = star.genRandomPositions();
   //Position posStar = Position(300, 300); // Default value to keep above ground
   //unsigned char phase = 0;
   
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
   gout.drawLander(lander.getPosition() , a.getRadians());

   // draw 50 stars
   for (int i = 0; i < randomStarPositions.size(); i++)
   {
      gout.drawStar(randomStarPositions[i], star.getPhase() + i);
   }
   
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

   // draw the game
   pSimulator->display();


   Thrust thrust;
   // handle input
   if (pUI->isUp())
   {
      pSimulator->lander.input(thrust, -1.0);
   }
   if (pUI->isLeft())
   {
      pSimulator->a.add(M_PI/ 10);     // rotate left
   }
   if (pUI->isRight())
   {
      pSimulator->a.add(-M_PI_2 / 4);  // rotate right
   }
   
   // Make starts twinkle
   pSimulator->star.incrementPhase();

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