#include <stdio.h>
#include <stdlib.h>

#define M 100

typedef struct node
{
    char data;
    struct node *lchild, *rchild;
}BTNode;



/*
 * 创建二叉树:
 *
 *创建次序为从左到右
 *遇到 # 时返回上一层，标志位变为 2 也就是该节点的右子树
 *右子树为 # 时出栈该节点，并访问父节点的右子树
 *
*/
BTNode *createBiTree( char *str )
{
    BTNode *s[M];   /* 栈 */
    BTNode *b=NULL, *p;  /* b:指向根节点， p:直接新创节点 */
    int top=-1, i=0, flag=1;

    while ( str[i] != '\0')
    {
        if ( str[i] != '#' )
        {
            p = (BTNode *)malloc(sizeof(BTNode));
            p->data = str[i];
            p->lchild = p->rchild = NULL;

            if ( b == NULL )    /* b 指向根节点 */
                b = p;
            else
            {
                switch ( flag )
                {
                case 1:       /* 左子树 */
                    s[top]->lchild = p;
                    break;
                case 2:        /* 右子树 */
                    s[top]->rchild = p;
                    top--;      /* 出栈 */
                    break;
                }
            }
            s[++top] = p;   /* 入栈 */
            flag = 1;
        }
        else
        {
            flag = 2;
            if ( str[i-1] == '#' )      /* 该节点没有左右子树，则出栈 */
                top--;
        }
        i++;
    }

    return b;
}

///////////////// 递归遍历  ////////////////////////
/* 先序递归算法 */
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

/* 中序递归算法 */
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


/* 后序递归算法 */
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

///////////////// 非递归遍历  ////////////////////////
///////////////// 非递归借助于栈来实现


/* 先序非递归算法 */
/*
 *先序遍历从左到右，当p指向空时，该节点出栈，并且 p 指向该节点的右子树
 *若右子树也为空，则出栈该节点的父节点，并且 p 指向父节点的右子树
 *
*/
void PreOrder( BTNode *b )
{
    BTNode *s[M], *p = b;
    int top=-1;

    while ( p != NULL || top != -1 )    /* p不为空，栈不为空 */
    {
        if ( p != NULL )        /* 访问左子树 */
        {
            printf(" %c", p->data);
            s[++top] = p;   /* 入栈 */
            p = p->lchild;
        }
        else        /* 访问右子树 */
        {
            p = s[top--];   /* p 指向栈顶，并且出栈*/
            p = p->rchild;
        }
    }
}

/* 中序非递归算法 */
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


/* 后序非递归算法 */
/*
 *后序与前、中序不同，需要另一个栈来存放对应入栈的标志位
 *当第三次访问该节点时才打印该节点
 *
 *--当打印第一个数后，并不会返回执行if，而是执行else if，也就是父节点的右子树
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
            s1[++top] = p;      /* 入栈 */
            p = p->lchild;
            s2[top] = 1;    /* 第 1 次访问该节点 */
        }
        else if ( s2[top] == 1 )
        {
            p = s1[top];
            p = p->rchild;
            s2[top] = 2;    /* 第 2 次访问该节点 */
        }
        else
        {
            p = s1[top--];  /* 出栈 */
            printf(" %c", p->data);
            p = NULL;       /* 跳过直接下次循环的 if 语句, 进行 else if 的判断 */
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
    PreOrder1( b );     /* 先序递归算法 */
    printf("\n");

    printf("InOrder1:   ");
    InOrder1( b );     /* 中序递归算法 */
    printf("\n");

    printf("PostOrder1: ");
    PostOrder1( b );     /* 后序递归算法 */
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
