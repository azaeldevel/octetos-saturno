
#ifndef OCTETOS_SATURNO_MAIN_HH
#define OCTETOS_SATURNO_MAIN_HH

#include "Saturno.hh"
#include "DB.hh"

class Main
{

public:
	Main();
	Main(Index length);

	int main(const int argc, const char* argv[]);

private:
	int emule_db(Index,const std::filesystem::path&,const std::filesystem::path&);
	int gen_db(Index,unsigned int,const std::filesystem::path&);
	int gen_db_default();
	int sort_db(const std::filesystem::path&,const std::filesystem::path&,bool unique);
	int full();
	Votacion* search(const std::filesystem::path&,const char*);
	Index lengthArray;
};

#endif