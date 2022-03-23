
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
 

#include "Saturno.hh"

namespace oct::sat
{

RandomHash::RandomHash()
{
	alpha = new std::uniform_int_distribution<int>(97,122);
	number = new std::uniform_int_distribution<int>(48,57);
	selection = new std::bernoulli_distribution(0.6);
}

RandomHash::~RandomHash()
{
	delete alpha;
	delete number;
	delete selection;
}

void RandomHash::generate(char* string,unsigned int length)
{
	for(unsigned int i = 0; i < length; i++)
	{
		if(selection->operator()(generator))
		{
			string[i] = (char)(alpha->operator()(generator));
		}
		else
		{
			string[i] = (char)(number->operator()(generator));
		}
	}
}




}