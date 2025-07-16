/***********************************************************************
 * Header File:
 *    User Interface Draw : put pixels on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This is the code necessary to draw on the screen. We have a collection
 *    of procedural functions here because each draw function does not
 *    retain state. In other words, they are verbs (functions), not nouns
 *    (variables) or a mixture (objects)
 ************************************************************************/

#pragma once

#include <string>     // To display text on the screen
#include <cmath>      // for M_PI, sin() and cos()
#include <algorithm>  // used for min() and max()
#include "position.h" // Where things are drawn
using std::string;
using std::min;
using std::max;

#include <sstream>


#define GL_SILENCE_DEPRECATION

/*************************************************************************
 * GRAPHICS STREAM
 * A graphics stream that behaves much like COUT except on a drawn screen
 *************************************************************************/
class ogstream : public std::ostringstream
{
public:
   ogstream() {}
   ogstream(const Position& pt) : pt(pt) {}
   ~ogstream() { flush(); };

   // This is mostly for the text drawing stuff
   virtual void flush();
   virtual void setPosition(const Position& pt) { flush(); this->pt = pt; }
   virtual ogstream& operator = (const Position& pt)
   {
      setPosition(pt);
      return *this;
   }

   // This is specific to the orbit simulator
   virtual void drawShip(const Position& center, double rotation, bool thrust);

   virtual void drawRectangle(const Position& posBegin,
      const Position& posEnd,
      double red = 1.0,
      double green = 1.0,
      double blue = 1.0) const;

   virtual void drawLine(const Position& posBegin,
      const Position& posEnd,
      double red = 1.0,
      double green = 1.0,
      double blue = 1.0) const;

   virtual void drawCircle(const Position& center,
      double radius,
      double red = 1.0,
      double green = 1.0,
      double blue = 1.0) const;
   virtual void drawControlTower(const Position& base, double height);
protected:
   Position pt;
};

/*************************************************************************
 * GRAPHICS STREAM DUMMY
 * Better not be called!
 *************************************************************************/
class ogstreamDummy : public ogstream
{
public:
   ogstreamDummy(const Position& pt) {}
   ~ogstreamDummy() {}

   // This is mostly for the text drawing stuff
   void flush();
   void setPosition(const Position& pt);
   ogstreamDummy& operator = (const Position& pt);

   // This is specific to the orbit simulator
   void drawShip(const Position& center, double rotation, bool thrust);
};

/*************************************************************************
 * GRAPHICS STREAM Fake
 * Better not be called!
 *************************************************************************/
class ogstreamFake : public ogstream
{
public:
   ogstreamFake(const Position& pt) {}
   ~ogstreamFake() {}

   // This is mostly for the text drawing stuff
   void flush();
   void setPosition(const Position& pt);
   ogstreamFake& operator = (const Position& pt);

   // This is specific to the orbit simulator
   void drawShip(const Position& center, double rotation, bool thrust);

};

/******************************************************************
 * RANDOM
 * This function generates a random number.  The user specifies
 * The parameters
 *    INPUT:   min, max : The number of values (min <= num <= max)
 *    OUTPUT   <return> : Return the integer/double
 ****************************************************************/
int    random(int    min, int    max);
double random(double min, double max);


