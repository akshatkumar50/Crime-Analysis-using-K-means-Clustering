#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include<time.h>

#define ANS 15
#define ACS 4
COORD coord= {0,0}; // this is global variable
void gotoxy(int x,int y)
{
    coord.X=x;
    coord.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
/*declaration of checking functions*/
void c_code(char[]);
int check(char[]);

/*structure declaration*/
typedef struct
{
    char name[ANS],code[ACS];
    float rate;
    int quantity;
    int date;
    int month;
    int year;
} rec;
rec item;
typedef struct
{
	char name[ANS],code[ACS],address[350];
	long int no;
} abc;
abc cust;

void analysis();
void dis_analysis();
void d_analysis();
void dbill();
void d_mainmenu();
void display(rec *,int,int);
void window(int,int,int,int);
void dis_con();
void d_search();
void disCust();
void dis_cust();
void highlight(int,int);
int no_of_days(int,int,int);
int days(int,int,int,int,int,int);
int month(int,int);
int mon[12]={31,28,31,30,31,30,31,31,30,31,30,31};

/*declaration of main menu functions*/
void bill() ;
void edit();
void add();
void Customer();
void del();
void exit();

/*declaration of display submenu functions*/
void d_code();
void d_rate();
void d_quan();
void d_all();
void newCust();
void delCust();
void displayCust();

/*start of main*/
int main()
{
    d_mainmenu();
    return 0;
}

void d_mainmenu()
{
    int i;
    char ch;
    	while(1)
	{
		system("cls");
		gotoxy(30,1);
		printf("Store Management System");
		gotoxy(1,2);
		printf("-------------------------------------------------------------------");
		gotoxy(1,30);
		printf("--------------------------------------------------------------------");
		gotoxy(20,25);
		gotoxy(30,8);
		printf("1.   Calculate Bill");
		gotoxy(30,10);
		printf("2.   Adds Products");
		gotoxy(30,12);
		printf("3.   Edit Products");
		gotoxy(30,14);
		printf("4.   Display All");
		gotoxy(30,16);
		printf("5.   Search");
		gotoxy(30,18);
		printf("6.   Delete Goods");
		gotoxy(30,20);
		printf("7.   Analysis");
		gotoxy(30,22);
		printf("8.   Customer");
		gotoxy(30,24);
		printf("9.   Exit");
		gotoxy(30,26);
		printf("Enter Choice:   ");
		scanf("%d",&ch);
		if (ch==1) bill() ;
                else if(ch==2) 
				add();
                else if(ch==3) 
				edit();
                else if (ch==4) 
				d_all();
                else if (ch==5) 
				d_search();
                else if (ch==6) 
				del();
                else if(ch==7) 
				d_analysis();
                else if  (ch==8) 
                Customer();
                else if(ch==9)
				exit(0);
                else
                {
					printf("Try Again");
					getch();
                d_mainmenu();
            }
                
	}
}

void d_search()
{
	system("cls");
    	char ch;
    	gotoxy(30,4);
    	printf("Search Menu");
   		gotoxy(30,8);
		printf("1.   By Code");
		gotoxy(30,10);
		printf("2.   By Rate");
		gotoxy(30,12);
		printf("3.   By Quantity");
		gotoxy(30,14);
		printf("4.   Main Menu");
		gotoxy(30,16);
    	printf("Enter Choice");
    	scanf("%d",&ch);
    	if (ch==1) 
		d_code();
        else if (ch==2)
		d_rate();
        else if (ch==3) 
		d_quan();
        else 
        {
        system("cls");
		printf("Try Again................................");
		getch();
		d_mainmenu();
    	}	
}
void bill()
{
    char x[4]= {0};
    int j=29,q=0,size=0,i=1;
    float total=0,gtotal=0;
    FILE *file;
    file=fopen("record.txt","r+");
    rewind(file);
    system("cls");
    dbill();
    gotoxy(26,15);
    printf("enter  \"end\" to finish input");
    while(1)
    {
        gotoxy(25,18);
        printf("                    ");
        gotoxy(25,19);
        printf("                    ");
        gotoxy(25,18);
        printf("enter item code:");
        scanf("%s",x);
        if(strcmp(x,"end")==0)
            break;
        gotoxy(25,19);
        printf("enter quantity:");
        scanf("%d",&q);
        rewind(file);
        while(fread(&item,sizeof(item),1,file))
        {
            if((strcmp(item.code,x)==0))
            {
                total=item.rate*q;
                gotoxy(11,j);
                printf("%4d",i);
                printf("%9s",item.name);
                printf("%13d",q);
                printf("%15.2f",item.rate);
                printf("%13.2f",total);
                gtotal=gtotal+total;
                size=sizeof(item);
                item.quantity=item.quantity-q;
                j+=2;
                i++;
                fseek(file,-size,SEEK_CUR);
                fwrite(&item,sizeof(item),1,file);
                break;
            }
        }
    }
    if(gtotal!=0)
    {
        gotoxy(30,j+5);
        printf("TOTAL AMOUNT = NRs. %6.2f",gtotal);
    }
    fclose(file);
    getch();
    d_mainmenu();
}
/*function to display bill window*/
void dbill()
{
    int i;
    gotoxy(20,10);
    for (i=1; i<=10; i++)
        printf("*");
    printf(" * Departmental System * ");
    for (i=1; i<=10; i++)
        printf("*");
    printf("\n\n");
    gotoxy(30,11);
    printf("My System");
    gotoxy(32,25);
    printf("CUSTOMER'S BILL") ;
//textcolor(8);
    gotoxy(13,27);
    printf("SN.   Item Name     Quantity     Rate          Total");

}
/*function to add records*/
void add ()
{
    FILE *file;
    char y[ACS],x[12];
    system("cls");
    gotoxy(25,25);
    printf("Enter new record(Y/N)?");
    while(toupper(getche())=='Y')
    {
        system("cls");
        file=fopen("record.txt","a");
        c_code(y);
        strcpy(item.code,y);
        gotoxy(22,27);
        printf("Enter rate of the item:");
        scanf("%f",&item.rate);
        gotoxy(22,28);
        printf("Enter quantity of the item:");
        scanf("%d",&item.quantity);
        gotoxy(22,29);
        printf("Enter the purchase Date(DD/MM/YYYY)");
        int a,b,c;
        scanf("%d/%d/%d",&a,&b,&c);
        if((a>0&&a<32)&&(b>0&&b<13)&&(c>2000&&c<2020))
        {
        	item.date=a;
        	item.month=b;
        	item.year=c;
		}
        gotoxy(22,30);
        printf("Enter name of the item:");
        scanf("%s",item.name);
        fseek(file,0,SEEK_END);
        fwrite(&item,sizeof(item),1,file);
        fclose(file);
        gotoxy(22,29);
        system("cls");
        printf("Enter new record(Y/N)?");

    }
    d_mainmenu();
}

/*function to check availability of code*/
void c_code(char y[])
{
    int flag;
    FILE *file;
    file=fopen("record.txt","r");
    while(1)
    {
        system("cls");
        window(20,58,23,36);
        gotoxy(32,18);
        printf(" ADDING ")  ;
        flag=1;
        rewind(file);
        gotoxy(22,25);
        printf("Enter new code of the article:");
        scanf(" %[^\n]",y);
        while(fread(&item,sizeof(item),1,file)==1)
        {
            if (strcmp(y,item.code)==0)
            {
                flag=0;
                gotoxy(26,30);
                printf("code already exists");
                gotoxy(29,32);
                printf("enter again");
                getch();
                break;
            }
        }
        if (flag==1)
            break;
    }
}

/*function for editing*/
void edit()
{
    int flag=0,choice;
    char x[ACS],y[ACS];
    FILE *file;
    int size;
    system("cls");
    window(20,63,20,46);
    gotoxy(35,18);
    printf("EDIT RECORDS");
    ;
    gotoxy(25,23);
    printf("enter item code: ");
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
        file=fopen("record.txt","r+");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)==0)
            {
                //textcolor(0);
                gotoxy(25,27);
                printf("name       = %s",item.name);
                gotoxy(25,28);
                printf("code       = %s",item.code);
                gotoxy(25,29);
                printf("rate       = %g",item.rate);
                gotoxy(25,30);
                printf("quantity   = %d",item.quantity);
                gotoxy(25,32);;
                printf("Do you want to edit this record?(y/n):");
                fflush(file);
                if(toupper(getche())=='Y')
                {
                    //textcolor(0);
                    gotoxy(25,34);
                    printf("1- edit name ");
                    gotoxy(25,35);
                    printf("2- edit code ");
                    gotoxy(25,36);
                    printf("3- edit rate ");
                    gotoxy(25,37);
                    printf("4- edit quantity ");
                    gotoxy(25,39);  ;
                    printf(" enter your choice(1, 2, 3, 4) ");
                    scanf("%d",&choice);
                    switch(choice)
                    {
                    case 1:
                        system("cls");
                        window(23,48,20,40);
                        gotoxy(35,18);
                        printf("EDIT RECORDS");
                        gotoxy(25,24);
                        printf(" enter new name: ");
                        scanf("%s",item.name);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 2:
                        system("cls");
                        window(23,65,20,40);
                        gotoxy(35,18);
                        printf("EDIT RECORDS");
                        gotoxy(25,24);
                        c_code(y);
                        strcpy(item.code,y);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 3:
                        system("cls");
                        window(23,65,20,40);
                        gotoxy(35,18);
                        printf("EDIT RECORDS");
                        gotoxy(25,24);
                        printf(" enter new rate: ");
                        scanf("%f",&item.rate);
                        size=sizeof(item);
                        fseek(file,-size,SEEK_CUR);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    case 4:
                        system("cls");
                        window(23,65,20,40);
                        gotoxy(35,18);
                        printf("EDIT RECORDS");
                        gotoxy(25,24);
                        printf(" enter new quantity: ");
                        scanf("%d",&item.quantity);
                        size=sizeof(item);
                        fseek(file,-size,1);
                        fwrite(&item,sizeof(item),1,file);
                        break;
                    }
                    gotoxy(27,30);
                    printf("--- item edited---");
                    break;
                }
            }
        }
    }
    if (flag==1)
    {
        gotoxy(32,30);
        printf("Item does not exist.");
        gotoxy(36,32);
        printf("TRY ABGAIN");
    }
    getch();
    fclose(file);
    d_mainmenu();
}

