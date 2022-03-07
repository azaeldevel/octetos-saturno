
/*
 * main.cc
 * Copyright (C) 2022 Azael R. <azael.devel@gmail.com>
 * 
 * octetos-saturno is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * octetos-saturno is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include <iostream>
#include "Main.hh"

int main(const int argc, const char* argv[])
{
	Main app;
	if(argc <= 1) 
	{
		std::cout << "Indique la operacion que desea realizar\n";
		return EXIT_FAILURE;
	}

	int ret = app.main(argc - 1, argv + 1);
	
	return ret;
}

