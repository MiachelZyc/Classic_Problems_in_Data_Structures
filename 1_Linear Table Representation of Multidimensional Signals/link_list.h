#ifndef LINK_LIST_H
#define LINK_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义 Link 结构体
typedef struct Link {
    float data[3];
    struct Link* next;
} Link;

// 创建链表
void CreateData(Link* head);

// 展示链表
void showData(Link* head);

// 链表的插入
void ListInsert(Link* head, int index);

// 链表的删除
void removeNode(Link* head, int position);

// 链表的取值
void LocateData(Link* head, int i);

// 均值滤波
Link* aven_filter(Link* head, int filter_constant);

// 信号上采样
Link* sampling(Link* head);

// 保存文件
void SaveData(Link* head, const char* filename);

// 读取文件数据到链表
void ReadData(Link* head, const char* filename);

// 界面交互
void Initwork();

#endif // LINK_LIST_H