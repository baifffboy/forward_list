#include "Parser.h"
#include <sstream>


int main() {
	setlocale(LC_ALL, "RUS");
	std::cout << "Введите полином:\nВид полинома: x^ny^uz^q, где n, u, q - целые числа, z, y, q - дробные\n";
	std::string line;
	std::getline(std::cin, line);
	std::cout << "Преобразованный полином:\n";
	forward_list* n = new forward_list();
	Parser(line, *n);
	n->print();
	std::cout << "\nВведите точку для вычисления полинома(числа представляют тип double): Пример: 354.0 65.0 87.0 enter\n";
	double number;
	line.clear();
	std::getline(std::cin, line);
	std::stringstream ss(line); 
	while (ss >> number) { 
		n->xyz.push_back(number);
	}
	std::cout << "-----------------------------------------------------------------------------------------\n";
	std::cout << "Ответ:\n";
	std::cout << n->calculate(n->xyz) << std::endl;
	return 0;
}