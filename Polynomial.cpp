/**
 *
 * Polynomial.cpp
 *
 * Project 1
 * Polynomial Arithmetic
 * Leslie Kim
 * NetID: LK584
 * COSC 160
 * Section 02
 *
 **/

#include <iostream>
#include <math.h>
#include <string>
#include "Polynomial.h"

//#define DEBUG_POLY

using namespace std;

/**************************************************************
 *                                                            *
 *               struct PolyNode implementation               *
 *                                                            *
 **************************************************************/

PolyNode::PolyNode() {
#ifdef DEBUG_POLY
  cout << "Entering PolyNode::PolyNode() constructor" << endl;
#endif
  
  coefficient = 0;
  exponent = 0;
  next = NULL;
  
#ifdef DEBUG_POLY
  cout << "Exiting PolyNode::PolyNode() constructor" << endl;
#endif
}

PolyNode::PolyNode(int coef, int exp, PolyNode *nextPtr) {
#ifdef DEBUG_POLY
  cout << "Entering PolyNode::PolyNode(int, int, PolyNode*) constructor" << endl;
#endif
  
  coefficient = coef;
  exponent = exp;
  next = nextPtr;
  
#ifdef DEBUG_POLY
  cout << "Exiting PolyNode::PolyNode(int, int, PolyNode*) constructor" << endl;
#endif
}

/**************************************************************
 *                                                            *
 *              class Polynomial implementation               *
 *                                                            *
 **************************************************************/

Polynomial::Polynomial() {
#ifdef DEBUG_POLY
  cout << "Entering constructor Polynomial::Polynomial()" << endl;
#endif
  
  head = NULL;
  tail = NULL;
  termCount = 0;
  
#ifdef DEBUG_POLY
  cout << "Exiting constructor Polynomial::Polynomial()" << endl;
#endif
}

Polynomial::~Polynomial() {
#ifdef DEBUG_POLY
  cout << "Entering destructor ~Polynomial::Polynomial()" << endl;
#endif
  
  PolyNode *temp = head;
  
  while (temp != NULL) {
    head = head->next;
//    cout << "Deleting " << temp->coefficient << "x^" << temp->exponent << endl;
    delete temp;
    temp = head;
    termCount--;
  }
  
  head = NULL;
  tail = NULL;
  
#ifdef DEBUG_POLY
  cout << "Exiting destructor ~Polynomial::Polynomial()" << endl;
#endif
}

void Polynomial::termAppend(int coef, int exp) {
//  cout << "Adding term " << coef << "x^" << exp << "." << endl;
  
  if (coef == 0)
    return;
  
  PolyNode *temp = head;
  PolyNode *current = new PolyNode(coef, exp, NULL);
  
  if (temp == NULL) {                                         // New polynomial - first PolyNode
    head = current;
    tail = current;
    termCount++;
  }
  else if (temp->next == NULL) {                              // Second PolyNode
    if (temp->exponent == current->exponent)                  // Equal exponents
      head->coefficient += current->coefficient;
    else if (temp->exponent > current->exponent) {            // temp PolyNode exp > current PolyNode exp
      head->next = current;
      tail = current;
      termCount++;
    }
    else {                                                    // temp PolyNode exp < current PolyNode exp
      current->next = head;
      head = current;
      termCount++;
    }
  }
  else {                                                      // More than two PolyNodes in polynomial
    while (temp != NULL) {
      if (temp->exponent == current->exponent) {              // current == temp PolyNode exp
        temp->coefficient += current->coefficient;
        break;
      }
      else if (temp->exponent < current->exponent) {          // current exp > temp PolyNode exp
        current->next = head;
        head = current;
        termCount++;
        break;
      }
      else {                                                  // current exp < temp  exp
        if (temp->next == NULL){
          temp->next = current;
          tail = current;
          termCount++;
          break;
        }
        else if (temp->next->exponent == current->exponent) { // current exp == temp->next exp
          temp->next->coefficient += current->coefficient;
          break;
        }
        else if (temp->next->exponent < current->exponent) {  // current exp > temp->next exp
          current->next = temp->next;
          temp->next = current;
          termCount++;
          break;
        }
        else if (temp->next->exponent > current->exponent) {  // current exp < temp->next exp
          temp = temp->next;
          if (temp->next == NULL) {
            temp->next = current;
            tail = temp->next;
            termCount++;
            break;
          }
        }
        else {
          break;
        }
      }
    } // END while loop
  } // END main else
  
  if (exp >=0)
    return;
}

