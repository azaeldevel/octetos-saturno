
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
	EngineVotacion<Votacion,const char*,Index> engine(lengthArray);

	//std::ifstream infile(db);
	std::cout << "Cargando base de datos..\n";
	auto begin = high_resolution_clock::now();
	bool ret_search = engine.load(db);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - begin);//microseconds	
	if(not ret_search)
	{
		std::cout << "Fallo la apertura de la base de datos.\n";
		return NULL;
	} 
	std::cout << "Lectura de BD : " << float(duration.count())/float(1000)  << "ms\n";
	disk_ope += duration.count();
	if(engine.get_actual() != lengthArray)
	{
		std::cout << "Para propositos de medicion la base de datos deve contener exactamente 1 000 000 (" << engine.get_actual() << ")  de registro.\n";
		return NULL;
	}
	
	begin = high_resolution_clock::now();
	Votacion* voto = engine.search(value);
	end = high_resolution_clock::now();
	std::cout << "Busqueda: " << float(duration.count())/float(1000) << "ms\n";
	
	if(voto) return new Votacion(*voto);	
	return NULL;
}