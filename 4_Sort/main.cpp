#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Sort.cpp"

// 主函数
int main()
{
	LinkedList l;
	createList(&l);
	if (read("data.txt", l) == ERROR)
		return -1;

	float AnchorPoint[3] = {0, 0, 0};

	printf("\n********* 请输入比较的关键字类型​*********\n");
	printf("0:原key ");
	printf("1:欧式距离 ");
	printf("2:街区距离 ");
	printf("3:余弦距离）：");
	int nflag;
	scanf("%d", &nflag);

	if (nflag == 1)
		Euclideandistance(l, AnchorPoint);
	else if (nflag == 2)
		blockdistance(l, AnchorPoint);
	else if (nflag == 3)
		cosdistance(l);

	LinkedList RD = clone(l);
	RecType R[SIZE];
	int n = CreateList(RD, R);

	while (1)
	{
		printf("\n********* 排序选择 (按速度从快到慢) ​*********\n");
		printf("1. 快速排序 (最快)\n");
		printf("2. 希尔排序\n");
		printf("3. 插入排序\n");
		printf("4. 简单选择排序\n");
		printf("5. 冒泡排序 (最慢)\n");
		printf("6. 退出\n");
		printf("请输入选项 (1-6): ");

		int input;
		scanf("%d", &input);

		clock_t start = clock();
		switch (input)
		{
		case 1:
			QuickSort(R, 0, n - 1);
			saveData(R, n, "Quick_Sort.txt"); // 快速排序 (最快)
			break;
		case 2:
			ShellSort(R, n);
			saveData(R, n, "Shell_Sort.txt"); // 希尔排序
			break;
		case 3:
			InsertSort(R, n);
			saveData(R, n, "Insert_Sort.txt"); // 插入排序
			break;
		case 4:
			SelectSort(R, n);
			saveData(R, n, "Select_Sort.txt"); // 简单选择排序
			break;
		case 5:
			BubbleSort(R, n);
			saveData(R, n, "Bubble_Sort.txt"); // 冒泡排序 (最慢)
			break;
		case 6:
			exit(0);
		default:
			printf("无效输入，请重新输入 (1-6)！\n");
			continue;
		}
		clock_t finish = clock();
		double timeUsed = (double)(finish - start) / CLOCKS_PER_SEC;

		printf("排序后结果:\n");
		DispList(R, n);
		printf("排序耗时: %.9f 秒\n", timeUsed);
	}
	return OK;
}