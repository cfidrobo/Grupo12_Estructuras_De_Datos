#include <iostream>
#include "MCM.h"

int MCM::MinimoComunMultiplo(int num1, int num2) {
	int r = (num1 * num2) / MCM::MinimoComunMultiplo(num1, num2);
	return r;
}