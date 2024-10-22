// 哈夫曼压缩解码文件.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include"huffman.h"
#include"Scanner.h"
static int a = 0;
#pragma warning(disable:4996)
#include<iostream>
using namespace std;


int main()
{
	int count = 0; int choose = 0;
	char filename[256]; int ch; int weight[257] = { 0 };
	cout << "========哈夫曼文件压缩===========" << endl;
	cout << "选择操作 1. 压缩  2. 解压缩" << endl;
	cin >> choose;
	if (choose == 1) {
		cout << "输入文件的路径：";
		cin >> filename;
		FILE *in = fopen(filename, "rb");
		if (!in) { cout << "文件读取错误"; fclose(in); return 0; }
		else
		{
			ch = fgetc(in);
			while (ch != EOF)
			{
				count++;
				weight[ch]++;
				ch = fgetc(in);
			}
			fclose(in);
			//cout << "Byte" << "  weight" << endl;
			////显示256个字符的权值
			//for (int i = 0; i < 256; i++)
			//	printf("0x%02x %d\n", i, weight[i]);
		}
		for (int i = 0; i < 256; i++) {
			Code[i].weight = weight[i];
		}
		InitTree(&*Hftree, weight);
		BuildTree(&*Hftree);
		huf_code(&*Hftree,&*Code);
		//for (int j = 0; j < 512; j++)
		//	cout << j << "-->" << "       left:" << Hftree[j].leftchild << "    right:" << Hftree[j].rightchild << "   parent" << Hftree[j].parent << endl;
		HEAD head;
	//	for (int i = 0; i < 256; i++)
		//	cout << i << " " << Code[i].post << endl;
		init_head(filename, head);
		char tar[30] = { 0 };
		cout << "输入压缩的目标文件名称(例如-->  压缩文件.huf)" << endl;
		cin >> tar;
		int a = Target_file(head, filename, tar);
		cout << "压缩的比率是:";
		cout << endl;
		cout << "源文件的长度" << head.length << endl;
		cout << "--" << endl;
		cout << "压缩之后的长度：" << a << endl;
		double percent = a * 1.0 / head.length * 100;
		printf("%.2f %c", percent,'%');
		cout << endl;
		int input = 1;
		while (input)
		{
			cout << "输出压缩信息 1->哈夫曼树 2->权值 3->哈夫曼编码 0->退出" << endl;
			int In;
			cin >> In;
			switch (In)
			{
			case 1: {for (int j = 0; j < 512; j++)
				cout << j << "-->" << "       left:" << Hftree[j].leftchild << "    right:" << Hftree[j].rightchild << "   parent" << Hftree[j].parent << endl; break; }
			case 2: {	cout << "Byte" << "  weight" << endl;
				//显示256个字符的权值
				for (int i = 0; i < 256; i++)
					printf("0x%02x %d\n", i, weight[i]); break; }
			case 3: {
				for (int i = 0; i < 256; i++)
					cout << i << " " << Code[i].post << endl; break;
			}
			default:
			{input = 0; break; }

			}

		}
	}
	else
	{
		cout << "输入解压缩的文件路径" << endl;
		char src_name[30] = { 0 }; char tar_name[30] = { 0 };
		cin >> src_name;
		cout << "输入目标文件的路径(例如mypicture.bmp)包含文件类型的名称" << endl;
		cin >> tar_name;
		HEAD de_head; de_head.type[4] = {0}; de_head.length = 0; memset(de_head.weight, 0, sizeof(int) * 256);
		for (int i = 0; i < 256; i++) {
			Code[i].weight = weight[i];
		}
		 decode_file(de_head,src_name,tar_name);
		 cout << "解压缩成功" << endl;
	}
	system("pause");
    return 0;
}

