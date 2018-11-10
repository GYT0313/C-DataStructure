#include <stdio.h>
#include <stdlib.h>

/*
要求：
1．	输入说明：输入为一行正整数，其中第1个数字N（N<=1000）为顾客总数，后面跟着N位顾客的编号。
    编号为奇数的顾客需要到A窗口办理业务，为偶数顾客则去B窗口。数字以空格分隔。
2．	输出说明：按业务处理完成的顺序输出顾客的编号。数字间以空格分隔，但最后一个编号不能有多余的空格。
*/

typedef struct node     /* 指向数据的结构体 */
{
    int Data;
    struct node *Next;
} Qnode;

typedef struct link     /* 指向节点的结构体 */
{
    Qnode *Front, *Rear;
    struct link *Next;
} LinkQueue;


/* 初始化 */
LinkQueue *initQueue()
{
    LinkQueue *q;
    Qnode *p;

    q = (LinkQueue *)malloc(sizeof(LinkQueue));
    q->Front = q->Rear = (Qnode *)malloc(sizeof(Qnode));
    q->Front->Next = NULL;

    return q;
}


/* 是否为空，为空返回1 */
int isEmpty( LinkQueue *q )
{
    if ( q->Front == q->Rear )
        return 1;
    else
        return 0;
}


/* 入队 A 窗口*/
void EnqueueA( LinkQueue *q, int data )
{
    Qnode *p;

    p = (Qnode *)malloc(sizeof(Qnode));

    p->Data = data;
    p->Next = NULL;

    q->Rear->Next = p;
    q->Rear = p;
}

/* 入队 B 窗口 */
void EnqueueB( LinkQueue *q, int data )
{
    Qnode *p;

    p = (Qnode *)malloc(sizeof(Qnode));

    p->Data = data;
    p->Next = NULL;

    q->Rear->Next = p;
    q->Rear = p;
}

/* 出队 */
void OutQueue( LinkQueue *q, int *queue )
{
    if ( isEmpty(q) )
        return '#';

    Qnode *p, *m;

    p = q->Front->Next;
    q->Front->Next = p->Next;   /* 队头指向下一个节点 */
    *queue = p->Data;

    m = q->Front;
    while( m->Next )    /* m 指向队尾*/
        m = m->Next;
    q->Rear = m;
}

/* Question I II 打印语句 */
void print( int N, LinkQueue *qA, LinkQueue *qB, int *queue )
{
    int i, flag=0;      /* flag 判断 A 出队次数 */
    /* 入队 */
    for ( i=0; i<N; i++ )
    {
        if ( queue[i]%2 == 1 )  /* 奇数到 A 窗口 */
        {
            EnqueueA( qA, queue[i] );
        }
        else                    /* 偶数到 B 窗口 */
            EnqueueB( qB, queue[i] );
    }
    /* 出队 */
    for ( i=0; i<N; i++ )
    {
        if ( flag < 2 && !isEmpty( qA ))    /* A 出队 */
        {
            OutQueue( qA, &queue[i] );
            flag++;
        }
        else if ( !isEmpty( qB ) )          /* B 出队 */
        {
            OutQueue( qB, &queue[i] );
            flag = 0;
        }
        else
        {
            if ( !isEmpty( qA ) )
                OutQueue( qA, &queue[i] );
            else if ( !isEmpty( qB ) )
                OutQueue( qB, &queue[i] );
            flag = 0;
        }
    }

    printf("The order of queue: ");
    for ( i=0; i<N; i++ )
        printf(" %d", queue[i]);
    printf("\n");
}

/* Question III 打印语句 */
void print2( int N, int NA, int NB, LinkQueue *qA, LinkQueue *qB, int *queue )
{
    int i, flag=0, flag2=0;     /* flag 判断 A 出队次数, flag2 判断 B 出队次数 */
    /* 入队 */
    for ( i=0; i<N; i++ )
    {
        if ( queue[i]%2 == 1 )  /* 奇数到 A 窗口 */
        {
            EnqueueA( qA, queue[i] );
        }
        else                    /* 偶数到 B 窗口 */
            EnqueueB( qB, queue[i] );
    }
    /* 出队 */
    for ( i=0; i<N; i++ )
    {
        if ( flag < NA && !isEmpty( qA ))       /* A 出队 */
        {
            OutQueue( qA, &queue[i] );
            flag++;
            flag2 = 0;
        }
        else if ( !isEmpty( qB ) )          /* B 出队 */
        {
            OutQueue( qB, &queue[i] );
            flag2++;
            if ( flag2 >= NB )      /* 判断 B 出队次数是否满足 */
                flag = 0;
        }
        else
        {
            if ( !isEmpty( qA ) )
                OutQueue( qA, &queue[i] );
            else if ( !isEmpty( qB ) )
                OutQueue( qB, &queue[i] );
            flag = 0;
            flag2 = 0;
        }
    }

    printf("The order of queue: ");
    for ( i=0; i<N; i++ )
        printf(" %d", queue[i]);
    printf("\n");
}


int main()
{
    LinkQueue *qA, *qB;
    int N;
    int queue[1000], i;
    int NA, NB;

    qA = initQueue();
    qB = initQueue();

    printf("Question I:\n");        /* 从键盘接收 */
    printf("N: ");
    scanf("%d", &N);
    for ( i=0; i<N; i++ )
        scanf("%d", &queue[i]);
    print( N, qA, qB, queue );


    ////////////////////////////////////////////////////
    printf("\n");
    printf("Question II:\n");       /* 按照 rand() 计算 */
    printf("N: ");
    scanf("%d", &N);
    for ( i=0; i<N; i++ )
        queue[i] = rand()%1000+1;

    printf("The rand number: ");
    for(i=0; i<N; i++)
        printf("%d ", queue[i]);
        printf("\n");
    print( N, qA, qB, queue );


    ////////////////////////////////////////////////////
    printf("\n");
    printf("Question III:\n");      /* 按照 NA : NB 计算 */
    printf("N: ");
    scanf("%d", &N);
    printf("NA:NB: ");
    scanf("%d%d", &NA, &NB);
    for ( i=0; i<N; i++ )
        queue[i] = rand()%1000+1;

    printf("The rand number: ");
    for(i=0; i<N; i++)
        printf("%d ", queue[i]);
        printf("\n");
    print2( N, NA, NB, qA, qB, queue );

    return 0;
}

