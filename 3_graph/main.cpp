#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
#include <string>
#include "graph.cpp"

int main()
{
	// 起始界面选择
	showWelcomeScreen();

	printInputChoiceMenu();
	int choice;
	scanf("%d", &choice);

	std::vector<std::vector<int>> metaData;
	std::vector<std::string> vertexNames;
	int edgeNum = 0;
	int result;

	// 读取选择
	if (choice == 1)
	{
		result = readFromUserInput(metaData, vertexNames, edgeNum);
	}
	else if (choice == 2)
	{
		result = read("source.txt", metaData, vertexNames, edgeNum);
	}
	else
	{
		printf("输入选择有误，请重新运行程序。\n");
		return ERROR;
	}

	if (result == ERROR)
	{
		return ERROR;
	}

	graph g;
	creategraph(&g, metaData, vertexNames, edgeNum);

	while (1)
	{
		printMenu();
		int input;
		scanf("%d", &input);
		int startVertexIndex;
		std::string startVertex;
		switch (input)
		{
		case 1:
			insertvexnode(&g);
			break;
		case 2:
			insertedgenode(&g);
			break;
		case 3:
			find(g);
			break;
		case 4:
			printf("请输入深度优先遍历的起始顶点: ");
			std::cin >> startVertex;
			startVertexIndex = locatevex(g, startVertex);
			if (startVertexIndex == -1)
			{
				printf("输入的顶点不存在，请重新输入。\n");
				break;
			}
			printf("\n");
			printf("图的深度优先遍历序列（从 %s 开始）：\n", startVertex.c_str());
			for (int v = 0; v < g.n; v++)
				visited[v] = 0; // 初始化标志数组
			DFS(g, startVertexIndex);
			printf("\n");
			break;
		case 5:
			printf("请输入广度优先遍历的起始顶点: ");
			std::cin >> startVertex;
			startVertexIndex = locatevex(g, startVertex);
			if (startVertexIndex == -1)
			{
				printf("输入的顶点不存在，请重新输入。\n");
				break;
			}
			printf("\n");
			printf("图的广度优先遍历序列（从 %s 开始）：\n", startVertex.c_str());
			for (int v = 0; v < g.n; v++)
				visited[v] = 0; // 初始化标志数组
			BFS(g, startVertexIndex);
			printf("\n");
			break;
		case 6:
			print(g);
			break;
		case 7:
		{
			FILE *fp = fopen("path.txt", "w");
			if (NULL == fp)
			{
				printf("无法打开文件\n");
				return ERROR;
			}
			int src = 0;
			int visited[201] = {0}; // 标记顶点是否已经被记录为最短路径
			int distance[201];		// 标记从源点到其他顶点的路径长度
			int prenode[201] = {0}; // 如果某个顶点要加入最短路径，记录该顶点在最短路径中的前一个顶点
			// 初始将每个顶点的距离设置为无穷大
			for (int i = 0; i < 201; i++)
			{
				distance[i] = INF;
			}
			shortestpath(&g, visited, distance, prenode, src);
			int path[200] = {0}; // 用于保存路径信息
			// 输出最短路径信息
			for (int i = 1; i < g.n; i++)
			{
				if (distance[i] == INF)
				{
					printf("顶点 %s 到顶点 %s 之间没有最短路径\n", g.vexlist[src].data.c_str(), g.vexlist[i].data.c_str());
					fprintf(fp, "\n顶点 %s 到顶点 %s 之间没有最短路径\n", g.vexlist[src].data.c_str(), g.vexlist[i].data.c_str());
				}
				else
				{
					int p = i;
					int n = 0;
					while (p != 0)
					{
						path[n] = p;
						p = prenode[p]; // 使p指向自己的前驱节点
						n++;
					}
					// n为路径中节点数量
					printf("顶点 %s 到顶点 %s 之间的最短路径为: ", g.vexlist[src].data.c_str(), g.vexlist[i].data.c_str());
					printf("%s", g.vexlist[src].data.c_str());
					fprintf(fp, "顶点 %s 到顶点 %s 之间的最短路径为: ", g.vexlist[src].data.c_str(), g.vexlist[i].data.c_str());
					fprintf(fp, "%s", g.vexlist[src].data.c_str());
					for (int j = n - 2; j >= 0; j--)
					{
						printf("—>%s", g.vexlist[path[j]].data.c_str());
						fprintf(fp, "—>%s", g.vexlist[path[j]].data.c_str());
					}
					printf("—>%s", g.vexlist[i].data.c_str());
					printf("    路径长度为 %d\n", distance[i]);
					fprintf(fp, "—>%s", g.vexlist[i].data.c_str());
					fprintf(fp, "    路径长度为 %d\n", distance[i]);
				}
			}
			fclose(fp);
			printf("\n结果已保存到path.txt文件。\n\n");
			break;
		}
		case 8:
			exit(0);
			break;
		default:
			printf("输入操作项有误，请重新输入\n");
			break;
		}
	}
	return 0;
}