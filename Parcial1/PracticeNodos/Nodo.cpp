
#ifndef NULL
#define NULL (0)
#endif
#include "Nodo.h"
/**
 * .Constructor
 * 
 * \param val
 * \param sig
 */
Nodo::Nodo(int val, Nodo* sig = NULL) {
	this->valor = val;
	this->siguiente = sig;
}