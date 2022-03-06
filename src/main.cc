
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

#include "saturno.hh"


#include <chrono>
using namespace std::chrono;


template <typename I = unsigned int> struct DataOption : public oct::sat::Data<I>
{
	bool option;
};
int main()
{
	unsigned int lengthArray = 1000;
	unsigned int lengthString = 32;	
	char** array = new char*[lengthArray];
	for(unsigned int i = 0; i < lengthArray; i++)
	{
		array[i] = new char[lengthString + 1];
		array[i][lengthString] = (char)0;//null terminations string
	}
	
	
	oct::sat::RandomHash hashs;	
	for(unsigned int i = 0; i < lengthArray; i++)
	{
		hashs.generate(array[i],lengthString);
		//std::cout << array[i] << "\n";
	}
	
	oct::sat::Array<DataOption<unsigned int>> arrayData(lengthArray);
	for(unsigned int i = 0; i < lengthArray; i++)
	{
		arrayData[i].index = array[i];
		arrayData[i].length = lengthString;
		//std::cout << arrayData[i].index << "\n";
	}
	//oct::sat::Array<DataOption> arrayDataSorted(lengthArray,false);
	
	auto begin = high_resolution_clock::now();
	oct::sat::Merge<DataOption<unsigned int>> merge(arrayData);
	merge.sort();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(end - begin);//	 milliseconds
	std::cout << "Duracion : " << duration.count() << "\n";
	/*for(unsigned int i = 0; i < lengthArray; i++)
	{
		std::cout << arrayData[i].index << "\n";
	}*/
	
	for(unsigned int i = 0; i < lengthArray; i++)
	{
		delete[] array[i];
	}
	delete array;
	return 0;
}

