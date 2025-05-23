#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h> // 引入windows.h头文件以支持控制台编码设置

#define OK 0
#define ERROR -1
#define MAXSIZE 1000

using namespace std;

// 定义结构体
typedef struct
{
    char data;
    int weight;
    int parent, lch, rch;
} ZYCNode, *HuffmanTree;

// 动态分配数组存储霍夫曼编码
typedef char **HuffmanCode;

// 初始化哈夫曼树
void InitHuffmanTree(HuffmanTree &HT, int n)
{
    if (n <= 1)
        return;

    int m = 2 * n - 1;
    HT = new ZYCNode[m + 1]; // 0号单元用来存放根节点位置
    for (int i = 1; i <= m; ++i)
    {
        HT[i].parent = 0;
        HT[i].lch = 0;
        HT[i].rch = 0;
    }
}

// 选择出最小的两个结点
void select(HuffmanTree &HT, int n, int &s1, int &s2)
{
    int min1 = MAXSIZE, min2 = MAXSIZE; // 先赋予最大值
    for (int i = 1; i <= n; i++)
    {
        if (HT[i].weight < min1 && HT[i].parent == 0)
        {
            min1 = HT[i].weight;
            s1 = i;
        }
    }
    int temp = HT[s1].weight; // 将原值存放起来，然后先赋予最大值，防止s1被重复选择
    HT[s1].weight = MAXSIZE;
    for (int i = 1; i <= n; i++)
    {
        if (HT[i].weight < min2 && HT[i].parent == 0)
        {
            min2 = HT[i].weight;
            s2 = i;
        }
    }
    HT[s1].weight = temp; // 恢复原来的值
}

// 构造HuffmanTree
void CreatHuffmanTree(HuffmanTree &HT, int n)
{
    int m, s1, s2;

    if (n <= 1)
        return;

    m = 2 * n - 1;
    for (int i = n + 1; i <= m; ++i)
    { // 通过n-1次的选择、删除、合并来创建赫夫曼树
        select(HT, i - 1, s1, s2);
        // 在HT[k](1≤k≤i-1)中选择两个其双亲域为0且权值最小的结点,
        // 并返回它们在HT中的序号s1和s2
        HT[s1].parent = i;
        HT[s2].parent = i;

        HT[i].lch = s1;
        HT[i].rch = s2;                               // s1,s2分别作为i的左右孩子
        HT[i].weight = HT[s1].weight + HT[s2].weight; // i 的权值为左右孩子权值之和
    }
    HT[0].data = m; // 将根节点的编号，存入HT[0].data中
}

// 构造HuffmanTree编码
void CreatHuffmanCode(HuffmanTree HT, HuffmanCode &HC, int n)
{
    // 从叶子到根逆向求每个字符的赫夫曼编码，存储在编码表HC中
    HC = new char *[n + 1];
    char *cd = new char[n]; // 分配临时存放编码的动态数组空间，长度为n
    cd[n - 1] = '\0';       // 编码结束符

    for (int i = 1; i <= n; ++i)
    {                      // 逐个字符求赫夫曼编码
        int start = n - 1; // 初始化start，指向编码的最后一个位置
        int c = i;
        int f = HT[i].parent;

        while (f != 0)
        {            // 从叶子结点开始向上回溯，直到根结点
            start--; // 回溯一次start向前指一个位置
            if (HT[f].lch == c)
            {
                cd[start] = '0'; // 结点c是f的左孩子，则生成代码0
            }
            else
            {
                cd[start] = '1'; // 结点c是f的右孩子，则生成代码1
            }
            c = f;
            f = HT[f].parent; // 继续向上回溯
        }

        // 编码的实际长度是从start到n-1的部分
        int length = n - start - 1; // 编码的长度（不包括结束符）

        // 为第i个字符编码分配足够的空间，并加上'\0'作为结束符
        HC[i] = new char[length + 1];
        strcpy(HC[i], &cd[start]); // 将求得的编码从临时空间cd复制到HC的当前行中
    }

    delete[] cd; // 释放临时空间
}

// 显示Huffman编码,并储存
void showHuffmanTree(HuffmanTree HT, HuffmanCode HC, int n, char *data, char *show)
{
    int index = 0;

    for (int i = 0; i < n; i++)
    {
        int j = 1; // 0号单元未用
        // 查找当前数据对应的哈夫曼树节点
        while (j <= n && data[i] != HT[j].data)
        {
            j++;
        }
        if (j > n)
        {
            printf("错误: 数据 %c 不在哈夫曼树里面\n", data[i]);
            continue;
        }
        // 将哈夫曼编码复制到 show 数组中
        strcpy(show + index, HC[j]);
        index += strlen(HC[j]);
    }
    show[index] = '\0'; // 添加结束标志
    printf("Huffman编码是: %s\n", show);
}

