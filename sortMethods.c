#ifndef DEBUG_SORT
#define DEBUG_SORT
#endif

#ifdef DEBUG_SORT
#include <windows.h>
#include <stdio.h>
#endif
#include "sortMethods.h"

/*
================================================
 功能：选择排序
 输入：数组名称（也就是数组首地址）、数组中元素个数
================================================
*/
/*
====================================================
算法思想简单描述：
 在要排序的一组数中，选出最小的一个数与第一个位置的数交换；
 然后在剩下的数当中再找最小的与第二个位置的数交换，如此循环
 到倒数第二个数和最后一个数比较为止。 
 选择排序是不稳定的。算法复杂度O(n2)--[n的平方]
=====================================================
*/
void select_sort(int *x, int n)
{
    int i, j, min, t;
    for (i = 0; i < n - 1; i++) /*要选择的次数：0~n-2共n-1次*/
    {
        min = i;                    /*假设当前下标为i的数最小，比较后再调整*/
        for (j = i + 1; j < n; j++) /*循环找出最小的数的下标是哪个*/
        {
            if (*(x + j) < *(x + min))
            {
                min = j; /*如果后面的数比前面的小，则记下它的下标*/
            }
        }

        if (min != i) /*如果min在循环中改变了，就需要交换数据*/
        {
            t = *(x + i);
            *(x + i) = *(x + min);
            *(x + min) = t;
        }
    }
}

/*
================================================
 功能：直接插入排序
 输入：数组名称（也就是数组首地址）、数组中元素个数
================================================
*/
/*
====================================================
算法思想简单描述：
 在要排序的一组数中，假设前面(n-1) [n>=2] 个数已经是排
 好顺序的，现在要把第n个数插到前面的有序数中，使得这n个数
 也是排好顺序的。如此反复循环，直到全部排好顺序。
 
 直接插入排序是稳定的。算法时间复杂度O(n2)--[n的平方]
=====================================================
*/
void insert_sort(int *x, int n)
{
    int i, j, t;
    for (i = 1; i < n; i++) /*要选择的次数：1~n-1共n-1次*/
    {
        /*
   暂存下标为i的数。注意：下标从1开始，原因就是开始时
   第一个数即下标为0的数，前面没有任何数，单单一个，认为
   它是排好顺序的。
  */
        t = *(x + i);
        for (j = i - 1; j >= 0 && t < *(x + j); j--) /*注意：j=i-1，j--，这里就是下标为i的数，在它前面有序列中找插入位置。*/
        {
            *(x + j + 1) = *(x + j); /*如果满足条件就往后挪。最坏的情况就是t比下标为0的数都小，它要放在最前面，j==-1，退出循环*/
        }
        *(x + j + 1) = t; /*找到下标为i的数的放置位置*/
    }
}

/*
================================================
 功能：冒泡排序
 输入：数组名称（也就是数组首地址）、数组中元素个数
================================================
*/
/*
====================================================
算法思想简单描述：
 在要排序的一组数中，对当前还未排好序的范围内的全部数，自上
 而下对相邻的两个数依次进行比较和调整，让较大的数往下沉，较
 小的往上冒。即：每当两相邻的数比较后发现它们的排序与排序要
 求相反时，就将它们互换。
 
 下面是一种改进的冒泡算法，它记录了每一遍扫描后最后下沉数的
 位置k，这样可以减少外层循环扫描的次数。
 冒泡排序是稳定的。算法时间复杂度O(n2)--[n的平方]
=====================================================
*/
void bubble_sort(int *x, int n)
{
    int j, k, h, t;

    for (h = n - 1; h > 0; h = k) /*循环到没有比较范围*/
    {
        for (j = 0, k = 0; j < h; j++) /*每次预置k=0，循环扫描后更新k*/
        {
            if (*(x + j) > *(x + j + 1)) /*大的放在后面，小的放到前面*/
            {
                t = *(x + j);
                *(x + j) = *(x + j + 1);
                *(x + j + 1) = t; /*完成交换*/
                k = j;            /*保存最后下沉的位置。这样k后面的都是排序排好了的。*/
            }
        }
    }
}

