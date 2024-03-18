#include <stdio.h>
#include <string.h>

typedef struct aBook
{
	char name[51];
	char writer[21];
	char press[31];
	char publish_date[11];
} Book;
Book book[500];
int book_num;
//------------------------------------------------------------------//
void bubbleSortPLUS(Book a[], int n) // 冒泡排序
{
	int i, j, flag;
	Book temp;
	for (i = 0; i < n - 1; i++)
	{
		flag = 0;
		for (j = 0; j < n - 1 - i; j++)
		{
			if (strcmp(a[j].name, a[j + 1].name) > 0)
			{
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
				flag = 1;
			}
		}
		if (flag == 0)
			break;
	}
}
//------------------------------------------------------------------//

void transfer(char ch[], Book *book) // 将字符串变成book类型
{
	int chj, bookj;
	//-----------------------------------------------------
	for (chj = 0, bookj = 0; ch[chj] != ' '; chj++, bookj++) // 书名
	{
		(*book).name[bookj] = ch[chj];
	}
	for (int k = bookj; k < 50; k++)
	{
		(*book).name[k] = ' ';
	}
	(*book).name[50] = '\0';
	chj++;
	// printf("%s",(*book).name);
	//-----------------------------------------------------
	for (bookj = 0; ch[chj] != ' '; chj++, bookj++) // 作者
	{
		(*book).writer[bookj] = ch[chj];
	}
	for (int k = bookj; k < 20; k++)
	{
		(*book).writer[k] = ' ';
	}
	(*book).writer[20] = '\0';
	chj++;
	// printf("%s",(*book).writer);
	//-----------------------------------------------------
	for (bookj = 0; ch[chj] != ' '; chj++, bookj++) // 出版社
	{
		(*book).press[bookj] = ch[chj];
	}
	for (int k = bookj; k < 30; k++)
	{
		(*book).press[k] = ' ';
	}
	(*book).press[30] = '\0';
	chj++;
	// printf("%s",(*book).press);
	//-----------------------------------------------------
	for (bookj = 0; ch[chj] != '\0' && ch[chj] != '\n'; chj++, bookj++) // 出版时间
	{
		(*book).publish_date[bookj] = ch[chj];
	}
	for (int k = bookj; k < 10; k++)
	{
		(*book).publish_date[k] = ' ';
	}
	(*book).publish_date[30] = '\0';
	// printf("%s嘉然可爱捏\n",(*book).publish_date);
	book_num++;
}
//------------------------------------------------------------------//

void all_file_print_out(int book_num) // 输出到ordered.txt文件中
{
	FILE *pp;
	pp = fopen("ordered.txt", "w");
	for (int m = 0; m < book_num; m++)
	{
		fputs(book[m].name, pp);
		fputs(book[m].writer, pp);
		fputs(book[m].press, pp);
		fputs(book[m].publish_date, pp);
		fputc('\n', pp);
	}
	fclose(pp);
}
//------------------------------------------------------------------//
void delete_item(Book book0[], int *n, char item[])
{
	int k = 0;
	for (int i = 0; i < *n; i++)
	{
		if (strstr(book0[i].name, item) != NULL)
			k++;
		else
			book0[i - k] = book0[i];
	}
	(*n) -= k;
}
//------------------------------------------------------------------//
void search_item(Book book[], int book_num, char item[])
{
	for (int j = 0; j < book_num; j++)
	{
		if (strstr(book[j].name, item) != NULL)
		{
			printf("%s%s%s%s\n", book[j].name, book[j].writer, book[j].press, book[j].publish_date);
		}
	}
}
//------------------------------------------------------------------//
void all_system_print_out(int book_num) // test function
{
	for (int j = 0; j < book_num; j++)
	{
		printf("%s%s%s%s嘉然可爱捏\n", book[j].name, book[j].writer, book[j].press, book[j].publish_date);
	}
}
//------------------------------------------------------------------//

int main()
{
	FILE *fp;
	fp = fopen("books.txt", "r");
	char information[120];
	char item[51];
	char buf;
	int i = 0;
	int flag = 0;
	int length;
	while ((fgets(information, 1024, fp)) && information != NULL)
	{

		transfer(information, &book[i]);
		i++;
	}
	fclose(fp);

	// printf("%s%s%s%s\n",book[0].name,book[0].writer,book[0].press,book[0].publish_date);
	// printf("%s%s%s%s\n",book[1].name,book[1].writer,book[1].press,book[1].publish_date);
	bubbleSortPLUS(book, book_num);

	// printf("%d",book_num);
	scanf("%d", &flag);
	buf = fgetc(stdin);
	while (flag != 0)
	{
		switch (flag)
		{
		case 1:
			fgets(information, 1024, stdin);
			transfer(information, &book[book_num]);
			// printf("%d\n",book_num);
			// printf("%s%s%s%s\n",book[book_num-1].name,book[book_num-1].writer,book[book_num-1].press,book[book_num-1].publish_date);
			bubbleSortPLUS(book, book_num);
			break;
		case 2:
			fgets(item, 1024, stdin);
			length = strlen(item);
			item[length - 1] = '\0';
			search_item(book, book_num, item);
			break;
		case 3:
			fgets(item, 1024, stdin);
			length = strlen(item);
			item[length - 1] = '\0';
			delete_item(book, &book_num, item);
			break;
		}
		scanf("%d", &flag);
		buf = fgetc(stdin);
		// all_system_print_out(book_num);
	}
	// all_system_print_out(book_num);
	all_file_print_out(book_num);
	return 0;
}
