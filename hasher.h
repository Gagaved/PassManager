#include <string>
#include <fstream>
#include <iostream>
#include <vector>

unsigned long long hash(std::string password);//считает хеш-функцию по поролю
std::vector<char> hasher(unsigned long long  hash, std::string str_data); //Получает хеш и строку которую нужно захешировать
void de_hasher(unsigned long long hash, std::string path, std::vector<char>& str); //Получает хеш,строку "путь" до файла