/*function to display all records*/
void d_all()
{
    int i,j=1;
    FILE *file;
    dis_con();
    file=fopen("record.txt","r");
    rewind(file);
    i=26;
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        display(&item,i,j);
        i++;
        j++;
        if ((j%20)==0)
        {
            gotoxy(27,47);/*textcolor(0)*/;
            printf("Press any key to see more...........");
            getch();
            system("cls");
            dis_con();
            i=26;
            continue;
        }
    }
    getch();
    if (i==26)
    {
        gotoxy(24,30);
        printf("-- no articles found --");
    }
    getch();
    fclose(file);
    d_mainmenu();
}

/*function to display by quantity*/
void d_quan()
{
    int i,j=1;
    int a,b;
    FILE *file;
    dis_con();
    file=fopen("record.txt","r");
    rewind(file);
    i=26;
    gotoxy(16,20);;
    printf("Enter lower range: ");
    scanf("%d",&a);
    gotoxy(16,21);
    printf("Enter upper range:");
    scanf("%d",&b);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((item.quantity>=a)&&(item.quantity<=b))
        {
            display(&item,i,j);
            i++;
            j++;
            if ((j%20)==0)
            {
                gotoxy(27,47);
                printf("Press any key to see more...........");
                getch();
                system("cls");
                dis_con();
                i=26;
                continue;
            }
        }
    }
    getch();
    if (i==26)
    {
        gotoxy(28,30);
        printf(" No items found.");
    }
    getch();
    d_search();
    fclose(file);
}

