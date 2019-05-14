#include"stdafx.h"
#define Max 999999
#define N 256
#define M 2*N-1
#include"huffman.h"
#include<iostream>
Store_Huf Code[256]; HTNode Hftree[512];
using namespace std;
//初始化文件头节点
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
	cout << "头文件长度" << head.length << endl;
	fclose(in);
	in = NULL;
	return 1;
}

//初始化哈夫曼树
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

//构建哈夫曼树
void BuildTree(HTNode *Hftree)
{
	int x = 0; int y=0;
	//构建过程需要循环N-1次
	for (int i = 0; i < N-1; i++)
	{
		int min=Max;
		x = y = -1;
		//找出最小的两个点，构造哈夫曼树
		//1.找出最小的节点
		for (int j = 0; j < i + N; j++)
		{
			if (Hftree[j].parent == -1 && Hftree[j].weight >= 0 && min > Hftree[j].weight)
			{
				min = Hftree[j].weight;
				x = j;
			}
		}
		//找到第二小的点，构造哈夫曼树
		min = Max;
		for (int j = 0; j < i + N; j++)
		{
			if(Hftree[j].parent == -1 && Hftree[j].weight >= 0 && j!=x && min > Hftree[j].weight)
			{
				min = Hftree[j].weight;
				y = j;
			}
		}
    //构造哈夫曼树节点
		Hftree[x].parent = Hftree[y].parent = i + N;
		Hftree[i + N].leftchild = x;
		Hftree[i + N].rightchild = y;
		Hftree[i + N].weight = Hftree[x].weight + Hftree[y].weight;
	
	}
	
}

//构建哈夫曼编码
void huf_code(HTNode *Hftree, Store_Huf *Code)
{
	int i, j;
	int pos, parent, child;
	//依次从底向上遍历叶子节点实现每一个叶子节点的编码
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
		//将反序的内容正序输入到back数组中
		pos--;
		for (j = 0; j < Code[i].len; j++, pos--)
			Code[i].post[j] = Code[i].back[pos];
		Code[i].post[Code[i].len] = '\0';
	}
}

//输出哈夫曼树的编码
void show_code(char *a, int len)
{
	for(int i=0;i<len;i++)
		cout<<a[i];
	cout << endl;
}

