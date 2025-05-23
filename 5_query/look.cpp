#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <time.h>
#define ERROR -1
#define OK 0
#define size 999
#define NULLKEY -56465 // 空关键字

typedef struct
{
    int ID;
    float key;
    float item1;
    float item2;
    float item3;
} RecType;

// 定义链表结构体
typedef struct Node
{
    RecType data;
    struct Node *next;
} Node, *LinkedList;

// 追加元素
int listAppend(LinkedList &l, float e[], int ID, float key)
{
    LinkedList p = l, s;
    if (p == NULL)
    {
        return ERROR;
    }
    else
    {
        while (p->next != NULL)
        {
            p = p->next;
        }
        s = (LinkedList)malloc(sizeof(Node));
        s->data.ID = ID;
        s->data.key = key;
        s->data.item1 = e[0];
        s->data.item2 = e[1];
        s->data.item3 = e[2];
        s->next = NULL;
        p->next = s;
        return OK;
    }
}

// 读取文件
int read(char *name, LinkedList &l)
{
    FILE *fp = fopen(name, "r");
    float e[3], key = 0;
    int ID;
    if (fp == NULL)
    {
        puts("无法打开文件\n");
        return ERROR;
    }
    while (!feof(fp))
    {
        fscanf(fp, "%d,\t", &ID);
        fscanf(fp, "%f,\t", &key);
        fscanf(fp, "%f,\t", &e[0]);
        fscanf(fp, "%f,\t", &e[1]);
        fscanf(fp, "%f\n", &e[2]);
        listAppend(l, e, ID, key);
    }
    fclose(fp);
    return OK;
}

// 初始化链表
void createList(LinkedList &l)
{
    l = (LinkedList)malloc(sizeof(Node));
    l->next = NULL;
}

// 考虑到链表遍历的复杂度较高，不适合频繁增删改查，所以读取时先转换为顺序表
// 欧式距离
void Euclideandistance(LinkedList l, float AnchorPoint[3])
{
    Node *s = l;
    while (l != NULL)
    {
        float tmpD = ((AnchorPoint[0] - l->data.item1) * (AnchorPoint[0] - l->data.item1) + (AnchorPoint[1] - l->data.item2) * (AnchorPoint[1] - l->data.item2) + (AnchorPoint[2] - l->data.item3) * (AnchorPoint[2] - l->data.item3));
        l->data.key = sqrt(tmpD);
        l = l->next;
    }
    l = s;
    // delete s;
}

// 街区距离
void blockdistance(LinkedList l, float AnchorPoint[3])
{
    Node *s = l;
    while (l != NULL)
    {
        float tmpD = (fabs(AnchorPoint[0] - l->data.item1) + fabs(AnchorPoint[1] - l->data.item2) + fabs(AnchorPoint[2] - l->data.item3));
        l->data.key = tmpD;
        l = l->next;
    }
    l = s;
    // delete s;
}

// 余弦距离
void cosdiatance(LinkedList l)
{
    Node *s = l;
    float AnchorPoint[3];
    AnchorPoint[0] = 1;
    AnchorPoint[1] = 0;
    AnchorPoint[2] = 0;
    while (l != NULL)
    {
        float tmpD1 = (AnchorPoint[0] * l->data.item1 + AnchorPoint[1] * l->data.item2 + AnchorPoint[2] * l->data.item3);
        float tmpD2 = (AnchorPoint[0] * AnchorPoint[0] + AnchorPoint[1] * AnchorPoint[1] + AnchorPoint[2] * AnchorPoint[2]) * (l->data.item1 * l->data.item1 + l->data.item2 * l->data.item2 + l->data.item3 * l->data.item3);
        float tmpD = tmpD1 / sqrt(tmpD2);
        tmpD = ((float)((int)(tmpD * 1000000))) / 1000000; // 这里保留小数点后6位以便比较，不然系统默认float型保留6~7位会有比较失败的情况
        l->data.key = tmpD;
        l = l->next;
    }
    l = s;
    // delete s;
}

// 克隆链表
LinkedList clone(LinkedList l)
{
    LinkedList RD;
    RD = (LinkedList)malloc(sizeof(Node));
    Node *s = NULL, *r = RD, *p = l->next;
    while (p != NULL)
    {
        s = (LinkedList)malloc(sizeof(Node));
        s->data = p->data;
        r->next = s;
        r = s;
        p = p->next;
    }
    r->next = NULL;
    return RD;
}

// 考虑到内部操作不需要频繁增删改查，所以转换为顺序表比较方便
// 链表转换为数组
void CreateList(LinkedList RD, RecType R[]) // 创建顺序表,需要用于链表结点的值比较，ID值默认为序号，比较即为key值
{
    Node *s = RD->next;
    int i = 0;
    while (s != NULL && i < size)
    {
        R[i].key = s->data.key;
        R[i].ID = s->data.ID;
        R[i].item1 = s->data.item1;
        R[i].item2 = s->data.item2;
        R[i].item3 = s->data.item3;
        s = s->next;
        i++;
    }
}

