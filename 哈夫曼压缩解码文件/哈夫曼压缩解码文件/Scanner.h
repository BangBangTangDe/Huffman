#pragma once
#include<string>
using namespace std;


void print_temp(const char* source, const char * target);
char* Hex_two(char a);
char transform_byte(char *a);
int Target_file(const HEAD head , const char * source, const char * target);
int decode_file(HEAD  de_head, const char *de_file, const char *success_file);