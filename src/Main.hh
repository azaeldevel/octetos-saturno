
#ifndef OCTETOS_SATURNO_MAIN_HH
#define OCTETOS_SATURNO_MAIN_HH

#include <filesystem>

typedef unsigned int Index;

struct Votacion
{
	char* keys;
	unsigned int length;
	bool voto;

	Votacion();
	Votacion(const Votacion&);
	~Votacion();
	
	bool operator < (const Votacion& d) const;
	bool operator > (const Votacion& d) const;
	bool operator == (const Votacion& d) const;

	bool operator < (const char*) const;
	bool operator > (const char*) const;
	bool operator == (const char*) const;
};


class Main
{

public:
	Main();
	Main(Index length);

	int main(const int argc, const char* argv[]);

private:
	int gen_db(Index,const std::filesystem::path&);
	int gen_db_default();
	int sort_db(const std::filesystem::path&,const std::filesystem::path&);
	int full();
	Votacion* search(const std::filesystem::path&,const char*);
	Index lengthArray;
};

#endif