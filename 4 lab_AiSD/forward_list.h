#pragma once

#include <iostream>
#include <vector>

class forward_list {
private:
	class node { //класс node
	private:
		unsigned koefficient; // коэффициент перед мономом
		std::vector <int> degrees; // вектор степеней xyz
		char znak; // знак перед мономом (+ или -)
	public:
		node* ptr = nullptr; // указатель следующей ноды

		node(unsigned p_koefficient = 0, int x = 0, int y = 0, int z = 0, char p_znak = ' ') { // реализация конструктора node
			koefficient = p_koefficient;
			degrees.push_back(x);
			degrees.push_back(y);
			degrees.push_back(z);
			znak = p_znak;
		}
		~node() {}
		unsigned return_koef() {
			return koefficient;
		}
		std::vector <int> return_degrees() {
			return degrees;
		}
		char return_znak() {
			return znak;
		}
	};
	node* first_ptr; // указатель на первую ноду односвязного списка
	unsigned size = 0; // размер форвард листа
public:
	node* get_first_ptr() { return first_ptr; }
	unsigned return_size() { return size; }
	std::vector <double> xyz; // вектор, хранящий координаты точки

	class iterator{
	public:
		node* PTR;
		iterator() { PTR = nullptr; }
		iterator(node* m) {
			PTR = m;
		}
		~iterator() {}
		void operator ++() {
			if (PTR != nullptr) {
				PTR = PTR->ptr;
			}
			else { std::cout << "Введите позицию итератора" << std::endl; }
		}
		bool operator ==(node* m) const{
			return PTR == m;
		}
		bool operator !=(node* m) const {
			if (PTR != m) return true;
			else return false;
		}
		node* operator +=(int m) {
			for (int i = 0; i < m; i++) {
				PTR = PTR->ptr;
			}
			return PTR;
		}
		node* operator +(int m) {
			iterator ptr2(this->PTR);
			for (int i = 0; i < m; i++) {
				ptr2.PTR = ptr2.PTR->ptr;
			}
			return ptr2.PTR;
		}
	};
	
	forward_list() { 
		create_first_node();
	}

	~forward_list() {}

	node* begin() {
		return first_ptr;
	}

	node* end() {
		iterator m(begin());
		m += size-1;
		/*node* m = first_ptr->ptr;
		for (int i = 0; i < size; i++) {
			m = m->ptr;
		}*/
		return m.PTR;
	}

	void create_last_node() {
		node* Node = new node();
		iterator m(begin());
		if (size == 0) { size++; first_ptr = Node; }
		else {
			m += size - 1;
			m.PTR->ptr = Node;
			size++;
		}
	}

	void create_last_node(unsigned p_koefficient, int x, int y, int z, char p_znak) {
		node* Node = new node(p_koefficient, x, y, z, p_znak);
		iterator m(begin());
		if (size == 0) { size++; first_ptr = Node; }
		else {
			m += size - 1;
			m.PTR->ptr = Node;
			size++;
		}
	}

	void create_first_node(unsigned p_koefficient, char x, char y, char z, char p_znak) {
		node* Node = new node(p_koefficient, x, y, z, p_znak);
		if (size == 0) { first_ptr = Node; size++; }
		else { Node->ptr = first_ptr; first_ptr = Node; size++; }
	}

	void create_first_node() {
		node* Node = new node();
		if (size == 0) { first_ptr = Node; size++;}
		else { Node->ptr = first_ptr; first_ptr = Node; size++;}
	}

	void delete_first_node() {
		node* m = first_ptr->ptr;
		first_ptr->~node();
		first_ptr = m;
		size--;
	}

	void delete_last_node() {
		iterator m(begin());
		m += size - 1;
		m.PTR->~node();
		size--;
	}

	void insert_node(unsigned index, unsigned p_koefficient, char x, char y, char z, char p_znak) {
		iterator m(begin());
		node* Node = new node();
		if (index == 0) { Node->ptr = first_ptr; first_ptr = Node; size++; }
		else {
			m += index - 1;
			Node->ptr = m.PTR;
			m.PTR->ptr = Node;
			size++;
		}
	}

	void insert_node(unsigned index) {
		iterator m(begin());
		node* Node = new node();
		if (index == 0) { Node->ptr = first_ptr; first_ptr = Node; size++; }
		else {
			m += index - 1;
			Node->ptr = m.PTR;
			m.PTR->ptr = Node;
			size++;
		}
	}

