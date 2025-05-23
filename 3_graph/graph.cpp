#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <string>

#define maxsize 100
#define queuesize 100
#define INF 36451
#define ERROR -1
#define OK 0

using namespace std;

// 边结点的类型定义
typedef struct edgenode
{
    int adjvex;            // 存放邻接的点在顶点表的下标，邻接点
    struct edgenode *next; // 指向Vi下一个邻接点的边结点
    int weight;            // 权值
} edgenode;

// 顶点结点类型定义
typedef struct vexnode
{
    string data;         // 顶点信息，使用 string 类型
    edgenode *firstedge; // 边表头指针
} vexnode;

// 图的结构定义
typedef struct
{
    vexnode vexlist[maxsize]; // 顶点表
    int n, e;                 // n是顶点数，e是边数
} graph;

// 读取文件
int read(char *name, vector<vector<int>> &metaData, vector<string> &vertexNames, int &edgeNum)
{
    FILE *fp = fopen(name, "r");
    edgeNum = 0;
    char c[100];
    if (fp == NULL)
    {
        puts("不能打开文件！\n");
        return ERROR;
    }
    while (fgets(c, sizeof(c), fp))
    {
        vector<int> edge;
        char *p = strtok(c, ",");
        if (p)
        {
            string vertex = p;
            bool found = false;
            int index;
            for (index = 0; index < vertexNames.size(); ++index)
            {
                if (vertexNames[index] == vertex)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                vertexNames.push_back(vertex);
                index = vertexNames.size() - 1;
            }
            edge.push_back(index);
        }
        while (p = strtok(NULL, ","))
        {
            if (edge.size() < 2)
            {
                string vertex = p;
                bool found = false;
                int index;
                for (index = 0; index < vertexNames.size(); ++index)
                {
                    if (vertexNames[index] == vertex)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    vertexNames.push_back(vertex);
                    index = vertexNames.size() - 1;
                }
                edge.push_back(index);
            }
            else
            {
                edge.push_back(atoi(p));
            }
        }
        metaData.push_back(edge);
        edgeNum++;
    }
    fclose(fp);
    return OK;
}

// 从用户输入读取数据
int readFromUserInput(vector<vector<int>> &metaData, vector<string> &vertexNames, int &edgeNum)
{
    // 清空输入缓冲区
    while (getchar() != '\n')
        ;

    printf("请输入类似 A,B,1 或 10,12,2 格式的数据，输入空行结束输入：\n");
    edgeNum = 0;
    char c[100];
    while (fgets(c, sizeof(c), stdin) && c[0] != '\n')
    {
        vector<int> edge;
        char *p = strtok(c, ",");
        if (p)
        {
            string vertex = p;
            bool found = false;
            int index;
            for (index = 0; index < vertexNames.size(); ++index)
            {
                if (vertexNames[index] == vertex)
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                vertexNames.push_back(vertex);
                index = vertexNames.size() - 1;
            }
            edge.push_back(index);
        }
        while (p = strtok(NULL, ","))
        {
            if (edge.size() < 2)
            {
                string vertex = p;
                bool found = false;
                int index;
                for (index = 0; index < vertexNames.size(); ++index)
                {
                    if (vertexNames[index] == vertex)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    vertexNames.push_back(vertex);
                    index = vertexNames.size() - 1;
                }
                edge.push_back(index);
            }
            else
            {
                edge.push_back(atoi(p));
            }
        }
        metaData.push_back(edge);
        edgeNum++;
    }
    return OK;
}

// 初始化图
int creategraph(graph *g, const vector<vector<int>> &metaData, const vector<string> &vertexNames, int edgeNum)
{
    g->n = vertexNames.size();
    g->e = edgeNum;
    for (int i = 0; i < g->n; i++)
    {
        g->vexlist[i].data = vertexNames[i];
        g->vexlist[i].firstedge = NULL;
    }
    for (int k = 0; k < g->e; k++)
    {
        int i = metaData[k][0];
        int j = metaData[k][1];
        int weight = metaData[k][2];
        edgenode *s = (edgenode *)malloc(sizeof(edgenode));
        s->adjvex = j;
        s->weight = weight;
        s->next = g->vexlist[i].firstedge;
        g->vexlist[i].firstedge = s;
    }
    return OK;
}

// 在图g中查找顶点v,存在顶点数组中的下标，不存在返回-1
int locatevex(const graph &g, const string &v)
{
    for (int i = 0; i < g.n; i++)
    {
        if (g.vexlist[i].data == v)
        {
            return i;
        }
    }
    return ERROR;
}

