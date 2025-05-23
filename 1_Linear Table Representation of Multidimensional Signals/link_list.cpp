#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

// 定义结构体
typedef struct Link{
    float data[3];
    struct Link* next;
}Link;

// 创建链表
void CreateData(struct Link* head){
    if (!head){
        printf("无效表头\n");
        return;
    }

    int n;
    printf("请输入创建的链表数量\n");
    scanf("%d", &n);

    if (n <= 0){
        printf("输入的链表有错，请仔细检查\n");
        return;
    } 

    printf("请输入数据（data1, data2,data3）类似这种格式\n");

    Link* tail = head;

    for(int i = 0; i < n; i++){
        //malloc动态分布
        Link* Newnode = (Link*)malloc(sizeof(Link));
        if(!Newnode){
            printf("创建失败");
            return;
        }

        scanf("%f,%f,%f", &Newnode->data[0], &Newnode->data[1], &Newnode->data[2]);
        Newnode->next = NULL;

        // 移动尾指针
        tail->next = Newnode;
        tail = Newnode;
    }
}

// 展示链表
void showData(Link* head){
    struct Link* temp;
    temp = head->next;// 跳过空的首节点
    while (temp){
        printf("%f, %f, %f\n", temp->data[0], temp->data[1], temp->data[2]);
        temp = temp->next;
    }
}

// 链表的插入
void ListInsert(Link* head, int index){
    if (!head){
        printf("无效表头\n");
        return;
    }

    struct Link* current = head;
    int count = 0; // 计数器，头节点是0；

    while(current && count < index -1){
        count++;
        current = current->next;
    }

    if(!current || count < index -1){
        printf("无法找到指定位置\n");
        return;
    }

    struct Link* Newnode = (struct Link*)malloc(sizeof(struct Link));
    if(!Newnode){
        printf("创建失败");
        return;
    }

    printf("请输入要插入的数据：\n");
    scanf("%f,%f,%f", &Newnode->data[0], &Newnode->data[1], &Newnode->data[2]);
    
    //插入操作
    Newnode->next = current->next;
    current->next = Newnode;
}

// 链表的删除
void removeNode(Link* head, int position){
    if(position <= 0){
        printf("有问题\n");
        return;
    }

    struct Link* current = head;
    struct Link* Delete = NULL;

    for(int index = 0; current != NULL && index < position -1; index++){
        current = current->next;
    }

    if(current == NULL || current->next == NULL){
        printf("错误，已经超出范围。\n");
        return;
    }

    // 删除操作
    Delete = current->next;
    current->next = Delete->next;
    free(Delete); // 释放内存；
}

// 链表的取值
void LocateData(Link* head, int i){
    if (!head){
        printf("表长是空\n");
        return;
    }

    Link* current = head;
    int count = 0;

    //遍历链表直到找到第i个元素
    while (current && count < i){
        current = current->next;
        count++;
    }

    //如果没有这个位置
    if (!current){
        printf("没有找到这个位置的元素。\n");
        return;
    }

    //输出找到的元素
    printf("查询到的元素是：%.3f, %.3f, %.3f\n", current->data[0], current->data[1], current->data[2]);

    return;
}

// 均值滤波
struct Link* aven_filter(struct Link* head, int filter_constant) {
    if (!head || !head->next) 
    {
        printf("链表为空或元素不足，无法进行均值滤波\n");
        return head;
    }
    struct Link* newList = (struct Link*)malloc(sizeof(struct Link));
    struct Link* prev = head;
    struct Link* current = head->next; // current和prev指向参与均值滤波的前两个节点
    newList->next = NULL;
    struct Link* newTail = newList;

