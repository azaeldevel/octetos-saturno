
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


struct DataOption
{
	const char* keys;
	unsigned int length;

	bool operator < (const DataOption& d) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		unsigned int min_length = std::min(strlen(keys),strlen(d.keys));
		for(unsigned int c = 0; c < min_length; c++)
		{
			//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
			if(keys[c] < d.keys[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return true;
			}
			else if(keys[c] > d.keys[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return false;
			}
		}
		
		return false;
	}
	
	bool operator > (const DataOption& d) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		unsigned int min_length = std::min(strlen(keys),strlen(d.keys));
		for(unsigned int c = 0; c < min_length; c++)
		{
			//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
			if(keys[c] > d.keys[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return true;
			}
			else if(keys[c] < d.keys[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return false;
			}
		}
		
		return false;
	}
};
int main()
{
	unsigned int lengthArray = 1000000;
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
	
	oct::sat::Array<DataOption,unsigned int> arrayData(lengthArray);
	for(unsigned int i = 0; i < lengthArray; i++)
	{
		arrayData[i].keys = array[i];
		arrayData[i].length = lengthString;
		//std::cout << arrayData[i].index << "\n";
	}
	//oct::sat::Array<DataOption> arrayDataSorted(lengthArray,false);
	
	oct::sat::Merge<DataOption,unsigned int> merge(arrayData);
	auto begin = high_resolution_clock::now();
	merge.asc();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - begin);//microseconds	 
	std::cout << "Duracion : " << duration.count() << "ms\n";
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

