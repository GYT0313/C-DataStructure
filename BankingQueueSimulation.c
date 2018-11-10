#include <stdio.h>
#include <stdlib.h>

/*
Ҫ��
1��	����˵��������Ϊһ�������������е�1������N��N<=1000��Ϊ�˿��������������Nλ�˿͵ı�š�
    ���Ϊ�����Ĺ˿���Ҫ��A���ڰ���ҵ��Ϊż���˿���ȥB���ڡ������Կո�ָ���
2��	���˵������ҵ������ɵ�˳������˿͵ı�š����ּ��Կո�ָ��������һ����Ų����ж���Ŀո�
*/

typedef struct node     /* ָ�����ݵĽṹ�� */
{
    int Data;
    struct node *Next;
} Qnode;

typedef struct link     /* ָ��ڵ�Ľṹ�� */
{
    Qnode *Front, *Rear;
    struct link *Next;
} LinkQueue;


/* ��ʼ�� */
LinkQueue *initQueue()
{
    LinkQueue *q;
    Qnode *p;

    q = (LinkQueue *)malloc(sizeof(LinkQueue));
    q->Front = q->Rear = (Qnode *)malloc(sizeof(Qnode));
    q->Front->Next = NULL;

    return q;
}


/* �Ƿ�Ϊ�գ�Ϊ�շ���1 */
int isEmpty( LinkQueue *q )
{
    if ( q->Front == q->Rear )
        return 1;
    else
        return 0;
}


/* ��� A ����*/
void EnqueueA( LinkQueue *q, int data )
{
    Qnode *p;

    p = (Qnode *)malloc(sizeof(Qnode));

    p->Data = data;
    p->Next = NULL;

    q->Rear->Next = p;
    q->Rear = p;
}

/* ��� B ���� */
void EnqueueB( LinkQueue *q, int data )
{
    Qnode *p;

    p = (Qnode *)malloc(sizeof(Qnode));

    p->Data = data;
    p->Next = NULL;

    q->Rear->Next = p;
    q->Rear = p;
}

/* ���� */
void OutQueue( LinkQueue *q, int *queue )
{
    if ( isEmpty(q) )
        return '#';

    Qnode *p, *m;

    p = q->Front->Next;
    q->Front->Next = p->Next;   /* ��ͷָ����һ���ڵ� */
    *queue = p->Data;

    m = q->Front;
    while( m->Next )    /* m ָ���β*/
        m = m->Next;
    q->Rear = m;
}

/* Question I II ��ӡ��� */
void print( int N, LinkQueue *qA, LinkQueue *qB, int *queue )
{
    int i, flag=0;      /* flag �ж� A ���Ӵ��� */
    /* ��� */
    for ( i=0; i<N; i++ )
    {
        if ( queue[i]%2 == 1 )  /* ������ A ���� */
        {
            EnqueueA( qA, queue[i] );
        }
        else                    /* ż���� B ���� */
            EnqueueB( qB, queue[i] );
    }
    /* ���� */
    for ( i=0; i<N; i++ )
    {
        if ( flag < 2 && !isEmpty( qA ))    /* A ���� */
        {
            OutQueue( qA, &queue[i] );
            flag++;
        }
        else if ( !isEmpty( qB ) )          /* B ���� */
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

/* Question III ��ӡ��� */
void print2( int N, int NA, int NB, LinkQueue *qA, LinkQueue *qB, int *queue )
{
    int i, flag=0, flag2=0;     /* flag �ж� A ���Ӵ���, flag2 �ж� B ���Ӵ��� */
    /* ��� */
    for ( i=0; i<N; i++ )
    {
        if ( queue[i]%2 == 1 )  /* ������ A ���� */
        {
            EnqueueA( qA, queue[i] );
        }
        else                    /* ż���� B ���� */
            EnqueueB( qB, queue[i] );
    }
    /* ���� */
    for ( i=0; i<N; i++ )
    {
        if ( flag < NA && !isEmpty( qA ))       /* A ���� */
        {
            OutQueue( qA, &queue[i] );
            flag++;
            flag2 = 0;
        }
        else if ( !isEmpty( qB ) )          /* B ���� */
        {
            OutQueue( qB, &queue[i] );
            flag2++;
            if ( flag2 >= NB )      /* �ж� B ���Ӵ����Ƿ����� */
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

    printf("Question I:\n");        /* �Ӽ��̽��� */
    printf("N: ");
    scanf("%d", &N);
    for ( i=0; i<N; i++ )
        scanf("%d", &queue[i]);
    print( N, qA, qB, queue );


    ////////////////////////////////////////////////////
    printf("\n");
    printf("Question II:\n");       /* ���� rand() ���� */
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
    printf("Question III:\n");      /* ���� NA : NB ���� */
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

