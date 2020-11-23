#pragma once
#include <stdio.h>

struct BigNum
{
	int i_digit[100];
	int d_digit[100];
	int i_total_digit;
	int d_total_digit;
	int i_digit_add[100];
	int d_digit_add[100];
	int sign;
};
int reverseChar(char* a, int len);
int makeBigInt(char input[201], char* ret);
int makeBinary(char input[201], char* ret);
int enter_number(char* input, struct BigNum* object);
int compare_number(struct BigNum* object, struct BigNum* object2);
int plus(struct BigNum* object, struct BigNum* object2, struct BigNum* object3);
int minus(struct BigNum* object, struct BigNum* object2, struct BigNum* object3);
int multiple(struct BigNum* object, struct BigNum* object2, struct BigNum* object3);
int divide(struct BigNum* object, struct BigNum* object2, struct BigNum* object3, struct BigNum* object4, struct BigNum* object5, struct BigNum* object6, int* d_total);