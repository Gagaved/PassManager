#include <string>
#include <fstream>
#include <iostream>
#include <vector>

unsigned long long hash(std::string password);//������� ���-������� �� ������
std::vector<char> hasher(unsigned long long  hash, std::string str_data); //�������� ��� � ������ ������� ����� ������������
void de_hasher(unsigned long long hash, std::string path, std::vector<char>& str); //�������� ���,������ "����" �� �����