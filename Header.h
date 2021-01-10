#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include "hasher.h"

typedef std::vector<std::vector<std::string>> data;
bool verification(std::string recive_pass, std::string way);
bool is_emptyf(std::ifstream& pFile);
void delone(std::string site, std::string login, data& base);
void set_master_pass(std::string new_password, data& base);
void new_couple(std::string site, std::string login, std::string password, data& base);
void get_pass(std::string site, std::string login,data& base);
void del(std::string site, data& base);
void check(std::string site, std::string login, data& base);
void help();
void list(data& base);
bool pars_command(std::string command, data& base);
void hidden_input_pass(std::string& recive_pass);
void save(std::string passwordsway, data& base);
void read_data(data& base, std::string passwordsWay, std::string pass);
