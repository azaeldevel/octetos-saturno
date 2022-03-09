
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
		alpha = new std::uniform_int_distribution<int>(65,90);
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
		if(names_f.size() == 0 or names_m.size() == 0 or apellidos.size() == 0)
		{
			throw oct::sat::Exception(oct::sat::Exception::NO_DATA_NAME_LOADED,__FILE__,__LINE__);
		}

		std::list<std::string>::iterator it_names_f;
		std::uniform_int_distribution<int> random_names_f(0,names_f.size() - 1);		
		std::list<std::string>::iterator it_names_m;
		std::uniform_int_distribution<int> random_names_m(0,names_m.size() - 1);		
		std::list<std::string>::iterator it_apellidos_p;
		std::uniform_int_distribution<int> random_names_ap(0,apellidos.size() - 1);		
		std::list<std::string>::iterator it_apellidos_m;
		std::uniform_int_distribution<int> random_names_am(0,apellidos.size() - 1);
		std::bernoulli_distribution genero(0.7);
		std::bernoulli_distribution second(0.8);
		std::bernoulli_distribution abrev(0.3);
		std::bernoulli_distribution votar(0.7);
		std::string name_full;
		
		std::ofstream db;
		db.open(out,std::ios::app);
		
		for(count = 0; count < max;count++)
		{
			if(genero(generator))
			{
				it_names_f = names_f.begin();
				std::advance(it_names_f,random_names_f(generator));
				name_full = *it_names_f;
				if(second(generator))
				{
					name_full += " ";
					it_names_f = names_f.begin();
					std::advance(it_names_f,random_names_f(generator));
					name_full = *it_names_f;
				}
			}
			else
			{
				it_names_m = names_m.begin();
				std::advance(it_names_m,random_names_m(generator));
				name_full = *it_names_m;	
				if(second(generator))
				{
					name_full += " ";
					it_names_m = names_m.begin();
					std::advance(it_names_m,random_names_m(generator));
					name_full = *it_names_m;
				}			
			}
			
			if(abrev(generator))
			{
				name_full += " ";
				char l = letter();
				name_full += l;
				name_full += ".";
			}

			name_full += " ";

			it_apellidos_p = apellidos.begin();
			std::advance(it_apellidos_p,random_names_ap(generator));
			name_full += *it_apellidos_p;
			
			name_full += " ";
						
			it_apellidos_m = apellidos.begin();
			std::advance(it_apellidos_m,random_names_am(generator));
			name_full += *it_apellidos_m;

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
		std::list<std::string>::iterator it_names_f;
		std::uniform_int_distribution<int> random_names_f(0,names_f.size() - 1);		
		std::list<std::string>::iterator it_names_m;
		std::uniform_int_distribution<int> random_names_m(0,names_m.size() - 1);		
		std::list<std::string>::iterator it_apellidos_p;
		std::uniform_int_distribution<int> random_names_ap(0,apellidos.size() - 1);		
		std::list<std::string>::iterator it_apellidos_m;
		std::uniform_int_distribution<int> random_names_am(0,apellidos.size() - 1);
		std::bernoulli_distribution genero(0.7);
		std::bernoulli_distribution second(0.8);
		std::bernoulli_distribution abrev(0.3);
		std::string name_full;
		//std::cout << "step 3"<< "\n";
		for(count = 0; count < max;count++)
		{
			if(genero(generator))
			{
				it_names_f = names_f.begin();
				std::advance(it_names_f,random_names_f(generator));
				name_full = *it_names_f;
				if(second(generator))
				{
					name_full += " ";
					it_names_f = names_f.begin();
					std::advance(it_names_f,random_names_f(generator));
					name_full = *it_names_f;
				}
			}
			else
			{
				it_names_m = names_m.begin();
				std::advance(it_names_m,random_names_m(generator));
				name_full = *it_names_m;	
				if(second(generator))
				{
					name_full += " ";
					it_names_m = names_m.begin();
					std::advance(it_names_m,random_names_m(generator));
					name_full = *it_names_m;
				}			
			}
			
			if(abrev(generator))
			{
				name_full += " ";
				char l = letter();
				name_full += l;
				name_full += ".";
			}

			name_full += " ";

			it_apellidos_p = apellidos.begin();
			std::advance(it_apellidos_p,random_names_ap(generator));
			name_full += *it_apellidos_p;
			
			name_full += " ";
						
			it_apellidos_m = apellidos.begin();
			std::advance(it_apellidos_m,random_names_am(generator));
			name_full += *it_apellidos_m;

			//std::cout << name_full << "\n";
			//std::cout << "step 4"<< "\n";
			buffer[count] = new char[name_full.size() + 1];
			//std::cout << "step 5"<< "\n";
			strcpy(buffer[count],name_full.c_str());
			buffer[count][name_full.size()] = (char)0;
		}
		
		return count;
	}
	char letter()
	{
		return (char)(alpha->operator()(generator));
	}
	char** get_strings()
	{
		return buffer;
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
	std::uniform_int_distribution<int>* alpha;
};


#endif