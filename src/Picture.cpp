/*
 * Picture.cpp
 *
 *  Created on: Feb 14, 2022
 *      Author: doug
 */


#include "Picture.h"

// This is where we actually instantiate the groups
LightGroup grp_Test   ("test",   noRows, noCols);
LightGroup grp_Sky    ("sky",    noRows, noCols);
LightGroup grp_SkyBlue("skyBlue",noRows, noCols);
LightGroup grp_Ocean  ("ocean",  noRows, noCols);
LightGroup grp_Ocean2 ("ocean2", noRows, noCols);
LightGroup grp_Land   ("land",   noRows, noCols);
LightGroup grp_Orange ("orange", noRows, noCols);
LightGroup grp_Yellow ("yellow", noRows, noCols);

void Init_Test()
{
	static const int lumins=64;

	// Test pattern - a cross.
	// Vertical bar RED
	int count=0;
	for (int row=0; row<noRows/2; row++)
	{
		grp_Test.pushRGB( noCols/2, row, lumins, 0, 0);  // One row (red)
		count++;
	}

	// Horizonal bar GREEN
	for (int col=0; col<noCols/2; col++)
		{
		grp_Test.pushRGB(col, noRows/2, 0,lumins,0);  // One row (green)
		count++;
		}

	// Surround with BLUE
	for (int col=0; col<noCols; col++)
	{
		grp_Test.pushRGB(col, 0, 0,0,lumins);
		grp_Test.pushRGB(col, noRows, 0,0,lumins);
	}
	for (int row=0; row<noRows; row++)
	{
		grp_Test.pushRGB(0,row,0,0,lumins);
		grp_Test.pushRGB(noCols, row, 0,0,lumins);
	}

}

void Init_Sky()
{
  for (int row=0; row<6; row++)
  {
    for (int col=0; col<15; col++)
    {
      grp_Sky.pushRGB(row, col, 176, 33, 136);
    }
  }

}

void Init_SkyBlue()
{
  uint8_t r=5;
  uint8_t g=226;
  uint8_t b=255;
  grp_SkyBlue.pushRGB(2,0, r,g,b);
  grp_SkyBlue.pushRGB(2,1, r,g,b);
  grp_SkyBlue.pushRGB(2,3, r,g,b);
  grp_SkyBlue.pushRGB(2,4, r,g,b);

  grp_SkyBlue.pushRGB(3,2, r,g,b);
  grp_SkyBlue.pushRGB(3,3, r,g,b);
  grp_SkyBlue.pushRGB(3,4, r,g,b);
}

void Init_Ocean() {
  grp_Ocean.pushRGB( 0,0,  0,0,0);
  int r= 216  ; //305/360
  int g= 209 ; // 82/100
  int b= 178 ; // 70/100
  for (int row=7; row<15; row++)
  {
    for (int col=0; col<15; col++)
    {
      grp_Ocean.pushRGB(row,col, r, g, b);
    }
  }
}

void Init_Ocean2()
{
  uint8_t r=58;
  uint8_t g=128;
  uint8_t b=214;

  grp_Ocean2.pushRGB(12,6, r, g, b);
  grp_Ocean2.pushRGB(12,7, r, g, b);
  grp_Ocean2.pushRGB(12,8, r, g, b);
  grp_Ocean2.pushRGB(12,9, r, g, b);
  grp_Ocean2.pushRGB(12,10, r, g, b);

  grp_Ocean2.pushRGB(13,7, r, g, b);
  grp_Ocean2.pushRGB(13,8, r, g, b);
  grp_Ocean2.pushRGB(13,9, r, g, b);
  grp_Ocean2.pushRGB(13,10, r, g, b);
  grp_Ocean2.pushRGB(13,11, r, g, b);
  grp_Ocean2.pushRGB(13,12, r, g, b);
  grp_Ocean2.pushRGB(13,13, r, g, b);
  grp_Ocean2.pushRGB(13,14, r, g, b);
  grp_Ocean2.pushRGB(13,15, r, g, b);

  grp_Ocean2.pushRGB(14,9, r, g, b);
  grp_Ocean2.pushRGB(14,10, r, g, b);
  grp_Ocean2.pushRGB(14,11, r, g, b);
  grp_Ocean2.pushRGB(13,12, r, g, b);
  grp_Ocean2.pushRGB(13,13, r, g, b);
  grp_Ocean2.pushRGB(13,14, r, g, b);
  grp_Ocean2.pushRGB(13,15, r, g, b);
}

void Init_Land()
{
  //TODO: Finish me!
	grp_Land.pushRGB(4,12,255,0,255);
}

void Init_Orange()
{
  uint8_t r=252;
  uint8_t g=179;
  uint8_t b=118;
  grp_Orange.pushRGB(8, 14, r, g, b);
  // TODO: Finish me!
}

void Init_Yellow()
{
  uint8_t r=238;
  uint8_t g=252;
  uint8_t b=33;
  for (int col=7;col<=15;col++)
    grp_Yellow.pushRGB(7,col,r,g,b);
}

void initAll()
{
  Init_Test();
  Init_Sky();
  Init_SkyBlue();
  Init_Ocean();
  Init_Ocean2();
  Init_Land();
  Init_Orange();
  Init_Yellow();
  return;
}


void generateFlash(const char * path) {
//	grp_Test.print();

	grp_Test.generate2(path);
	grp_Sky.generate2(path);
	grp_SkyBlue.generate2(path);
	grp_Ocean.generate2(path);
	grp_Ocean2.generate2(path);
	grp_Land.generate2(path);
	grp_Orange.generate2(path);
	grp_Yellow.generate2(path);
	return;
}


