#include <stdio.h>
#include <stdlib.h>
#define  MAX   8 /*线性表的最大长度*/

typedef int ElemType; /*数据元素类型*/
/*顺序表类型定义*/
typedef  struct
{
	 ElemType  data[MAX];
     int  length;  /*当前表的长度*/
} SeqList;

/* 初始化 */
SeqList *InitSeqlist()
{
    SeqList *L;
    L = (SeqList *)malloc(sizeof(SeqList));
    L->length = 0;

    return L;
}

/* 输入 */
void input(SeqList *L)
{
    int i;

    srand( time(NULL) );
    for ( i=0; i<MAX; i++ )
    {
        L->data[i] = rand()%100;
        L->length++;
    }
}


/* 输出 */
void output(SeqList *L)
{
    int i;

    for ( i=0; i<MAX; i++ )
        printf("%-4d", L->data[i]);

    printf("\n\n");
}



/* 冒泡排序  O(n^2) */
void BubbleSort( SeqList *L )
{
    int i, j, flag, tmp;

    for ( i=1; i<L->length; i++ )   /* 循环N-1次 */
    {
        flag = 0;   /* 标志位 */

        for ( j=0; j<L->length-i; j++ )
        {
            if ( L->data[j] > L->data[j+1] )
            {
                flag = 1;
                tmp = L->data[j];
                L->data[j] = L->data[j+1];
                L->data[j+1] = tmp;
            }
        }
        if ( flag == 0 )
            return ;
    }
}


/* 快速排序  O(nlog2^n) */
void QuickSort( SeqList *L, int s, int t )
{
    int i, j, tmp;

    i = s;
    j = t;
    tmp = L->data[i];

    if ( s<t )
    {
        while ( i != j )
        {
            /* 右 */
            while ( i<j && L->data[j] >= tmp )    /* 右分区a[j] >= tmp ，继续向左扫描 */
                j--;
            if ( i<j && L->data[j] < tmp )        /* 有分区a[j] < tmp， 赋值，并转向左分区 */
                L->data[i++] = L->data[j];
            /* 左 */
            while ( i<j && L->data[i] <= tmp )
                i++;
            if ( i<j && L->data[i] > tmp )
                L->data[j--] = L->data[i];
        }
        L->data[i] = tmp;
        /* 递归调用 */
        QuickSort( L, s, i-1 );
        QuickSort( L, i+1, t );
    }
}

/* 选择排序  O(n ^2) */
void selectSort( SeqList *L )
{
    int i, j, min, tmp;     /* 该次循环最小值下标  */

    for ( i=0; i<L->length-1; i++ )
    {
        for ( j=i+1, min=i; j<L->length; j++ )
        {
            /* 若最小值为a[min] 则重新赋值min */
            if ( L->data[j] < L->data[min] )
                min = j;
        }
        /* 判断 a[i] 是否是最小值，若不是则重新赋值 */
        if ( min != i )
        {
            tmp = L->data[i];
            L->data[i] = L->data[min];
            L->data[min] = tmp;
        }
    }
}

/* 插入排序 O(n^2) */
void InsertSort( SeqList *L )
{
    int i, j, tmp;

    /* i =1, 第一个数据作为有序对，其余数据作为无序对 */
    for ( i=1; i<L->length; i++ )
    {
        tmp = L->data[i];   /* tmp 为待排数据 */
        j = i-1;    /* j指向待排数据的前一个数据 */
        /* 循环找出待排数据的位置，同时又有数据的后移 */
        while ( j>=0 && tmp < L->data[j] )
        {
            L->data[j+1] = L->data[j];
            j--;
        }
        L->data[j+1] = tmp;     /* j+1 为带插入数据的位置 */
    }
}

/* 希尔排序  O(n^(2/3) */
void ShellSort( SeqList *L )
{
    int d, i, j, tmp;

    /* 每次以 d 为间距进行分组 */
    for ( d=L->length/2; d>0; d/=2 )
    {
        /* 每次进行每组的一个数据的排序（分时） */
        for ( i=d; i<L->length; i++ )
        {
            tmp = L->data[i];
            /* 直接排序，从后往前 */
            for ( j=i-d; j>=0 && tmp<L->data[j]; j-=d )
            {
                L->data[j+d] = L->data[j];
            }
            L->data[j+d] = tmp;     /* 因为上层for循环跳出多执行了一次 j-d */
        }
    }
}


/* 菜单 */
int menu()
{
    int choice;

    printf("               |****************顺序表排序操作************|\n");
    printf("               |                 1. 冒泡排序法            |\n");
    printf("               |                 2. 快速排序法            |\n");
    printf("               |                 3. 选择排序法            |\n");
    printf("               |                 4. 插入排序法            |\n");
    printf("               |                 5. 希尔排序              |\n");
    printf("               |                 0. 退出                  |\n");
    printf("               |******************************************|\n");

    do{
        printf("请输入(0~5): ");
        scanf("%d", &choice);
    }while( choice < 0 || choice > 5 );

    return choice;
}


void form()
{
    SeqList *L;
    int flag=1;

    while ( flag )
    {
        switch( menu() )
        {
        case 1: /* 1. 冒泡排序法 */
            printf("\t\t冒泡排序：\n");
            L = InitSeqlist();
            input( L );
            printf("\n\tBefore sort: \n");
            output( L );
            BubbleSort( L );
            printf("\tSort:\n");
            output( L );
            printf("\n");
            system("pause"); //暂停
            system("cls"); //清屏
            break;
        case 2: /* 2. 快速排序法 */
            printf("\t\t快速排序：\n");
            L = InitSeqlist();
            input( L );
            printf("\n\tBefore sort: \n");
            output( L );
            QuickSort( L, 0, MAX );
            printf("\tSort:\n");
            output( L );
            printf("\n");
            system("pause"); //暂停
            system("cls"); //清屏

            break;
        case 3: /* 3. 选择排序法 */
            printf("\t\t选择排序：\n");
            L = InitSeqlist();
            input( L );
            printf("\n\tBefore sort: \n");
            output( L );
            selectSort( L );
            printf("\tSort:\n");
            output( L );
            printf("\n");
            system("pause"); //暂停
            system("cls"); //清屏

            break;
        case 4: /* 4. 插入排序法 */
            printf("\t\t插入排序：\n");
            L = InitSeqlist();
            input( L );
            printf("\n\tBefore sort: \n");
            output( L );
            InsertSort( L );
            printf("\tSort:\n");
            output( L );
            printf("\n");
            system("pause"); //暂停
            system("cls"); //清屏

            break;
        case 5: /* 5. 希尔排序 */
            printf("\t\t希尔排序：\n");
            L = InitSeqlist();
            input( L );
            printf("\n\tBefore sort: \n");
            output( L );
            ShellSort( L );
            printf("\tSort:\n");
            output( L );
            printf("\n");
            system("pause"); //暂停
            system("cls"); //清屏

            break;
        case 0: /* 0. 退出 */
            flag = 0;
        }
    }
}



int main()
{
    form();

    return 0;
}
