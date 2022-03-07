
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <chrono>
using namespace std::chrono;


#include "Main.hh"
#include "saturno.hh"


struct Votacion
{
	char* keys;
	unsigned int length;
	bool voto;

	bool operator < (const Votacion& d) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		unsigned int min_length = std::min(length,d.length);
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
	
	bool operator > (const Votacion& d) const
	{
		//std::cout << "\t" << index << " < " << d.index << "\n";
		unsigned int min_length = std::min(length,d.length);
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

Main::Main() : lengthArray(1000000)
{

}
int Main::main(const int argc, const char* argv[])
{
	if(strcmp("gen-db",argv[0]) == 0)
	{
		if(argc < 4) 
		{
			std::cout << "gen-db length_db length_string file\n";
			return EXIT_FAILURE;
		}
		return gen_db(std::stoul(argv[1]),argv[2]);
	}
	else if(strcmp("sort-db",argv[0]) == 0)
	{
		if(argc < 2) 
		{
			std::cout << "sort-db in out\n";
			return EXIT_FAILURE;
		}
		return sort_db(argv[1],argv[2]);		
	}
	else if(strcmp("full",argv[0]) == 0)
	{
		return full();
	}
	else
	{
		if(argc > 0) std::cout << "comando desconocido\n";
		else std::cout << "Indique la operacion que desea realizar\n";
	}

	return EXIT_SUCCESS;
}

int Main::gen_db(Index lengthArray,const char* filename)
{
	unsigned int lengthString = 32;
	char** array = new char*[lengthArray];
	for(Index i = 0; i < lengthArray; i++)
	{
		array[i] = new char[lengthString + 1];
		array[i][lengthString] = (char)0;//null terminations string
	}
	
	std::cout << "Generando base de datos...\n";
	oct::sat::RandomHash hashs;	
	for(Index i = 0; i < lengthArray; i++)
	{
	
		hashs.generate(array[i],lengthString);
		//std::cout << array[i] << "\n";
	}
	
	std::default_random_engine generator;
	std::bernoulli_distribution distribution(0.75);
	oct::sat::Array<Votacion,Index> arrayData(lengthArray);
	for(Index i = 0; i < lengthArray; i++)
	{
		arrayData[i].keys = array[i];
		arrayData[i].length = lengthString;
		arrayData[i].voto = distribution(generator);
		//std::cout << arrayData[i].index << "\n";
	}
	
	std::ofstream db;	
	std::cout << "Guardando base de datos...\n";
	db.open(filename,std::ios::app);
	for(Index i = 0; i < lengthArray; i++)
	{
		db << arrayData[i].keys << "," << arrayData[i].voto << "\n";
	}
	db.flush();
	db.close();
	
	for(Index i = 0; i < lengthArray; i++)
	{
		delete[] array[i];
	}
	delete array;
	
	return EXIT_SUCCESS;
}

int Main::sort_db(const char* in,const char* out)
{	
	std::cout << "in : " << in << "\n";	
	std::cout << "out : " << out << "\n";
	
	std::ifstream infile(in);
	bool voto;
	std::string line,field;
	Index index = 0;
	oct::sat::Array<Votacion,Index> arrayData(lengthArray);
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
				
		std::getline(iss, field, ',');
		arrayData[index].keys = new char[field.size()+1];
		arrayData[index].keys[field.size()] = (char)0;
		strcpy(arrayData[index].keys, field.c_str());
		arrayData[index].length = field.size();
		
		std::getline(iss, field, ',');
		voto = (bool)std::stoi(field);
		//std::cout << person << "," << voto << "\n";
		index++;
	}
	if(index != lengthArray)
	{
		std::cout << "Para propositos de medicion la base de datos deve contener exactamente 1 000 000 de registro.\n";
		return EXIT_FAILURE;
	}
	
	oct::sat::Merge<Votacion,unsigned int> merge(arrayData);
	std::cout << "Ordenando ascendente...\n";
	auto begin = high_resolution_clock::now();
	merge.asc();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - begin);//microseconds	 
	std::cout << "Duracion : " << duration.count() << "ms\n";
	
	std::ofstream outfile;	
	std::cout << "Guardando base de datos...\n";
	outfile.open(out,std::ios::app);
	for(Index i = 0; i < lengthArray; i++)
	{
		outfile << arrayData[i].keys << "\n";
	}
	outfile.flush();
	outfile.close();
	infile.close();	
	for(Index i = 0; i < lengthArray; i++)
	{
		delete[] arrayData[i].keys;
	}
	std::cout << "Completado..\n";
	return EXIT_SUCCESS;
}
int Main::full()
{
	std::cout << "Iniciando...\n";
	unsigned int lengthString = 32;	
	char** array = new char*[lengthArray];
	for(unsigned int i = 0; i < lengthArray; i++)
	{
		array[i] = new char[lengthString + 1];
		array[i][lengthString] = (char)0;//null terminations string
	}
	
	std::cout << "Generando base de datos...\n";
	oct::sat::RandomHash hashs;	
	for(unsigned int i = 0; i < lengthArray; i++)
	{
		hashs.generate(array[i],lengthString);
		//std::cout << array[i] << "\n";
	}
	
	oct::sat::Array<Votacion,unsigned int> arrayData(lengthArray);
	for(unsigned int i = 0; i < lengthArray; i++)
	{
		arrayData[i].keys = array[i];
		arrayData[i].length = lengthString;
		//std::cout << arrayData[i].index << "\n";
	}
	//oct::sat::Array<DataOption> arrayDataSorted(lengthArray,false);
	
	std::cout << "Ordenando ascendente...\n";
	oct::sat::Merge<Votacion,unsigned int> merge(arrayData);
	auto begin = high_resolution_clock::now();
	merge.asc();
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - begin);//microseconds	 
	std::cout << "Duracion : " << duration.count() << "ms\n";
	
	std::ofstream db;	
	std::cout << "Guardando base de datos...\n";
	db.open("db.csv",std::ios::app);
	for(unsigned int i = 0; i < lengthArray; i++)
	{
		db << arrayData[i].keys << "\n";
	}
	db.flush();
	db.close();
	
	for(unsigned int i = 0; i < lengthArray; i++)
	{
		delete[] array[i];
	}
	delete array;
	
	return EXIT_SUCCESS;
}