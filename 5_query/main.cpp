#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <algorithm>
#include <iostream>
#include <math.h>
#include <time.h>
#include "look.cpp"

// 假设OK是一个已经定义的常量
#define OK 1

// 主函数
int main()
{
    int result;
    LinkedList l;
    createList(l);
    char data[] = "data.txt";
    read(data, l);

    // 参考点(欧式距离、街区距离)
    float AnchorPoint[3];
    AnchorPoint[0] = 0;
    AnchorPoint[1] = 0;
    AnchorPoint[2] = 0;

    // 选择比较关键字类型
    int nflag;
    printf("请选择比较的关键字类型（0取文件；1欧式距离；2街区距离；3余弦距离）：");
    scanf("%d", &nflag);
    if (nflag == 1)
        Euclideandistance(l, AnchorPoint); // 欧式距离
    else if (nflag == 2)
        blockdistance(l, AnchorPoint); // 街区距离
    else if (nflag == 3)
        cosdiatance(l); // 余弦距离

    // 克隆链表
    LinkedList RD;
    RD = clone(l);

    // 转换为数组
    RecType R[size];
    CreateList(RD, R);

    // 时间复杂度
    clock_t start, finish; // 记录第一次调用CPU时钟的单位时间，实际上，它们是以毫秒为单位
    double Total_time;     // 定义一个double类型的变量，用于存储时间单位

    // 显示待查找的顺序表
    DispList(R);
    while (1)
    {
        printf("**********************************\n");
        printf("*    1.折半查找                  *\n");
        printf("*    2.动态查找表（二叉排序树）  *\n");
        printf("*    3.哈希查找表                *\n");
        printf("*    4.退出                      *\n");
        printf("**********************************\n");
        printf("开始操作吧，请输入相应数字\n");
        int input;
        scanf("%d", &input);
        switch (input)
        {
        case 1:
            BubbleSort(R, size);
            // 查找关键字
            float k;
            printf("请输入要查找的关键字：");
            scanf("%f", &k);
            start = clock();
            Bin_Search(R, size, k); // 折半查找
            finish = clock();
            Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("折半查找(耗时=%f秒):\n", Total_time);
            break;
        case 2:
        { // 动态查找表（二叉排序树）
            BSTree T, p, f;
            CreateBST(T, R);
            int s;
            printf("是否对查找表进行操作（0是，-1否）？");
            scanf("%d", &s);
            if (s == 0)
            {
                while (1)
                {
                    printf("********************************\n");
                    printf("*   a.插入结点                 *\n");
                    printf("*   b.删除结点                 *\n");
                    printf("*   c.打印查找表               *\n");
                    printf("*   d.返回                     *\n");
                    printf("********************************\n");
                    printf("请输入相应字母                    \n");
                    char input1;
                    scanf(" %c", &input1);
                    switch (input1)
                    {
                    case 'a':
                        // 插入结点
                        RecType m;
                        printf("请输入要插入的结点（以key+空格+ID+空格+item1+空格+item2+空格+item3）:\n");
                        scanf("%f %d %f %f %f", &m.key, &m.ID, &m.item1, &m.item2, &m.item3);
                        InsertBST(T, m);
                        printf("插入成功\n");
                        break;
                    case 'b':
                        // 删除结点
                        RecType n;
                        printf("请输入要删除的结点（以key+空格+ID+空格+item1+空格+item2+空格+item3）:\n");
                        scanf("%f %d %f %f %f", &n.key, &n.ID, &n.item1, &n.item2, &n.item3);
                        DeleteBST(T, n);
                        printf("删除成功\n");
                        break;
                    case 'c':
                        TraverseBST(T);
                        break;
                    case 'd':
                        goto flag;
                    default:
                        printf("输入错误，请重新输入\n");
                        break;
                    }
                }
            }
        flag:
            float searchKey;
            printf("请输入要查找的关键字：");
            scanf("%f", &searchKey);
            start = clock();
            int found = SearchBST_Recursive(T, searchKey, &p, &f);
            finish = clock();
            Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("二叉排序树(耗时=%f秒):\n", Total_time);
            if (!found)
            {
                char createChoice;
                while (1)
                {
                    printf("找不到该关键字。是否要创建该节点？(y/n) ");
                    scanf(" %c", &createChoice);
                    if (createChoice == 'y' || createChoice == 'Y')
                    {
                        RecType newNode;
                        printf("请输入要创建的结点（以key+空格+ID+空格+item1+空格+item2+空格+item3）:\n");
                        scanf("%f %d %f %f %f", &newNode.key, &newNode.ID, &newNode.item1, &newNode.item2, &newNode.item3);
                        InsertBST(T, newNode);
                        printf("节点创建成功。\n");
                        break;
                    }
                    else if (createChoice == 'n' || createChoice == 'N')
                    {
                        break;
                    }
                    else
                    {
                        printf("输入无效，请输入 'y' 或 'n'。\n");
                    }
                }
            }
            break;
        }
        case 3:
        {
            // 哈希表
            float m = 997; // 除数，用于哈希函数计算
            // 在case中不能再定义变量，需要用{}括起来，否则会超出作用域
            HashTable ha[size];
            int tmpkey[size];
            hashfun(R, tmpkey, m);     // 哈希函数
            InitHashTable(ha);         // 初始化散列表
            insertHash(ha, R, tmpkey); // 将关键字存入哈希表
            //					showHash(ha);//显示哈希表
            char haxibiao[] = "haxi.txt";
            result = saveData(ha, haxibiao);
            if (result == 0)
                printf("哈希表已保存,路径与本程序一致\n");
            else
                printf("保存失败\n");
            // 查找关键字
            float key;
            printf("请输入要查找的关键字：");
            scanf("%f", &key);
            start = clock();
            searchHash(ha, key, m);
            finish = clock();
            Total_time = (double)(finish - start) / CLOCKS_PER_SEC;
            printf("哈希查找表(耗时=%f秒):\n", Total_time);
            aslHash(ha);
            break;
        }
        case 4:
            exit(0);
        default:
            printf("输入错误，请重新输入\n");
            break;
        }
    }
    return OK;
}