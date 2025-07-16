/***********************************************************************
 * Source File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#include <string>     // need you ask?
#include <sstream>    // convert an integer into text
#include <cassert>    // I feel the need... the need for asserts
#include <time.h>     // for clock


#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#include <openGL/gl.h>    // Main OpenGL library
#include <GLUT/glut.h>    // Second OpenGL library
#endif // __APPLE__

#ifdef __linux__
#include <GL/gl.h>        // Main OpenGL library
#include <GL/glut.h>      // Second OpenGL library
#endif // __linux__

#ifdef _WIN32
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>         // OpenGL library we copied 
#define _USE_MATH_DEFINES
#include <math.h>
#endif // _WIN32

#include "position.h"
#include "uiDraw.h"

using namespace std;

// colors ueed in the simulator
const int RGB_WHITE[] = { 255, 255, 255 };
const int RGB_LIGHT_GREY[] = { 196, 196, 196 };
const int RGB_GREY[] = { 128, 128, 128 };
const int RGB_DARK_GREY[] = { 64,   64,  64 };
const int RGB_DEEP_BLUE[] = { 64,   64, 156 };
const int RGB_BLUE[] = { 0,     0, 256 };
const int RGB_RED[] = { 255,   0,   0 };
const int RGB_GOLD[] = { 255, 255,   0 };
const int RGB_TAN[] = { 180, 150, 110 };
const int RGB_GREEN[] = { 0, 150,   0 };

/************************************************************************
 * ROTATE
 * Rotate a given point (point) around a given origin (center) by a given
 * number of degrees (angle).
 *    INPUT  origin   The center point we will rotate around
 *           x,y      Offset from center that we will be rotating, in pixels
 *           rotation Rotation in degrees
 *    OUTPUT point    The new position
 *************************************************************************/
Position rotate(const Position& origin, double x, double y, double rotation)
{
   // because sine and cosine are expensive, we want to call them only once
   double cosA = cos(rotation);
   double sinA = sin(rotation);

   // start with our original point
   Position ptReturn(origin);

   // find the new values
   ptReturn.addPixelsX(x * cosA + y * sinA);
   ptReturn.addPixelsY(y * cosA - x * sinA);

   return ptReturn;
}

/*************************************************************************
 * GL RESET COLOR
 * Just a more convenient way to reset the color
 *************************************************************************/
inline void glResetColor()
{
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
}

/************************************************************
 * COLOR RECTANGLE
 * A structure used to conveniently specify a rectangle
 * of a certain color
 ************************************************************/
struct ColorRect
{
   int x0;
   int y0;
   int x1;
   int y1;
   int x2;
   int y2;
   int x3;
   int y3;
   const int* rgb;
};

/************************************************************************
* GL COLOR
* Set the color on the board
*   INPUT  rgb  RGB color in integers (0...255)
*************************************************************************/
void glColor(const int* rgb)
{
   glColor3f((GLfloat)(rgb[0] / 256.0),
      (GLfloat)(rgb[1] / 256.0),
      (GLfloat)(rgb[2] / 256.0));
}

/*************************************************************************
 * GL VERTEXT POINT
 * Just a more convenient format of glVertext2f
 *************************************************************************/
inline void glVertexPoint(const Position& point)
{
   glVertex2f((GLfloat)point.getPixelsX(), (GLfloat)point.getPixelsY());
}

/*************************************************************************
 * GL DRAW RECT
 * Draw a colored rectangle
 *************************************************************************/
void glDrawRect(const Position& center, const Position& offset,
   const ColorRect& rect, double rotation)
{
   glBegin(GL_QUADS);
   glColor(rect.rgb);
   glVertexPoint(rotate(center,
      rect.x0 + offset.getPixelsX(),
      rect.y0 + offset.getPixelsY(),
      rotation));
   glVertexPoint(rotate(center,
      rect.x1 + offset.getPixelsX(),
      rect.y1 + offset.getPixelsY(),
      rotation));
   glVertexPoint(rotate(center,
      rect.x2 + offset.getPixelsX(),
      rect.y2 + offset.getPixelsY(),
      rotation));
   glVertexPoint(rotate(center,
      rect.x3 + offset.getPixelsX(),
      rect.y3 + offset.getPixelsY(),
      rotation));
   glEnd();
}

/*************************************************************************
 * DRAW TEXT
 * Draw text using a simple bitmap font
 *   INPUT  topLeft   The top left corner of the text
 *          text      The text to be displayed
 ************************************************************************/
