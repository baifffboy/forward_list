#include "Parser.h"
forward_list* Parser(std::string polinom, forward_list& list) {
	list.delete_first_node();
	unsigned koefficient = 1; // коэффициент перед мономом
	std::vector <int> degrees(3); // вектор степеней xyz
	char znak = ' '; // знак перед мономом (+ или -)
	std::string rr;
	for (int i = 0; i <= polinom.size(); i++) {
		if (polinom[i] == '+' || polinom[i] == '-' || i == polinom.size()) {
			if (znak == ' ' && list.return_size() == 0 && koefficient != 0) {
				znak = '+';
				list.create_last_node(koefficient, degrees[0], degrees[1], degrees[2], znak);
				if (i == polinom.size()) break;
				degrees.clear();
				std::vector<int>::iterator iter = degrees.begin();
				degrees.insert(iter, 3, 0);
				koefficient = 1;
				znak = polinom[i];
				continue;
			}
			if (znak != ' ' && list.return_size() != 0 && koefficient != 0) {
				list.create_last_node(koefficient, degrees[0], degrees[1], degrees[2], znak);
				if (i == polinom.size()) break;
				degrees.clear();
				std::vector<int>::iterator iter = degrees.begin();
				degrees.insert(iter, 3, 0);
				koefficient = 1;
				znak = polinom[i];
				continue;
			}
			if (koefficient == 0) {
				if (i == polinom.size()) break;
				degrees.clear();
				std::vector<int>::iterator iter = degrees.begin();
				degrees.insert(iter, 3, 0);
				koefficient = 1;
				znak = polinom[i];
				continue;
			}

		}
		if (polinom[i] == 'x') {
			while (polinom[i] != '^') { i++; } i++;
			while ((48 > polinom[i]) || (polinom[i] > 57)) i++;
			std::string m;
			while (polinom[i] != 'y' && polinom[i] != 'z' && polinom[i] != '+' && polinom[i] != '-' && polinom[i] != '\0' && polinom[i] != ' ') {
				if (48 <= polinom[i] <= 57) {
					m += polinom[i];
					if (polinom[i + 1] != 'y' && polinom[i + 1] != 'z' && i != polinom.size() - 1) i++;
					else break;
				}
			}
			degrees[0] = std::stoi(m);
			m.clear();
			if (polinom[i + 1] == 'y' || polinom[i + 1] == 'z') continue;
		}
		if (polinom[i] == 'y') {
			while (polinom[i] != '^') { i++; } i++;
			while ((48 > polinom[i]) || (polinom[i] > 57)) i++;
			std::string m;
			while (polinom[i] != 'x' && polinom[i] != 'z' && polinom[i] != '+' && polinom[i] != '-' && polinom[i] != '\0' && polinom[i] != ' ') {
				if (48 <= polinom[i] <= 57) {
					m += polinom[i];
					if (polinom[i + 1] != 'x' && polinom[i + 1] != 'z' && i != polinom.size() - 1) i++;
					else break;
				}
			}
			degrees[1] = std::stoi(m);
			m.clear();
			if (polinom[i + 1] == 'x' || polinom[i + 1] == 'z') continue;
		}
		if (polinom[i] == 'z') {
			while (polinom[i] != '^') { i++; } i++;
			while ((48 > polinom[i]) || (polinom[i] > 57)) i++;
			std::string m;
			while (polinom[i] != 'x' && polinom[i] != 'y' && polinom[i] != '+' && polinom[i] != '-' && polinom[i] != '\0' && polinom[i] != ' ') {
				if (48 <= polinom[i] <= 57) {
					m += polinom[i];
					if(polinom[i+1] != 'x' && polinom[i+1] != 'y' && i != polinom.size() - 1) i++;
					else break;
				}
			}
			degrees[2] = std::stoi(m);
			m.clear();
			if (polinom[i + 1] == 'y' || polinom[i + 1] == 'x') continue;
		}
		if ((48 <= polinom[i]) && (polinom[i] <= 57) && (i != polinom.size())) {
			rr += polinom[i];
			if (polinom[i+1] == ' ' || polinom[i+1] == 'x' || polinom[i+1] == 'y' || polinom[i+1] == 'z') {
				koefficient = std::stoi(rr);
				rr.clear();
				continue;
			}
		}
	}
	list.podobie();
	return &list;
}