// 插入结点
int insertvexnode(graph *g)
{
    printf("\n请输入待插入的顶点\n");
    string m;
    cin >> m;
    int i;
    for (i = 0; i < g->n; i++)
    {
        if (m == g->vexlist[i].data)
        {
            printf("该顶点已存在\n");
            return i;
        }
    }
    if (i < g->n)
        ;
    else
    {
        g->vexlist[g->n].data = m;
        g->vexlist[g->n].firstedge = NULL;
        g->n++; // 填充
        printf("插入已完成");
        printf("\n总顶点数=%d\n", g->n);
    }
    return OK;
}

// 插入边
int insertedgenode(graph *g)
{
    string v1, v2;
    int k;
    edgenode *s;
    printf("请输入插入的边的两个顶点(顶点1+空格+顶点2+空格+权重)\n");
    cin >> v1 >> v2 >> k;
    int i = locatevex(*g, v1);
    int j = locatevex(*g, v2);
    if (i >= 0 && j >= 0)
    {
        // 建立有向图的邻接表
        s = (edgenode *)malloc(sizeof(edgenode));
        s->adjvex = j;
        s->weight = k;
        s->next = g->vexlist[i].firstedge;
        g->vexlist[i].firstedge = s;
        printf("插入已完成\n");
    }
    else
        printf("输入端点有误\n"); // 边界条件
    return OK;
}

// 寻找序号为v的第一个邻接点
int find(const graph &g)
{
    string k;
    printf("请输入顶点：");
    cin >> k;
    int index = locatevex(g, k);
    if (index >= 0)
    {
        printf("顶点为：%s\n", g.vexlist[index].data.c_str());
    }
    else
    {
        printf("查找有误\n"); // 边界条件
        return ERROR;
    }
    edgenode *s;
    s = g.vexlist[index].firstedge;
    if (s != NULL)
    {
        printf("第一个邻接结点为：%s\n", g.vexlist[s->adjvex].data.c_str());
    }
    else
    {
        printf("该顶点没有邻接结点\n");
    }
    return OK;
}

// 队列
// 循环队列存储结构定义
typedef struct cirqueue
{
    int *data; // 队列存储空间的首地址
    int front; // 队头位置：指向当前队头元素
    int rear;  // 队尾位置：指向当前队尾元素的下一位置
} cirqueue;    // 循环队列

int initqueue(cirqueue *q) // 构造空队，如果成功，返回1，如果失败，返回0
{
    q->data = (int *)malloc(queuesize * sizeof(int));
    if (q->data == NULL)
        return 0; // 存储分配失败
    q->front = q->rear = 0;
    return 1;
}

// 插入元素e为Q的新的队尾元素 ,如果成功，返回1，如果失败，返回0
int enqueue(cirqueue *q, int e)
{
    if ((q->rear + 1) % queuesize == q->front)
        return 0; // 队列满
    q->data[q->rear] = e;
    q->rear = (q->rear + 1) % queuesize; // 队尾后移一位
    return 1;
}

// 若队列不空，则删除Q的队头元素，用e返回其值,并返回1；否则返回0
int dequeue(cirqueue *q, int *e)
{
    if (q->front == q->rear)
        return 0; // 队列为空
    *e = q->data[q->front];
    q->front = (q->front + 1) % queuesize; // 队头后移一位
    return 1;
}

// 若栈不空，则用e返回队头元素,并返回1；否则返回0
int getfront(cirqueue q, int *e)
{
    if (q.front == q.rear)
        return 0; // 队列为空
    *e = q.data[q.front];
    return 1;
}

// 若队列为空栈，则返回1，否则返回0
int queueempty(cirqueue q) // 栈非空
{
    if (q.front == q.rear)
        return 1; // 队列为空
    else
        return 0;
}

// 返回队列的元素个数，即队列的长度
int queuelength(cirqueue q)
{
    return (q.rear - q.front + queuesize) % queuesize;
}

// 深度优先遍历
int visited[maxsize]; // 访问标志数组

// 从第i个顶点出发递归地深度优先遍历图G
void DFS(const graph &g, int i)
{
    edgenode *p;
    printf("%s ", g.vexlist[i].data.c_str()); // 访问第i个项点
    visited[i] = 1;
    p = g.vexlist[i].firstedge;
    while (p != NULL)
    {
        if (visited[p->adjvex] == 0)
            DFS(g, p->adjvex); // 对i的尚未访问的邻接顶点j递归调用DFS
        p = p->next;
    }
}

// 对图g进行深度优先遍历
// 去掉原来的循环，让用户指定起始顶点
// void DFStraverse(const graph &g)
// {
//     int v;
//     for (v = 0; v < g.n; v++)
//         visited[v] = 0;       // 初始化标志数组
//     for (v = 0; v < g.n; v++) // 保证非连通图的遍历
//         // 从第v个顶点出发递归地深度优先遍历图g
//         if (!visited[v])
//             DFS(g, v);
// }

// 广度优先遍历
int BFSvisited[maxsize];
cirqueue q;

