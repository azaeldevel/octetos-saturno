
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <chrono>
using namespace std::chrono;

#include "Main.hh"
#include "search-binary.hh"



Votacion* Main::search(const std::filesystem::path& db,const char* value)
{
	if(not std::filesystem::exists(db))
	{
		std::cout << "No existe la base de datos : " << db << "\n";
		return NULL;
	}
	unsigned int disk_ope = 0;
	unsigned int sort = 0;

	std::ifstream infile(db);
	std::string line,field;
	Index index = 0;
	oct::sat::Array<Votacion,Index> arrayData(lengthArray);
	std::cout << "Cargando base de datos..\n";
	auto begin = high_resolution_clock::now();
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
				
		std::getline(iss, field, ',');
		arrayData[index].keys = new char[field.size()+1];
		arrayData[index].keys[field.size()] = (char)0;
		strcpy(arrayData[index].keys, field.c_str());
		arrayData[index].length = field.size();
		
		std::getline(iss, field, ',');
		arrayData[index].voto = (bool)std::stoi(field);
		//std::cout << person << "," << voto << "\n";
		index++;
	}
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - begin);//microseconds	 
	//std::cout << "Lectura de BD: " << duration.count() << "ms\n";
	disk_ope += duration.count();
	if(index != lengthArray)
	{
		std::cout << "Para propositos de medicion la base de datos deve contener exactamente 1 000 000 de registro.\n";
		return NULL;
	}
	
	oct::sat::Binary<Votacion,const char*> binary(arrayData);
	Votacion* voto = binary.search(value);
	
	if(voto) return new Votacion(*voto);	
	return NULL;
}