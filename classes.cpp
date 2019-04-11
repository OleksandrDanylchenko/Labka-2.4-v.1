//LABKA 2-4 v.1 Class implementation
#include <iostream>
#include <fstream>
#include "classes.h"

constexpr double eps = 1e-7;

Polynom::Polynom(const Polynom& p) {
	for (auto i = p.begin(); i != p.end(); ++i)
		push(*i);
}
// TODO CONVERT transfer
Polynom::Polynom(Polynom&& p) noexcept {
	first = p.first;
	p.first = nullptr;
}

Polynom& Polynom::operator=(const Polynom& p) {
	for (auto i = p.begin(); i != p.end(); ++i)
		push(*i);
	return *this;
}

Polynom& Polynom::operator=(Polynom&& p) noexcept {
	dispose();
	if (this != &p) {
		//for (auto i = p.begin(); i != p.end(); ++i)
		//	push(*i);
		first = p.first;
		p.first = nullptr;
	}
	return *this;
}

Polynom Polynom::operator+(const Polynom& p) const {
	double coefA = 0, coefB = 0, resultCoef = 0;
	Polynom resultP;
	auto iA = begin();
	auto iB = p.begin();
	while (true) {
		if (iA != nullptr && iB == nullptr) {
			Monom& currA = *iA;
			resultP.push(currA); ++iA;
		} else if (iA == nullptr && iB != nullptr) {
			Monom& currB = *iB;
			resultP.push(currB); ++iB;
		} else if (iA != nullptr && iB != nullptr) {
			Monom& currA = *iA;
			Monom& currB = *iB;
			if (abs(currA.pow - currB.pow) < eps) { // A and B operands have the same power
				coefA = currA.coef;
				coefB = currB.coef;
				resultCoef = coefA + coefB;
				Monom resultM{ resultCoef, currA.pow };
				resultP.push(resultM);
				++iA;
				++iB;
			} else if (currA.pow < currB.pow) {
				resultP.push(currA); ++iA;
			} else {
				resultP.push(currB); ++iB;
			}
		} else
			break;
	}
	return resultP;
}

Polynom Polynom::operator-(const Polynom& p) const {
	double coefA = 0, coefB = 0, resultCoef = 0;
	Polynom resultP;
	auto iA = begin();
	auto iB = p.begin();
	while (true) {
		if (iA != nullptr && iB == nullptr) {
			Monom& currA = *iA;
			resultP.push(currA); ++iA;
		} else if (iA == nullptr && iB != nullptr) {
			Monom& currB = *iB;
			resultP.push(currB); ++iB;
		} else if (iA != nullptr && iB != nullptr) {
			Monom& currA = *iA;
			Monom& currB = *iB;
			if (abs(currA.pow - currB.pow) < eps) { // A and B operands have the same power
				coefA = currA.coef;
				coefB = currB.coef;
				resultCoef = coefA - coefB;
				Monom resultM{ resultCoef, currA.pow };
				resultP.push(resultM);
				++iA;
				++iB;
			} else if (currA.pow < currB.pow) {
				resultP.push(currA); ++iA;
			} else {
				resultP.push(currB); ++iB;
			}
		} else
			break;
	}
	return resultP;
}

Polynom& Polynom::operator+=(const Polynom& p) {
	double coefA = 0, coefB = 0, resultCoef = 0;
	auto iA = begin();
	auto iB = p.begin();
	while (true) {
		if (iA != nullptr && iB == nullptr) {
			break;
		} else if (iA == nullptr && iB != nullptr) {
			Monom& currB = *iB;
			push(currB); ++iB;
		} else if (iA != nullptr && iB != nullptr) {
			Monom& currA = *iA;
			Monom& currB = *iB;
			if (abs(currA.pow - currB.pow) < eps) { // A and B operands have the same power
				currA.coef += currB.coef; ++iA; ++iB;
			} else {
				push(currB); ++iB;
			}
		} else
			break;
	}
	return *this;
}

Polynom::~Polynom() { dispose(); }

