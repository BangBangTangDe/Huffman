#pragma once
#include<string>
#pragma warning (disable:4996)
//�����������ڵ�
typedef struct HTNode{
	int weight;
	int parent;
	int leftchild;
	int rightchild;
}; extern HTNode Hftree[512];
//����ַ��������Ϣ
typedef struct Store_Huf
{
	char a;
	int weight;
	char post[100];//�������
	char back[100];//�������
	int len;
};extern Store_Huf Code[256];
//�ļ�ͷ�ڵ�
struct HEAD
{
	char type[4];
	int length;
	int weight[256];
};
//�����б�
int  init_head(const char *filename, HEAD &head);
void InitTree(HTNode *Hftree, int weight[]);
void BuildTree(HTNode *Hftree);
void huf_code(HTNode *Hftree, Store_Huf *Code);
void show_code(char *a, int len);