// Huffman解码
void HuffmanDecode(HuffmanTree HT, char *show)
{
    int i, j = 0;
    char end = '\0';    // 电文结束标志取'\0'
    int m = HT[0].data; // 根节点序号
    i = m;              // 从根结点开始往下搜索

    printf("Huffman解码是: ");

    while (show[j] != end)
    {
        if (show[j] == '0')
            i = HT[i].lch; // 走向左孩子
        else
            i = HT[i].rch; // 走向右孩子

        if (HT[i].lch == 0 || HT[i].rch == 0) // HT[i]是叶结点
        {
            printf("%c ", HT[i].data);
            i = m; // 回到根结点
        }
        j++;
    }
    printf("\n");
}

// 读取文件+频数统计
int read(const char *name, int n, char *data, char *Data, int *weight, int &length)
{

    for (int x = 0; x < n; x++)
    {
        data[x] = '\0';
        weight[x] = 0;
    }

    int i = 0, x = 0;
    int result = 0;
    FILE *fp = fopen(name, "r");
    if (fp == NULL)
    {
        puts("不能打开文件！\n");
        return ERROR;
    }

    char buffer[256];
    if (fgets(buffer, sizeof(buffer), fp))
    {
        char *p = strtok(buffer, ",\n");
        while (p != NULL && x < 100)
        {
            Data[x++] = *p;
            length++;

            int found = 0;
            for (int j = 0; j < i; j++)
            {
                if (data[j] == *p)
                {
                    weight[j]++;
                    found = 1;
                    break;
                }
            }

            if (!found && i < n)
            {
                data[i] = *p;
                weight[i] = 1;
                i++;
            } // 若不存在，就需要把这个新字符记录下来，并为其设置初始权重为 1

            p = strtok(NULL, ",\n");
        }
    }
    fclose(fp);
    return OK;
}

// 快速排序
void quickSort(char *data, int *weight, int left, int right)
{
    if (left >= right)
        return;

    char pivot = data[(left + right) / 2];

    int i = left, j = right;

    while (i <= j)
    {
        while (data[i] < pivot)
            i++;
        while (data[j] > pivot)
            j--;
        if (i <= j)
        {
            swap(data[i], data[j]);
            swap(weight[i], weight[j]);
            i++;
            j--;
        }
    }

    quickSort(data, weight, left, j);
    quickSort(data, weight, i, right);
}

void replaceContent(const char *filename)
{
    // 获取用户输入的旧字符串和新字符串
    char oldStr[256], newStr[256];
    printf("请输入要替换的旧字符串: ");
    fgets(oldStr, sizeof(oldStr), stdin);
    oldStr[strcspn(oldStr, "\n")] = '\0'; // 去掉换行符

    printf("请输入要替换的新字符串: ");
    fgets(newStr, sizeof(newStr), stdin);
    newStr[strcspn(newStr, "\n")] = '\0'; // 去掉换行符

    // 打开文件进行读取
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("无法打开文件 %s\n", filename);
        return;
    }

    // 读取文件内容到buffer
    char buffer[1024]; // 使用更大的buffer避免读取内容被截断
    size_t len = fread(buffer, sizeof(char), sizeof(buffer) - 1, file);
    buffer[len] = '\0'; // 确保buffer是一个以null结尾的字符串
    fclose(file);

    // 目标文件数据的替换操作
    char temp[1024];
    char *pos, *start = buffer;
    temp[0] = '\0';

    // 替换字符串
    while ((pos = strstr(start, oldStr)) != NULL)
    {
        strncat(temp, start, pos - start); // 将原始内容复制到temp
        strcat(temp, newStr);              // 添加新字符串
        start = pos + strlen(oldStr);      // 跳过旧字符串部分
    }
    strcat(temp, start); // 追加剩余部分

    // 将替换后的内容写回到文件
    file = fopen(filename, "w");
    if (!file)
    {
        printf("无法写入文件 %s\n", filename);
        return;
    }
    fputs(temp, file);
    fclose(file);

    printf("文件内容已成功替换。\n");
}

void setConsoleUTF8()
{
    SetConsoleOutputCP(CP_UTF8); // 设置输出编码为 UTF-8
    SetConsoleCP(CP_UTF8);       // 设置输入编码为 UTF-8
}

void showWelcomeScreen()
{
    cout << "========================================\n";
    cout << "        欢迎来到哈夫曼树系统\n";
    cout << "========================================\n";
    cout << "        作者：赵言诚（Miachel）\n";
    cout << "        日期：2025年\n";
    cout << "        版本：v1.0\n";
    cout << "========================================\n\n";
    cout << "根据提示键使用本系统...\n";
    cin.ignore(); // 防止输入缓冲区残留
    cin.get();    // 等待用户按下回车键继续
}