#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ADestination
{
    char city[20];
    int distance;
} Destination;

typedef struct ACabin
{
    int code;
    char city[20];
    int distance;
} Cabin;

Destination destination[50];

void bubbleSortPLUS(int a[], int n)
{
    int i, j, hold, flag;
    for (i = 0; i < n - 1; i++)
    {
        flag = 0;
        for (j = 0; j < n - 1 - i; j++)
        {
            if (a[j] < a[j + 1])
            {
                hold = a[j];
                a[j] = a[j + 1];
                a[j + 1] = hold;
                flag = 1;
            }
        }
        if (flag == 0)
            break;
    }
}

int main()
{
    int destination_num, B_cabin_num;
    int push = 0;
    scanf("%d", &destination_num);
    for (int i = 0; i < destination_num; i++)
    {
        scanf("%s %d", destination[i].city, &destination[i].distance);
    }

    scanf("%d", &B_cabin_num);

    Cabin A_cabin[50];
    Cabin B_cabin[50];
    Cabin C_cabin[50];
    int Compare_cabin[50];

    int top_A = -1;
    int top_B = -1;
    int top_C = -1;

   

    for (int i = 0; i < B_cabin_num; i++)
    {
        scanf("%d %s", &B_cabin[B_cabin_num - i - 1].code, B_cabin[B_cabin_num - i - 1].city);

        
        for (int j = 0; j < destination_num; j++)
        {
            if (strcmp(B_cabin[B_cabin_num - i - 1].city, destination[j].city) == 0)
            {
                B_cabin[B_cabin_num - i - 1].distance = destination[j].distance;
            }
        }
        top_B++;
        Compare_cabin[B_cabin_num - i - 1] = B_cabin[B_cabin_num - i - 1].distance;
    }

    bubbleSortPLUS(Compare_cabin, B_cabin_num);
 int temp_code;
    while (B_cabin_num > 0)
    {
        bool flag = true;
        int max_distance = 0;
        int max_code = 0;
        for (int i = top_B; i >= 0; i--) //从B中找到发往地最远的车厢中离顶最近的车厢
        {
            if (max_distance < B_cabin[i].distance)
            {
                max_distance = B_cabin[i].distance;
                max_code = B_cabin[i].code;
            }
        }
        // printf("%d %d\n",max_code,max_distance);

        while (B_cabin[top_B].code != max_code) //将发往地最远的车厢中离顶最近的车厢至顶的所有车厢依次推进至A中
        {
            A_cabin[++top_A] = B_cabin[top_B--];
            B_cabin_num--;
            push++;
        }
        A_cabin[++top_A] = B_cabin[top_B--];
        B_cabin_num--;
        push++;

        for (int i = 0; i < top_A; i++) //检查车厢是否按里程从远到近排列
        {
            if (A_cabin[i].distance != Compare_cabin[i])
            {
                flag = false;
                temp_code = A_cabin[i].code;
                break;
            }
        }

        if (!flag) //车厢中有不按里程从远到近排列的
        {
            // printf("ERROR!\n");
            C_cabin[++top_C] = A_cabin[top_A--];

            while (A_cabin[top_A + 1].code != temp_code) //将A中不按里程从远到近排列的车厢依次推回至B中
            {
                B_cabin[++top_B] = A_cabin[top_A--];
                B_cabin_num++;
            }

            A_cabin[++top_A] = C_cabin[top_C--];
            push++;
        }
 
        /*for (int i = top_B; i >= 0; i--)
        {
            printf("%.4d %s %d\n", B_cabin[i].code, B_cabin[i].city, B_cabin[i].distance);
        }
        printf("\n");

        for (int i = 0; i <= top_A; i++)
        {
            printf("%.4d %s %d\n", A_cabin[i].code, A_cabin[i].city, A_cabin[i].distance);
        }
        printf("\n");
        printf("%d %d\n", push, B_cabin_num);
        printf("\n\n\n\n");*/
    }
        for (int i = 0; i <= top_A; i++)
        {
            printf("%.4d ", A_cabin[i].code);
        }
        printf("\n");
        printf("%d\n", push);
    return 0;
}
