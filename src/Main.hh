
#ifndef OCTETOS_SATURNO_MAIN_HH
#define OCTETOS_SATURNO_MAIN_HH


typedef unsigned int Index;

class Main
{

public:
	Main();
	int main(const int argc, const char* argv[]);

private:
	int gen_db(Index,const char*);
	int gen_db_default();
	int sort_db(const char*,const char*);
	int full();
	Index lengthArray;
};

#endif