#include <iostream>
#include "link_list.h"

using namespace std;

int main() {
    // 初始化链表头节点
    Link* head = (Link*)malloc(sizeof(Link));
    if (!head) {
        cout << "内存分配失败！\n";
        return 1;
    }
    head->next = NULL;  // 头节点的 next 初始化为 NULL

    int choice, index, position, filter_constant;

    // 主菜单循环
    while (1) {
        Initwork();  // 显示操作菜单
        cout << "\n请输入你的选择: ";
        cin >> choice;

        switch (choice) {
            case 1: // 创建链表
                CreateData(head);
                break;
            case 2: // 查找元素
                cout << "请输入要查找的元素位置: ";
                cin >> index;
                LocateData(head, index);
                break;
            case 3: // 插入元素
                cout << "请输入插入的位置: ";
                cin >> index;
                ListInsert(head, index);
                break;
            case 4: // 删除元素
                cout << "请输入删除的位置: ";
                cin >> position;
                removeNode(head, position);
                break;
            case 5: // 显示链表
                cout << "当前链表内容:\n";
                showData(head);
                break;
            case 6: // 上采样
                head = sampling(head);
                cout << "上采样完成。\n";
                break;
            case 7: // 均值滤波
                cout << "请输入滤波常数: ";
                cin >> filter_constant;
                head = aven_filter(head, filter_constant);
                cout << "均值滤波完成。\n";
                break;
            case 8: // 保存数据
                {
                    char filename[100];
                    cout << "请输入保存的文件名: ";
                    cin >> filename;
                    SaveData(head, filename);
                    cout << "数据保存完成。\n";
                }
                break;
            case 9: // 读取数据
                {
                    char filename[100];
                    cout << "请输入读取的文件名: ";
                    cin >> filename;
                    ReadData(head, filename);
                    cout << "数据读取完成。\n";
                }
                break;
            case 0: // 退出
                cout << "退出系统\n";
                free(head);  // 释放头节点内存
                return 0;
            default:
                cout << "无效的选择，请重新输入。\n";
        }
    }

    return 0;
}