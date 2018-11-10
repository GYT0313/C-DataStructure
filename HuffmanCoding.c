#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 8  //字母个数
#define M ( 2*N-1 )  //节点数目

// 哈夫曼编码


typedef struct      /* HaffmanTree 结构体: weight  parent  lchild  rchild */
{
    int weight;
    int parent, lchild, rchild;
}HTNode;
typedef HTNode HaffmanTree[M];      /* HTNode 类型的数组结构体 */


typedef struct      /* HaffmanTree 结构体: data  weight  code[N] */
{
    char data;
    int weight;
    char code[N];   /* 编码 原本最长:N-1, 最后一位存放'\0'*/
}HTCode;
typedef HTCode HaffmanCode[N];      /* HTCode 类型的数组结构体 */

/* 初始化 haffmancode */
int initHaffmanCode( HaffmanCode hc )  /* hc 是数组 */
{
    int i;

    for (i=0; i<N; i++)
    {
        printf("Please input %d's code and weight: ", i+1);
        fflush(stdin);  /* 清空缓冲区 */
        scanf("%c%d", &hc[i].data, &hc[i].weight);
    }
}


/*初始化 haffmantree*/
/*
 *给叶节点赋 weight，其余赋-1
 */
void initHaffmanTree( HaffmanTree ht, HaffmanCode hc )
{
    int i;

    for (i=0; i<N; i++)
    {
        ht[i].weight = hc[i].weight;    /*初始化 weight*/
    }

    for (i=0; i<M; i++)
    {
        ht[i].parent = ht[i].lchild = ht[i].rchild = -1;   /*赋值 -1*/
    }
}


/*创建 哈夫曼树*/
void createHaffmanTree( HaffmanTree ht )
{
    int i, j;
    int min1, min2, index1, index2;     /*最小值、 次小值、 最小值下标、 次小值下标*/

    for (i=N; i<M; i++)     /*查找 min1 和 min2*/
    {
        min1 = min2 = INT_MAX;  /* int类型的最大值  (引入头文件limts.h)*/
        index1 = index2 = -1;
        for (j=0; j<i; j++)     /*注：每次查找的范围在扩大（+1）*/
        {
            if (ht[j].parent == -1)     /*没有双亲才比较*/
            {
                if (ht[j].weight < min1)    /* ht[j].weight < min1 < min2 */
                {
                    min2 = min1;    /*原来的最小值变为了次小值*/
                    index2 = index1;
                    min1 = ht[j].weight;    /*新的最小值为 ht[j].weight */
                    index1 = j;
                }
                else if(ht[j].weight < min2)
                {
                    min2 = ht[j].weight;    /* min1 < ht[j].weight < min2 */
                    index2 = j;
                }
            }
        }
        ht[i].weight = min1 + min2;     /* 计算新权值，最小值 和 次小值相加得到二者的双亲节点的权值 */
        ht[i].lchild = index1;    /* 最小值在左 */
        ht[i].rchild = index2;   /* 次小在右 */              /* 修改父节点 */

        ht[index1].parent = ht[index2].parent = i;  /* 最小值 和 次小值的 parent */     /* 修改两个子树节点 */
    }
}

/*创建 哈夫曼代码*/
void createHaffmanCode( HaffmanTree ht, HaffmanCode hc )
{
    char code[N];   /*暂时存放哈夫曼代码*/
    int i, j, start;

    for (i=0; i<N; i++)     /*倒叙查找*/
    {
        start = N - 1;
        code[start] = '\0';
        j = i;
        while(ht[j].parent != -1)   /*到达根节点跳出*/
        {
            code[--start] = ht[ht[j].parent].lchild == j?'0':'1'; /* 双亲的lchild == 该节点的下标，即值为0，否则为1 */
            j = ht[j].parent;   /*双亲的下标*/
        }
        strcpy(hc[i].code, &code[start]);   /*code 是数组, 有值的地方的地址(因为是倒叙)赋给 hc[i].code（相当于赋首地址）*/
    }

}


/*打印 code*/
void printCode( HaffmanCode hc )
{
    int i;

    for (i=0; i<N; i++)
    {
        printf("%c的编码是: %s\n", hc[i].data, hc[i].code);
    }
}



int main()
{
    HaffmanCode hc;
    HaffmanTree ht;

    initHaffmanCode(hc);       /*初始化*/
    initHaffmanTree(ht, hc);

    createHaffmanTree(ht);     /*创建*/
    createHaffmanCode(ht, hc);

    printCode(hc);

    return 0;
}
