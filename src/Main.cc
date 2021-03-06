
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
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <chrono>
using namespace std::chrono;


#include "Main.hh"
#include "Saturno.hh"



Main::Main() : lengthArray(1000000)
{
}
Main::Main(Index l) : lengthArray(l)
{
}
int Main::main(const int argc, const char* argv[])
{
	if(strcmp("emule-db",argv[0]) == 0)
	{
		if(argc < 4)
		{
			std::cout << "emule-db length_db db_name names_directory\n";
			return EXIT_FAILURE;
		}

		return emule_db(std::stoul(argv[1]),argv[2],argv[3]);
	}
	else if(strcmp("gen-db",argv[0]) == 0)
	{
		if(argc < 4)
		{
			std::cout << "gen-db length_db length_string file\n";
			return EXIT_FAILURE;
		}
		//std::cout << "file : " << argv[3] << "\n";
		return gen_db(std::stoul(argv[1]),std::stoul(argv[2]),argv[3]);
	}
	else if(strcmp("gen-db-default",argv[0]) == 0)
	{
		return gen_db(lengthArray,32,"db.csv");
	}
	else if(strcmp("sort-db",argv[0]) == 0)
	{
		if(argc < 3)
		{
			std::cout << "sort-db in out\n";
			return EXIT_FAILURE;
		}
		if(argc == 3)
		{
			return sort_db(argv[1],argv[2],false);
		}
		else if(argc == 4)
		{
			bool unique = false;
			unsigned int measure = 0;

			for(int i = 1; i < argc; i++)
			{
				if(strcmp("--unique",argv[i]) == 0) 
				{
					unique = true;
				}
				else if(strcmp("--measure",argv[i]) == 0) 
				{
					measure = std::atoi(argv[++i]);
				}
			}
			
			if(measure > 0) return sort_db(argv[2],argv[3],unique,measure);
			return sort_db(argv[2],argv[3],unique);
		}
		std::cout << "Paramatros incompletos.\n";
		return EXIT_FAILURE;
	}
	else if(strcmp("search",argv[0]) == 0)
	{
		if(argc < 2)
		{
			std::cout << "search db text\n";
			return EXIT_FAILURE;
		}
		std::shared_ptr<Votacion> voto = search(argv[1],argv[2]);
		if(voto)
		{
			std::cout << argv[2] << (voto->voto ? " Si " : " No ") << "voto\n";
			//delete voto;
			return EXIT_SUCCESS;
		}
		else
		{
			std::cout << argv[2] << " no se encontro.\n";
			return EXIT_FAILURE;
		}
	}
	else if(strcmp("print",argv[0]) == 0)
	{
		if(argc < 3)
		{
			std::cout << "print db i-esino\n";
			return EXIT_FAILURE;
		}

		return print(argv[1],std::atoi(argv[2]));
	}
	else
	{
		if(argc > 0) std::cout << "comando desconocido\n";
		else std::cout << "Indique la operacion que desea realizar\n";
	}

	return EXIT_SUCCESS;
}