/*
================================================
 功能：希尔排序
 输入：数组名称（也就是数组首地址）、数组中元素个数
================================================
*/
/*
====================================================
算法思想简单描述：
 
 在直接插入排序算法中，每次插入一个数，使有序序列只增加1个节点，
 并且对插入下一个数没有提供任何帮助。如果比较相隔较远距离（称为
 增量）的数，使得数移动时能跨过多个元素，则进行一次比较就可能消除
 多个元素交换。D.L.shell于1959年在以他名字命名的排序算法中实现
 了这一思想。算法先将要排序的一组数按某个增量d分成若干组，每组中
 记录的下标相差d.对每组中全部元素进行排序，然后再用一个较小的增量
 对它进行，在每组中再进行排序。当增量减到1时，整个要排序的数被分成
 一组，排序完成。
 
 下面的函数是一个希尔排序算法的一个实现，初次取序列的一半为增量，
 以后每次减半，直到增量为1。
 希尔排序是不稳定的。
=====================================================
*/
void shell_sort(int *x, int n)
{
    int h, j, k, t;
    for (h = n / 2; h > 0; h = h / 2) /*控制增量*/
    {
        for (j = h; j < n; j++) /*这个实际上就是上面的直接插入排序*/
        {
            t = *(x + j);
            for (k = j - h; (k >= 0 && t < *(x + k)); k -= h)
            {
                *(x + k + h) = *(x + k);
            }
            *(x + k + h) = t;
        }
    }
}

/*
================================================
 功能：快速排序
 输入：数组名称（也就是数组首地址）、数组中起止元素的下标
================================================
*/
/*
====================================================
算法思想简单描述：
 快速排序是对冒泡排序的一种本质改进。它的基本思想是通过一趟
 扫描后，使得排序序列的长度能大幅度地减少。在冒泡排序中，一次
 扫描只能确保最大数值的数移到正确位置，而待排序序列的长度可能只
 减少1。快速排序通过一趟扫描，就能确保某个数（以它为基准点吧）
 的左边各数都比它小，右边各数都比它大。然后又用同样的方法处理
 它左右两边的数，直到基准点的左右只有一个元素为止。它是由
 C.A.R.Hoare于1962年提出的。
 
 显然快速排序可以用递归实现，当然也可以用栈化解递归实现。下面的
 函数是用递归实现的，有兴趣的朋友可以改成非递归的。
 快速排序是不稳定的。最理想情况算法时间复杂度O(nlog2n)，最坏O(n2)
 
=====================================================
*/
void quick_sort(int *x, int low, int high)
{
    int i, j, t;
    if (low < high) /*要排序的元素起止下标，保证小的放在左边，大的放在右边。这里以下标为low的元素为基准点*/
    {
        i = low;
        j = high;
        t = *(x + low); /*暂存基准点的数*/
        while (i < j)   /*循环扫描*/
        {
            while (i<j &&*(x + j)> t) /*在右边的只要比基准点大仍放在右边*/
            {
                j--; /*前移一个位置*/
            }
            if (i < j)
            {
                *(x + i) = *(x + j); /*上面的循环退出：即出现比基准点小的数，替换基准点的数*/
                i++;                 /*后移一个位置，并以此为基准点*/
            }
            while (i < j && *(x + i) <= t) /*在左边的只要小于等于基准点仍放在左边*/
            {
                i++; /*后移一个位置*/
            }
            if (i < j)
            {
                *(x + j) = *(x + i); /*上面的循环退出：即出现比基准点大的数，放到右边*/
                j--;                 /*前移一个位置*/
            }
        }
        *(x + i) = t;               /*一遍扫描完后，放到适当位置*/
        quick_sort(x, low, i - 1);  /*对基准点左边的数再执行快速排序*/
        quick_sort(x, i + 1, high); /*对基准点右边的数再执行快速排序*/
    }
}

