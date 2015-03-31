/**
 *
 * main.cpp
 *
 * Project 1
 * Polynomial Arithmetic
 * Leslie Kim
 * NetID: LK584
 * COSC 160
 * Section 02
 * In accordance with the class policies and Georgetown's Honor Code,
 * I certify that I have neither given nor received any assistance on
 * this project with the exceptions of lecture notes and those items
 * listed below.
 * Any help items:
 * Description <This program will perform various operations on
 * polynomials. User shall be able to input a polynomial and have the
 * program evaluate the polynomial. Furthermore, user can input two or
 * more polynomials and the program will perform addition, subtraction,
 * multiplication, exponentiation or modulus functions on given
 * polynomials. This program will use pointers and linked lists.>
 *
 **/

#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>

#include "Polynomial.h"
using namespace std;

// FUNCITON PROTOTYPES
void printInstructions();
char selectMenuOption();

// MAIN FUNCTION
int main() {
  bool finished = false;
  char userSelection = ' ';
  
  printInstructions();
  while (!finished) {
    Polynomial one, two, three;
    userSelection = selectMenuOption();           // Output menu and read in user selection
    
    switch(userSelection) {
      case 'E':
      case 'e': {                                 // Evaluate function
        cout << "Enter values for Polynomial 1:" << endl;
        one.getPoly();                            // Get user input polynomial and store in one
        int xVal = 0;                             // Get user input value to evaluate polynomial at
        cout << endl << "Please enter an x-value at which to evaluate function: ";
        cin >> xVal;
        cout << endl << "Polynomial 1 entered is: ";
        one.print();
        cout << ".";
        int eVal = one.polyEval(xVal);            // Evaluate polynomial at xVal
        cout << endl << "Evaluation of Polynomial 1 at " << xVal << " is " << eVal
        << "." << endl;
        break;
      }
      case 'P':
      case 'p': {                                 // Print function
        one.getPoly();                            // Get user input polynomial and store in one
        cout << endl << "Polynomial 1 entered is: ";
        one.print();
        cout << "." << endl;
        break;
      }
      case 'A':
      case 'a': {                                 // Add two polynomials
        cout << "Enter values for Polynomial 1:" << endl;
        one.getPoly();                            // Get user input polynomial and store in one
        cout << endl << "Enter values for Polynomial 2:" << endl;
        two.getPoly();                            // Get user input polynomial and store in two
        cout << endl << "Polynomial 1 entered is: ";
        one.print();
        cout << "." << endl << "Polynomial 2 entered is: ";
        two.print();
        cout << "." << endl;
        three.polyAdd(one, two);                  // Add one and two
        cout << endl << "Polynomials 1 + 2 is: "; // Output results
        three.print();
        cout << "." << endl;
        break;
      }
      case 'S':
      case 's': {                                 // Subtract two polynomials
        cout << "Enter values for Polynomial 1 (minuend):" << endl;
        one.getPoly();                            // Get user input polynomial and store in one
        cout << endl << "Enter values for Polynomial 2 (subtrahend):" << endl;
        two.getPoly();                            // Get user input polynomial and store in two
        cout << endl << "Polynomial 1 entered is: ";
        one.print();
        cout << "." << endl << "Polynomial 2 entered is: ";
        two.print();
        cout << "." << endl;
        three.polySub(one, two);                  // Subtract two from one
        cout << endl << "Polynomials 1 - 2 is: "; // Output results
        three.print();
        cout << "." << endl;
        break;
      }
      case 'M':
      case 'm': {                                 // Multiply two polynomials
        cout << "Enter values for Polynomial 1:" << endl;
        one.getPoly();                            // Get user input polynomial and store in one
        cout << endl << "Enter values for Polynomial 2:" << endl;
        two.getPoly();                            // Get user input polynomial and store in two
        cout << endl << "Polynomial 1 entered is: ";
        one.print();
        cout << "." << endl << "Polynomial 2 entered is: ";
        two.print();
        cout << "." << endl;
        three.polyMul(one, two);                  // Multiply one and two
        cout << endl << "Polynomials 1 * 2 is: "; // Output results
        three.print();
        cout << "." << endl;
        break;
      }
      case 'X':
      case 'x': {                                 // Exponentiate a function
        cout << "Enter values for Polynomial 1:" << endl;
        one.getPoly();                            // Get user input polynomial and store in one
        cout << "Polynomial 1 entered is: ";
        one.print();
        cout << "." << endl;
        int xVal = 0;                             // Get user input value to exponentiate polynomial to
        cout << "Please enter an x-value at which to exponentiate function to: ";
        cin >> xVal;
        one.polyExp(xVal);                        // Exponentiate polynomial at xVal
        cout << endl << "Exponentiation of Polynomial 1 to the " << xVal;
        if (xVal == 1)
          cout << "st power is ";
        else if (xVal == 2)
          cout << "nd power is ";
        else
          cout << "th power is ";
        one.print();
        cout << "." << endl;
        break;
      }
      case 'D':
      case 'd': {                                 // Mod two polynomials
        cout << "Enter values for Polynomial 1 (dividend):" << endl;
        one.getPoly();                            // Get user input polynomial and store in one
        cout << endl << "Enter values for Polynomial 2 (divisor):" << endl;
        cout << "NOTE: Coefficient for largest degree term must be 1 or -1!" << endl;
        two.getPoly();                            // Get user input polynomial and store in two
        cout << endl << "Polynomial 1 entered is: ";
        one.print();
        cout << "." << endl << "Polynomial 2 entered is: ";
        two.print();
        cout << "." << endl;
        three.polyMod(one, two);                  // Mod one by two
        cout << endl << "Polynomials 1 % 2 is: "; // Output results
        three.print();
        cout << "." << endl;
        break;
      }
      case 'Q':
      case 'q': {                                 // Gracefully exit the program
        cout << "Goodbye!" << endl;
        finished = true;
        break;
      }
      default: {                                  // Error in selection
        cout << "ERROR: Please select valid menu option." << endl;
        break;
      }
    }
  }
  return 0;
}

