/*
Assignment 111
Polynomials.
Write a class operating on polynomials:
adding them, multiplying, printing, evaluating for a given argument.
*/

#include "stdafx.h"
#include <iostream>
#include <cmath>
using namespace std;

//CLASS of Polynomials---------------------------------------------------------------
class Poly {
	double coefficient[30]; //array to hold coefficient values
	int degree = 30; //to be precise, this is not a degree of the polynomial, because it counts a constant value as 1st degree, instead of 0th
public:
	//CONSTRUCTORS
	Poly() {
		for (int i = 0; i < degree; i++) {
			coefficient[i] = 0;
		}
	}
	Poly(int deg, double coeffs[]) { //initialize an object by rewriting provided data
		for (int i = 0; i < deg; i++) {
			coefficient[i] = coeffs[i]; //rewrite all values
		}
		for (int i = deg; i < degree; i++) { //for the ramaining coefficients write 0, because I used fixed max degree of 30
			coefficient[i] = 0;
		}
	}
	//METHODS
	double evaluate(double x) { //calculates the value of the polynomial for given argument
		double y = 0;
		for (int i = 0; i < degree; i++) {
			y += coefficient[i] * pow(x,i);
		}
		return y;
	}
	void print() { //prints the polynomial to the console
		//if all coefficients are 0, then write 0 and stop the function
		int CheckIfallCoeffsAreZero = 0;
		for (int i = 0; i < degree; i++) {
			if (coefficient[i] != 0) CheckIfallCoeffsAreZero++;
		}
		if (CheckIfallCoeffsAreZero == 0) {
			cout << "0" << endl;
			return;
		}
		//write the polynomial from the highest one
		int nonZeroTerms = 0;
		for (int i = degree-1; i >= 0; i--) {
			if (coefficient[i] == 0) continue; // omit entire term if coefficient is 0
			if (coefficient[i] < 0) cout << " - "; // print "- 5" instead of "+ -5"
				else if (nonZeroTerms != 0) { // don't write "+" if it's first value
					cout << " + ";
			}
			if (abs(coefficient[i]) != 1 || i==0) cout << abs(coefficient[i]); // omit "1" near x to prevent "1x" etc.
			switch(i) {
			case 0:
				break;
			case 1:
				cout << "x";
				break;
			default:
				cout << "x^" << i;
			}
			nonZeroTerms++;
		}
		cout << endl;
	}
	//OPERATORS
	Poly operator=(const Poly &f) { //=
		for (int i = 0; i < degree; i++) {
			coefficient[i] = f.coefficient[i];
		}
		return *this;
	}
	Poly operator+=(const Poly &f) { //+=
		for (int i = 0; i < degree; i++) {
			coefficient[i] += f.coefficient[i];
		}
		return *this;
	}
	Poly operator-=(const Poly &f) { //-=
		for (int i = 0; i < degree; i++) {
			coefficient[i] -= f.coefficient[i];
		}
		return *this;
	}
	Poly operator*=(const Poly &f) { //*
		Poly temp;
		temp = (*this)*f;
		*this = temp;
		return *this;
	}
	Poly operator+(const Poly &f) { //+
		Poly temp;
		for (int i = 0; i < degree; i++) {
			temp.coefficient[i] = coefficient[i] + f.coefficient[i];
		}
		return temp;
	}
	Poly operator-(const Poly &f) { //-
		Poly temp;
		for (int i = 0; i < degree; i++) {
			temp.coefficient[i] = coefficient[i] - f.coefficient[i];
		}
		return temp;
	}
	Poly operator*(const Poly &f) { //*
		Poly temp;
		for (int i = 0; i < degree; i++) {
			for (int j = 0; j < f.degree; j++) {
				temp.coefficient[i+j] += coefficient[i] * f.coefficient[j];
			}
		}
		return temp;
	}
};

double* inputPoly(int degree) { //acquires coefficients for the polynomials from the user
	double *coeffs = nullptr;
	coeffs = new double[degree];
	for (int i = 0; i < degree; i++) {
		cout << " ?x^" << i << " = "; //user will be asked to provide coefficients up to the size they specified, starting from the constant
		cin >> coeffs[i];
	}
	return coeffs;
}

void menu() { //prints menu
	cout << endl << "What operation do you want to perform on those polynomials" << endl;
	cout << "1. Add" << endl;
	cout << "2. Subtract" << endl;
	cout << "3. Multiply" << endl;
	cout << "4. Calculate" << endl;
	cout << "0. Exit" << endl;
}


//MAIN---------------------------------------------------------------
int main()
{
	//INPUT FIRST POLYNOMIAL
	cout << endl << "INPUT FIRST POLYNOMIAL" << endl;
	int degree1;
	cout << "degree = ";
	cin >> degree1; //take the size of user's polynomial, so that the function inputPoly() could act accordingly
	cout << endl;
	double *ff = inputPoly(degree1); //saves the returning array from the function, to be later used in construction of an object
	Poly f(degree1, ff);
	//INPUT SECOND POLYNOMIAL
	cout << endl << "INPUT SECOND POLYNOMIAL" << endl;
	int degree2;
	cout << "degree = ";
	cin >> degree2; //take the size of the second polynomial
	cout << endl;
	double *gg = inputPoly(degree2); //saves the second array from the function
	Poly g(degree2, gg);
	//LOOP THE MENU
	int choice;
	do {
		//PRINT
		system("cls"); //clear the screen
		cout << endl << "f() = "; //prints accquired polynomials
		f.print();
		cout << "g() = ";
		g.print();

		//MENU
		Poly z; //creates an "empty" polynomial equal to 0, to avoid changing the values inside user-defined polynomials
		menu();
		do {
			cout << "choice = ";
			cin >> choice; //tak user menu choice and act accordingly
		} while (choice < 0 || choice > 4); //ask for a new choice untill correct given
		cout << endl;
		switch (choice) {
		case 0: //exit
			system("pause");
			return 0;
		case 1: //addition
			cout << "f + g = ";
			z = f + g;
			z.print();
			break;
		case 2: //subtraction
			cout << "f - g = ";
			z = f - g;
			z.print();
			break;
		case 3: //multiplication
			cout << "f * g = ";
			z = f * g;
			z.print();
			break;
		case 4: //evaluataion of both polynomials
			cout << "Input an argument: " << endl << "x = ";
			int x = 0;
			cin >> x;
			cout << "f(" << x << ") = " << f.evaluate(x) << endl;
			cout << "g(" << x << ") = " << g.evaluate(x) << endl;
			break;
		}
		system("pause");
	} while (choice != 0); //repeat the menu for given polynomials untill user exits the app
    return 0;
}