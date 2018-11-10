#include <stdio.h>
#include <stdlib.h>

#define M 100

typedef struct node
{
    char data;
    struct node *lchild, *rchild;
}BTNode;



/*
 * ����������:
 *
 *��������Ϊ������
 *���� # ʱ������һ�㣬��־λ��Ϊ 2 Ҳ���Ǹýڵ��������
 *������Ϊ # ʱ��ջ�ýڵ㣬�����ʸ��ڵ��������
 *
*/
BTNode *createBiTree( char *str )
{
    BTNode *s[M];   /* ջ */
    BTNode *b=NULL, *p;  /* b:ָ����ڵ㣬 p:ֱ���´��ڵ� */
    int top=-1, i=0, flag=1;

    while ( str[i] != '\0')
    {
        if ( str[i] != '#' )
        {
            p = (BTNode *)malloc(sizeof(BTNode));
            p->data = str[i];
            p->lchild = p->rchild = NULL;

            if ( b == NULL )    /* b ָ����ڵ� */
                b = p;
            else
            {
                switch ( flag )
                {
                case 1:       /* ������ */
                    s[top]->lchild = p;
                    break;
                case 2:        /* ������ */
                    s[top]->rchild = p;
                    top--;      /* ��ջ */
                    break;
                }
            }
            s[++top] = p;   /* ��ջ */
            flag = 1;
        }
        else
        {
            flag = 2;
            if ( str[i-1] == '#' )      /* �ýڵ�û���������������ջ */
                top--;
        }
        i++;
    }

    return b;
}

///////////////// �ݹ����  ////////////////////////
/* ����ݹ��㷨 */
void PreOrder1( BTNode *b )
{
    if ( b == NULL )
        return ;
    else
    {
        printf(" %c", b->data);
        PreOrder1( b->lchild );
        PreOrder1( b->rchild );
    }
}

/* ����ݹ��㷨 */
void InOrder1( BTNode *b )
{
    if ( b == NULL )
        return ;
    else
    {
        InOrder1( b->lchild );
        printf(" %c", b->data);
        InOrder1( b->rchild );
    }
}


/* ����ݹ��㷨 */
void PostOrder1( BTNode *b )
{
    if ( b == NULL )
        return ;
    else
    {
        PostOrder1( b->lchild );
        PostOrder1( b->rchild );
        printf(" %c", b->data);
    }
}

///////////////// �ǵݹ����  ////////////////////////
///////////////// �ǵݹ������ջ��ʵ��


/* ����ǵݹ��㷨 */
/*
 *������������ң���pָ���ʱ���ýڵ��ջ������ p ָ��ýڵ��������
 *��������ҲΪ�գ����ջ�ýڵ�ĸ��ڵ㣬���� p ָ�򸸽ڵ��������
 *
*/
void PreOrder( BTNode *b )
{
    BTNode *s[M], *p = b;
    int top=-1;

    while ( p != NULL || top != -1 )    /* p��Ϊ�գ�ջ��Ϊ�� */
    {
        if ( p != NULL )        /* ���������� */
        {
            printf(" %c", p->data);
            s[++top] = p;   /* ��ջ */
            p = p->lchild;
        }
        else        /* ���������� */
        {
            p = s[top--];   /* p ָ��ջ�������ҳ�ջ*/
            p = p->rchild;
        }
    }
}

/* ����ǵݹ��㷨 */
void InOrder( BTNode *b )
{
    BTNode *s[M], *p = b;
    int top=-1;

    while ( p != NULL || top != -1 )
    {
        if ( p != NULL )
        {
            s[++top] = p;
            p = p->lchild;
        }
        else
        {
            p = s[top--];
            printf(" %c", p->data);
            p = p->rchild;
        }
    }
}


/* ����ǵݹ��㷨 */
/*
 *������ǰ������ͬ����Ҫ��һ��ջ����Ŷ�Ӧ��ջ�ı�־λ
 *�������η��ʸýڵ�ʱ�Ŵ�ӡ�ýڵ�
 *
 *--����ӡ��һ�����󣬲����᷵��ִ��if������ִ��else if��Ҳ���Ǹ��ڵ��������
 *
*/
void PostOrder( BTNode *b )
{
    BTNode *s1[M], *s2[M], *p = b;
    int top=-1;

    while ( p != NULL || top != -1 )
    {
        if ( p != NULL )
        {
            s1[++top] = p;      /* ��ջ */
            p = p->lchild;
            s2[top] = 1;    /* �� 1 �η��ʸýڵ� */
        }
        else if ( s2[top] == 1 )
        {
            p = s1[top];
            p = p->rchild;
            s2[top] = 2;    /* �� 2 �η��ʸýڵ� */
        }
        else
        {
            p = s1[top--];  /* ��ջ */
            printf(" %c", p->data);
            p = NULL;       /* ����ֱ���´�ѭ���� if ���, ���� else if ���ж� */
        }
    }


}


int main()
{
    BTNode *b;
    char str[M];

    gets( str );
    b = createBiTree( str );

    ///////////////////////////////////////
    printf("              Recursion: \n\n");
    printf("PreOrder1:  ");
    PreOrder1( b );     /* ����ݹ��㷨 */
    printf("\n");

    printf("InOrder1:   ");
    InOrder1( b );     /* ����ݹ��㷨 */
    printf("\n");

    printf("PostOrder1: ");
    PostOrder1( b );     /* ����ݹ��㷨 */
    printf("\n\n\n");

    ////////////////////////////////////////
    printf("           No Recursion: \n\n");
    printf("PreOrder:   ");
    PreOrder( b );
    printf("\n");

    printf("InOrder:    ");
    InOrder( b );
    printf("\n");

    printf("PostOrder:  ");
    PostOrder( b );
    printf("\n");

    return 0;
}