// FUNCTION DEFINITIONS
// Prints instructions for program
void printInstructions() {
  cout << "INSTRUCTIONS: This program will perform various operations" << endl;
  cout << "on user polynomials input by users. When prompted, type int" << endl;
  cout << "value for coefficient followed by a space, followed by int" << endl;
  cout << "value for exponent for a term of the polynomial. Separate" << endl;
  cout << "the exp value of the preceeding term and the coef value of" << endl;
  cout << "the following term with a space. When all terms have been" << endl;
  cout << "input, input -1 for exp value to terminate term input process." << endl << endl;
  cout << "NOTES:" << endl;
  cout << "1) All input for coefficients, exponents and x-values are ints." << endl;
  cout << "2) All exponents are positive ints." << endl;
  cout << "3) Constants should have exponent value of 0." << endl;
  cout << "4) Terms do not need to be in exponential order." << endl << endl;
  cout << "EXAMPLE:" << endl;
  cout << "13x^9 - 3x^5 + 28^4 - x + 3 can be input as:" << endl;
  cout << "1) Terms NOT in order according to degree:" << endl;
  cout << "   Please enter coef and exp: 3 0 -3 5 28 4 13 9 -1 1 0 -1" << endl;
  cout << "2) Terms in order according to degree:" << endl;
  cout << "   Please enter coef and exp: 13 9 -3 5 28 4 -1 1 3 0 0 -1" << endl << endl;
}

// Prints menu options and returns user selection
char selectMenuOption() {
  char selection = ' ';
  string trash;
  
  cout << endl;
  cout << right << setw(45) << "Evaluate polynomial for x value" << setw(10)
  << "E" << endl;
  cout << setw(45) << "Print polynomial" << setw(10) << "P" << endl;
  cout << setw(45) << "Add two polynomials" << setw(10) << "A" << endl;
  cout << setw(45) << "Subtract two polynomials" << setw(10) << "S" << endl;
  cout << setw(45) << "Multiply two polynomials" << setw(10) << "M" << endl;
  cout << setw(45) << "Exponentiate a polynomial" << setw(10) << "X" << endl;
  cout << setw(45) << "Modulus two polynomials" << setw(10) << "D" << endl;
  cout << setw(45) << "Exit the program" << setw(10) << "Q" << endl << endl;
  
  cout << "Please enter your choice: ";
  cin >> selection;
  getline(cin, trash);
  cin.clear();
  cout << endl;
  
  return selection;
}
