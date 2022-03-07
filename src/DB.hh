
#ifndef OCTETOS_SATURNO_DB_HH
#define OCTETOS_SATURNO_DB_HH

#include <list>

#include "saturno.hh"

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


template <oct::sat::Data S,oct::sat::Index I = unsigned int> class DB
{
public:
	DB()
	{
		load_names();
	}
	I generate(const std::filesystem::path& out, I max)
	{		
		std::list<std::string>::iterator it_names_f = names_f.begin();
		std::list<std::string>::iterator it_names_m = names_m.begin();
		std::list<std::string>::iterator it_apellidos_p = apellidos.begin();
		std::list<std::string>::iterator it_apellidos_m = --apellidos.end();
		std::bernoulli_distribution genero(0.7);
		std::string name_full;
		for(I i = 0; i < (2*max)/3;i++)
		{
			if(genero(generator))
			{
				name_full = *it_names_m;
				it_names_m++;
				if(it_names_m == names_m.end()) it_names_m = names_m.begin();
			}
			else
			{
				name_full = *it_names_f;
				it_names_f++;
				if(it_names_f == names_f.end()) it_names_f = names_f.begin();				
			}
			name_full += " ";
			
			name_full += *it_apellidos_p;
			it_apellidos_p++;
			if(it_apellidos_p == apellidos.end()) it_apellidos_p = apellidos.begin();
			
			name_full += " ";
			
			name_full += *it_apellidos_p;
			it_apellidos_m--;			
			if(it_apellidos_m != apellidos.begin()) it_apellidos_m = --apellidos.end();

			//std::cout << name_full << "\n";
			names.push_back(name_full);
		}

		std::bernoulli_distribution votar(0.75);
		std::ofstream db;
		db.open(out,std::ios::app);
		for(const std::string& str : names)
		{
			db << str << "," << std::to_string(votar(generator)) << "\n";
		}
		db.flush();
		db.close();
			
		return names.size();
	}
private:

	bool load_names()
	{
		load_names("tests/nombres-f.csv",names_f);
		//std::cout << "nombre-f : " << names_f.size() << "\n";
		load_names("tests/nombres-m.csv",names_m);
		//std::cout << "nombre-m : " << names_m.size() << "\n";
		load_names("tests/apellidos.csv",apellidos);
		//std::cout << "apellidos : " << apellidos.size() << "\n";
			
		return true;
	}
	bool load_names(const std::filesystem::path& in,std::list<std::string>& out)
	{
		if(not std::filesystem::exists(in)) return false;

		std::ifstream infile(in);
		std::string line,field;
		while (std::getline(infile, line))
		{
			out.push_back(line);
			//std::cout << line << "\n";
		}

		infile.close();
		return true;
	}
private:
	//char** array;
	std::list<std::string> names_f;
	std::list<std::string> names_m;
	std::list<std::string> apellidos;
	std::default_random_engine generator;
	std::list<std::string> names;
};


#endif