/*function to display by rate*/
void d_rate()
{
    int i,j=1;
    float a,b;
    FILE *file;
    dis_con();
    file=fopen("record.txt","r");
    rewind(file);
    i=26;
    gotoxy(16,20);;
    printf("enter lower range: ");
    scanf("%f",&a);
    gotoxy(16,21);
    printf("enter upper range: ");
    scanf("%f",&b);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((item.rate>=a)&&(item.rate<=b))
        {
            display(&item,i,j);
            i++;
            j++;
            if ((j%20)==0)
            {
                gotoxy(27,47);
                printf("press any key to see more...........");
                getch();
                system("cls");
                dis_con();
                i=26;
                continue;
            }
        }
    }
    getch();
    if (i==26)
    {
        gotoxy(28,30);
        printf(" no item found ");
    }
    getch();
    fclose(file);
    d_search();
}

/*function to display by code*/
void d_code()
{
    int i,j=1;
    char x[4]= {0};
    FILE *file;
    dis_con();
    file=fopen("record.txt","r");
    rewind(file);
    i=26;
    gotoxy(16,20);;
    printf("enter item code: ");
    scanf("%s",x);
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        if((strcmp(item.code,x)==0))
        {
            display(&item,i,j);
            i++;
            j++;
            break;
        }
    }
    if (i==26)
    {
        gotoxy(28,30);
        printf("no item found");
    }
    getch();
    fclose(file);
    d_search();
}

