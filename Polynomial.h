/**
 *
 * Polynomial.h
 *
 * Project 1
 * Polynomial Arithmetic
 * Leslie Kim
 * NetID: LK584
 * COSC 160
 * Section 02
 *
 **/

#ifndef __Polynomials__Polynomial__
#define __Polynomials__Polynomial__

#include <stdio.h>


/*****************************************************
 *                                                   *
 *             struct PolyNode definition            *
 *                                                   *
 *****************************************************/

struct PolyNode {
  int coefficient;
  int exponent;
  PolyNode *next;
  
  PolyNode();
  PolyNode(int coef, int exp, PolyNode *nextPtr = NULL);
};  // END PolyNode definition

/*****************************************************
 *                                                   *
 *            class Polynomial definition            *
 *                                                   *
 *****************************************************/

class Polynomial {
private:
  PolyNode *head;
  PolyNode *tail;
  int termCount;
public:
  Polynomial();
  ~Polynomial();
  
  int getTermCount() const { return termCount; }    // Return number of terms in polynomial
  
  void termAppend(int, int);                        // Add a term resulting in degree ordered polynomial
  void getPoly();                                   // Get user input polynomial
  
  int polyEval(int);                                // Evaluate polynomial for a given int
  void print();                                     // Print polynomial
  Polynomial& polyAdd(Polynomial&, Polynomial&);    // Add two polynomials
  Polynomial& polySub(Polynomial&, Polynomial&);    // Subtract two polynomials
  Polynomial& polyMul(Polynomial&, Polynomial&);    // Multiply two polynomials
  Polynomial& polyExp(int);                         // Exponentiate a polynomial
  Polynomial& polyMod(Polynomial&, Polynomial&);    // Modulus two polynomials
};  // END Polynomial definition
#endif