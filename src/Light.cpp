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

Light::~Light()
{
	// TODO Auto-generated destructor stub
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
	// Convert rgb to color
	uint32_t color = (r<<16) | (g<<8) | (b);

	Light *alight = new Light(row, col, color);
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
 *      The name of the resuling file has the grp_ prefix
 *      removed.
 * FORMAT of FILE:
 *     4 bytes   "LEDS" Identifies this as type of file
 *     1 byte    len    Length of name string
 *     len bytes  char  The name of this group.
 *     2 byte    cnt    The number of entries.
 *     8 * cnt bytes  'cnt' Entries follow.
 *     ENTRY (8 bytes per entry):
 *       1 row
 *       1 col
 *       1 red
 *       1 green
 *       1 blue
 *       3 reserved (Must be zero).
 */
void LightGroup::generate2(const char *path)
{
	// First, determine the 8.3 version (shortened) groupName
	size_t pos=this->listName.find_last_of('_');
	if (pos == std::string::npos) {
		pos=0;
	}
	std::string groupName=listName.substr(pos);
	groupName.append(".led");

	// Now create the file name

	std::string fname= path;
	fname.append("/");
	fname.append(groupName);

	// open file
	int fout=creat(fname.c_str(),S_IRWXU|S_IRWXG|S_IRWXO);
	// HEADER
	write(fout, "LEDS",4);                          // Header
	char l = groupName.size();                      // length of group name
	write(fout, &l,1);
	write(fout, groupName.c_str(), groupName.size()); // file name

	uint16_t cnt=(uint16_t)this->getNoOfLeds();
	if (sizeof(cnt) != 2 ) {
		fprintf(stderr,"ERROR in LightGroup::generate2 - count is %ld bytes - should be 2 bytes!!!\n", sizeof(cnt));
	}
	write(fout, &cnt, 2);                             // Number of entries. (2 bytes)

	// Per entry...

	Light *entry;
	uint8_t row,col,red,green,blue;

	for (entry=this->first; entry!=nullptr; entry=entry->next)
	{
		unsigned char fill[3];
		bzero(fill,3);
		row=entry->row;
		col=entry->col;
		red   = (entry->rgb>>16) & 0xff;
		green = (entry->rgb>>8)  & 0xff;
		blue  = entry->rgb       & 0xff;
		write(fout,&row,1);                               // row
		write(fout,&col,1);                               // col
		write(fout,&red,1);                               // red
		write(fout,&green,1);                             // green
		write(fout,&blue,1);                              // blue
		write(fout,fill, sizeof(fill));                   // Fill (3 bytes) - all zeros.
	}
	printf("In group %15s there are %3d entries \n", groupName.c_str(),cnt);
	close(fout);
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
void LightGroup::generate(FILE *outfile) {
	fprintf(outfile, "// Begin  %s:\n", this->listName.c_str());
	fprintf(outfile, "#include <Arduino.h>\n");
	fprintf(outfile, "const PROGMEM int %s[] = \n", this->listName.c_str());
	fprintf(outfile, "{\n");
	Light *cur;

	for (cur=first; cur!=nullptr; cur=cur->next)
	{
		/***
		if (cur->next !=nullptr)
			fprintf(outfile, "  {%d,%d,%6X},\n", cur->row, cur->col, cur->rgb);
		else
			fprintf(outfile, "  {%d,%d,%6X}\n", cur->row, cur->col, cur->rgb);
		**/
		if (cur->next !=nullptr)
			fprintf(outfile, "  %d,%d,%d,\n", cur->row, cur->col, cur->rgb);
		else
			fprintf(outfile, "  %d,%d,%d\n", cur->row, cur->col, cur->rgb);
	}
	fprintf(outfile, "}; \n");
	fprintf(outfile,"// End %s\n\n", this->listName.c_str());
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
	printf( "// Begin  %s:\n", this->listName.c_str());
	printf( "#include <Arduino.h>\n");
	printf( "const PROGMEM int %s[] = \n", this->listName.c_str());
	printf( "{\n");
	Light *cur;

	for (cur=first; cur!=nullptr; cur=cur->next)
	{
		if (cur->next !=nullptr)
			printf( "Row,Col,RGB:  %d,%d,%d,\n", cur->row, cur->col, cur->rgb);
		else
			printf( "Row,Col,RGB:  %d,%d,%d\n", cur->row, cur->col, cur->rgb);

	}
	printf( "}; \n");
	printf("// End %s\n\n", this->listName.c_str());
	return;
}
