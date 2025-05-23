#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define SIZE 5000 // 数据量

int main()
{
	int ID[SIZE];		 // 存储ID
	float data[SIZE][4]; // 存储4列浮点数数据
	int i, j;

	// 1. 初始化ID（倒序：1000, 999, ..., 1）
	for (i = 0; i < SIZE; i++)
	{
		ID[i] = SIZE - i;
	}

	// 2. 初始化随机种子
	srand(time(0));

	// 3. 生成随机数据
	for (i = 0; i < SIZE; i++)
	{
		data[i][0] = (float)(i + 1); // 第1列：顺序值 (1.0 ~ 1000.0)
		for (j = 1; j < 4; j++)
		{
			// 第2~4列：随机浮点数 (1.0 ~ 1001.0)
			data[i][j] = 1.0 + 1000.0 * rand() / (RAND_MAX + 1.0);
		}
	}

	// 4. 写入文件（严格按你的格式要求）
	FILE *fp = fopen("data.txt", "w");
	if (!fp)
	{
		perror("无法打开文件");
		return 1;
	}

	for (i = 0; i < SIZE; i++)
	{
		// 格式：ID, Key, Item1, Item2, Item3（用逗号+制表符分隔）
		fprintf(fp, "%d,\t%.6f,\t%.6f,\t%.6f,\t%.6f\n",
				ID[i], data[i][0], data[i][1], data[i][2], data[i][3]);
	}

	fclose(fp);
	printf("数据已生成到 data.txt，格式严格匹配要求。\n");
	return 0;
}