void Polynom::push(const Monom& m) {
	if (first == nullptr || first->data.pow > m.pow) {
		LE* temp = new LE{ m.coef, m.pow, first};
		first = temp;
	} else {
		LE* seek = first;
		while (seek->next != nullptr && seek->next->data.pow <= m.pow)
			seek = seek->next; 
		if (seek->data.pow < m.pow) { // insert in the end of list
			LE* temp = new LE{ m.coef, m.pow, nullptr };
			seek->next = temp;
		}
		else if (seek->data.pow > m.pow) {
			LE* temp = new LE{ m.coef, m.pow, seek };
			seek = temp;
		}
		else if (seek->data.pow == m.pow)
			seek->data.coef += m.coef;
	}
}
bool Polynom::pop(Monom& m) {
	if (first == nullptr)
		return false;
	m.coef = first->data.coef;
	m.pow = first->data.pow;
	LE* tempDel = first;
	first = first->next;
	delete tempDel;
	return true;
}
void Polynom::dispose() {
	Monom temp;
	while (pop(temp));
}

void operator >>(std::istream& ifs, Polynom& p) {
	short checkVal = -1;
	double tempCoef, tempPow;
	if (&ifs == &std::cin) {
		while (true) {
			std::cout << "Coef: ";
			if (!(ifs >> tempCoef))
				break;
			else {
				std::cout << "Pow: ";
				if (!(ifs >> tempPow))
					break;
			}
			Monom tempMonom{ tempCoef, tempPow };
			p.push(tempMonom);
			++checkVal;
		}
		if (checkVal == -1)
			throw std::logic_error("Keyboard input is empty!");
	} else
		while (!(ifs.eof())) {
			ifs >> tempCoef >> tempPow;
			Monom tempMonom{ tempCoef, tempPow };
			p.push(tempMonom);
		}
	close(ifs);
}

void operator <<(std::ostream& ofs, const Polynom& p) {
	if (&ofs == &std::cout) {
		short amountOfMonoms = 0;
		for (auto i = p.begin(); i != p.end(); ++i) {
			Monom& tempM = *i;
			if (tempM.coef > 0 && amountOfMonoms != 0) //dont put '-' on the start of polynom
				ofs << " + ";
			else if (tempM.coef < 0)
				ofs << " - ";
			if (abs(tempM.coef - 0.) < eps) // coefficient equal to 0
				continue;
			else if (abs(tempM.coef - 1.) < eps && abs(tempM.pow - 0.) > eps) // coefficient equal to 1 and power is not equal to zero
				ofs << " x^" << tempM.pow;
			else if (abs(tempM.pow - 0.) < eps) // power equal to zero
				ofs << abs(tempM.coef);
			else if (abs(tempM.pow - 1.) < eps) // power equa to one
				ofs << abs(tempM.coef) << "*x";
			else
				ofs << abs(tempM.coef) << "*x^" << tempM.pow;
			++amountOfMonoms;
		}
	ofs << std::endl;
	} else {
		for (auto i = p.begin(); i != p.end(); ++i) {
			Monom& tempM = *i;
			if (abs(tempM.coef - 0.) < eps)
				continue;
			else
				ofs << tempM.coef << ' ' << tempM.pow << std::endl;
		}
	}
	close(ofs);
}
void close(std::istream& s) {
	if (&s == &std::cin) {
		s.sync();
		s.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	} else
		((std::ifstream&)s).close();
}
void close(std::ostream& s) {
	if (&s != &std::cout)
		((std::ofstream&)s).close();
}

Polynom::Iter::Iter(Polynom::LE* init) : current{ init } {}
Monom& Polynom::Iter::operator*() {
	if (current != nullptr)
		return current->data;
	else
		throw std::out_of_range("Memory access violation due to * operator");
}
Polynom::Iter& Polynom::Iter::operator++() {
	if (current != nullptr)
		current = current->next;
	else
		throw std::out_of_range("Memory access violation due to ++i operator");
	return *this;
}
Polynom::Iter& Polynom::Iter::operator++(int) {
	Iter temp = *this;
	if (current != nullptr)
		current = current->next;
	else
		throw std::out_of_range("Memory access violation due to i++ operator");
	return *this;
}

bool Polynom::Iter::operator==(const Iter& it) { return (current == it.current); }
bool Polynom::Iter::operator!=(const Iter& it) { return (current != it.current); }

Polynom::Iter Polynom::begin() const { return Iter(first); }
Polynom::Iter Polynom::end() const { return Iter(nullptr); }