	void pop(unsigned index) {
		if (index < size) {
			iterator m(begin());
			if (index != 0) m += index - 1;
			node* k = m + 1;
			if (index == 0) { first_ptr = k; m.PTR->~node(); }
			else 
			{
				m.PTR->ptr = k->ptr;
				k->~node();
			}
			size--;
		}
	}

	forward_list reverse_list() {
		iterator m(begin());
		iterator k(begin());
		node* last_ptr = first_ptr;
		m += size - 1;
		first_ptr = m.PTR;
		m += 1;
		k += size - 2;
		int i = size;
		int r = size - 2;
		while (k.PTR != last_ptr) {
			m.PTR = k.PTR;
			m.PTR = last_ptr;
			i--;
			m += i;
			k.PTR = last_ptr;
			r--;
			k += r;
		}
		m.PTR->ptr = last_ptr;
		last_ptr->~node();
		return *this;
	}

	node* centre_of_list() {
		iterator m(begin());
		m += size / 2;
		return m.PTR;
	}

	bool is_empty() {
		if (size == 0) return true; else return false;
	}

	void podobie() {
		iterator k(begin());
		iterator v(begin());
		for (int i = 0; i < size - 1; i++) {
			k = first_ptr;
			k += i;
			int j;
			if (i == 0) j = 0;
			else j = -1;
			for (j = j + i + 1; j < size - i; j++) {
				v = k + j;
				if ((k.PTR->return_degrees()[0] == v.PTR->return_degrees()[0]) && 
					(k.PTR->return_degrees()[1] == v.PTR->return_degrees()[1]) && 
					(k.PTR->return_degrees()[2] == v.PTR->return_degrees()[2])) 
				{
					if (k.PTR->return_znak() == v.PTR->return_znak()) {
						create_last_node(k.PTR->return_koef() + v.PTR->return_koef(), k.PTR->return_degrees()[0], k.PTR->return_degrees()[1], k.PTR->return_degrees()[2], v.PTR->return_znak()); pop(i); pop(i + j - 1); 
						i = 0; j = i + 1; k = first_ptr; v = first_ptr; continue;
					}
					else {
						if (k.PTR->return_koef() > v.PTR->return_koef()) { 
							create_last_node(k.PTR->return_koef() - v.PTR->return_koef(), k.PTR->return_degrees()[0], k.PTR->return_degrees()[1], k.PTR->return_degrees()[2], k.PTR->return_znak()); 
							pop(i); 
							pop(i + j - 1); 
							i = 0; 
							j = i;
							k = first_ptr;
							v = first_ptr;
							continue;
						}
						if (k.PTR->return_koef() < v.PTR->return_koef()) { 
							create_last_node(v.PTR->return_koef() - k.PTR->return_koef(), k.PTR->return_degrees()[0], k.PTR->return_degrees()[1], k.PTR->return_degrees()[2], v.PTR->return_znak()); 
							pop(i); 
							pop(i + j - 1); 
							i = 0; 
							j = i;
							k = first_ptr;
							v = first_ptr;
							continue;
						}
						if (k.PTR->return_koef() == v.PTR->return_koef()) { 
							pop(i); 
							pop(i + j - 1); 
							i = 0; 
							j = i;
							k = first_ptr;
							v = first_ptr;
							continue;
						}
					}
				}
			}
		}
	}

	void print() {
		iterator m(begin());
		for (int i = 1; i <= size; i++) {
			std::cout << m.PTR->return_znak() << " " << m.PTR->return_koef() << "x^" << m.PTR->return_degrees()[0] << "y^" << m.PTR->return_degrees()[1] << "z^" << m.PTR->return_degrees()[2] << " ";
			m += 1;
		}
	}

	void resize_list(unsigned m) {
		if (m > size) {
			for (int i = 0; i < size - m; i++) { create_last_node(); }
		}
	}

	float calculate(std::vector<double> numbers) {
		double k = 0.0;
		iterator m(begin());
		for (int i = 1; i <= size; i++) {
			if (m.PTR->return_znak() == '-') {
				k -= (powf(numbers[0], m.PTR->return_degrees()[0]) * powf(numbers[1], m.PTR->return_degrees()[1]) * powf(numbers[2], m.PTR->return_degrees()[2]));
			}
			else {
				k += (powf(numbers[0], m.PTR->return_degrees()[0]) * powf(numbers[1], m.PTR->return_degrees()[1]) * powf(numbers[2], m.PTR->return_degrees()[2]));
			}
			m += 1;
		}
		return k;
	}
};