void DispList(RecType R[]) // 输出顺序表
{
    for (int i = 0; i < size; i++)
        printf("key=%f,ID=%d,item1=%f,item2=%f,item3=%f \n", R[i].key, R[i].ID, R[i].item1, R[i].item2, R[i].item3);
}

// 冒泡排序
void BubbleSort(RecType R[], int len)
{
    int i;
    int j;
    RecType temp;
    for (i = 0; i < len; i++) // 比较次数
    {
        for (j = len - 1; j > i; j--)
        {
            if (R[j - 1].key > R[j].key) // 比较大小
            {
                temp = R[j];
                R[j] = R[j - 1];
                R[j - 1] = temp;
            }
        }
    }
}

// 折半查找
void Bin_Search(RecType R[], int n, float k) //(k为查找值)
{
    int low = 0;
    int high = n - 1;
    int count = 0;
    while (low <= high)
    {
        int mid = (low + high) / 2;
        printf("第%d次比较，在[%d,%d]中比较元素R[%d]:%f\n", ++count, low, high, mid, k);
        if (R[mid].key < k)
        {
            low = mid + 1;
        }
        else if (R[mid].key > k)
        {
            high = mid - 1;
        }
        else
        {
            printf("关键字%f的查询结果如下\n", k);
            printf("位置为R[%d]:key=%f,ID=%d,item1=%f,item2=%f,item3=%f\n", mid, R[mid].key, R[mid].ID, R[mid].item1, R[mid].item2, R[mid].item3);
            int tmp1 = mid + 1;
            int tmp2 = mid - 1;
            while (tmp1 < n && R[tmp1].key == k)
            {
                printf("位置为R[%d]:key=%f,ID=%d,item1=%f,item2=%f,item3=%f\n", tmp1, R[tmp1].key, R[tmp1].ID, R[tmp1].item1, R[tmp1].item2, R[tmp1].item3);
                tmp1++;
            }
            while (tmp2 >= 0 && R[tmp2].key == k)
            {
                printf("位置为R[%d]:key=%f,ID=%d,item1=%f,item2=%f,item3=%f\n", tmp2, R[tmp2].key, R[tmp2].ID, R[tmp2].item1, R[tmp2].item2, R[tmp2].item3);
                tmp2--;
            }
            break;
        }
    }
    if (low > high)
    {
        printf("没有找到%f\n", k);
    }
}

