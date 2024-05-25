/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Daniel Malasky & Matt
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "star.h"       // for star
#include "uiDraw.h"     // for RANDOM and DRAWSTAR
#include <random>       // for Random
#include <vector>       // for vector
#include <iostream>     
using namespace std;

/*****************************************************
* GENRANDOMPOSITIONS
* generate a vector of random positions
*****************************************************/
vector<Position> Star::genRandomPositions()
{
   const int numStars = 50;
   vector<Position> randomPositions(numStars);  // Initialize numStars

   random_device rd;                            // obtain a random number 
   mt19937 gen(rd());                           // seed the generator
   uniform_int_distribution<> distrY(300, 400); // define the range 
   uniform_int_distribution<> distrX(0, 400);

   // Loop for 50 stars.
   for (int i = 0; i < numStars; i++)
   {
      randomPositions[i].setX(distrX(gen));
      randomPositions[i].setY(distrY(gen));
   }

   return randomPositions;
}