int Main::emule_db(Index lengthArray,const std::filesystem::path& filename,const std::filesystem::path& name)
{
	//std::cout << "Step 1...\n";
	std::cout << "Generando base de datos...\n";
	Index full = lengthArray;
	if(std::filesystem::exists(filename)) std::filesystem::remove(filename);
	//std::cout << "Step 2...\n";
	DB<Votacion,Index> gendb(name);
	//std::cout << "Step 3...\n";
	Index ret_count;
	//std::cout << "Step 4...\n";
	try
	{
		ret_count = gendb.generate(full) ;
	}
	catch(const std::exception& ex)
	{
		//std::cout << "Exception : require " << lengthArray << " "  << ex.what() << "\n";
		return EXIT_FAILURE;
	}
	if(ret_count != full)
	{
		//std::cout << "Fallo la generacion de la base de datos\n";
		return EXIT_FAILURE;
	}
	
	std::default_random_engine generator;
	std::bernoulli_distribution distribution(0.75);
	oct::sat::Array<Votacion,Index> arrayData(lengthArray);
	for(Index i = 0; i < lengthArray; i++)
	{
		//arrayData[i].length = strlen(gendb.get_strings()[i]);
		arrayData[i].copy(gendb.get_strings()[i]);
		//strcpy(arrayData[i].keys,gendb.get_strings()[i]);
		arrayData[i].voto = distribution(generator);
		//std::cout << arrayData[i].index << "\n";
	}
	
	if(std::filesystem::exists(filename)) std::filesystem::remove(filename);
	//std::ofstream db;
	std::cout << "Guardando base de datos...\n";
	/*
	db.open(filename,std::ios::app);
	const Votacion* votacion_array = (const Votacion*)arrayData;
	for(Index i = 0; i < lengthArray; i++)
	{
		db << arrayData[i].key << "," << arrayData[i].voto << "\n";
	}
	db.flush();
	db.close();
	*/
	EngineVotacion<Votacion,const char*,Index> engine(arrayData);
	engine.save(filename);

	/*for(Index i = 0; i < lengthArray; i++)
	{
		delete[] arrayData[i].keys;
	}*/
	return EXIT_SUCCESS;
}
int Main::gen_db(Index lengthArray,unsigned int lengthString,const std::filesystem::path& filename)
{
	char** array = new char*[lengthArray];
	for(Index i = 0; i < lengthArray; i++)
	{
		array[i] = new char[lengthString + 1];
		array[i][lengthString] = (char)0;//null terminations string
	}

	//std::cout << "Step 0\n";
	std::cout << "Generando base de datos...\n";
	//std::cout << "Step 1\n";
	oct::sat::RandomHash hashs;
	for(Index i = 0; i < lengthArray; i++)
	{

		hashs.generate(array[i],lengthString);
		//std::cout << array[i] << "\n";
	}
	//std::cout << "Step 2\n";
	std::default_random_engine generator;
	std::bernoulli_distribution distribution(0.75);
	oct::sat::Array<Votacion,Index> arrayData(lengthArray);
	//std::cout << "Step 3\n";
	for(Index i = 0; i < lengthArray; i++)
	{
		arrayData[i].copy(array[i]);
		//arrayData[i].length = lengthString;
		arrayData[i].voto = distribution(generator);
		//std::cout << arrayData[i].index << "\n";
	}
	//std::cout << "Step 3\n";

	std::ofstream db;
	std::cout << "Guardando base de datos...\n";
	db.open(filename,std::ios::app);
	for(Index i = 0; i < lengthArray; i++)
	{
		db << arrayData[i].key << "," << arrayData[i].voto << "\n";
	}
	db.flush();
	db.close();

	for(Index i = 0; i < lengthArray; i++)
	{
		delete[] array[i];
	}
	delete[] array;
	return EXIT_SUCCESS;
}
int Main::sort_db(const std::filesystem::path&,const std::filesystem::path&,bool unique,unsigned int& time_disk,unsigned int& time_sort)
{

}
int Main::sort_db(const std::filesystem::path& in,const std::filesystem::path& out,bool unique,unsigned int measure)
{
	unsigned int time_disk = 0;
	unsigned int time_sort = 0;
	EngineVotacion<Votacion,const char*,Index>* engine;
	for(unsigned int i = 1; i <= measure; i++)
	{
		engine = new EngineVotacion<Votacion,const char*,Index>(in);

		engine->sort(true,unique);
		
		delete engine;
	}

	return EXIT_FAILURE;
}
int Main::sort_db(const std::filesystem::path& in,const std::filesystem::path& out,bool unique)
{
	std::cout << "Inician..\n";
	if(not std::filesystem::exists(in))
	{
		std::cout << "No existe la base de datos : " << in << "\n";
		return EXIT_FAILURE;
	}
	unsigned int disk_ope = 0;
	unsigned int sort = 0;

	EngineVotacion<Votacion,const char*,Index> engine(in);

	//std::ifstream infile(in);
	std::string line,field;
	//oct::sat::Array<Votacion,Index> arrayData(lengthArray);
	std::cout << "Cargando base de datos..\n";
	auto begin = high_resolution_clock::now();
	bool ret_search = engine.load(in);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - begin);//microseconds
	//std::cout << "Lectura de BD: " << duration.count() << "ms\n";
	if(not ret_search)
	{
		std::cout << "Fallo la apertura de la base de datos.\n";
		return EXIT_FAILURE;
	}
	disk_ope += duration.count();
	if(engine.get_array().size() != lengthArray)
	{
		std::cout << "Por cuestion de medicion deven ser exactamente 1 000 000 registros, sin embargo, hay '" << engine.get_actual() << "'.\n";
		return EXIT_FAILURE;
	}

	//oct::sat::Merge<Votacion,unsigned int> merge(arrayData);
	std::cout << "Ordenando ascendente...\n";
	begin = high_resolution_clock::now();
	try
	{
		engine.sort(true,unique);
	}
	catch(const std::exception& ex)
	{
		std::cout << "Error --> " << ex.what() << "\n";
		return EXIT_FAILURE;
	}
	end = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(end - begin);//microseconds
	//std::cout << "Ordenamiento : " << duration.count() << "ms\n";
	sort = duration.count();

	if(std::filesystem::exists(out)) std::filesystem::remove(out);
	std::cout << "Guardando base de datos...\n";
	begin = high_resolution_clock::now();
	/*std::ofstream outfile;
	outfile.open(out,std::ios::app);
	for(Index i = 0; i < lengthArray; i++)
	{
		outfile << engine.get_array()[i].key << "," << engine.get_array()[i].voto << "\n";
	}
	outfile.flush();
	outfile.close();
	end = high_resolution_clock::now();*/
	engine.save(out);
	duration = duration_cast<milliseconds>(end - begin);//microseconds
	//std::cout << "Guardar : " << duration.count() << "ms\n";
	disk_ope += duration.count();
	//infile.close();

	std::cout << "Lectura/Escritura de Disco : " << float(disk_ope)/float(1000) << "s\n";
	std::cout << "Ordenamiento : " << float(sort)/float(1000) << "s\n";

	std::cout << "Completado..\n";
	return EXIT_SUCCESS;
}
int Main::print(const std::filesystem::path& db, unsigned int i)
{
	EngineVotacion<Votacion,const char*,Index> engine(db);

	if(i >= engine.get_array().size()) 
	{
		std::cout << "No existe el elemento indicado.\n";
		return EXIT_FAILURE;
	}

	
	const Votacion* voto = &engine.get_array()[i];
	std::cout << voto->key << " -> " << (voto->voto? "Si" : "No") << "\n";
	
	return EXIT_SUCCESS;
}
/*
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
*/