/***************************动态查找表****************************/
using namespace std;
typedef struct BSTNode
{
    RecType data;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

// 在T中查找关键字值为 k 的结点，找到返回1，*p指向该结点，*f为*p双亲结点；否则返回0
int SearchBST(BSTree T, RecType k, BSTree *p, BSTree *f)
{
    *p = T;
    *f = NULL;
    while (*p)
    {
        if ((*p)->data.key == k.key)
            return 1;
        else
        {
            *f = *p;
            if (k.key < (*p)->data.key)
                *p = (*p)->lchild;
            else
                *p = (*p)->rchild;
        }
    }
    return 0;
}

// 插入结点
void InsertBST(BSTree &T, RecType k)
{
    BSTree p, f, s;
    if (!SearchBST(T, k, &p, &f))
    {
        s = (BSTNode *)malloc(sizeof(BSTNode));
        s->data = k;
        s->lchild = NULL;
        s->rchild = NULL;
        if (!T)
            T = s;
        else if (k.key < f->data.key)
            f->lchild = s;
        else
            f->rchild = s;
    }
}

// 创建二叉排序树（中序遍历有序）
void CreateBST(BSTree &T, RecType R[])
{
    T = NULL;
    for (int i = 0; i < size; i++)
    {
        InsertBST(T, R[i]);
    }
}

// 中序遍历BST
void TraverseBST(BSTree T)
{
    if (T)
    {
        TraverseBST(T->lchild);
        printf("%f,%d,%f,%f,%f \n", T->data.key, T->data.ID, T->data.item1, T->data.item2, T->data.item3);
        TraverseBST(T->rchild);
    }
}

// 删除T中关键字值为 k 的结点
void DeleteBST(BSTree &T, RecType k)
{
    BSTree p, f, s, q;
    p = T;
    f = NULL;
    while (p && p->data.key != k.key)
    {
        f = p;
        if (k.key < p->data.key)
            p = p->lchild;
        else
            p = p->rchild;
    }
    if (!p)
        return;
    if (!p->lchild && !p->rchild)
    {
        if (f)
        {
            if (f->lchild == p)
                f->lchild = NULL;
            else
                f->rchild = NULL;
        }
        else
            T = NULL;
        free(p);
    }
    else if (!p->lchild || !p->rchild)
    {
        q = p->lchild ? p->lchild : p->rchild;
        if (f)
        {
            if (f->lchild == p)
                f->lchild = q;
            else
                f->rchild = q;
        }
        else
            T = q;
        free(p);
    }
    else
    {
        s = p->lchild;
        while (s->rchild)
        {
            f = s;
            s = s->rchild;
        }
        p->data = s->data;
        if (f != p)
            f->rchild = s->lchild;
        else
            p->lchild = s->lchild;
        free(s);
    }
}

// 查找
int SearchBST_Recursive(BSTree T, float k, BSTree *p, BSTree *f)
{
    if (!T)
    {
        printf("查找失败：未找到关键字 %f\n", k);
        return 0;
    }
    if (k == T->data.key)
    {
        printf("查找成功：\n");
        printf("关键字%f的查询结果如下\n", k);
        printf("key=%f,ID=%d,item1=%f,item2=%f,item3=%f\n", T->data.key, T->data.ID, T->data.item1, T->data.item2, T->data.item3);
        *p = T;
        return 1;
    }
    else if (k < T->data.key)
        return SearchBST_Recursive(T->lchild, k, p, &T);
    else
        return SearchBST_Recursive(T->rchild, k, p, &T);
}
/***************************动态查找表****************************/

/***************************哈希查找表****************************/
typedef struct
{
    RecType data;
    int count;
} HashTable;

// 初始化散列表
void InitHashTable(HashTable ha[])
{
    for (int i = 0; i < size; i++)
        ha[i].data.key = NULLKEY;
}

// 计算哈希函数
void hashfun(RecType R[], int tmpkey[], float m) // 将对应关键字转换为整数存入tmpkey，作为哈希表的存储地址，tmpkey和R下标一致
{
    for (int i = 0; i < size; i++)
    {
        tmpkey[i] = (int)fmod(R[i].key, m); // m为除数，fmod为浮点数取模，(int)强制转换为整数
        if (tmpkey[i] == 0)
            tmpkey[i] = m; // 使关键字为m的，存储地址为m
    }
}

// 将关键字存入哈希表
void insertHash(HashTable ha[], RecType R[], int tmpkey[])
{
    for (int i = 0; i < size; i++)
    {
        int j = 1;
        int adress = tmpkey[i];
        while (ha[adress].data.key != NULLKEY) // 地址不为空，则冲突
        {
            adress = (int)fmod((adress + 1), size); // 开放定址法线性探测
            j++;
        }
        ha[adress].data = R[i]; // 直接有空位存入关键字
        ha[adress].count = j;
    }
}

// 显示哈希表
void showHash(HashTable ha[])
{
    printf("显示哈希表如下：\n");
    for (int i = 0; i < size; i++)
    {
        //		printf("key=%f,ID=%d,item1=%f,item2=%f,item3=%f  ",ha[i].data.key,ha[i].data.ID,ha[i].data.item1,ha[i].data.item2,ha[i].data.item3);
        printf("地址：%d  关键字：key=%f  探测次数：%d\n", i, ha[i].data.key, ha[i].count);
    }
}

// 哈希表查找关键字
int searchHash(HashTable ha[], float key, float m)
{
    int j = 0;
    int adress = (int)fmod(key, m); // 计算哈希地址
    while (ha[adress].data.key != key && ha[adress].data.key != NULLKEY && j < size)
    {
        j++;
        adress = (int)fmod((adress + 1), size); // 开放定址法线性探测
    }
    if (ha[adress].data.key == key)
    {
        printf("查找成功!\n");
        printf("关键字%f的查询结果如下\n", key);
        printf("key=%f,ID=%d,item1=%f,item2=%f,item3=%f\n", ha[adress].data.key, ha[adress].data.ID, ha[adress].data.item1, ha[adress].data.item2, ha[adress].data.item3);
        return adress;
    }
    else
    {
        printf("查找失败：未找到关键字 %f\n", key);
        return -1;
    }
}

// 计算平均查找长度
void aslHash(HashTable ha[])
{
    int asl;
    int temp = 0;
    for (int i = 0; i < size; i++)
        temp = temp + ha[i].count;
    asl = temp / size;
    printf("平均查找长度ASL(1000)=%d\n", asl);
}

// 保存哈希表
int saveData(HashTable ha[], char *name)
{
    FILE *fp = fopen(name, "w");
    if (NULL == fp)
    {
        printf("无法打开文件\n");
        return ERROR;
    }
    for (int i = 0; i < size; i++)
    {
        fprintf(fp, "地址：%d  关键字：key=%f  探测次数：%d\n", i, ha[i].data.key, ha[i].count);
    }
    fclose(fp);
    return OK;
}
/***************************哈希查找表****************************/