
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

#include <CUnit/Basic.h>
#include <saturno.hh>
#include <DB.hh>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <random>
#if defined(__linux__)
	#include <execinfo.h>
	#include <csignal>
#elif defined(_WIN32) || defined(_WIN64)
    
#else
	#error "Plataforma desconocida"
#endif


int init(void)
{
	return 0;
}

int clean(void)
{
	return 0;
}


void test_develop()
{
	DB<Votacion,Index> db("../../tests");
	std::filesystem::path file = "db-tests.csv";
	Index count = 100;
	if(std::filesystem::exists(file)) std::filesystem::remove(file);
	CU_ASSERT(db.generate(file,count) == count);
	

	EngineVotacion<Votacion,const char*,Index> engine(count);
	std::ifstream sfile(file);
	CU_ASSERT(engine.load(sfile));
	
	engine.sort(true,false);
	
	const oct::sat::Array<Votacion,Index>& db_array = engine.get_db();
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
		CU_ASSERT(voto_random->keys != NULL);
		//std::cout << voto_random->keys << "\n"; 
		voto_search = engine.search(voto_random->keys);
		CU_ASSERT(voto_search == voto_random);
		if(voto_search != voto_random)
		{
			if(voto_random == NULL) std::cout << "Voto seleccionar\n";
			if(voto_search == NULL) std::cout << "Voto search\n";
			CU_ASSERT(false);
		}
	}
	
	
	DB<Votacion,Index> db2("../../tests");
	Index count2 = 100;
	CU_ASSERT(db2.generate(count) == count);
	for(Index i = 0; i < count2; i++)
	{
		//std::cout << db2.get_strings()[i] << "\n";
		CU_ASSERT(strlen(db2.get_strings()[i]) > 0);
	}
}


int main()
{
	
	signal(SIGABRT,oct::signal_abort);
	signal(SIGSEGV,oct::signal_segmentv);
	
	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

	CU_pSuite pSuite = CU_add_suite("Testing Math..", init, clean);
	if (NULL == pSuite) 
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "Test for deveelping..", test_develop)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
	
	return 0;
}

