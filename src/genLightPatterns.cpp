//============================================================================
// Name        : genLightPatterns.cpp
// Author      : Doug
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <stdio.h>
#include <string>
#include <string.h>

using namespace std;
#include "Light.h"
#include "Picture.h"


int main(int argc, char *argv[]) {
	initAll();
	if (argc<2) {
		fprintf(stderr, "ERROR: Missing target file prefix!\n");
		return(-1);
	}
	fprintf(stderr, "PATH is %s\n", argv[1]);
	generateFlash(argv[1]);
	return 0;
}
