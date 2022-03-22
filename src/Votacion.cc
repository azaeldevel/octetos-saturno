
#include <string.h>
#include <fstream>

#include "Main.hh"




	Votacion::Votacion() : key(NULL)
	{
	}
	Votacion::Votacion(const Votacion& v)
	{
		length = v.length;
		voto = v.voto;
		key = new char[v.length + 1];
		strcpy(key,v.key);
	}
	/*Votacion::~Votacion()
	{
		//if(keys) delete keys;
	}*/
	
	
	bool Votacion::operator < (const Votacion& d) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		unsigned int min_length = std::min(length,d.length);
		for(unsigned int c = 0; c < min_length; c++)
		{
			//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
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
		unsigned int min_length = std::min(length,d.length);
		for(unsigned int c = 0; c < min_length; c++)
		{
			//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
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
		if(length != d.length) return false;
		
		unsigned int min_length = std::min(length,d.length);
		for(unsigned int c = 0; c < min_length; c++)
		{
			//std::cout << "\t\t" << index[c]  << " < " << d.index[c] << "\n";
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
		unsigned int index = 0;
		while(true)
		{			
			if(value[index] == (char)0) return false;
			if(key[index] == (char)0) return false;
			if(index == length - 1) return false;
			
			if(key[index] < value[index]) 
			{
				return true;
			}
			else if(key[index] > value[index]) 
			{
				return false;
			}
			
			index++;
		}
		
		return false;
	}
	
	bool Votacion::operator > (const char* value) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		unsigned int index = 0;
		while(true)
		{
			if(value[index] == (char)0) return false;
			if(key[index] == (char)0) return false;
			if(index == length - 1) return false;
			
			if(key[index] > value[index]) 
			{
				return true;
			}
			else if(key[index] < value[index]) 
			{
				return false;
			}
			
			index++;
		}
		
		return false;
	}
	
	bool Votacion::operator == (const char* value) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		unsigned int index = 0;
		while(true)
		{
			if(key[index] == (char)0 and value[index] == (char)0) return true;
			if(key[index] == (char)0) return false;
			if(index == length) return false;
			
			if(key[index] != value[index]) 
			{
				return false;
			}
			
			index++;			
		}
		
		return true;
	}