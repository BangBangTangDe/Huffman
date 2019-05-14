#include"stdafx.h"
const int SIZE = 256;
const int ROOT = 510;
static int nSize = 0;
#pragma warning (disable:4996)
#include<iostream>
#include"huffman.h"
using namespace std;

void print_temp(const char * source, const char* target)
{
	int ch;
	const char* src = source; const char*tar = target;
	FILE * fsource = fopen(src, "rb+");
	FILE * ftarget = fopen(tar, "wb+");
	if (fsource == NULL) { cout << "打开源文件失败" << endl; return; }
	else
	{
		ch = getc(fsource); 
		while (ch != EOF)
		{
			ch = getc(fsource);
			for (int i = 0; i < Code[ch].len; i++)
			{
				char a = char(Code[ch].post[i]); 
				fputc(a, ftarget);
			}
				
		}
	}
	fclose(fsource);
	fclose(ftarget);
}
//十六进制转换成2进制
char* Hex_two(char a)
{
	char temp[256] = {0};
	for (int i = 0; i < 8; i++) {
		if (a & 1) {
			temp[7 - i] = '1';
		}
		else {
			temp[7 - i] = '0';
		}
		a >>= 1;
	}
	return temp;
}
//二进制转换成十六进制
char transform_byte(char *a)
{
	char b = 0x00;
	for (int i = 0; i < 8; i++)
	{
		b=b << 1;//字符左移
		if (a[i] == '1')
			b = b | 0x01;
	}
	return b;
}
//编码的函数
int Target_file(const HEAD head ,const char * source ,const char * target)
{
	FILE * src = fopen(source, "rb");
	FILE *tar = fopen(target, "wb");
	char cd[SIZE] = {0};
	int  ch; 
	for (int i = 0; i < 256; i++) {
		nSize += Code[i].weight * Code[i].len;
	}
	nSize = nSize % 8 ? (nSize >> 3) + 1 : nSize >> 3;
	char *buffer = new char[nSize + 1];
	memset(buffer, 0, sizeof(char) * (nSize + 1));
	int pos = 0;
	while ((ch=fgetc(src)) != EOF)
	{
		strcat(cd, Code[ch].post);
		while (strlen(cd) > 8)
		{
			buffer[pos++] = transform_byte(cd);
			for (int i = 0; i < SIZE- 8; i++)
				cd[i] = cd[i + 8];
		}
	}
	if (strlen(cd) > 0)
	{buffer[pos++] = transform_byte(cd);}
	fwrite(&head, sizeof(HEAD), 1, tar);
	fwrite(buffer, sizeof(char), nSize, tar);
	fclose(tar);
	fclose(src);
	int a = sizeof(head);
	return nSize+sizeof(HEAD);
}
//解码函数
int decode_file(HEAD de_head, const char *de_file, const char *success_file)
{
	HEAD *a = NULL; int ch; int count = 1; int my_lenth = 0;
	FILE * read = fopen(de_file, "rb");
	FILE *write = fopen(success_file, "wb");
	fread(&de_head, sizeof(de_head), 1, read);
	char *buffer = new  char[de_head.length + 1];
	char binary_buffer[1024] = {0};
	memset(buffer, 0, sizeof(char)*(de_head.length + 1));
	InitTree(&*Hftree, de_head.weight);
	BuildTree(&*Hftree);
	int pos = 0;
	while ((ch = getc(read)) != EOF)
	{
		strcat(binary_buffer, Hex_two(ch));
		my_lenth = strlen(binary_buffer);
		while (my_lenth >=8)
		{
		int i = 510;//根节点
		int j = 0;
		while (Hftree[i].leftchild != -1 && Hftree[i].rightchild != -1)
		{
			if (binary_buffer[j] == '0')
				i = Hftree[i].leftchild;
			else if (binary_buffer[j] == '1')
				i = Hftree[i].rightchild;
			j++;
		}
		buffer[pos++] = i;
		for (int k = 0; k < strlen(binary_buffer) - j; k++)
			binary_buffer[k] = binary_buffer[k + j];

		binary_buffer[strlen(binary_buffer) - j] = '\0';
			 my_lenth = strlen(binary_buffer);
		}
	}
	if (my_lenth > 0)
	{
		int i = 510;//根节点
		int j = 0;
		while (Hftree[i].leftchild != -1 && Hftree[i].rightchild != -1)
		{
			if (binary_buffer[j] == '0')
				i = Hftree[i].leftchild;
			else if (binary_buffer[j] == '1')
				i = Hftree[i].rightchild;
			j++;
		}
		buffer[pos++] = i;
		int changdu = strlen(binary_buffer) - j;

		for (int k = 0; k < strlen(binary_buffer) - j; k++)
			binary_buffer[k] = binary_buffer[k + j];

		binary_buffer[strlen(binary_buffer) - j] = '\0';
		my_lenth = strlen(binary_buffer);
	}
		
	buffer[pos] = '\0';
	fwrite(buffer, sizeof(char), de_head.length, write);
	fclose(read);
	fclose(write);
	return 1;
}
