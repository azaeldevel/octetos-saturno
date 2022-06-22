
/*
 * main.cc
 * Copyright (C) 2021 Azael Reyes <azael.devel@gmail.com>
 * 
 * Math is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Math is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


//#include <random>
//#include<iostream>
//#include<fstream>
//#include <stdlib.h>
#if defined(__linux__)
	#include <CUnit/Basic.h>
	#include <execinfo.h>
	#include <csignal>
	#include <unistd.h>
	#include <stdio.h>
#elif defined(_WIN32) || defined(_WIN64) 
	#include <iostream>
	#define CU_ASSERT(EXP) if (not EXP) std::cout << "Fallo en : " << __FILE__ << ":" << __LINE__ << "\n";
#else
	#error "Plataforma desconocida"
#endif

#include "../src/Votacion.hh"
#include "../src/Array.hh"

static const std::filesystem::path data_tests_directory = "../../tests";
static const std::filesystem::path data1 = "Data-1.dat";

int init(void)
{
	if(not std::filesystem::exists(data_tests_directory))
	{
		//std::cout << "No se encontro el directorio de datos para pruebas.\n";
		return 1;
	}
	return 0;
}

int clean(void)
{
	return 0;
}

struct Data
{
	unsigned int id;
	bool flag;
	
	bool operator < (const Data& d) const
	{
		return id < d.id;
	}
	bool operator > (const Data& d) const
	{
		return id > d.id;
	}
	bool operator == (const Data& d) const
	{
		return id == d.id;
	}
};

class Datas : public oct::sat::Array<Data,unsigned int>
{
public:
	Datas(unsigned int len, const std::filesystem::path from) : oct::sat::Array<Data,unsigned int>(len)
	{
		std::ifstream from_file(from, std::ios::binary);
		from_file.read(reinterpret_cast<char*>(&operator[](0)), sizeof(Data)*1000);
	}
};

void generate_files()
{
	if(!std::filesystem::exists(data1))
	{
		std::ofstream database_1;
		database_1.open(data1, std::ios::binary);
		Data data;
		data.flag = false;
		for(unsigned int i = 0; i < 1000; i++)
		{
			data.flag = !data.flag;
			data.id = i;
			database_1.write(reinterpret_cast<const char*>(&data),sizeof(Data));
		}
	}
}
void test_develop()
{
	CU_ASSERT(sizeof(Votacion::key) == 50);
	DB<Votacion,Index> db(data_tests_directory);
	std::filesystem::path file = "db-tests";
	Index count = 100;
	if(std::filesystem::exists(file)) std::filesystem::remove(file);
	CU_ASSERT(db.generate(file,count) == count);
	

	EngineVotacion<Votacion,const char*,Index> engine(count);
	//std::ifstream sfile(file);
	//std::cout << "Step a\n";
	CU_ASSERT(engine.import(file) == count);
	//std::cout << "Step b\n";
	
	engine.sort(true,false);
	
	const oct::sat::Array<Votacion,Index>& db_array = engine.get_array();
	std::default_random_engine generator;
	CU_ASSERT(db_array.size() == 100)
	std::uniform_int_distribution<int> votar(0,count - 1);
	int index_voto;
	const Votacion* voto_random;
	const Votacion* voto_search;
	for(unsigned int i = 0; i < 10; i++)
	{
		index_voto = votar(generator);
		//std::cout << "Index : " << index_voto << "\n";
		voto_random = &db_array[index_voto];
		CU_ASSERT(voto_random != NULL);
		CU_ASSERT(voto_random->key != NULL);
		//std::cout << voto_random->key << "\n"; 
		voto_search = engine.search(voto_random->key);
		//CU_ASSERT(voto_search == voto_random);
		if(voto_search != voto_random)
		{
			//if(voto_random == NULL) std::cout << "Voto seleccionar\n";
			//if(voto_search == NULL) std::cout << "Voto search\n";
			CU_ASSERT(false);
		}
	}

	CU_ASSERT(engine.search("askjfdhaskdj") == NULL);
	CU_ASSERT(engine.search("zx2wdf56") == NULL);

	std::filesystem::path file2 = "votacion.db";	
	CU_ASSERT(engine.save(file2));
	CU_ASSERT(std::filesystem::exists(file2));

	
	EngineVotacion<Votacion,char*,Index> engine2(file2);
	CU_ASSERT(engine2.get_header().version == 1);
	//std::cout << "read>>>\n";
	/*for(unsigned int i = 0; i < engine2.get_header().counter; i++)
	{
		std::cout << i << " : '" << engine2.get_array()[i].key << "'\n";
	}*/
	CU_ASSERT(strcmp(engine.get_array()[25].key,engine2.get_array()[25].key) == 0);
	CU_ASSERT(strcmp(engine.get_array()[50].key,engine2.get_array()[50].key) == 0);
	CU_ASSERT(strcmp(engine.get_array()[75].key,engine2.get_array()[75].key) == 0);
	
	/*
	std::filesystem::path file2 = "db-tests2.csv";
	Index count_filter = 50;
	if(std::filesystem::exists(file2)) std::filesystem::remove(file2);
	std::ofstream dbtest2(file2);
	oct::sat::Block<Votacion,Index> db_array2(engine.get_array());
	EngineVotacion<Votacion,const char*,Index> engineVotacion(50);
	engineVotacion.sort(true,false);
	engineVotacion.filter(count_filter);
	const Votacion** vota_array = (const Votacion**)db_array2;
	Index count_completes = 0;
	for(Index i = 0; i < db_array2.size(); i++)
	{
		if(vota_array[i]) 
		{
			dbtest2 << db_array2[i].keys << "\n";
			count_completes++;
		}
	}
	dbtest2.flush();
	dbtest2.close();
	*/
	
	
	//std::cout << "second database \n";
	/*DB<Votacion,Index> db2(data_tests_directory);
	Index count2 = 100;
	CU_ASSERT(db2.generate(count) == count);
	for(Index i = 0; i < count2; i++)
	{
		//std::cout << db2.get_strings()[i] << "\n";
		CU_ASSERT(strlen(db2.get_strings()[i]) > 0);
	}*/
	
	
	//Datas datas(1000,data1);
	
}



int main(int argc, char** argv)
{
	//signal(SIGABRT,oct::signal_abort);
	//signal(SIGSEGV,oct::signal_segmentv);
	generate_files();
#if defined(__linux__)
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite pSuite = CU_add_suite("Testing Saturno..", init, clean);
	if (NULL == pSuite)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite, "Test for developing..", test_develop)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
#elif defined(_WIN32) || defined(_WIN64) 
	test_develop();
#else
	#error "Plataforma desconocida"
#endif
		
	return 0;
}
