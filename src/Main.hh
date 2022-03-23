
#ifndef OCTETOS_SATURNO_MAIN_HH
#define OCTETOS_SATURNO_MAIN_HH

/*
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


#include "Votacion.hh"

class Main
{

public:
	Main();
	Main(Index length);

	int main(const int argc, const char* argv[]);

private:
	int emule_db(Index,const std::filesystem::path&,const std::filesystem::path&);
	int gen_db(Index,unsigned int,const std::filesystem::path&);
	int gen_db_default();
	int sort_db(const std::filesystem::path&,const std::filesystem::path&,bool unique);
	int full();
	Votacion* search(const std::filesystem::path&,const char*);
	Index lengthArray;
};

#endif