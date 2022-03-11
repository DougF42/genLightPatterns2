/*
 * skyblue.cpp
 *
 *  Created on: Feb 4, 2022
 *      Author: doug
 */
#include <stdio.h>
#include <string.h>
#include <vector>
#include "Light.h"

#ifndef P_I_C_T_U_R_E__H
#define P_I_C_T_U_R_E__H

#define noRows 16
#define noCols 15

extern LightGroup grp_test;
extern LightGroup grp_Ocean ;
extern LightGroup grp_Ocean2;
extern LightGroup grp_Sky   ;
extern LightGroup grp_SkyBlue;
extern LightGroup grp_Land   ;
extern LightGroup grp_Orange ;
extern LightGroup grp_Yellow ;

void initAll();
void generateFlash(const char *path);

#endif
