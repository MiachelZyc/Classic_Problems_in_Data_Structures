#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <windows.h>  // 引入windows.h头文件以支持控制台编码设置
#include "Huffman.cpp"

using namespace std;

#define ERROR -1
#define OK 0




int main() {
    // 显示欢迎界面
    showWelcomeScreen();
    setConsoleUTF8();
    int choice;
    cout << "请选择操作: \n";
    cout << "0 - 修改文件内容\n";
    cout << "1 - 执行Huffman编码程序\n";
    cout << "请输入选项: ";
    cin >> choice;
    cin.ignore(); // 清除缓冲区中的换行符

    switch (choice) {
        case 0: {
            // 修改文件内容
            const char* filename = "E:\\School_Work\\data_structure\\data_structure_Cpp\\code2\\source.txt";
            replaceContent(filename);
            break;
        }
        case 1: {

            int n;
            cout << "请输入符号数n: ";
            cin >> n;
            getchar(); // 清除缓冲区的换行符
            
            int length = 0;
            char c[256];
            char* data = (char*)malloc(n * sizeof(char));
            int* weight = (int*)malloc(n * sizeof(int));
            char* Data = (char*)malloc(100 * sizeof(char));

            // 初始化Huffman Tree
            HuffmanTree HT;
            InitHuffmanTree(HT, n);

            // 读文件
            if (read("E:\\School_Work\\data_structure\\data_structure_Cpp\\code2\\source.txt", n, data, Data, weight, length) == ERROR) {
                cerr << "无法读取文件: E:\\School_Work\\data_structure\\data_structure_Cpp\\code2\\source.txt" << endl;
                free(data);
                free(weight);
                free(Data);
                return ERROR;
            }
            cout << "读文件: E:\\School_Work\\data_structure\\data_structure_Cpp\\code2\\source.txt" << endl;

            cout << "源数据: ";
            for (int i = 0; i < length; i++) {
                cout << Data[i] << " ";
            }
            cout << endl;

            // 分类归纳文件数据并创建树
            quickSort(data, weight, 0, n - 1);
            for (int i = 1; i <= n; i++) {
                HT[i].data = data[i - 1];
                HT[i].weight = weight[i - 1];
                cout << "符号: " << HT[i].data << ", 权重: " << HT[i].weight << endl;
            }

            // 创建 Huffman codes
            HuffmanCode HC;
            CreatHuffmanTree(HT, n);
            CreatHuffmanCode(HT, HC, n);

            // 输出 Huffman codes
            cout << "\n\n";
            for (int i = 1; i <= n; i++) {
                cout << "符号: " << HT[i].data << ", 编码: " << HC[i] << endl;
            }

            // 树书
            cout << "\n输入数据 (字母，以逗号分隔): ";
            fgets(c, sizeof(c), stdin);
            c[strcspn(c, "\n")] = '\0';  

            if (strcmp(c, "-1") != 0) {
                length = 0;
                char* p = strtok(c, ",");
                int num = 0;
                while (p != NULL && num < 100) { 
                    Data[num++] = *p;
                    length++;
                    p = strtok(NULL, ",");
                }
            }
            else {
                cout << "用户输入退出指令，程序结束。" << endl;
                free(data);
                free(weight);
                free(Data);
                for (int i = 1; i <= n; i++) {
                    delete[] HC[i];
                }
                delete[] HC;
                delete[] HT;
                return OK;
            }

            // 展示Tree书
            char* show = (char*)malloc(200);
            showHuffmanTree(HT, HC, length, Data, show);

            // 解码
            cout << "\n解码:\n";
            HuffmanDecode(HT, show);

            free(data);
            free(weight);
            free(Data);
            free(show);
            for (int i = 1; i <= n; i++) {
                delete[] HC[i];
            }
            delete[] HC;
            delete[] HT;

            return OK;
        }
        default:
            cout << "无效的选择，程序退出。" << endl;
            return ERROR;
    }
}



