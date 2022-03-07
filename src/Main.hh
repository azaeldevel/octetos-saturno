
#ifndef OCTETOS_SATURNO_MAIN_HH
#define OCTETOS_SATURNO_MAIN_HH


class Main
{

public:
	int main(const int argc, const char* argv[]);

private:
	int gen_db_default();
	int sort_db();
	int full();
};

#endif