void drawText(const Position& topLeft, const char* text)
{
   void* pFont = GLUT_BITMAP_HELVETICA_12;  // also try _18

   // prepare to draw the text from the top-left corner
   glRasterPos2f((GLfloat)topLeft.getPixelsX(),
      (GLfloat)topLeft.getPixelsY());

   // loop through the text
   for (const char* p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}

/*************************************************************************
 * DRAW Circle
 ************************************************************************/
 // Draw a filled circle with given center, radius and color
void ogstream::drawCircle(const Position& center,
   double radius,
   double red,
   double green,
   double blue) const
{
   const int segments = 40; // number of triangles used to approximate the circle
   const double angleIncrement = 2.0 * M_PI / segments;

   glColor3f(red, green, blue);
   glBegin(GL_TRIANGLE_FAN);
   glVertex2d(center.getMetersX(), center.getMetersY()); // center vertex

   for (int i = 0; i <= segments; i++)
   {
      double angle = i * angleIncrement;
      double x = center.getMetersX() + radius * cos(angle);
      double y = center.getMetersY() + radius * sin(angle);
      glVertex2d(x, y);
   }

   glEnd();
}

/*************************************************************************
 * DISPLAY the results on the screen
 *************************************************************************/
void ogstream::flush()
{
   string sOut;
   string sIn = str();

   // copy everything but the newlines
   for (string::iterator it = sIn.begin(); it != sIn.end(); ++it)
      // newline triggers an buffer flush and a move down
      if (*it == '\n')
      {
         drawText(pt, sOut.c_str());
         sOut.clear();
         pt.addPixelsY(-18);
      }
   // othewise append
      else
         sOut += *it;

   // put the text on the screen
   if (!sOut.empty())
   {
      drawText(pt, sOut.c_str());
      pt.addPixelsY(-18);
   }

   // reset the buffer
   str("");
}

/************************************************************************
 * DRAW LINE
 * Draw a line on the screen from the beginning to the end.
 *   INPUT  begin     The position of the beginning of the line
 *          end       The position of the end of the line
 *************************************************************************/
void ogstream::drawLine(const Position& posBegin, const Position& posEnd,
   double red, double green, double blue) const
{
   // Get ready...
   glBegin(GL_LINES);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertexPoint(posBegin);
   glVertexPoint(posEnd);

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

/************************************************************************
 * DRAW RECTANGLE
 * Draw a rectangle on the screen from the beginning to the end.
 *   INPUT  begin     The position of the beginning of the rectangle
 *          end       The position of the end of the rectangle
 *************************************************************************/
void ogstream::drawRectangle(const Position& posBegin, const Position& posEnd,
   double red, double green, double blue) const
{
   // Get ready...
   glBegin(GL_QUADS);
   glColor3f((GLfloat)red, (GLfloat)green, (GLfloat)blue);

   // Draw the actual line
   glVertex2f((GLfloat)posBegin.getPixelsX(), (GLfloat)posBegin.getPixelsY());
   glVertex2f((GLfloat)posBegin.getPixelsX(), (GLfloat)posEnd.getPixelsY());
   glVertex2f((GLfloat)posEnd.getPixelsX(), (GLfloat)posEnd.getPixelsY());
   glVertex2f((GLfloat)posEnd.getPixelsX(), (GLfloat)posBegin.getPixelsY());

   // Complete drawing
   glColor3f((GLfloat)1.0 /* red % */, (GLfloat)1.0 /* green % */, (GLfloat)1.0 /* blue % */);
   glEnd();
}

// Helper to draw a filled circle (wheel)
void drawWheel(const Position& center, double rotation, double x, double y, double radius)
{
   const int numSegments = 20;  // smooth circle
   glBegin(GL_TRIANGLE_FAN);
   glColor(RGB_DARK_GREY); // Black color
   // Center of the wheel
   glVertexPoint(rotate(center, x, y, rotation));
   for (int i = 0; i <= numSegments; i++)
   {
      double angle = i * 2.0 * M_PI / numSegments;
      double px = x + radius * cos(angle);
      double py = y + radius * sin(angle);
      glVertexPoint(rotate(center, px, py, rotation));
   }
   glEnd();
}

/************************************************************************
 * DRAW Ship
 * Draw a spaceship on the screen
 *  INPUT center    The position of the ship
 *        rotation  Which direction it is point
 *        offset    For pieces of the satellite, this is the relative position of the center
 *                  of rotation when it is connected to the main satellite
 *        thrust    Whether the thrusters are on
 *************************************************************************/
void ogstream::drawShip(const Position& center, double rotation, bool thrust)
{
   const double scale = 0.7;
   const double centerShift = 60.0 * scale; // scaled center of rotation

   // Scaled fuselage points
   const PT fuselage[] = {
       {(0 - 60.0) * scale, 0 * scale},       // Nose tip
       {(10 - 60.0) * scale, 8 * scale},      // Nose upper curve
       {(50 - 60.0) * scale, 12 * scale},     // Front fuselage upper
       {(100 - 60.0) * scale, 12 * scale},    // Rear fuselage upper
       {(120 - 60.0) * scale, 8 * scale},     // Tail upper taper
       {(120 - 60.0) * scale, -8 * scale},    // Tail lower taper
       {(100 - 60.0) * scale, -12 * scale},   // Rear fuselage lower
       {(50 - 60.0) * scale, -12 * scale},    // Front fuselage lower
       {(10 - 60.0) * scale, -8 * scale},     // Nose lower curve
       {(0 - 60.0) * scale, 0 * scale}        // Back to nose tip to close
   };

   // Scaled wing points
   const PT wing[] = {
       {(40 - 60.0) * scale, 12 * scale},     // Wing root upper front
       {(70 - 60.0) * scale, 30 * scale},     // Wing tip upper
       {(90 - 60.0) * scale, 30 * scale},     // Wing tip lower
       {(70 - 60.0) * scale, 12 * scale}      // Wing root lower back
   };

   // Scaled engine points
   const PT engine[] = {
       {(60 - 60.0) * scale, 12 * scale},    // Front top
       {(75 - 60.0) * scale, 12 * scale},    // Front bottom
       {(75 - 60.0) * scale, 0 * scale},     // Back bottom
       {(60 - 60.0) * scale, 0 * scale}      // Back top
   };

   // Scaled horizontal stabilizer
   const PT tailWing[] = {
       {(110 - 12 - 60.0) * scale, 8 * scale},    // Root front
       {(130 - 12 - 60.0) * scale, 20 * scale},   // Tip upper
       {(140 - 12 - 60.0) * scale, 15 * scale},   // Tip lower
       {(115 - 12 - 60.0) * scale, 8 * scale}     // Root back
   };

   // Scaled vertical stabilizer
   const PT tailFin[] = {
       {(120 - 12 - 60.0) * scale, 8 * scale},    // Base bottom
       {(140 - 12 - 60.0) * scale, 40 * scale},   // Top tip
       {(135 - 12 - 60.0) * scale, 8 * scale}     // Base top back
   };

   // Draw fuselage
   glBegin(GL_TRIANGLE_FAN);
   glColor(RGB_WHITE);
   for (int i = 0; i < sizeof(fuselage) / sizeof(PT); i++)
      glVertexPoint(rotate(center, fuselage[i].x, fuselage[i].y, rotation));
   glEnd();

   // Draw wing
   glBegin(GL_POLYGON);
   glColor(RGB_DEEP_BLUE);
   for (int i = 0; i < sizeof(wing) / sizeof(PT); i++)
      glVertexPoint(rotate(center, wing[i].x, wing[i].y, rotation));
   glEnd();

   // Draw engine
   glBegin(GL_POLYGON);
   glColor(RGB_DEEP_BLUE);
   for (int i = 0; i < sizeof(engine) / sizeof(PT); i++)
      glVertexPoint(rotate(center, engine[i].x, engine[i].y, rotation));
   glEnd();

   // Draw tail horizontal stabilizer
   glBegin(GL_POLYGON);
   glColor(RGB_DEEP_BLUE);
   for (int i = 0; i < sizeof(tailWing) / sizeof(PT); i++)
      glVertexPoint(rotate(center, tailWing[i].x, tailWing[i].y, rotation));
   glEnd();

   // Draw vertical tail fin
   glBegin(GL_TRIANGLES);
   glColor(RGB_DEEP_BLUE);
   for (int i = 0; i < sizeof(tailFin) / sizeof(PT); i++)
      glVertexPoint(rotate(center, tailFin[i].x, tailFin[i].y, rotation));
   glEnd();

   // Draw cockpit window (small trapezoid near nose)
   glBegin(GL_POLYGON);
   glColor(RGB_LIGHT_GREY);
   glVertexPoint(rotate(center, (15 - 60.0) * scale, 6 * scale, rotation));
   glVertexPoint(rotate(center, (30 - 60.0) * scale, 8 * scale, rotation));
   glVertexPoint(rotate(center, (35 - 60.0) * scale, 4 * scale, rotation));
   glVertexPoint(rotate(center, (15 - 60.0) * scale, 2 * scale, rotation));
   glEnd();

   // Draw wheels under fuselage
   const double wheelRadius = 4.0 * scale;
   // Front wheel near nose bottom
   drawWheel(center, rotation, (20 - 60.0) * scale, -15 * scale, wheelRadius);
   // Rear wheel near tail bottom
   drawWheel(center, rotation, (90 - 60.0) * scale, -15 * scale, wheelRadius);

   // Draw thrust flames if thrust on (behind tail)
   if (thrust)
   {
      glBegin(GL_TRIANGLES);
      glColor(RGB_RED);
      glVertexPoint(rotate(center, (120 - 60.0) * scale, 0, rotation));
      glVertexPoint(rotate(center, (140 - 60.0) * scale, random(-8.0 * scale, 8.0 * scale), rotation));
      glVertexPoint(rotate(center, (120 - 60.0) * scale, 8 * scale, rotation));
      glEnd();
   }

   glResetColor();
}

// Draw control tower at fixed background location
void ogstream::drawControlTower(const Position& base, double height)
{
   const double towerWidth = 25.0;
   const double towerHeight = height;
   const double roomHeight = 25.0;
   const double roomWidth = 45.0;
   const double antennaHeight = 30.0;

   // Tower base (rectangle)
   glBegin(GL_QUADS);
   glColor(RGB_DARK_GREY);
   glVertexPoint(base);
   glVertexPoint(Position(base.getMetersX() + towerWidth, base.getMetersY()));
   glVertexPoint(Position(base.getMetersX() + towerWidth, base.getMetersY() + towerHeight));
   glVertexPoint(Position(base.getMetersX(), base.getMetersY() + towerHeight));
   glEnd();

   // Control room at top (wider)
   glBegin(GL_QUADS);
   glColor(RGB_GREY);
   glVertexPoint(Position(base.getMetersX() - (roomWidth - towerWidth) / 2, base.getMetersY() + towerHeight));
   glVertexPoint(Position(base.getMetersX() + towerWidth + (roomWidth - towerWidth) / 2, base.getMetersY() + towerHeight));
   glVertexPoint(Position(base.getMetersX() + towerWidth + (roomWidth - towerWidth) / 2, base.getMetersY() + towerHeight + roomHeight));
   glVertexPoint(Position(base.getMetersX() - (roomWidth - towerWidth) / 2, base.getMetersY() + towerHeight + roomHeight));
   glEnd();

   // Antenna on top
   glBegin(GL_LINES);
   glColor(RGB_DARK_GREY);
   glVertexPoint(Position(base.getMetersX() + towerWidth / 2, base.getMetersY() + towerHeight + roomHeight));
   glVertexPoint(Position(base.getMetersX() + towerWidth / 2, base.getMetersY() + towerHeight + roomHeight + antennaHeight));
   glEnd();
}

/******************************************************************
 * DUMMY
 ****************************************************************/
void ogstreamDummy::flush() { assert(false); }
void ogstreamDummy::setPosition(const Position& pt) { assert(false); }
ogstreamDummy& ogstreamDummy::operator = (const Position& pt) { assert(false); return *this; }
void ogstreamDummy::drawShip(const Position& center, double rotation, bool thrust) { assert(false); }


/******************************************************************
 * FAKE
 ****************************************************************/
void ogstreamFake::flush() { assert(false); }
void ogstreamFake::setPosition(const Position& pt) { assert(false); }
ogstreamFake& ogstreamFake::operator = (const Position& pt) { assert(false); return *this; }

void ogstreamFake::drawShip(const Position& center, double rotation, bool thrust) { *this << "Ship" << center << rotation << "\n"; }

/******************************************************************
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer
 ****************************************************************/
int random(int min, int max)
{
   assert(min < max);
   int num = (rand() % (max - min)) + min;
   assert(min <= num && num <= max);

   return num;
}

/******************************************************************
 * RANDOM
 * This function generates a random number.
 *
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the double
 ****************************************************************/
double random(double min, double max)
{
   assert(min <= max);
   double num = min + ((double)rand() / (double)RAND_MAX * (max - min));

   assert(min <= num && num <= max);

   return num;
}