    while (current != NULL)
    {
        struct Link* newNode = (struct Link*)malloc(sizeof(struct Link));
        if (!newNode) {
            printf("内存分配失败\n");
            return newList;
        }

        if (current == head->next) 
        {
            // 第一个节点和第二个节点的均值
            newNode->data[0] = (current->data[0] + current->next->data[0]) / filter_constant;
            newNode->data[1] = (current->data[1] + current->next->data[1]) / filter_constant;
            newNode->data[2] = (current->data[2] + current->next->data[2]) / filter_constant;
            prev = current;
            current = current->next;
        }
        else if (!current->next) 
        {
            // 最后一个节点和前一个节点的均值
            newNode->data[0] = (prev->data[0] + current->data[0]) / filter_constant;
            newNode->data[1] = (prev->data[1] + current->data[1]) / filter_constant;
            newNode->data[2] = (prev->data[2] + current->data[2]) / filter_constant;
            prev = current;
            current = current->next;
        }
        else 
        {
            // 中间节点和前后两个节点的均值
            newNode->data[0] = (prev->data[0] + current->data[0] + current->next->data[0]) / filter_constant;
            newNode->data[1] = (prev->data[1] + current->data[1] + current->next->data[1]) / filter_constant;
            newNode->data[2] = (prev->data[2] + current->data[2] + current->next->data[2]) / filter_constant;
            prev = current;
            current = current->next;
        }

        // 将新节点插入到新的链表中
        newNode->next = newTail->next;
        newTail->next = newNode;
        newTail = newNode;
    }

    return newList;
}

// 信号上采样
struct Link* sampling(struct Link* head) {
    struct Link* p1, * p2, * p3;
    p1 = head;
    p2 = p1->next;
    
    while (p2 != NULL) {
        p3 = (struct Link*)malloc(sizeof(struct Link));
        if (!p3) {
            printf("内存分配失败\n");
            return head;
        }
        p3->data[0] = (p1->data[0] + p2->data[0]) / 2;
        p3->data[1] = (p1->data[1] + p2->data[1]) / 2;
        p3->data[2] = (p1->data[2] + p2->data[2]) / 2;
        p1->next = p3;
        p3->next = p2;
        p1 = p2;
        p2 = p2->next;
    }
    
    return(head);
}

// 保存文件
void SaveData(struct Link* head, const char* filename){
    if (!head || !filename) {
        fprintf(stderr, "无效输入：head 或文件名为空。\n");
        return;
    }

    FILE* fp = fopen(filename, "w"); //"w" 表示写模式，允许写入数据。如果文件已经存在，它会被覆盖；如果文件不存在，会创建一个新文件。
    if (!fp) {
        perror("打开文件失败");
        return;
    }

    for (struct Link* p = head->next; p; p = p->next) {
        if (fprintf(fp, "%f,%f,%f\n", p->data[0], p->data[1], p->data[2]) < 0) {
            perror("写入数据失败");
            fclose(fp);
            return;
        }
    }

    fclose(fp);
}

// 读取文件数据到链表
void ReadData(struct Link* head, const char* filename) {
    if (!head || !filename) {
        fprintf(stderr, "无效输入：head 或文件名为空。\n");
        return;
    }

    FILE* fp = fopen(filename, "rt"); //表示以文本模式打开文件进行读取。
    if (!fp) {
        perror("打开文件失败");
        return;
    }

    struct Link* temp = head;

    // 直接读取并连接数据，避免不必要的 malloc 调用
    while (1) {
        struct Link* p = (struct Link*)malloc(sizeof(struct Link));
        if (!p) {
            fprintf(stderr, "内存分配失败。\n");
            fclose(fp);
            return;
        }

        // 读取数据
        if (fscanf(fp, "%f,%f,%f", &p->data[0], &p->data[1], &p->data[2]) != 3) {
            free(p); // 如果读取失败，释放内存并结束循环
            break;
        }

        // 插入链表
        temp->next = p;
        p->next = NULL;
        temp = p;  // 移动到新节点
    }

    fclose(fp);
}

//界面交互
void Initwork() {
    printf("\n====== 链表管理系统 ======\n");
    printf("1. 创建链表\n");
    printf("2. 查找元素\n");
    printf("3. 插入元素\n");
    printf("4. 删除元素\n");
    printf("5. 显示链表\n");
    printf("6. 上采样\n");    
    printf("7. 均值滤波\n");
    printf("8. 保存数据\n");
    printf("9. 读取数据\n");
    printf("0. 退出本系统\n");
}