// 从第k个顶点出发广度优先遍历图g
void BFS(const graph &g, int k)
{
    int i;
    edgenode *p;
    initqueue(&q);                            // 初始化队列
    printf("%s ", g.vexlist[k].data.c_str()); // 访问第k个项点
    visited[k] = 1;
    enqueue(&q, k); // 第k个顶点进队
    while (queueempty(q) == 0)
    { // 队列非空
        dequeue(&q, &i);
        p = g.vexlist[i].firstedge; // 获取第1个邻接点
        while (p != NULL)
        {
            if (visited[p->adjvex] == 0)
            {
                // 访问第i个顶点的末曾访问的顶点
                printf("%s ", g.vexlist[p->adjvex].data.c_str());
                visited[p->adjvex] = 1;
                enqueue(&q, p->adjvex); // 第k个顶点进队
            }
            p = p->next;
        }
    }
}

// 对图g进行广度优先遍历
// 去掉原来的循环，让用户指定起始顶点
// void BFStraverse(const graph &g)
// {
//     int v;
//     for (v = 0; v < g.n; v++) // 初始化标志数组
//         visited[v] = 0;
//     for (v = 0; v < g.n; v++) // 保证非连通图的遍历
//         if (!visited[v])
//             BFS(g, v); // 从第v个顶点出发递归地广度优先遍历图g
// }

// 打印图的信息
void print(const graph &g)
{
    int i;
    edgenode *p;
    printf("图的邻接表表示：");
    for (i = 0; i < g.n; i++)
    {
        printf("\n%4s", g.vexlist[i].data.c_str());
        p = g.vexlist[i].firstedge;
        while (p != NULL)
        {
            printf("-->%s(权值：%d)", g.vexlist[p->adjvex].data.c_str(), p->weight);
            p = p->next;
        }
    }
    printf("\n");
}

// 计算从源顶点到其他顶点的单源最短路径
void shortestpath(graph *g, int visited[], int distance[], int prenode[], int src)
{
    int count = 0;    // 记录直接与源点相连的顶点个数
    visited[src] = 1; // 源点已经添加到最短路径中
    distance[src] = 0;
    count++;
    // 如果有顶点和源点直接相连，另外设置距离
    if (g->vexlist[src].firstedge != NULL)
    {
        edgenode *p = g->vexlist[src].firstedge;
        for (; p != NULL;)
        {
            distance[p->adjvex] = p->weight;
            prenode[p->adjvex] = src; // 这些顶点的前驱顶点为源点
            p = p->next;
        }
    }
    while (count < g->n)
    {
        int min = INF;
        int target_node = -1;
        // 首先在剩余节点中寻找距离最新加入最短路径的顶点，最近的那一个
        for (int i = 0; i < g->n; i++)
        {
            if (visited[i] == 0 && min > distance[i])
            {
                min = distance[i];
                target_node = i;
            }
        }
        if (target_node == -1)
            break;
        visited[target_node] = 1; // 将最短距离顶点加入最短路径中
        count++;
        // 更新剩余未加入最短路径的顶点的距离
        if (g->vexlist[target_node].firstedge != NULL)
        {
            edgenode *p = g->vexlist[target_node].firstedge;
            for (; p != NULL;)
            {
                if (visited[p->adjvex] == 0 && distance[target_node] + p->weight < distance[p->adjvex])
                {
                    distance[p->adjvex] = distance[target_node] + p->weight;
                    prenode[p->adjvex] = target_node;
                }
                p = p->next;
            }
        }
    }
}

void showWelcomeScreen()
{
    cout << "========================================\n";
    cout << "        欢迎来到图的遍历系统\n";
    cout << "========================================\n";
    cout << "        作者：赵言诚（Miachel）\n";
    cout << "        日期：2025年\n";
    cout << "        版本：v1.0\n";
    cout << "========================================\n\n";
    cout << "根据提示键使用本系统...\n";
    cin.ignore(); // 防止输入缓冲区残留
    cin.get();    // 等待用户按下回车键继续
}

// 打印菜单
void printMenu()
{
    printf("**********************************\n");
    printf("*    1.插入顶点                  *\n");
    printf("*    2.插入边                    *\n");
    printf("*    3.寻找序号为v的第一个邻接点 *\n");
    printf("*    4.图的深度优先遍历          *\n");
    printf("*    5.图的广度优先遍历          *\n");
    printf("*    6.打印图                    *\n");
    printf("*    7.最短路径                  *\n");
    printf("*    8.退出                      *\n");
    printf("**********************************\n");
    printf("初始化已完成，请输入操作：\n");
}

// 打印数据输入选择菜单
void printInputChoiceMenu()
{
    printf("请选择数据输入方式：\n");
    printf("1. 自己输入类似 A,B,1 或 10,12,2 格式的数据\n");
    printf("2. 直接读取 Source 文件\n");
}