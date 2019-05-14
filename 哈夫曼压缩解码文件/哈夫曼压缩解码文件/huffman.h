#pragma once
#include<string>
#pragma warning (disable:4996)
//哈夫曼的树节点
typedef struct HTNode{
	int weight;
	int parent;
	int leftchild;
	int rightchild;
}; extern HTNode Hftree[512];
//存放字符编码的信息
typedef struct Store_Huf
{
	char a;
	int weight;
	char post[100];//正序编码
	char back[100];//反序编码
	int len;
};extern Store_Huf Code[256];
//文件头节点
struct HEAD
{
	char type[4];
	int length;
	int weight[256];
};
//函数列表
int  init_head(const char *filename, HEAD &head);
void InitTree(HTNode *Hftree, int weight[]);
void BuildTree(HTNode *Hftree);
void huf_code(HTNode *Hftree, Store_Huf *Code);
void show_code(char *a, int len);