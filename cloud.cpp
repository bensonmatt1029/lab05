/***********************************************************************
 * Source File:
 *    CLOUD
 * Author:
 *    Matt Benson
 * Summary:
 *    Everything we need to know about a cloud
 ************************************************************************/

#include "Cloud.h"

 /***************************************************************
  * DRAW
  * Draw the clouds on the screen
  ***************************************************************/
void Cloud::draw(ogstream& gout) const
{
   // Draw cloud as several overlapping white circles
   gout.drawCircle(Position(pos.getMetersX(), pos.getMetersY()), size, 1.0, 1.0, 1.0);
   gout.drawCircle(Position(pos.getMetersX() - size * 0.6, pos.getMetersY()), size * 0.8, 1.0, 1.0, 1.0);
   gout.drawCircle(Position(pos.getMetersX() + size * 0.6, pos.getMetersY()), size * 0.8, 1.0, 1.0, 1.0);
   gout.drawCircle(Position(pos.getMetersX() - size * 0.3, pos.getMetersY() + size * 0.4), size * 0.8, 1.0, 1.0, 1.0);
   gout.drawCircle(Position(pos.getMetersX() + size * 0.3, pos.getMetersY() + size * 0.4), size * 0.8, 1.0, 1.0, 1.0);
}