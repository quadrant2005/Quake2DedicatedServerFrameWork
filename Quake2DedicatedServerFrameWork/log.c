/*------------------------------------------------------------------------
Client.h:
		Based on the Poly Engine by Alexey Goloshubin
		Quad Engine - version 1.0.0.8

	Copyright (C) 2001 Quadrant BBS Systems Uk

	This program is free software; you can redistribute it and/or
	modify it under the terms of the GNU General Public License
	as published by the Free Software Foundation; either version 2
	of the License, or (at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program; if not, write to the Free Software
	Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

	Examine the license.txt file located in the main source code directory
	to see the full text of the GPL license document.

	Direct inquiries to:	Subject: The QuadEngine Project
							Quadrant@PlanetQuake.com
							

	Or on the Internet at:	http://www.PlanetQuake.com/QuadKill/QuadEngine
							Quadrant@PlanetQuake.com
------------------------------------------------------------------------*/


// blinky
#include "log.h"
//[QBS]
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <process.h>
//[QBS]end
#include <stdarg.h>
#include <time.h>

const char * f_szLogFile = "logging/Engine.log";//[QBS]



void Log_Printf(const char * format,...)
{
	time_t now;
	char timestring[64];
	va_list marker;
	FILE * fp = 0;
	va_start(marker, format);
	fp = fopen(f_szLogFile , "a+");
	if (!fp)
		return;
	time(&now);
	strcpy(timestring, ctime(&now));
	strcpy(&timestring[strlen(timestring)-1], ")) ");
	fprintf(fp, timestring);
	vfprintf(fp, format, marker);
	fclose(fp);
}

void Log_PrintfNoDate(const char * format,...)
{
	va_list marker;
	FILE * fp = 0;
	va_start(marker, format);
	fp = fopen(f_szLogFile , "a+");
	if (!fp)
		return;
	vfprintf(fp, format, marker);
	fclose(fp);
}

//=============================================================