void Polynomial::getPoly() {
  int coef = 0;
  int exp = 0;
  
  cout << "Please enter coef and exp values: ";
  do {
    cin >> coef >> exp;
    if (exp >= 0)
      termAppend(coef, exp);
  } while (exp >= 0);
}

int Polynomial::polyEval(int value) {
  PolyNode *temp = head;
  int currentValue = 0;
  
  while (temp != NULL) {
    currentValue += temp->coefficient * pow(value, temp->exponent);
    temp = temp->next;
  }
  
  return currentValue;
}

void Polynomial::print() {
  PolyNode *temp = head;
  
  if (temp == NULL) {
    cout << "0";
    return;
  }
  
  while (temp != NULL) {
    if (temp == head) {                         // First term print out
      if (temp->coefficient == 0)               // First term, zero coefficient
        temp = temp->next;
      else {                                    // First term, non-zero coefficient
        if (temp->coefficient == 1) {
          if (temp->exponent == 0)
            cout << temp->coefficient;
          else if (temp->exponent == 1)
            cout << "x";
          else
            cout << "x^" << temp->exponent;
        }
        else if (temp->coefficient == -1) {
          if (temp->exponent == 0)
            cout << temp->coefficient;
          else if (temp->exponent == 1)
            cout << "-x";
          else
            cout << "-x^" << temp->exponent;
        }
        else {
          if (temp->exponent == 0)
            cout << temp->coefficient;
          else if (temp->exponent == 1)
            cout << temp->coefficient << "x";
          else
            cout << temp->coefficient << "x^" << temp->exponent;
        }
      }
    }
    else {                                      // All other terms
      if (temp->coefficient == 0) {             // Zero coefficient
        temp = temp->next;
      }
      else if (temp->coefficient == 1) {        // One coefficient
        if (temp->exponent == 0)
          cout << "1";
        else if (temp->exponent == 1)
          cout << "x";
        else
          cout << "x^" << temp->exponent;
      }
      else if (temp->coefficient == -1) {       // Negative one coefficient
        if (temp->exponent == 0)
          cout << "1";
        else if (temp->exponent == 1)
          cout << "x";
        else
          cout << "x^" << temp->exponent;
      }
      else if (temp->coefficient > 0) {         // Positive coefficient
        if (temp->exponent == 0)
          cout << temp->coefficient;
        else if (temp->exponent == 1)
          cout << temp->coefficient << "x";
        else
          cout << temp->coefficient << "x^" << temp->exponent;
      }
      else if (temp->coefficient < -1) {        // Negative coefficient
        if (temp->exponent == 0)
          cout << (temp->coefficient) * -1;
        else if (temp->exponent == 1)
          cout << (temp->coefficient) * -1 << "x";
        else
          cout << (temp->coefficient) * -1 << "x^" << temp->exponent;
      }
      else
        break;
    }

    temp = temp->next;
    if (temp != NULL) {
      if (temp->coefficient == 0)
        temp = temp->next;
      else if (temp->coefficient < 0)
        cout << " - ";
      else
        cout << " + ";
    }
    else
      break;
  } // END while
}

Polynomial& Polynomial::polyAdd(Polynomial &poly1, Polynomial &poly2) {
  PolyNode *temp = head;
  PolyNode *temp1 = poly1.head;
  PolyNode *temp2 = poly2.head;
  
  int count1 = poly1.getTermCount();
  int count2 = poly2.getTermCount();
  
  if ((count1 != 0) && (count2 != 0)) {                       // Two polynomials with terms
    while (temp1 != NULL) {
      while (temp2 != NULL) {                                 // While terms exist in both polynomials
        if (temp1 != NULL) {                                  // It temp1 still has terms
          if (temp1->exponent == temp2->exponent) {           // If temp1 exp == temp2 exp
            termAppend(temp1->coefficient + temp2->coefficient, temp1->exponent);
            temp1 = temp1->next;
            temp2 = temp2->next;
          }
          else if (temp1->exponent < temp2->exponent) {       // If temp1 exp < temp2 exp
            termAppend(temp2->coefficient, temp2->exponent);
            temp2 = temp2->next;
          }
          else {                                              // If temp1 exp > temp2 exp
            termAppend(temp1->coefficient, temp1->exponent);
            temp1 = temp1->next;
          }
        } // END if (temp1 != NULL)
        else {                                                // temp1 == NULL but temp2 still has terms
          termAppend(temp2->coefficient, temp2->exponent);
          temp2 = temp2->next;
        }
      } // END while (temp2 != NULL)
      if (temp1 != NULL) {                                    // temp2 == NULL but temp1 still has terms
        termAppend(temp1->coefficient, temp1->exponent);
        temp1 = temp1->next;
      }
    } // END while (temp1 != NULL)
  } // END main if
  else {
    if ((count1 != 0) && (count2 == 0))
      temp = temp1;
    else if ((count1 == 0) && (count2 != 0))
      temp = temp2;
    else
      temp = NULL;
    while (temp != NULL) {
      termAppend(temp->coefficient, temp->exponent);
      temp = temp->next;
    }
  } // END main else
  
  return *this;
}

