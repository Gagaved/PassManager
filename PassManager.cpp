#include "Header.h"
#include <filesystem>
std::string config_way = "./config.cfg";
int main(int argc, char* argv[]) {
	if (argc != 1) {
		if (std::string(argv[1]) == std::string("--help")) {
			help();
			return 0;
		}
		else if (std::string(argv[1]) == std::string("--config")) {
			if (argc >= 2) {
				config_way = argv[2]; //указываем конфиг
			}
		}
		else {
			std::cout << "error: unknown parameter! \n";
			std::cout << argv[1] << '\n';
			return 1;
		}
	}
	std::ifstream firstin(config_way);
	if (!firstin.is_open()) {
		std::ofstream fcreate(config_way);
		fcreate << "./data";
		fcreate.close();
	}
	else if (is_emptyf(firstin)) {
		std::ofstream fout(config_way);
		fout << "./data";
		fout.close();
		firstin.close();
	}
	std::string passwordsWay;
	std::ifstream fin(config_way);
	fin >> passwordsWay;
	fin.close();

	data base;
	std::string pass;
	typedef std::vector<std::vector<std::string>> data;

	std::ifstream datain(passwordsWay);
	if (!datain.is_open()) {
		std::ofstream fcreate(passwordsWay);
		fcreate.close();
	}
	datain.close();
	std::ifstream data2in(passwordsWay);
	if (is_emptyf(data2in)) {
		std::cout << "Hello, set the master password:\n";
		std::string newpass;
		std::cin >> newpass;
		while (newpass.size() < 8) {
			std::cout << "The password should be at least 8 characters long! Try again:\n";
			std::cin >> newpass;
		}
		pass = newpass;
		base.push_back(std::vector<std::string> {newpass});
		save(passwordsWay, base);
		base.clear();
	} else {
		std::string recive_pass;
		std::cout << "Enter the password or enter 'q' for quit: \n";
		hidden_input_pass(recive_pass);

		while (true)  // АВТОРИЗАЦИЯ
		{
			if (!verification(recive_pass, passwordsWay) ){
				std::cout << "Invalid password! Try again or enter 'q' for quit. \n";
				recive_pass.clear();
				hidden_input_pass(recive_pass); 
				if (recive_pass.size() == 1 &&
					recive_pass[0] == 'q') return 0;
				continue;
			}
			else {
				pass = recive_pass;
				std::cout << "Successful login! \n";
				break;
			}
		}
	}
	read_data(base,passwordsWay,pass);
	while (true) 
	{
		std::string command;
		std::cout << "Enter the command: \n";
		std::cin >> command;
		if (pars_command(command, base)) {
			break;
		}
	}
	save(passwordsWay, base);
}