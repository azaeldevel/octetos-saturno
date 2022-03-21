
#include <chrono>
#include <fstream>

#include "Saturno.hh"

using namespace std::chrono;

int main()
{
	unsigned int lengthArray = 1000;
	unsigned int lengthString = 32;
	std::ofstream csv;
	csv.open("virtual.csv",std::ios_base::app);
	
	{
		
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
		}
		
		for(unsigned int i = 0; i < lengthArray; i++)
		{
			delete[] array[i];
		}
		delete array;
	}
	
	{
		char** array = new char*[lengthArray];
		for(unsigned int i = 0; i < lengthArray; i++)
		{
			array[i] = new char[lengthString + 1];
			array[i][lengthString] = (char)0;//null terminations string
		}
		
		oct::sat::RandomHash hashs;
		auto start = high_resolution_clock::now();
		for(unsigned int i = 0; i < lengthArray; i++)
		{
			hashs.generate(array[i],lengthString);
		}
		auto end = high_resolution_clock::now();
		auto time = end - start;
		//std::cout << "Duracion directa : " << time.count() << "\n";
		csv << time.count() << ",";
		
		for(unsigned int i = 0; i < lengthArray; i++)
		{
			delete[] array[i];
		}
		delete array;
	}
	
	
	{
		char** array = new char*[lengthArray];
		for(unsigned int i = 0; i < lengthArray; i++)
		{
			array[i] = new char[lengthString + 1];
			array[i][lengthString] = (char)0;//null terminations string
		}
		
		oct::sat::RandomHash hashs;
		oct::sat::RandomString& virtuaHashs = hashs;
		auto start = high_resolution_clock::now();
		for(unsigned int i = 0; i < lengthArray; i++)
		{
			virtuaHashs.generate(array[i],lengthString);
			//std::cout << array[i] << "\n";
		}
		auto end = high_resolution_clock::now();
		auto time = end - start;
		//std::cout << "Duracion virtual : " << time.count() << "\n";
		csv << time.count() << ",";
		
		for(unsigned int i = 0; i < lengthArray; i++)
		{
			delete[] array[i];
		}
		delete array;
	}
	
	
	{
		char** array = new char*[lengthArray];
		for(unsigned int i = 0; i < lengthArray; i++)
		{
			array[i] = new char[lengthString + 1];
			array[i][lengthString] = (char)0;//null terminations string
		}
			
		oct::sat::RandomHash hashs;
		oct::sat::RandomString* virtuaHashs = &hashs;
		typedef void (oct::sat::RandomString::*generator)(char*,unsigned int);
		generator gen = (generator)&oct::sat::RandomHash::generate;		
		auto start = high_resolution_clock::now();
		for(unsigned int i = 0; i < lengthArray; i++)
		{
			(virtuaHashs->*gen)(array[i],lengthString);
		}
		auto end = high_resolution_clock::now();
		auto time = end - start;
		//std::cout << "Duracion vpuntero resulto : " << time.count() << "\n";
		csv << time.count() << "\n";
		
		for(unsigned int i = 0; i < lengthArray; i++)
		{
			delete[] array[i];
		}
		delete array;
	}
	
	csv.flush();
	csv.close();
	
	return EXIT_SUCCESS;
}