/*function to display window for item display*/
void dis_con()
{
    int i;
    system("cls");
    gotoxy(20,10);
    for (i=1; i<=10; i++)
        printf("*");
    for (i=1; i<=10; i++)
        printf("*");
    printf("\n\n");
    gotoxy(30,11);
    printf("STORE MANAGEMENT SYSTEM");
    gotoxy(32,17);
    printf("RECORDS") ;
    gotoxy(3,23);
    printf ("%5s ","SN");
	printf("%12s ","Item Name");
	printf("%16s ","Item Code");
	printf("%16s ","Rate");
	printf("%15s ","Quantity");
	printf("%16s ","Pur_Date");
}

/*function to display in screen*/
void display(rec *item,int i,int j)
{
    gotoxy(3,i);//textcolor(13);
    printf("%5d ",j);
    printf("%12s ",item->name);
    printf("%16s ",item->code);
    printf("%16.2f ",item->rate);
    printf("%12d ",item->quantity);
    printf("%16d/%d/%d",item->date,item->month,item->year);
}

/*function to delete records*/
void del()
{
    int flag;
    char x[ANS];
    FILE *file,*file1;
    system("cls");
    window(23,51,25,34);
    gotoxy(29,18);
    printf("DELETE ARTICLES");
    gotoxy(27,27);
    printf("enter item code: ");
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
        file1=fopen("record1.txt","w");
        file=fopen("record.txt","r");
        rewind(file);
        while (fread(&item,sizeof (item),1,file))
        {
            if(strcmp(item.code,x)!=0)
            {
			    fwrite(&item,sizeof(item),1,file1);
            }
        }
        gotoxy(27,29);
        printf("---item deleted---");
        fclose(file);
        fclose(file1);
        if(remove("record.txt")==0)
        {
        	printf("yes");
		}
        rename("record1.txt","record.txt");
    }
    if (flag==1)
    {
        gotoxy(25,29);
        printf("---item does not exist---");
        gotoxy(30,31);
        printf("TRY AGAIN");
        getch();
        d_mainmenu();
    }
    fclose(file1);
    fclose(file);
    getch();
    d_mainmenu();
}

/*function to check validity of code while editing and deleting*/
int check(char x[ANS])
{
    FILE *file;
    int flag=1;
    file=fopen("record.txt","r");
    rewind(file);
    while (fread(&item,sizeof (item),1,file))
    {
        if(strcmp(item.code,x)==0)
        {
            flag=0;
            break;
        }
    }
    fclose(file);
    return flag;
}

