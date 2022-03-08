
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
	DB<Votacion,Index> db;
	std::filesystem::path file = "db-tests.csv";
	Index count = 10;
	if(std::filesystem::exists(file)) std::filesystem::remove(file);
	CU_ASSERT(db.generate(file,count) == count);
	
	
	try
	{
		EngineVotacion<Votacion,const char*,Index> engine(count);
	}
	catch(const std::exception& e)
	{
		std::cout << "Exception : " << e.what() << "\n";
	}
	
	
}

void print_backtrace(int)
{
	unsigned int BT_BUF_SIZE = 20;
	int nptrs;
    void *buffer[BT_BUF_SIZE];
    char **strings;

  	nptrs = backtrace(buffer, BT_BUF_SIZE);
	printf("backtrace() returned %d addresses\n", nptrs);

	/* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
	would produce similar output to the following: */

	strings = backtrace_symbols(buffer, nptrs);
	if (strings == NULL) {
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

	for (int j = 0; j < nptrs; j++) printf("%s\n", strings[j]);

	free(strings);
}

int main()
{
	signal(SIGABRT,print_backtrace);
	signal(SIGSEGV,print_backtrace);
	
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

