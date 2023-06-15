#include <iostream>
#include <locale.h>
#include <string>

class Fraction {
private:
	int Re, Im;
public:
	Fraction(int numerator = 1, int denominator = 1) {
		Re = numerator;
		Im = denominator;
	}
	void set_Re(int user_Re) { Re = user_Re; }
	void set_Im(int user_Im) { Im = user_Im; }
	void print() { std::cout << Re << "/" << Im; }
	Fraction operator+(const Fraction &right) {
		int nIm = Im * right.Im;
		int nRe = Re * right.Im + right.Re * Im;
		return Fraction(nRe, nIm);
	}
	Fraction operator-(const Fraction &right) {
		int nIm = Im * right.Im;
		int nRe = Re * right.Im - right.Re * Im;
		return Fraction(nRe, nIm);
	}
	Fraction operator*(const Fraction& right) {
		int nRe = Re * right.Re;
		int nIm = Im * right.Im;
		return Fraction(nRe, nIm);
	}
	Fraction operator/(const Fraction& right) {
		int nRe = Re * right.Im;
		int nIm = right.Re * Im;
		return Fraction(nRe, nIm);
	}
	Fraction& operator++() {
		Re = Re + Im;
		return *this;
	}
	Fraction operator++(int) {
		Fraction temp = *this;
		++(*this);
		return temp;
	}
	Fraction operator--() {
		Re = Re - Im;
		return *this;
	}
	Fraction operator--(int) {
		Fraction temp = *this;
		--(*this);
		return temp;
	}
	Fraction& operator-() {
		if (Re < 0) {
			abs(Re);
		} else if (Im < 0) {
			Im = abs(Im);
			Re = Re - Re - Re;
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& out, const Fraction& right);
	friend Fraction fraction_reduc(Fraction& frac);
};

std::ostream& operator<<(std::ostream& out, const Fraction& right) {
	out << right.Re << "/" << right.Im;
	return out;
}

Fraction fraction_reduc(Fraction& f) {
	int tRe = f.Re, tIm = f.Im, nod, rem;
	if (tRe < tIm) {
		int temp = tRe;
		tRe = tIm;
		tIm = temp;
	}
	while (rem = tRe % tIm) {
		tRe = tIm;
		tIm = rem;
	}
	nod = tIm;
	tRe = f.Re / nod;
	tIm = f.Im / nod;
	if (tIm < 0) {
	tIm = abs(tIm);
	tRe = tRe - tRe - tRe;
	}
	return Fraction(tRe, tIm);
}

int main() {
	setlocale(LC_ALL, "Russian");

	int user_Re_1, user_Im_1, user_Re_2, user_Im_2;
	Fraction f1(3, 4), f2(4, 5), f3;

	std::cout << "Введите числитель дроби 1:"; std::cin >> user_Re_1; f1.set_Re(user_Re_1);
	std::cout << "Введите знаменатель дроби 1: "; std::cin >> user_Im_1; f1.set_Im(user_Im_1);
	std::cout << "Введите числитель дроби 2: "; std::cin >> user_Re_2; f2.set_Re(user_Re_2);
	std::cout << "Введите знаменатель дроби 2: "; std::cin >> user_Im_2; f2.set_Im(user_Im_2);
    
	std::cout << f1 << " + " << f2 << " = "; f3 = f1 + f2; std::cout << (fraction_reduc(f3)) << std::endl;
	std::cout << f1 << " - " << f2 << " = "; f3 = f1 - f2; std::cout << (fraction_reduc(f3)) << std::endl;
	std::cout << f1 << " * " << f2 << " = "; f3 = f1 * f2; std::cout << (fraction_reduc(f3)) << std::endl;
	std::cout << f1 << " / " << f2 << " = "; f3 = f1 / f2; std::cout << (fraction_reduc(f3)) << std::endl;
	std::cout << "++" << f1 << " * " << f2 << " = "; f3 = ++f1 * f2; std::cout << (fraction_reduc(f3)) << std::endl;
	std::cout << "Значение дроби 1 = " << (fraction_reduc(f1)) << std::endl;
	std::cout << f1 << "--" << " * " << f2 << " = "; f3 = f1-- * f2; std::cout << (fraction_reduc(f3)) << std::endl;
	std::cout << "Значение дроби 1 = " << (fraction_reduc(f1)) << std::endl;

	return 0;
}