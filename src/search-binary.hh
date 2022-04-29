
#ifndef OCTETOS_SATURNO_SEARCH_BINARY_HH
#define OCTETOS_SATURNO_SEARCH_BINARY_HH

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

#include "Search.hh"


namespace oct::sat
{

template <Data S,typename V,Index I = unsigned int> class Binary : public Search<S,V,I>
{
public:
	Binary(Array<S,I>& in) : input(in)
	{
	}

	virtual S* search(V value)
	{
		//std::cout << "value = " << value << "\n";
		return search(value,0,input.size()-1);
	}

	S* search(V value, I begin, I end)
	{
		//std::cout << "Buscando en [" << begin << "," << end << "]\n";
		I middle = (begin + end)/ 2;
		//std::cout << "middle = " << middle << "\n";

		if(input[middle] < value)
		{
			//std::cout << "\t --> " << value << "\n";
			return search(value,middle,end);
		}
		else if(input[middle] > value)
		{
			//std::cout << "\t --> " << value << "\n";
			return search(value,begin,middle);
		}
		else if(input[middle] == value)
		{
			//std::cout << "\t --> " << value << "\n";
			return &input[middle];
		}

		return NULL;
	}
private:
	Array<S,I>& input;
};

}

#endif