/*
================================================
 功能：堆排序
 输入：数组名称（也就是数组首地址）、数组中元素个数
================================================
*/
/*
====================================================
算法思想简单描述：
 堆排序是一种树形选择排序，是对直接选择排序的有效改进。
 堆的定义如下：具有n个元素的序列（h1,h2,...,hn),当且仅当
 满足（hi>=h2i,hi>=2i+1）或（hi<=h2i,hi<=2i+1）(i=1,2,...,n/2)
 时称之为堆。在这里只讨论满足前者条件的堆。
 由堆的定义可以看出，堆顶元素（即第一个元素）必为最大项。完全二叉树可以
 很直观地表示堆的结构。堆顶为根，其它为左子树、右子树。
 初始时把要排序的数的序列看作是一棵顺序存储的二叉树，调整它们的存储顺序，
 使之成为一个堆，这时堆的根节点的数最大。然后将根节点与堆的最后一个节点
 交换。然后对前面(n-1)个数重新调整使之成为堆。依此类推，直到只有两个节点
 的堆，并对它们作交换，最后得到有n个节点的有序序列。
 从算法描述来看，堆排序需要两个过程，一是建立堆，二是堆顶与堆的最后一个元素
 交换位置。所以堆排序有两个函数组成。一是建堆的渗透函数，二是反复调用渗透函数
 实现排序的函数。
 堆排序是不稳定的。算法时间复杂度O(nlog2n)。
*/
/*
 功能：渗透建堆
 输入：数组名称（也就是数组首地址）、参与建堆元素的个数、从第几个元素开始
*/
void sift(int *x, int n, int s)
{
    int t, k, j;
    t = *(x + s);  /*暂存开始元素*/
    k = s;         /*开始元素下标*/
    j = 2 * k + 1; /*右子树元素下标*/
    while (j < n)
    {
        if (j < n - 1 && *(x + j) < *(x + j + 1)) /*判断是否满足堆的条件：满足就继续下一轮比较，否则调整。*/
        {
            j++;
        }
        if (t < *(x + j)) /*调整*/
        {
            *(x + k) = *(x + j);
            k = j; /*调整后，开始元素也随之调整*/
            j = 2 * k + 1;
        }
        else /*没有需要调整了，已经是个堆了，退出循环。*/
        {
            break;
        }
    }

    *(x + k) = t; /*开始元素放到它正确位置*/
}

/*
 功能：堆排序
 输入：数组名称（也就是数组首地址）、数组中元素个数
*/
void heap_sort(int *x, int n)
{
    int i, k, t;
    int *p;
    for (i = n / 2 - 1; i >= 0; i--)
    {
        sift(x, n, i); /*初始建堆*/
    }

    for (k = n - 1; k >= 1; k--)
    {
        t = *(x + 0); /*堆顶放到最后*/
        *(x + 0) = *(x + k);
        *(x + k) = t;
        sift(x, k, 0); /*剩下的数再建堆*/
    }
}

#if 1
void main()
{
#define MAX 4
    int *p, i, a[MAX];

    /*录入测试数据*/
    p = a;
    printf("Input %d number for sorting :\n", MAX);
    for (i = 0; i < MAX; i++)
    {
        scanf("%d", p++);
    }
    printf("\n");
    /*测试选择排序*/

    p = a;
    select_sort(p, MAX);
    /**/

    /*测试直接插入排序*/
    /*
 p = a;
 insert_sort(p,MAX);
 */

    /*测试冒泡排序*/
    /*
 p = a;
 insert_sort(p,MAX);
 */
    /*测试快速排序*/
    /*
 p = a;
 quick_sort(p,0,MAX-1);
 */
    /*测试堆排序*/
    /*
 p = a;
 heap_sort(p,MAX);
 */
    for (p = a, i = 0; i < MAX; i++)
    {
        printf("%d ", *p++);
    }

    printf("\n");
    system("pause");
}
#endif