/*function to display box*/
void window(int a,int b,int c,int d)
{
    int i;
    system("cls");
    gotoxy(20,10);
//textcolor(1);
    for (i=1; i<=10; i++)
        printf("*");
    printf(" * Store * ");
    for (i=1; i<=10; i++)
        printf("*");
    printf("\n\n");
    gotoxy(30,11);
    printf("Departmental Store");
//textcolor(4);
    for (i=a; i<=b; i++)
    {
        gotoxy(i,17);
        printf("\xcd");
        gotoxy(i,19);
        printf("\xcd");
        gotoxy(i,c);
        printf("\xcd");
        gotoxy(i,d);
        printf("\xcd");
    }

    gotoxy(a,17);
    printf("\xc9");
    gotoxy(a,18);
    printf("\xba");
    gotoxy(a,19);
    printf("\xc8");
    gotoxy(b,17);
    printf("\xbb");
    gotoxy(b,18);
    printf("\xba");
    gotoxy(b,19);
    printf("\xbc");
//textcolor(4);
    for(i=c; i<=d; i++)
    {
        gotoxy(a,i);
        printf("\xba");
        gotoxy(b,i);
        printf("\xba");
    }
    gotoxy(a,c);
    printf("\xc9");
    gotoxy(a,d);
    printf("\xc8");
    gotoxy(b,c);
    printf("\xbb");
    gotoxy(b,d);
    printf("\xbc");
}
int no_of_days(int a,int b,int c)
{
	int c1,b1,a1;
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  c1=tm.tm_year + 1900; b1=tm.tm_mon + 1; a1=tm.tm_mday;
   if(c1>=c)
  return days(c,c1,b,b1,a,a1);
  else
  return -1;
  }
 int days(int y1,int y2,int m1,int m2,int d1,int d2)
  {
  int count=0,i;
  for(i=y1;i<y2;i++)
    {
    if(i%4==0)
    count+=366;
    else
    count+=365;
    }
  count-=month(m1,y1);
  count-=d1;
  count+=month(m2,y2);
  count+=d2;
  if(count<0)
  count=count*-1;
  return count;
  }

 int month(int a,int yy)
  {
  int x=0,c;
  for(c=0;c<a-1;c++)
    {
   if(c==1)
      {
      if(yy%4==0)
      x+=29;
      else
      x+=28;
      }
    else
    x+=mon[c];
    }
  return(x);
  }
