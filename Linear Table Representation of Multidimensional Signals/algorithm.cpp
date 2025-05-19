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
    }

    int n;
    printf("请输入创建的链表数量\n");
    scanf("%d", &n);

    if (n <= 0){
        printf("输入的链表有错，请仔细检查\n");
    } 

    printf("请输入数据（data1, data2,data3）类似这种格式\n");

    Link* tail = head;

    for(int i = 0; i < n; i++){
        //malloc动态分布

        Link* Newnode = (Link*)malloc(sizeof(Link));
        if(!Newnode){
            printf("创建失败");
        }

        scanf("%f,%f,%f", &Newnode->data[0], &Newnode->data[1], &Newnode->data[2]);
        Newnode->next = NULL;

        // 移动尾指针

        tail->next = Newnode;
        tail = Newnode;
    }

}

// 
void showData(Link* head){
    struct Link* temp;
    temp = head->next;// 跳过空的首节点
        while (temp){
            printf("%f, %f, %f\n", temp->data[0], temp->data[1], temp->data[2]);
            temp = temp->next;
        }
        
}

int main(){
    //创建头节点
    Link* head = (Link*)malloc(sizeof(Link));
    head->next = NULL;

    CreateData(head);
    showData(head);

}