Polynomial& Polynomial::polySub(Polynomial &poly1, Polynomial &poly2) {
  PolyNode *temp = head;
  PolyNode *temp1 = poly1.head;
  PolyNode *temp2 = poly2.head;
  
  int count1 = poly1.getTermCount();
  int count2 = poly2.getTermCount();
  
  if ((count1 != 0) && (count2 != 0)) {                       // Two polynomials with terms
    while (temp1 != NULL) {
      while (temp2 != NULL) {                                 // While terms exist in both polynomials
        if (temp1 != NULL) {                                  // It temp1 still has terms
          if (temp1->exponent == temp2->exponent) {           // If temp1 exp == temp2 exp
            termAppend(temp1->coefficient + ((temp2->coefficient) * -1), temp1->exponent);
            temp1 = temp1->next;
            temp2 = temp2->next;
          }
          else if (temp1->exponent < temp2->exponent) {       // If temp1 exp < temp2 exp
            termAppend(((temp2->coefficient) * -1), temp2->exponent);
            temp2 = temp2->next;
          }
          else {                                              // If temp1 exp > temp2 exp
            termAppend(temp1->coefficient, temp1->exponent);
            temp1 = temp1->next;
          }
        } // END if (temp1 != NULL)
        else {                                                // temp1 == NULL but temp2 still has terms
          termAppend(((temp2->coefficient) * -1), temp2->exponent);
          temp2 = temp2->next;
        }
      } // END while (temp2 != NULL)
      if (temp1 != NULL) {                                    // temp2 == NULL but temp1 still has terms
        termAppend(temp1->coefficient, temp1->exponent);
        temp1 = temp1->next;
      }
    } // END while (temp1 != NULL)
  } // END main if
  else {
    if ((count1 != 0) && (count2 == 0)) {
      temp = temp1;
      while (temp != NULL) {
        termAppend(temp->coefficient, temp->exponent);
        temp = temp->next;
      }
    }
    else if ((count1 == 0) && (count2 != 0)) {
      temp = temp2;
      while (temp != NULL) {
        termAppend(((temp->coefficient) * -1), temp->exponent);
        temp = temp->next;
      }
    }
    else
      temp = NULL;
  } // END main else
  
  return *this;
}

Polynomial& Polynomial::polyMul(Polynomial &poly1, Polynomial &poly2) {
  PolyNode *temp = head;
  PolyNode *temp1 = poly1.head;
  PolyNode *temp2 = poly2.head;
  
  int count1 = poly1.getTermCount();
  int count2 = poly2.getTermCount();
  
  if ((count1 == 0) || (count2 == 0))                         // Poly1 or Poly2 are empty polynomial(s)
    temp = NULL;
  else if ((count1 == 1) && (temp1->coefficient == 1) && (temp1->exponent == 0)) {  // Poly1 == 1
    while (temp2 != NULL) {
      termAppend(temp2->coefficient, temp2->exponent);
      temp2 = temp2->next;
    }
  }
  else if ((count2 == 1) && (temp2->coefficient == 1) && (temp2->exponent == 0)) {  // Poly2 == 1
    while (temp1 != NULL) {
      termAppend(temp1->coefficient, temp1->exponent);
      temp1 = temp1->next;
    }
  }
  else {                                                      // Two polynomials with non-one terms
    while (temp1 != NULL) {
      while (temp2 != NULL) {                                 // While terms exist in both polynomials
        termAppend(temp1->coefficient * temp2->coefficient, temp1->exponent + temp2->exponent);
        temp2 = temp2->next;
      } // END while (temp2 != NULL)
      temp2 = poly2.head;
      temp1 = temp1->next;
    } // END while (temp1 != NULL)
  } // END main if

  return *this;
}

