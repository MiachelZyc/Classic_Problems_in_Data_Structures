#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#define ERROR -1
#define OK 0
#define SIZE 5000

typedef struct
{
    int ID;
    float key;
    float item1;
    float item2;
    float item3;
} RecType;

// 链表结点类型
typedef struct Node
{
    RecType data;
    struct Node *next;
} Node, *LinkedList;

// 初始化链表
void createList(LinkedList *l)
{
    *l = (LinkedList)malloc(sizeof(Node));
    if (*l != NULL)
    {
        (*l)->next = NULL;
    }
}

// 插入元素
int listAppend(LinkedList l, float e[], int ID, float key)
{
    LinkedList p = l;
    while (p->next != NULL)
    {
        p = p->next;
    }
    LinkedList s = (LinkedList)malloc(sizeof(Node));
    if (!s)
        return ERROR;
    s->data.ID = ID;
    s->data.key = key;
    s->data.item1 = e[0];
    s->data.item2 = e[1];
    s->data.item3 = e[2];
    s->next = NULL;
    p->next = s;
    return OK;
}

// 读取文件
int read(const char *name, LinkedList l)
{
    FILE *fp = fopen(name, "r");
    float e[3], key;
    int ID;
    if (fp == NULL)
    {
        puts("不能打开文件！");
        return ERROR;
    }
    while (fscanf(fp, "%d,%f,%f,%f,%f", &ID, &key, &e[0], &e[1], &e[2]) == 5)
    {
        listAppend(l, e, ID, key);
    }
    fclose(fp);
    return OK;
}

// 欧几里得距离
void Euclideandistance(LinkedList l, float AnchorPoint[3])
{
    Node *p = l->next;
    while (p != NULL)
    {
        float d = powf(AnchorPoint[0] - p->data.item1, 2) +
                  powf(AnchorPoint[1] - p->data.item2, 2) +
                  powf(AnchorPoint[2] - p->data.item3, 2);
        p->data.key = sqrtf(d);
        p = p->next;
    }
}

// 曼哈顿距离
void blockdistance(LinkedList l, float AnchorPoint[3])
{
    Node *p = l->next;
    while (p != NULL)
    {
        float d = fabsf(AnchorPoint[0] - p->data.item1) +
                  fabsf(AnchorPoint[1] - p->data.item2) +
                  fabsf(AnchorPoint[2] - p->data.item3);
        p->data.key = d;
        p = p->next;
    }
}

// 余弦距离
void cosdistance(LinkedList l)
{
    Node *p = l->next;
    float AnchorPoint[3] = {1, 0, 0}; // 默认向量
    while (p != NULL)
    {
        float dot = AnchorPoint[0] * p->data.item1 + AnchorPoint[1] * p->data.item2 + AnchorPoint[2] * p->data.item3;
        float normA = sqrtf(AnchorPoint[0] * AnchorPoint[0] + AnchorPoint[1] * AnchorPoint[1] + AnchorPoint[2] * AnchorPoint[2]);
        float normB = sqrtf(p->data.item1 * p->data.item1 + p->data.item2 * p->data.item2 + p->data.item3 * p->data.item3);
        if (normB == 0)
            p->data.key = 1.0;
        else
            p->data.key = 1.0f - (dot / (normA * normB)); // 转为“距离”形式
        p = p->next;
    }
}

// 复制链表
LinkedList clone(LinkedList l)
{
    LinkedList RD, tail, newNode;
    RD = (LinkedList)malloc(sizeof(Node));
    RD->next = NULL;
    tail = RD;

    Node *p = l->next;
    while (p != NULL)
    {
        newNode = (LinkedList)malloc(sizeof(Node));
        newNode->data = p->data;
        newNode->next = NULL;
        tail->next = newNode;
        tail = newNode;
        p = p->next;
    }
    return RD;
}

// 链表转数组
int CreateList(LinkedList l, RecType R[])
{
    int i = 0;
    Node *p = l->next;
    while (p != NULL && i < SIZE)
    {
        R[i++] = p->data;
        p = p->next;
    }
    return i;
}

// 显示顺序表
void DispList(RecType R[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("key=%f, ID=%d, item1=%f, item2=%f, item3=%f\n", R[i].key, R[i].ID, R[i].item1, R[i].item2, R[i].item3);
    }
}

// 保存文件
int saveData(RecType R[], int n, const char *name)
{
    FILE *fp = fopen(name, "w");
    if (!fp)
    {
        printf("无法打开文件\n");
        return ERROR;
    }
    fprintf(fp, "key\tID\titem1\titem2\titem3\n");
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%f\t%d\t%f\t%f\t%f\n", R[i].key, R[i].ID, R[i].item1, R[i].item2, R[i].item3);
    }
    fclose(fp);
    return OK;
}
/*---------------------------------------------------------
排序算法
-----------------------------------------------------------*/

// 希尔排序
void ShellSort(RecType R[], int n)
{
    RecType temp;
    for (int d = n / 2; d > 0; d /= 2)
    {
        for (int i = d; i < n; i++)
        {
            temp = R[i];
            int j;
            for (j = i - d; j >= 0 && R[j].key > temp.key; j -= d)
            {
                R[j + d] = R[j];
            }
            R[j + d] = temp;
        }
    }
}

// 冒泡排序
void BubbleSort(RecType R[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (R[j - 1].key > R[j].key)
            {
                RecType temp = R[j];
                R[j] = R[j - 1];
                R[j - 1] = temp;
            }
        }
    }
}

// 快速排序
int Partition(RecType R[], int low, int high)
{
    RecType pivot = R[low];
    while (low < high)
    {
        while (low < high && R[high].key >= pivot.key)
            high--;
        R[low] = R[high];
        while (low < high && R[low].key <= pivot.key)
            low++;
        R[high] = R[low];
    }
    R[low] = pivot;
    return low;
}

void QuickSort(RecType R[], int low, int high)
{
    if (low < high)
    {
        int pivot = Partition(R, low, high);
        QuickSort(R, low, pivot - 1);
        QuickSort(R, pivot + 1, high);
    }
}

// 简单选择排序
void SelectSort(RecType R[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
        {
            if (R[j].key < R[min].key)
            {
                min = j;
            }
        }
        if (min != i)
        {
            RecType temp = R[i];
            R[i] = R[min];
            R[min] = temp;
        }
    }
}

// 插入排序
void InsertSort(RecType R[], int n) // 对R[0..n-1]按递增序进行直接插入排序
{
    int i, j;
    RecType tmp;

    for (i = 1; i < n; ++i)
    {
        if (R[i].key < R[i - 1].key) // 需要将R[i]插入有序子表
        {
            tmp = R[i]; // 暂存待插入元素
            j = i - 1;

            // 查找插入位置的同时移动元素
            while (j >= 0 && R[j].key > tmp.key)
            {
                R[j + 1] = R[j]; // 记录后移
                j--;
            }
            R[j + 1] = tmp; // 插入到正确位置
        }
    }
}
