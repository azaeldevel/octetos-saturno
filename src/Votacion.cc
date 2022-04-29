
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
 
#include <string.h>
#include <fstream>

#include "Main.hh"
#include "Exception.hh"




	Votacion::Votacion()
	{
	}
	Votacion::Votacion(const Votacion& v)
	{
		//length = v.length;
		voto = v.voto;
		strcpy(key,v.key);
	}
	Votacion::~Votacion()
	{
	}
	
	bool Votacion::copy(const char* str)
	{
		auto leng = strlen(str);
		if(leng >= sizeof(key) - 1) throw oct::sat::Exception(oct::sat::Exception::OUT_OF_RANGE,__FILE__,__LINE__);

		strcpy(key,str);

		return true;
	}
	
	
	bool Votacion::operator < (const Votacion& d) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		//unsigned int min_length = std::min(LENGTH,d.length);
		for(unsigned int c = 0; c < LENGTH; c++)
		{
			//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
			//if(key[c] == '\0') return false; 
			if(key[c] < d.key[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return true;
			}
			else if(key[c] > d.key[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return false;
			}
		}
		
		return false;
	}
	
	bool Votacion::operator > (const Votacion& d) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		//unsigned int min_length = std::min(length,d.length);
		for(unsigned int c = 0; c < LENGTH; c++)
		{
			//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
			//if(key[c] == '\0') return false; 
			if(key[c] > d.key[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return true;
			}
			else if(key[c] < d.key[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return false;
			}
		}
		
		return false;
	}
		
	bool Votacion::operator == (const Votacion& d) const
	{
		//if(length != d.length) return false;
		
		//unsigned int min_length = std::min(length,d.length);
		for(unsigned int c = 0; c < LENGTH; c++)
		{
			//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
			//if(key[c] == '\0') return false; 
			if(key[c] != d.key[c]) 
			{
				//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
				return false;
			}
		}
		
		return true;
	}
	
	
	
	
	
	bool Votacion::operator < (const char* value) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		//unsigned int index = 0;
		for(unsigned int c = 0; c < LENGTH; c++)
		{			
			//if(value[c] == '\0') return false; 
			//if(key[c] == '\0') return false; 
			//if(index == length - 1) return false;
			
			if(key[c] < value[c]) 
			{
				return true;
			}
			else if(key[c] > value[c]) 
			{
				return false;
			}
			
			//index++;
		}
		
		return false;
	}
	
	bool Votacion::operator > (const char* value) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		//unsigned int index = 0;
		for(unsigned int c = 0; c < LENGTH; c++)
		{
			//if(value[c] == '\0') return false; 
			//if(key[c] == '\0') return false; 
			//if(index == length - 1) return false;
			
			if(key[c] > value[c]) 
			{
				return true;
			}
			else if(key[c] < value[c]) 
			{
				return false;
			}
			
			//index++;
		}
		
		return false;
	}
	
	bool Votacion::operator == (const char* value) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		//unsigned int index = 0;
		for(unsigned int c = 0; c < LENGTH; c++)
		{
			//if(key[c] == '\0') return false;
			//if(value[c] == '\0') return false;		
			if(key[c] != value[c]) return false;			
			//index++;			
		}
		
		return true;
	}