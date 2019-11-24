#include <stdio.h>
#include <stdlib.h>
int cnt_2k=1;
double mean1_2k=0.0,mean2_2k=0.0;
struct info c1, c2;
struct node
{
    char con[70]; // x axis
    int ipc[11]; // y axis
    int total_count;
    int ipc_cnt; //no of ipc count
    struct node *next;
};
struct node * pt1=NULL,* pt2=NULL;
int kmean_2k(struct info o[])
{

    int s=683;
        for(int i=0;i<5;i++)
        {
        kmeans2k(o,s,cnt_2k);
        }
    return 0;
}
void kmeans2k(struct info o[],int s, int cnt_2k)
{
    int i,j;
    int coa=0,cob=0;
    int a,b;
    if(cnt_2k==1)
    {
    j=((2*rand())%s);
    i=((2*rand())%s);
    }
    else
    {
    i= (int)mean1_2k;
    printf("\nmean val1: %f\n",mean1_2k);
    j= (int)mean2_2k;
    printf("\nmean val2: %f\n",mean2_2k);
    }
    a=i;
    printf("\nFirst centroid is: (%s,%d(total count))",o[i].constituency,o[i].total_count);
    b=j;
    printf("\nSecond centroid is: (%s,%d(total count))\n",o[j].constituency,o[j].total_count);
    distance2k(o,s,a,b,o[i],o[j],cnt_2k);
}
void distance2k(struct info o[],int s,int a,int b,struct info c11, struct info c22,int cnt_2k)
{
    double cov=0, cou=0, num1=0, num2=0;
    double inm=0, *one=&mean1_2k, *two=&mean2_2k;
    struct info *gc1= &c1, *gc2= &c2;
    *gc1= c11;
    *gc2= c22;

        for(int x=0;x<s;x++)
        {
            double a1=(totaldata-o[x].total_count)/totaldata;
            double b1=(totaldata-c1.total_count)/totaldata;
            double b2=(totaldata-c2.total_count)/totaldata;
            printf("dist:%f, %f\n",fabs(a1-b1),fabs(a1-b2)); //check logic!!!!!
            if(fabs((a1-b1)) < fabs((a1-b2)))
            {
                cov+=(a1);
                num1+=1.0;
                createForPt1_2k(o[x]);
                printf("1\n");
            }
            else if(fabs((a1-b1)) >= fabs((a1-b2)))
            {
                cou+=(a1);
                num2+=1.0;
                createForPt2_2k(o[x]);
                printf("2\n");
            }
        }
        inm=(cov/num1);
        *one=round(inm);
        printf("value of cov:%f\n",cov);
        printf("value of num1:%f\n",num1);
        inm=(cou/num2);
        *two=round(inm);
        printf("value of cou:%f\n",cou);
        printf("value of num2:%f\n",num2);
    printf("\nFor round %d:\n",cnt_2k);
    printf("Cluster-1\n");
    for(struct node* l=pt1;l!=NULL;l=l->next)
    {
        printf("(x:%s y(total count):%d)\t",l->con, l->total_count);
    }
    printf("\nCluster-2\n");
    for(struct node* m=pt2;m!=NULL;m=m->next)
    {
        printf("(x:%s,y (total count):%d)\t",m->con, m->total_count);
    }
    cnt_2k+=1;
    callFree2k();

}
void createForPt1_2k(struct info a)
{
    struct node *n= (struct node *)(malloc(sizeof(struct node)));
    strcpy(n->con,a.constituency); // array copy nahi ho raha
    n->total_count= a.total_count;
    n->ipc_cnt= a.No_ipc;// ip count
    for(int xy=0;xy<a.No_ipc;xy++)
    {
        n->ipc[xy]= a.ipc[xy];
    }
    n->next=NULL;
    if(pt1==NULL)
    {
        pt1=n;
    }
    else
    {
        struct node *p;
        for(p=pt1;(p->next!=NULL);p=p->next)
        {
        }
        p->next=n;
    }
}
void createForPt2_2k(struct info a)
{
    struct node *m= (struct node *)(malloc(sizeof(struct node)));
    strcpy(m->con,a.constituency);
    m->total_count= a.total_count;
    m->ipc_cnt=a.No_ipc;
    for(int xy=0;xy<a.No_ipc;xy++)
    {
        m->ipc[xy]= a.ipc[xy];
    }
    m->next=NULL;
    if(pt2==NULL)
    {
        pt2=m;
    }
    else
    {
        struct node *q;
        for(q=pt2;q->next!=NULL;q=q->next)
        {
        }
        q->next=m;
    }
}
void callFree2k()
{
        struct info *m1=&c1, *m2=&c2;
        int *cn=&cnt_2k;
        struct node *p=pt1,*q=pt2;
        double mm1=(mean1_2k), mm2=(mean2_2k);
        printf("\n%f %f\n",mm1,mm2);
        for(float e=0.0; e < mm1; e+=1.0)
        {
           printf("comparing 1\n");
            p=p->next;
        }
        strcpy(m1->constituency,p->con);
        m1->total_count= p->total_count;
        printf("val updated\n");
        for(float e=0.0; e <= mm2; e+=1.0)
        {
            printf("comparing 2\n");
            q=q->next;
        }
        strcpy(m2->constituency,q->con);
        m2->total_count=q->total_count;
        printf("val updated\n");
        printf("now mean1:%f mean2:%f\n",mean1_2k,mean2_2k);
        if(cnt_2k==5)
        {
            FILE *fptr1 = fopen("plot/sample2k_c1.txt", "w");
            if (fptr1 == NULL)
                {
                    printf("Could not open file");
                    return 0;
                }
        for(struct node *last=pt1; last!=NULL;last=last->next)
        {   printf("enter 1.1\n");
            //x=last->con;
            for(int l1=0;l1<last->ipc_cnt;l1++)
            { printf("enter 1.2\n");
                fprintf(fptr1,"(%s) %d\n",last->con ,last->ipc[l1]);
//                printf("ipc_count:%d\n",last->ipc_cnt);
//                printf("constituency:%s\n",last->con);
//                printf("ipc[%d]:%d",l1,last->ipc[l1]);
            }
        }
        fclose(fptr1);
        FILE *fptr2 = fopen("plot/sample2k_c2.txt", "w");
            if (fptr2 == NULL)
                {
                    printf("Could not open file");
                    return 0;
                }
        for(struct node *la=pt2; la!=NULL;la=la->next)
        { printf("enter 2.1\n");
            //x=last->con;
            for(int l1=0;l1<la->ipc_cnt;l1++)
            {   printf("enter 2.2\n");
                fprintf(fptr2,"(%s) %d\n",la->con ,la->ipc[l1]);
//                printf("constituency:%s\n",la->con);
//                printf("ipc[%d]:%d",l1,la->ipc[l1]);
            }
        }
        fclose(fptr2);
        }
        pt1=NULL;
        pt2=NULL;
        ++*cn;
        printf("starting again\n");
}