Polynomial& Polynomial::polyExp(int desiredPower) {
  PolyNode *temp = head;
  Polynomial toExp, highest, exponentiated, previousExp;
  PolyNode *exp = NULL;
  PolyNode *H = NULL;
  PolyNode *expPoly = NULL;
  PolyNode *P = NULL;
  int size = 0;
  int highestPower = 0;
  
  previousExp.termAppend(1,0);            // Initalize previous exponentiated poly == 1
  P = previousExp.head;
  
  if (desiredPower == 0) {                // If poly^0, exponentiated poly == 1
    while (temp != NULL) {
      this->head = this->head->next;
      delete temp;
      temp = this->head;
    }
    termAppend(1, 0);
    return *this;
  }
  
  while (desiredPower >= pow(2, size))    // Determine size of array to hold polys raised to nth power
    size++;
  
  highestPower = size - 1;                // Highest power initial poly will be raised to
  
  Polynomial *expPolys[size];             // Create array to hold size polynomials
  for (int i = 0; i < size; i++) {        // Put polys raised to 2^ith power in array
    expPolys[i] = new Polynomial;
    if (i == 0) {
      while (temp != NULL) {
        expPolys[i]->termAppend(temp->coefficient, temp->exponent);
        temp = temp->next;
      }
    }
    else
      expPolys[i]->polyMul(*expPolys[i - 1], *expPolys[i - 1]);
    exp = expPolys[i]->head;
  } // END for loop
  
  for (int j = size - 1; j >= 0; j--) {
    if ((desiredPower - pow(2, j) >= 0)) {
      desiredPower -= pow(2, j);
      if (j == highestPower) {
        while (exp != NULL) {
          highest.termAppend(exp->coefficient, exp->exponent);
          exp = exp->next;
        }
        H = highest.head;
      } // END inside if clause
      else {
        while (expPoly != NULL) {               // Delete previous exponentiated
          exponentiated.head = exponentiated.head->next;
          delete expPoly;
          expPoly = exponentiated.head;
        }
        exponentiated.polyMul(previousExp, highest);
        expPoly = exponentiated.head;
        while (P != NULL) {                      // Delete previousExp
          previousExp.head = previousExp.head->next;
          delete P;
          P = previousExp.head;
        }
        while (expPoly != NULL) {             // Set previousExp to exponentiated
          previousExp.termAppend(expPoly->coefficient, expPoly->exponent);
          expPoly = expPoly->next;
        }
        P = previousExp.head;
        expPoly = exponentiated.head;
        while (H != NULL) {                      // Delete highest
          highest.head = highest.head->next;
          delete H;
          H = highest.head;
        }
        while (exp != NULL) {                 // Set highest to previous poly in array
          highest.termAppend(exp->coefficient, exp->exponent);
          exp = exp->next;
        }
        H = highest.head;
      } // END inside else clause
    } // END first if clause
    else {
      if (j > 0)
        exp = expPolys[j - 1]->head;
      continue;
    } // END first else clause
    
    if (j > 0)
      exp = expPolys[j - 1]->head;
  } // END for loop
  
  while (expPoly != NULL) {               // Delete previous exponentiated
    exponentiated.head = exponentiated.head->next;
    delete expPoly;
    expPoly = exponentiated.head;
  }
  exponentiated.polyMul(previousExp, highest);
  expPoly = exponentiated.head;
  if (this->head != NULL) {
    PolyNode *original = this->head;
    while (original != NULL) {
      this->head = this->head->next;
      delete original;
      original = this->head;
    }
  }
  while (expPoly != NULL) {
    this->termAppend(expPoly->coefficient, expPoly->exponent);
    expPoly = expPoly->next;
  }
  
  return *this;
}