void Customer()
{
	system("cls");
		char ch;
    	gotoxy(30,4);
    	printf("Customer");
   		gotoxy(30,8);
		printf("1.   Add Customer");
		gotoxy(30,10);
		printf("2.   Delete Customer");
		gotoxy(30,12);
		printf("3.   Display Customer");
		gotoxy(30,14);
		printf("4. GoTO Main Menu");
		gotoxy(30,28);
		printf("Enter Choice");
		scanf("%d",&ch);
		if (ch==1)
		{
			system("cls");
	FILE *file;
    char y[ACS],x[12];
    system("cls");
    gotoxy(25,25);
    printf("Enter new record(Y/N)?");
    while(toupper(getche())=='Y')
    {
        system("cls");
        file=fopen("record.txt","a");
        c_code(y);
        strcpy(cust.code,y);
        gotoxy(22,28);
        printf("Enter Name:");
        scanf("%s",&cust.name);
        gotoxy(22,30);
        printf("Enter Address:");
        scanf("%s",&cust.address);
        gotoxy(22,32);
        printf("Enter Number:");
        scanf("%l",cust.no);
        fseek(file,0,SEEK_END);
        fwrite(&cust,sizeof(cust),1,file);
        fclose(file);
        gotoxy(22,29);
        system("cls");
        printf("Enter new record(Y/N)?");

    }
    d_mainmenu();
}
		
        else if(ch==2) 
		{
	int flag;
    char x[ANS];
    FILE *file,*file1;
    system("cls");
    window(23,51,25,34);
    gotoxy(29,18);
    printf("DELETE CUSTOMER");
    gotoxy(27,27);
    printf("enter customer code: ");
    scanf("%s",x);
    flag=check(x);
    if(flag==0)
    {
        file1=fopen("record1.txt","a");
        file=fopen("record.txt","r");
        rewind(file);
        while (fread(&cust,sizeof (cust),1,file))
        {
            if(strcmp(cust.code,x)!=0)
                fwrite(&item,sizeof(item),1,file1);
        }
        gotoxy(27,29);
        printf("---customer deleted---");
        remove("record.txt");
        rename("record1.txt","record.txt");
    }
    if (flag==1)
    {
        gotoxy(25,29);
        printf("---customer does not exist---");
        gotoxy(30,31);
        printf("TRY AGAIN");
    }
    fclose(file1);
    fclose(file);
    getch();
    d_mainmenu();
}

        else if(ch==3)		
	{
	int i,j=1;
    FILE *file;
    dis_cust();
    file=fopen("record.txt","r");
    rewind(file);
    i=26;
    fflush(file);
    while(fread(&cust,sizeof(cust),1,file))
    {
        disCust(&cust,i,j);
        i++;
        j++;
        if ((j%20)==0)
        {
            gotoxy(27,47);;
            printf("Press any key to see more...........");
            getch();
            system("cls");
            dis_cust();
            i=26;
            continue;
        }
    }
    getch();
    if (i==26)
    {
        gotoxy(24,30);
        printf("-- no customers found --");
    }
    getch();
    fclose(file);
    d_mainmenu();
}

      else
      d_mainmenu();
		
}
void dis_cust()
{
    int i;
    system("cls");
    gotoxy(20,10);
    for (i=1; i<=10; i++)
        printf("*");
    for (i=1; i<=10; i++)
        printf("*");
    printf("\n\n");
    gotoxy(30,11);
    printf("CUSTOMER RECORDS");
    gotoxy(32,17);
    printf("RECORDS") ;
    gotoxy(18,23);
    printf ("SN    Name   Address	Phone");
}
void disCust(abc *cust,int i,int j)
{
    gotoxy(16,i);
    printf("%3d",j);
    printf("%10s",cust->name);
    printf("%10s",cust->address);
    printf("%10l",cust->no);
}
void d_analysis()
{
    int i,j=1;
    FILE *file;
    dis_analysis();
    file=fopen("record.txt","r");
    rewind(file);
    i=26;
    fflush(file);
    while(fread(&item,sizeof(item),1,file))
    {
        analysis(&item,i,j);
        i++;
        j++;
        if ((j%20)==0)
        {
            gotoxy(27,47);/*textcolor(0)*/;
            printf("Press any key to see more...........");
            getch();
            system("cls");
            dis_con();
            i=26;
            continue;
        }
    }
    getch();
    if (i==26)
    {
        gotoxy(24,30);
        printf("-- no articles found --");
    }
    getch();
    fclose(file);
    d_mainmenu();
}
void dis_analysis()
{
    int i;
    system("cls");
    gotoxy(20,10);
    for (i=1; i<=10; i++)
        printf("*");
    for (i=1; i<=10; i++)
        printf("*");
    printf("\n\n");
    gotoxy(30,11);
    printf("STORE MANAGEMENT SYSTEM");
    gotoxy(32,17);
    printf("RECORDS") ;
    gotoxy(3,23);
    printf ("%5s ","SN");
	printf("%12s ","Item Name");
	printf("%25s","Purchase Date");
	printf("%16s ","Days");
}
void analysis(rec *item,int i,int j)
{
	int a,b,c,count=0;
    gotoxy(3,i);
    printf("%5d ",j);
    printf("%12s ",item->name);
    printf("%16d/%d/%d",item->date,item->month,item->year);
    a=item->date;
    b=item->month;
    c=item->year;
 	count=no_of_days(a,b,c);
   	printf("%16d",count);
    
    
}

