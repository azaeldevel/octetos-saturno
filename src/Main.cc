
#include <string.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <chrono>
using namespace std::chrono;


#include "Main.hh"
#include "saturno.hh"



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
			std::cout << "emule-db length_db db_name da_names\n";
			return EXIT_FAILURE;
		}
		//std::cout << "file : " << argv[3] << "\n";
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
		//std::cout << "file : " << argv[2] << "\n";
		return sort_db(argv[1],argv[2]);		
	}
	else if(strcmp("search",argv[0]) == 0)
	{
		if(argc < 2) 
		{
			std::cout << "search db text\n";
			return EXIT_FAILURE;
		}
		Votacion* voto = search(argv[1],argv[2]);		
		if(voto) 
		{
			std::cout << argv[2] << (voto->voto ? " Si " : " No ") << "voto\n";
			delete voto;
			return EXIT_SUCCESS;
		}
		else
		{
			std::cout << argv[2] << " no se encontro.\n";
			return EXIT_FAILURE;
		}
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
	std::cout << "Generando base de datos...\n";
	DB<Votacion,Index> gendb(name);
	Index ret_count;
	try
	{
		ret_count = gendb.generate(lengthArray);
	}
	catch(const std::exception& ex)
	{
		std::cout << "Exception : require " << lengthArray << " "  << ex.what() << "\n";
		return EXIT_FAILURE;
	}
	if(ret_count != lengthArray)
	{
		std::cout << "Fallo la generacion de la base de datos\n";
		return EXIT_FAILURE;
	}
	
	std::default_random_engine generator;
	std::bernoulli_distribution distribution(0.75);
	oct::sat::Array<Votacion,Index> arrayData(lengthArray);
	for(Index i = 0; i < lengthArray; i++)
	{
		arrayData[i].length = strlen(gendb.get_strings()[i]);
		arrayData[i].keys = new char[arrayData[i].length + 1];
		strcpy(arrayData[i].keys,gendb.get_strings()[i]);
		arrayData[i].voto = distribution(generator);
		//std::cout << arrayData[i].index << "\n";
	}
	
	if(std::filesystem::exists(filename)) std::filesystem::remove(filename);
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
		delete[] arrayData[i].keys;
	}
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
	delete[] array;	
	return EXIT_SUCCESS;
}

int Main::sort_db(const std::filesystem::path& in,const std::filesystem::path& out)
{	
	std::cout << "Inician..\n";
	if(not std::filesystem::exists(in))
	{
		std::cout << "No existe la base de datos : " << in << "\n";
		return EXIT_FAILURE;
	}
	unsigned int disk_ope = 0;
	unsigned int sort = 0;
	
	EngineVotacion<Votacion,const char*,Index> engine(lengthArray);

	std::ifstream infile(in);
	std::string line,field;
	//oct::sat::Array<Votacion,Index> arrayData(lengthArray);
	std::cout << "Cargando base de datos..\n";
	auto begin = high_resolution_clock::now();
	bool ret_search = engine.load(infile);
	auto end = high_resolution_clock::now();
	auto duration = duration_cast<milliseconds>(end - begin);//microseconds	 
	//std::cout << "Lectura de BD: " << duration.count() << "ms\n";
	if(not ret_search)
	{
		std::cout << "Fallo la apertura de la base de datos.\n";
		return EXIT_FAILURE;
	}
	disk_ope += duration.count();
	if(engine.get_count() != lengthArray)
	{
		std::cout << "Hay " << engine.get_count() << " deven ser exactamente 1 000 000.\n";
		return EXIT_FAILURE;
	}
	
	//oct::sat::Merge<Votacion,unsigned int> merge(arrayData);
	std::cout << "Ordenando ascendente...\n";
	begin = high_resolution_clock::now();
	engine.sort(true,false);
	end = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(end - begin);//microseconds	 
	//std::cout << "Ordenamiento : " << duration.count() << "ms\n";
	sort = duration.count();
	
	if(std::filesystem::exists(out)) std::filesystem::remove(out);
	std::ofstream outfile;	
	std::cout << "Guardando base de datos...\n";
	begin = high_resolution_clock::now();
	outfile.open(out,std::ios::app);
	for(Index i = 0; i < lengthArray; i++)
	{
		outfile << engine.get_db()[i].keys << "," << engine.get_db()[i].voto << "\n";
	}
	outfile.flush();
	outfile.close();
	end = high_resolution_clock::now();
	duration = duration_cast<milliseconds>(end - begin);//microseconds	 
	//std::cout << "Guardar : " << duration.count() << "ms\n";
	disk_ope += duration.count();
	infile.close();	
	
	std::cout << "Lectura/Escritura de Disco : " << float(disk_ope)/float(1000) << "s\n";
	std::cout << "Ordenamiento : " << float(sort)/float(1000) << "s\n";
	
	std::cout << "Completado..\n";
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