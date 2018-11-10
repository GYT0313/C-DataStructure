#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define N 8  //��ĸ����
#define M ( 2*N-1 )  //�ڵ���Ŀ

// ����������


typedef struct      /* HaffmanTree �ṹ��: weight  parent  lchild  rchild */
{
    int weight;
    int parent, lchild, rchild;
}HTNode;
typedef HTNode HaffmanTree[M];      /* HTNode ���͵�����ṹ�� */


typedef struct      /* HaffmanTree �ṹ��: data  weight  code[N] */
{
    char data;
    int weight;
    char code[N];   /* ���� ԭ���:N-1, ���һλ���'\0'*/
}HTCode;
typedef HTCode HaffmanCode[N];      /* HTCode ���͵�����ṹ�� */

/* ��ʼ�� haffmancode */
int initHaffmanCode( HaffmanCode hc )  /* hc ������ */
{
    int i;

    for (i=0; i<N; i++)
    {
        printf("Please input %d's code and weight: ", i+1);
        fflush(stdin);  /* ��ջ����� */
        scanf("%c%d", &hc[i].data, &hc[i].weight);
    }
}


/*��ʼ�� haffmantree*/
/*
 *��Ҷ�ڵ㸳 weight�����ำ-1
 */
void initHaffmanTree( HaffmanTree ht, HaffmanCode hc )
{
    int i;

    for (i=0; i<N; i++)
    {
        ht[i].weight = hc[i].weight;    /*��ʼ�� weight*/
    }

    for (i=0; i<M; i++)
    {
        ht[i].parent = ht[i].lchild = ht[i].rchild = -1;   /*��ֵ -1*/
    }
}


/*���� ��������*/
void createHaffmanTree( HaffmanTree ht )
{
    int i, j;
    int min1, min2, index1, index2;     /*��Сֵ�� ��Сֵ�� ��Сֵ�±ꡢ ��Сֵ�±�*/

    for (i=N; i<M; i++)     /*���� min1 �� min2*/
    {
        min1 = min2 = INT_MAX;  /* int���͵����ֵ  (����ͷ�ļ�limts.h)*/
        index1 = index2 = -1;
        for (j=0; j<i; j++)     /*ע��ÿ�β��ҵķ�Χ������+1��*/
        {
            if (ht[j].parent == -1)     /*û��˫�ײűȽ�*/
            {
                if (ht[j].weight < min1)    /* ht[j].weight < min1 < min2 */
                {
                    min2 = min1;    /*ԭ������Сֵ��Ϊ�˴�Сֵ*/
                    index2 = index1;
                    min1 = ht[j].weight;    /*�µ���СֵΪ ht[j].weight */
                    index1 = j;
                }
                else if(ht[j].weight < min2)
                {
                    min2 = ht[j].weight;    /* min1 < ht[j].weight < min2 */
                    index2 = j;
                }
            }
        }
        ht[i].weight = min1 + min2;     /* ������Ȩֵ����Сֵ �� ��Сֵ��ӵõ����ߵ�˫�׽ڵ��Ȩֵ */
        ht[i].lchild = index1;    /* ��Сֵ���� */
        ht[i].rchild = index2;   /* ��С���� */              /* �޸ĸ��ڵ� */

        ht[index1].parent = ht[index2].parent = i;  /* ��Сֵ �� ��Сֵ�� parent */     /* �޸����������ڵ� */
    }
}

/*���� ����������*/
void createHaffmanCode( HaffmanTree ht, HaffmanCode hc )
{
    char code[N];   /*��ʱ��Ź���������*/
    int i, j, start;

    for (i=0; i<N; i++)     /*�������*/
    {
        start = N - 1;
        code[start] = '\0';
        j = i;
        while(ht[j].parent != -1)   /*������ڵ�����*/
        {
            code[--start] = ht[ht[j].parent].lchild == j?'0':'1'; /* ˫�׵�lchild == �ýڵ���±꣬��ֵΪ0������Ϊ1 */
            j = ht[j].parent;   /*˫�׵��±�*/
        }
        strcpy(hc[i].code, &code[start]);   /*code ������, ��ֵ�ĵط��ĵ�ַ(��Ϊ�ǵ���)���� hc[i].code���൱�ڸ��׵�ַ��*/
    }

}


/*��ӡ code*/
void printCode( HaffmanCode hc )
{
    int i;

    for (i=0; i<N; i++)
    {
        printf("%c�ı�����: %s\n", hc[i].data, hc[i].code);
    }
}



int main()
{
    HaffmanCode hc;
    HaffmanTree ht;

    initHaffmanCode(hc);       /*��ʼ��*/
    initHaffmanTree(ht, hc);

    createHaffmanTree(ht);     /*����*/
    createHaffmanCode(ht, hc);

    printCode(hc);

    return 0;
}