Polynomial& Polynomial::polyMod(Polynomial &poly1, Polynomial &poly2) {
  PolyNode *temp1 = poly1.head;
  PolyNode *temp2 = poly2.head;
  PolyNode *remainder = head;                   // ptr that will point to returned polynomial
  Polynomial quotient, tempRemainder, dividend, divisor, subtractPoly, newDividend, quotientToMul;
  PolyNode *Q = NULL;
  PolyNode *D1 = dividend.head;
  PolyNode *D2 = divisor.head;
  PolyNode *S = subtractPoly.head;
  PolyNode *newD1 = newDividend.head;
  PolyNode *QTM = NULL;
  PolyNode *emptyQTM = NULL;
  
  int count1 = poly1.getTermCount();
  int count2 = poly2.getTermCount();
  int countQ = quotient.getTermCount();
  
  if (count2 == 0) {                            // If poly2 is zero, illegal operation
    remainder = NULL;
    cout << endl << "ERROR: Divisor cannot be zero!" << endl;
  }
  else if (((count2 == 1) && (temp2->coefficient == 1) && (temp2->exponent == 0)) || (count1 == 0))
                                                // If poly2 == 1 or poly1 == 0
    remainder = NULL;                           // remainder == 0
  else if ((temp2->coefficient != 1) && (temp2->coefficient != -1)) {
                                                // First term in temp2 coefficient != 1 or -1
    cout << endl << "ERROR: First term in divisor polynomial must have coefficient value of 1." << endl;
    remainder = NULL;
  }
  else if (temp2->exponent > temp1->exponent)   // poly2 higher degree, quotient == 0, remainder == poly1
    remainder = temp1;
  else {                                        // Non-zero && poly2 != 1 && poly1 != 0 && poly2 < poly1
    while (temp1 != NULL) {                     // Make dividend == poly1
      dividend.termAppend(temp1->coefficient, temp1->exponent);
      temp1 = temp1->next;
    }
    D1 = dividend.head;                         // D1 points to dividend
    while (temp2 != NULL) {                     // Make divisor == poly2
      divisor.termAppend(temp2->coefficient, temp2->exponent);
      temp2 = temp2->next;
    }
    D2 = divisor.head;                          // D2 points to divisor
    
    while (D2->exponent <= D1->exponent) {      // Get quotient
      if (countQ == 0) {                        // First PolyNode added to quotient
        quotient.termAppend((D1->coefficient / D2->coefficient), (D1->exponent - D2->exponent));
        Q = quotient.head;
        QTM = quotient.head;
        countQ++;
      }
      else {                                    // All following PolyNodes added to quotient
        quotient.termAppend((D1->coefficient / D2->coefficient), (D1->exponent - D2->exponent));
        QTM = QTM->next;
        countQ++;
      }
      
      while (emptyQTM != NULL) {                // Delete old quotientToMul - term to multiply w/ divisor
        delete emptyQTM;
        emptyQTM = NULL;
      }
      
      quotientToMul.head = emptyQTM;

      quotientToMul.termAppend(QTM->coefficient, QTM->exponent);  // Assign quotientToMul
      emptyQTM = quotientToMul.head;
      
      while (S != NULL) {                       // Delete old subtractPoly
        subtractPoly.head = subtractPoly.head->next;
        delete S;
        S = subtractPoly.head;
      }
      
      while (newD1 != NULL) {                   // Delete old newDividend
        newDividend.head = newDividend.head->next;
        delete newD1;
        newD1 = newDividend.head;
      }
      
      subtractPoly.polyMul(quotientToMul, divisor);       // Create new subtractPoly
      S = subtractPoly.head;
      newDividend.polySub(dividend, subtractPoly);        // Create newDividend
      newD1 = newDividend.head;
      
      while (D1 != NULL) {                                // Delete old dividend
        dividend.head = dividend.head->next;
        delete D1;
        D1 = dividend.head;
      }
      D1 = newDividend.head;                              // D1 points to newDividend
      while (D1 != NULL) {                                // Make dividend = newDividend
        dividend.termAppend(D1->coefficient, D1->exponent);
        D1 = D1->next;
      }
      D1 = dividend.head;                                 // D1 pionts to dividend
    } // END while (D2->exponent <= D1->exponent)
    
    remainder = dividend.head;                            // remainder points to dividend head
    while (remainder != NULL) {                           // create this poly = remainder
      this->termAppend(remainder->coefficient, remainder->exponent);
      remainder = remainder->next;
    }
  } // END main while
  
  return *this;
}