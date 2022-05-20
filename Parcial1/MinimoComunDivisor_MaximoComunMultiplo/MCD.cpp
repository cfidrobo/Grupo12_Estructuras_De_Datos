#include <iostream>
#include "MCD.h"

int MCD::MaximoComunDivisor(int num1, int num2) {
	if (num1 == 0) {
		return num2;
	}
	return MCD::MaximoComunDivisor(num2 % num1, num1);
}