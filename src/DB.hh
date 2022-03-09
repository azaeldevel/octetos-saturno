
#ifndef OCTETOS_SATURNO_DB_HH
#define OCTETOS_SATURNO_DB_HH

#include <list>


#include "Exception.hh"
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

template <oct::sat::Data S,typename Key,oct::sat::Index I = unsigned int> class EngineVotacion : public oct::sat::Engine<S,Key,I>
{
public:
	EngineVotacion(I length) : oct::sat::Engine<S,Key,I>(length)
	{
	}
	virtual ~EngineVotacion()
	{
		for(I i = 0; i < eng::count; i++)
		{
			delete[] eng::db[i].keys;
		}
	}
	
	using eng = oct::sat::Engine<S,Key,I>;
	virtual bool load(std::ifstream& dbfile)
	{
		std::string line,field;
		while (std::getline(dbfile, line))
		{
			std::istringstream iss(line);
					
			std::getline(iss, field, ',');
			eng::db[eng::count].keys = new char[field.size()+1];
			eng::db[eng::count].keys[field.size()] = (char)0;
			strcpy(eng::db[eng::count].keys, field.c_str());
			eng::db[eng::count].length = field.size();
			
			std::getline(iss, field, ',');
			eng::db[eng::count].voto = (bool)std::stoi(field);
			
			eng::count++;
			//std::cout << "eng::count = " << eng::count << "\n";
		}
		if(oct::sat::Engine<S,Key,I>::count != oct::sat::Engine<S,Key,I>::db.size()) return false;
		//std::cout << "end load\n";
		return true;
	}
};

template <oct::sat::Data S,oct::sat::Index I = unsigned int> class DB
{
public:
	DB(const std::filesystem::path& dir) : buffer(NULL)
	{
		load_names(dir);
	}
	~DB()
	{
		if(buffer)
		{
			for(I i = 0; i < count; i++)
			{
				delete[] buffer[i];
			}
			delete[] buffer;
		}
	}
	I generate(const std::filesystem::path& out, I max)
	{
		std::bernoulli_distribution genero(0.7);
		std::bernoulli_distribution votar(0.75);
		std::string name_full;
		std::list<std::string>::iterator it_names_f = names_f.begin();
		std::uniform_int_distribution<int> random_names_f(0,names_f.size() - 1);
		std::advance(it_names_f,random_names_f(generator));
		std::list<std::string>::iterator it_names_m = names_m.begin();
		std::uniform_int_distribution<int> random_names_m(0,names_m.size() - 1);
		std::advance(it_names_m,random_names_m(generator));
		std::list<std::string>::iterator it_apellidos_p = apellidos.begin();
		std::uniform_int_distribution<int> random_names_ap(0,apellidos.size() - 1);
		std::advance(it_apellidos_p,random_names_ap(generator));
		std::list<std::string>::iterator it_apellidos_m = --apellidos.end();
		std::uniform_int_distribution<int> random_names_am(0,apellidos.size() - 1);
		std::advance(it_apellidos_m,random_names_am(generator));
		std::ofstream db;
		db.open(out,std::ios::app);
		count = 0;
		for(; count < max;count++)
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
			db << name_full << "," << std::to_string(votar(generator)) << "\n";
		}

		db.flush();
		db.close();
			
		return count;
	}
	I generate(I max)
	{
		if(names_f.size() == 0 or names_m.size() == 0 or apellidos.size() == 0)
		{
			throw oct::sat::Exception(oct::sat::Exception::NO_DATA_NAME_LOADED,__FILE__,__LINE__);
		}
		
		//std::cout << "step 1"<< "\n";
		buffer = new char*[max];
		//std::cout << "step 2"<< "\n";
		std::list<std::string>::iterator it_names_f = names_f.begin();
		std::list<std::string>::iterator it_names_m = names_m.begin();
		std::list<std::string>::iterator it_apellidos_p = apellidos.begin();
		std::list<std::string>::iterator it_apellidos_m = --apellidos.end();
		std::bernoulli_distribution genero(0.7);
		std::string name_full;
		//std::cout << "step 3"<< "\n";
		for(count = 0; count < max;count++)
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
			//std::cout << "step 4"<< "\n";
			buffer[count] = new char[name_full.size() + 1];
			//std::cout << "step 5"<< "\n";
			strcpy(buffer[count],name_full.c_str());
			buffer[count][name_full.size()] = (char)0;
		}
		
		return count;
	}
	const char** get_strings()const
	{
		return (const char**)buffer;
	}

private:

	bool load_names(const std::filesystem::path& dir)
	{
		if(not std::filesystem::exists(dir)) throw oct::sat::Exception(oct::sat::Exception::NO_DIRECTORY_NAME_FOUND,__FILE__,__LINE__);

		std::filesystem::path path_nombres_f = dir/"nombres-f.csv";
		if(not std::filesystem::exists(path_nombres_f)) throw oct::sat::Exception(oct::sat::Exception::NO_FILE_NAMES_FOUND,__FILE__,__LINE__);
		if(not load_names(path_nombres_f,names_f)) return false;
		//std::cout << "nombre-f : " << names_f.size() << "\n";
		
		std::filesystem::path path_nombres_m = dir/"nombres-m.csv";
		if(not std::filesystem::exists(path_nombres_m)) throw oct::sat::Exception(oct::sat::Exception::NO_FILE_NAMES_FOUND,__FILE__,__LINE__);
		if(not load_names(path_nombres_m,names_m)) return false;


		//std::cout << "nombre-m : " << names_m.size() << "\n";
		std::filesystem::path path_nombres_apellidos = dir/"apellidos.csv";
		if(not std::filesystem::exists(path_nombres_apellidos)) throw oct::sat::Exception(oct::sat::Exception::NO_FILE_NAMES_FOUND,__FILE__,__LINE__);
		if(not load_names(path_nombres_apellidos,apellidos)) return false;
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
	I count;
	char** buffer;
};


#endif