
#ifndef OCTETOS_SATURNO_MAIN_HH
#define OCTETOS_SATURNO_MAIN_HH

#include "saturno.hh"
#include "DB.hh"


template <oct::sat::Data S,typename Key,oct::sat::Index I = unsigned int> class EngineVotacion : public oct::sat::Engine<S,Key,I>
{
public:
	EngineVotacion(I length) : oct::sat::Engine<S,Key,I>(length)
	{
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
		}
		if(oct::sat::Engine<S,Key,I>::count != oct::sat::Engine<S,Key,I>::db.size()) return false;

		return true;
	}
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