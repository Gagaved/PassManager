
#include "Header.h"
#include "Windows.h"
#include <winuser.h>
#include <WinBase.h>
bool is_emptyf(std::ifstream& pFile)
{
	return pFile.peek() == std::ifstream::traits_type::eof();
}
bool verification(std::string recive_pass, std::string way)
{
	std::string path = way;
	std::vector<char> vec_data_verif;
	de_hasher(hash(recive_pass), path, vec_data_verif);
	std::string exeptedpass;
	for (unsigned int i = 0; i < recive_pass.size(); i++) {
		exeptedpass.push_back(vec_data_verif[i]);
	}
	if (recive_pass == exeptedpass) {
		return true;
	}
	else {
		return false;
	}
}

bool pars_command(std::string command, data& base)
{
	if (command == "master") {
		std::string new_master;
		std::cin >> new_master;
		set_master_pass(new_master, base);
		return false;
	}
	else if (command == "get") {
		std::string site, login;
		std::cin >> site;
		std::cin >> login;
		get_pass(site, login, base);
		return false;
	}
	else if (command == "add") {
		std::string site, login, password;
		std::cin >> site;
		std::cin >> login;
		std::cin >> password;
		new_couple(site, login, password, base);
		return false;
	}
	else if (command == "del") {
		std::string site;
		std::cin >> site;
		/*if (site == "") {
			std::cout << "incorrect input\n"
				return false;
		}*/
		del(site, base);
		return false;
	}
	else if (command == "delone") {
		std::string site;
		std::string login;
		std::cin >> site;
		std::cin >> login;
		delone(site, login, base);
		return false;
	}
	else if (command == "chk") {
		std::string site, login;
		std::cin >> site;
		std::cin >> login;
		check(site, login, base);
		return false;
	}
	else if (command == "help") {
		help();
		return false;
	}
	else if (command == "list") {
		list(base);
		return false;
	}
	else if (command == "q" or command == "quit" or command == "exit") {
		return true;
	}
	else {
		std::cout << "error: invaluable command!\n";
		return false;
	}
}
void hidden_input_pass(std::string& recive_pass) {
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;
	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
	std::getline(std::cin, recive_pass);
	SetConsoleMode(hStdin, mode);
}
void save(std::string passwordsWay, data& base)
{
	std::string str_base;
	str_base.append(base[0][0]);
	str_base.push_back('\n');
	unsigned int size = base.size();
	for (unsigned int i = 1; i < size; i++) {
		str_base.append(base[i][0]);
		str_base.push_back(' ');
		str_base.append(base[i][1]);
		str_base.push_back(' ');
		str_base.append(base[i][2]);
		str_base.push_back('\n');
	}
	std::ofstream fout(passwordsWay, std::ios::binary);
	unsigned long long hash_result = hash(base[0][0]);
	std::vector<char> hasher_result = hasher(hash_result, str_base);
	for (auto elem : hasher_result) {
		fout << elem;
	}
	fout.close();
}
void read_data(data& base,std::string passwordsWay,std::string pass)
{
	std::string path = passwordsWay;
	std::vector<char> vec_data;
	de_hasher(hash(pass), path, vec_data);
	std::string str_data;
	for (char a : vec_data) {
		str_data.push_back(a);
	}
	std::stringstream ss(str_data);
	std::string mpass;
	std::string site;
	std::string login;
	std::string passw;
	ss >> mpass;
	base.push_back(std::vector<std::string>{mpass});
	unsigned int size = base.size();
	ss >> site;
	ss >> login;
	ss >> passw;
	while(!ss.eof()) {
		base.push_back(std::vector<std::string>{site,login,passw});
		ss >> site;
		ss >> login;
		ss >> passw;
	}
	str_data.clear();
}
void set_master_pass(std::string new_password,data& base)
{
	base[0][0] = new_password;
	std::cout << "New password was successfully set\n";
}
void new_couple(std::string site, std::string login, std::string password, data& base)
{
	base.push_back(std::vector<std::string> {site, login, password});
	std::cout << "Couple was added successfully\n";
}
void toClipboard(const std::string& s) {
	OpenClipboard(0);
	EmptyClipboard();
	HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, s.size()+1);
	if (!hg) {
		CloseClipboard();
		return;
	}
	memcpy(GlobalLock(hg), s.c_str(), s.size()+1);
	GlobalUnlock(hg);
	SetClipboardData(CF_TEXT, hg);
	CloseClipboard();
	GlobalFree(hg);
}
void get_pass(std::string site, std::string login, data& base)
{
	unsigned int size = base.size();
	for (unsigned int i = 1; i < size; i++) {
		if (base[i][0] == site and base[i][1] == login) {
			std::cout << "Password was copy to the clipboard" << "\n";
			toClipboard(base[i][2]);
			break;
		}
	}
	std::cout << "Couple was not found\n";
}
void del(std::string site, data& base)
{
	for (unsigned int i = 1; i < base.size(); i++) {
		if (base[i][0] == site) {
			std::cout << "couple was deleted: " << site << " " << base[i][1]<<'\n';
			base.erase(base.begin() + i);
		}
	}
}
void delone(std::string site, std::string login, data& base)
{
	for (unsigned int i = 1; i < base.size(); i++) {
		if (base[i][0] == site && base[i][1] == login) {
			std::cout << "couple was deleted: " << site << " " << base[0][1] << '\n';
			base.erase(base.begin() + i);
			return;
		}
	}
}
void check(std::string site, std::string login, data& base)
{
	unsigned int size = base.size();
	for (unsigned int i = 1; i < size; i++) {
		if (base[i][0] == site && base[i][1]==login && base[i][2]!= "" ) {
			std::cout << "password exists"<<"\n";
			return;
		}
	}
	std::cout << "password does not exist"<<"\n";
}
void list(data& base)
{
	unsigned int size = base.size();
	for (unsigned int i = 1; i < size; i++) {
		std::cout << base[i][0] << " ";
		std::cout << base[i][1] << "\n";
	}
	if (size == 1) {
		std::cout << "you do not have passwords, you can add them with the 'add' command\n\n";
	}
}

void help()
{
	std::cout << "Commands list:\nmaster - set a master password. For example: master myNewMasterPassword\n";
	std::cout << "list - shows a complete list of sites and logins \n";
	std::cout << "add - create new couple site, login and password. For example: google.com myLogin myPassword\n";
	std::cout << "get - copy the password from the site and login to the clipboard. For example: get google.com myLogin \n";
	std::cout << "del - removes all passwords for the site. For example: del google.com\n";
	std::cout << "delone - removes passwords for the site and login. For example: delone google.com myLogin\n";
	std::cout << "chk - checks if a password exists for the site and login. For example: chk google.com myLogin\n";
	std::cout << "q, quit, exit, - exit the program\n";
}


