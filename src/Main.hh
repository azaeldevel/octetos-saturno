
#ifndef OCTETOS_SATURNO_MAIN_HH
#define OCTETOS_SATURNO_MAIN_HH

#include <filesystem>

typedef unsigned int Index;

class Main
{

public:
	Main();
	int main(const int argc, const char* argv[]);

private:
	int gen_db(Index,const std::filesystem::path&);
	int gen_db_default();
	int sort_db(const std::filesystem::path&,const std::filesystem::path&);
	int full();
	Index lengthArray;
};

#endif