#include"stdafx.h"
#define Max 999999
#define N 256
#define M 2*N-1
#include"huffman.h"
#include<iostream>
Store_Huf Code[256]; HTNode Hftree[512];
using namespace std;
//��ʼ���ļ�ͷ�ڵ�
int  init_head(const char *filename, HEAD &head)
{
	int ch;
	strcpy(head.type, "huf");
	head.length = 0;
	for (int i = 0; i < 256; i++)
		head.weight[i] = 0;
	FILE *in = fopen(filename, "rb");
	while ((ch = fgetc(in)) != EOF)
	{
		head.weight[ch]++;
		head.length++;
	}
	cout << "ͷ�ļ�����" << head.length << endl;
	fclose(in);
	in = NULL;
	return 1;
}

//��ʼ����������
void InitTree(HTNode *Hftree, int weight[])
{
	int i = 0;
	for (i = 0; i < M; i++)
	{
		if (i < N)
		{
			Hftree[i].weight = weight[i];
		}
		else
		{
		Hftree[i].weight = 0;
		}
		Hftree[i].parent = Hftree[i].rightchild = Hftree[i].leftchild = -1;
	}
}

//������������
void BuildTree(HTNode *Hftree)
{
	int x = 0; int y=0;
	//����������Ҫѭ��N-1��
	for (int i = 0; i < N-1; i++)
	{
		int min=Max;
		x = y = -1;
		//�ҳ���С�������㣬�����������
		//1.�ҳ���С�Ľڵ�
		for (int j = 0; j < i + N; j++)
		{
			if (Hftree[j].parent == -1 && Hftree[j].weight >= 0 && min > Hftree[j].weight)
			{
				min = Hftree[j].weight;
				x = j;
			}
		}
		//�ҵ��ڶ�С�ĵ㣬�����������
		min = Max;
		for (int j = 0; j < i + N; j++)
		{
			if(Hftree[j].parent == -1 && Hftree[j].weight >= 0 && j!=x && min > Hftree[j].weight)
			{
				min = Hftree[j].weight;
				y = j;
			}
		}
    //������������ڵ�
		Hftree[x].parent = Hftree[y].parent = i + N;
		Hftree[i + N].leftchild = x;
		Hftree[i + N].rightchild = y;
		Hftree[i + N].weight = Hftree[x].weight + Hftree[y].weight;
	
	}
	
}

//��������������
void huf_code(HTNode *Hftree, Store_Huf *Code)
{
	int i, j;
	int pos, parent, child;
	//���δӵ����ϱ���Ҷ�ӽڵ�ʵ��ÿһ��Ҷ�ӽڵ�ı���
	for (i = 0; i < N; i++)
	{
		pos = 0;
		child = i;
		parent = Hftree[child].parent;
		while (parent!=-1)
		{
			if (child == Hftree[parent].leftchild)
				Code[i].back[pos] = '0';
			else
				Code[i].back[pos] = '1';
			pos++;
			child = parent;
			parent = Hftree[child].parent;
		}
		Code[i].len = pos;
		//������������������뵽back������
		pos--;
		for (j = 0; j < Code[i].len; j++, pos--)
			Code[i].post[j] = Code[i].back[pos];
		Code[i].post[Code[i].len] = '\0';
	}
}

//������������ı���
void show_code(char *a, int len)
{
	for(int i=0;i<len;i++)
		cout<<a[i];
	cout << endl;
}

