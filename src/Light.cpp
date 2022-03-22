/*
 * Lights.cpp
 *
 *  Created on: Feb 4, 2022
 *      Author: doug
 */

#include "Light.h"
#include <stdio.h>
#include <string>
#include <strings.h>
#include <unistd.h>
//#include <sys/types.h>
//#include <sys/stat.h>
#include <fcntl.h>

/**
 * A new entry using row, column and relative brightness
 * @param r <int> the Row
 * @param c <int> the Column
 * @param rgb <int> the color of this entry
 */
Light::Light(int r, int c, int  _rgb)
{
	row = r;
	col = c;
	rgb = _rgb;
	next = nullptr;
}

Light::Light(int r, int c, int _red, int _green, int _blue)
{
	row = r;
	col = c;
	rgb = ((_red&0xff)<<16) | ((_green&0xff)<<8) | (_blue&0xff);
	next = nullptr;
}


Light::~Light()
{
	// TODO Auto-generated destructor stub
}

uint8_t Light::red()
{
	return ((rgb>>16)&0xff);
}

uint8_t Light::green()
{
	return ((rgb>>8)&0xff);
}

uint8_t Light::blue()
{
	return(rgb&0xff);
}

LightGroup::LightGroup(std::string lname, int _rowCount, int _colCount)
{
	first = nullptr;
	last = nullptr;
	len=0;
	listName = lname;
	noOfRows = _rowCount;
	noOfCols = _colCount;
	noOfLeds=0L;
}


/**
 * Unlink and delete the entries
 */
LightGroup::~LightGroup() {
	Light *tmp;
	while (first != nullptr) {
		tmp=first->next;
		len--;
		delete (first);
		first=tmp;
	}
	last=nullptr;
}


/**
 * Define a new 'light' entry, and adds it to the list
 */
void LightGroup::pushRGB(int row, uint8_t col, uint8_t r, uint8_t g, uint8_t b)
{
	Light *alight = new Light(row, col, r, g, b);
	if (first == nullptr) {
		first=alight;
		last=alight;
		return;
	}

	last->next = alight;
	last = alight;
	len++;
	noOfLeds++;
}


/**
 * Output this array to flash.
 *
 * @param path - The path of the directory to write into.
 *
 *      The name of the resulting file is {PATH}/{groupname}.led
 *      each line is terminated with '\n'.
 *
 * FORMAT of FILE:
 *     line 1:  "LEDS"
 *     Line 2: Name of this group
 *     Line 3:  cnt                  The number of entries.
 *     Line 4...<cnt>+3 contains one entry each:
 *     	row,col,red,green,blue
 *     	       each is space separated. Multiple spaces in a row are treaded as single space.
 */
void LightGroup::generate2(const char *path)
{
	char fname[128];
	sprintf(fname, "%s/%s.led", path, listName.c_str());

	// open file
	FILE *fout=fopen(fname, "w");

	// HEADER - LEDS + FileName
	fprintf(fout, "LEDS\n");                          // Header
	fprintf(fout, "%s\n", listName.c_str());
	fprintf(fout, "%ld\n", getNoOfLeds()+1);

	// EACH ENTRY
	Light *entry;

	for (entry=this->first; entry!=nullptr; entry=entry->next)
	{
		unsigned char fill[3];
		bzero(fill,3);
		fprintf(fout, "%d %d %d %d %d\n", entry->row, entry->col,
				entry->red(), entry->green(), entry->blue());
	}
	printf("File %s written with  %ld entries \n", fname,getNoOfLeds()+1);
	fclose(fout);
	return;
}

/**
 * Generate the arduino array definition
 *   to put this array in flash.
 *   const int PROGMEMname[] =
 *       {
 *       r,c,b;
 *       }
 *
 * @param fname - the file name to output to.
 *     (note: We APPEND to this file - if desired,
 *      it should be removed by an external routine (e.g.: main)
 */
void LightGroup::print() {
	printf( "Print light group %s. %ld entries:\n", this->listName.c_str(), this->noOfLeds+1);
	Light *cur;

	for (cur=first; cur!=nullptr; cur=cur->next)
	{
		printf( "Row,Col,RGB:  %d,%d,%d,%d,%d",
				cur->row, cur->col,
				cur->red(), cur->green(), cur->blue());

		if (cur->next !=nullptr)
			printf(",\n");
		else
			printf("\n");

	}
	printf("// End %s\n\n", this->listName.c_str());
	return;
}
