#ifndef CONF_H
#define CONF_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <map>

namespace SNODE{
	class Conf{
		public:
			void init(const char* path){
				std::string line;
				char key[1024];
				char val[1024];
				std::ifstream myfile (path);
				if (myfile.is_open())
				{
					while ( getline (myfile,line) )
					{
						sscanf(line.c_str(), "%s %s", key, val);
						vals_.insert(std::pair<std::string, std::string>(std::string(key), std::string(val)));
					}
					myfile.close();
				}
			}
			int getInt(const char* key){
				std::string val = vals_[std::string(key)];
				return atoi(val.c_str());
			}
			std::string getStr(const char* key){
				return vals_[std::string(key)];
			}

			void setVal(const char* key, const char* val){
				//vals_.insert( std::pair<std::string, std::string>(std::string(key), std::string(val)) );
				vals_[std::string(key)] = std::string(val);
			}

			static Conf* getConf(){
				const char* path = "conf";
				static Conf* conf = NULL;
				if( conf == NULL ){
					conf = new Conf();
					conf->init(path);
				}
				return conf;
			}
		private:
			std::map<std::string, std::string> vals_;
	};
}

#endif