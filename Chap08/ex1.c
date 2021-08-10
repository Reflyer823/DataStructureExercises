// 08-图7 公路村村通
#include <stdio.h>

// 定义图
typedef int Vertex;
int G[1000][1000];
int N, M;
#define INFINITY 1000000

// 声明函数
int Prim(Vertex S);

// 主函数
int main() {
    int V1, V2, len;

    // 从输入中读取图
    scanf("%d %d", &N, &M);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            G[i][j] = INFINITY;
        G[i][i] = 0;
    }
    for (int i = 0; i < M; i++) {
        scanf("%d %d %d", &V1, &V2, &len);
        G[V1 - 1][V2 - 1] = len;
        G[V2 - 1][V1 - 1] = len;
    }

    // 对图执行Prim算法并输出结果
    printf("%d\n", Prim(0));

    return 0;
}

// Prim算法，返回图的最小生成树的权值和，若最小生成树不存在则返回-1
int Prim(Vertex S) {
    int dist[1000];
    Vertex V;
    int sum = 0;
    // 初始化距离数组
    for (int i = 0; i < N; i++) dist[i] = G[S][i];
    while (1) {
        // 查找树外距离当前树最近的点
        V = -1;
        for (int i = 0; i < N; i++)
            if (dist[i] > 0 && (V == -1 || dist[i] < dist[V]))
                V = i;
        // 所有的点都在树内时，返回最终结果
        if (V == -1) return sum;
        // 最小距离都是无穷大时，说明图不连通，返回错误
        if (dist[V] == INFINITY) return -1;
        // 将该节点加入树内并更新权值之和
        sum += dist[V];
        dist[V] = 0;
        // 检查新加入节点V的邻接点是否需要更新最小距离
        for (int i = 0; i < N; i++) {
            if (dist[i] > 0 && G[V][i] < INFINITY && G[V][i] < dist[i])
                dist[i] = G[V][i];
        }
    }
}