#include <stdio.h>
#include <stdlib.h>
int cnt_3k=1;
double mean1_3k=0.0,mean2_3k=0.0, mean3_3k=0.0;
struct info c1, c2, c3;
struct node_3k
{
    char con[70];
    int ipc[11];
    int total_count;
    int ipc_cnt;
    struct node_3k *next;
};
struct node_3k *pt1_3k=NULL, *pt2_3k=NULL, *pt3_3k=NULL;
int kmean_3k(struct info o[])
{

    int s=683;
        for(int i=0;i<6;i++)
        {
        kmeans3k(o,s,cnt_3k);
        }
    return 0;
}
void kmeans3k(struct info o[],int s, int cnt_3k)
{
    int i,j,k;
    int coa=0,cob=0,coc=0;
    int a,b,c;
    if(cnt_3k==1)
    {
    j=((2*rand())%s);
    i=((3*rand())%s);
    k=((4*rand())%s);
    }
    else
    {
    i= mean1_3k;
    printf("\nmean val1: %f\n",mean1_3k);
    j= mean2_3k;
    printf("\nmean val2: %f\n",mean2_3k);
    k=mean3_3k;
    printf("\nmean val3: %f\n", mean3_3k);
    }
    a=i;
    printf("\nFirst centroid is: (%s,%d(total count))",o[i].constituency,o[i].total_count);
    b=j;
    printf("\nSecond centroid is: (%s,%d(total count))\n",o[j].constituency,o[j].total_count);
    c=k;
    printf("\nThird centroid is: (%s,%d(total count))\n",o[k].constituency,o[k].total_count);
    distance3k(o,s,a,b,o[i],o[j],o[k],cnt_3k);
}
void distance3k(struct info o[],int s,int a,int b,struct info c11, struct info c22,struct info c33,int cnt_3k)
{
    double cov=0, cou=0, cox=0, num1=0, num2=0, num3=0;
    double inm=0, *one=&mean1_3k, *two=&mean2_3k, *three=&mean3_3k;
    struct info *gc1= &c1, *gc2= &c2, *gc3= &c3;
    *gc1= c11;
    *gc2= c22;
    *gc3= c33;
        for(int x=0;x<s;x++)
        {
            double a1=(totaldata-o[x].total_count)/totaldata;
            double b1=(totaldata-c1.total_count)/totaldata;
            double b2=(totaldata-c2.total_count)/totaldata;
            double b3=(totaldata-c3.total_count)/totaldata;
            printf("dist:%f, %f, %f\n",fabs(a1-b1),fabs(a1-b2),fabs(a1-b3)); //check logic!!!!!
            if(fabs((a1-b1)) <= fabs((a1-b2)) && fabs(a1-b1) <= fabs(a1-b3))
            {
                if(a1==0)
                {
                    cov+=0;
                }
                else
                {
                cov+=(a1);
                }
                num1+=1.0;
                createForPt1_3k(o[x]);
                printf("1\n");
            }
            else if(fabs((a1-b1)) >= fabs((a1-b2)) && fabs(a1-b3) >= fabs(a1-b2))
            {
                if(a1==0)
                {
                    cou+=0;
                }
                else
                {
                   cou+=(a1);
                }
                num2+=1.0;
                createForPt2_3k(o[x]);
                printf("2\n");
            }
            else if(fabs(a1-b3) <= fabs(a1-b1 && fabs(a1-b3) <= fabs(a1-b2)))
            {
                if(a1==0)
                {
                    cox+=0;
                }
                else
                {
                   cox+=(a1);
                }
                num3+=1.0;
                createForPt3_3k(o[x]);
                printf("3\n");
            }
        }
        inm=(cov/num1);
        *one=round(inm+0);
        printf("value of cov:%f\n",cov);
        printf("value of num1:%f\n",num1);
        inm=(cou/num2);
        *two=round(inm+1);
        printf("value of cou:%f\n",cou);
        printf("value of num2:%f\n",num2);
        inm=(cox/num3);
        *three=round(inm+3);
        printf("value of cox:%f\n",cox);
        printf("value of num3:%f\n",num3);
    printf("\nFor round %d:\n",cnt_3k);
    printf("Cluster-1\n");
    for(struct node_3k* l=pt1_3k;l!=NULL;l=l->next)
    {
        printf("(x:%s y(total count):%d)\t",l->con, l->total_count);
    }
    printf("\nCluster-2\n");
    for(struct node_3k* m=pt2_3k;m!=NULL;m=m->next)
    {
        printf("(x:%s,y (total count):%d)\t",m->con, m->total_count);
    }
    printf("\nCluster-3\n");
    for(struct node_3k *n=pt3_3k;n!=NULL;n=n->next)
    {
        printf("(x:%s,y (total count):%d)\t",n->con,n->total_count);
    }
    cnt_3k+=1;
    callFree3k();

}
void createForPt1_3k(struct info a)
{
    struct node_3k *n= (struct node_3k *)(malloc(sizeof(struct node_3k)));
    strcpy(n->con,a.constituency); // array copy nahi ho raha
    n->total_count= a.total_count;
    n->ipc_cnt=a.No_ipc;
    for(int xy=0;xy<a.No_ipc;xy++)
    {
        n->ipc[xy]= a.ipc[xy];
    }
    n->next=NULL;
    if(pt1_3k==NULL)
    {
        pt1_3k=n;
    }
    else
    {
        struct node_3k *p;
        for(p=pt1_3k;(p->next!=NULL);p=p->next)
        {
        }
        p->next=n;
    }
}
void createForPt2_3k(struct info a)
{
    struct node_3k *m= (struct node_3k *)(malloc(sizeof(struct node_3k)));
    strcpy(m->con,a.constituency);
    m->total_count= a.total_count;
    m->ipc_cnt=a.No_ipc;
    for(int xy=0;xy<a.No_ipc;xy++)
    {
        m->ipc[xy]= a.ipc[xy];
    }
    m->next=NULL;
    if(pt2_3k==NULL)
    {
        pt2_3k=m;
    }
    else
    {
        struct node_3k *q;
        for(q=pt2_3k;q->next!=NULL;q=q->next)
        {
        }
        q->next=m;
    }
}
void createForPt3_3k(struct info a)
{
    struct node_3k *n= (struct node_3k *)(malloc(sizeof(struct node_3k)));
    strcpy(n->con,a.constituency);
    n->total_count= a.total_count;
    n->ipc_cnt=a.No_ipc;
    for(int xy=0;xy<a.No_ipc;xy++)
    {
        n->ipc[xy]= a.ipc[xy];
    }
    n->next=NULL;
    if(pt3_3k==NULL)
    {
        pt3_3k=n;
    }
    else
    {
        struct node_3k *q;
        for(q=pt3_3k;q->next!=NULL;q=q->next)
        {
        }
        q->next=n;
    }
}
void callFree3k()
{
        struct info *m1=&c1, *m2=&c2, *m3=&c3;
        int *cn=&cnt_3k;
        struct node_3k *p=pt1_3k,*q=pt2_3k, *r=pt3_3k;
        double mm1=(mean1_3k), mm2=(mean2_3k), mm3=mean3_3k;
        printf("\n%f %f %f\n",mm1,mm2,mm3);
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
        for(float e=0.0; e <= mm3; e+=1.0)
        {
            printf("comparing 3\n");
            r=r->next;
        }
        strcpy(m3->constituency,r->con);
        m3->total_count=r->total_count;
        printf("val updated\n");
        printf("now mean1:%f mean2:%f mean3:%f\n",mean1_3k,mean2_3k,mean3_3k);
        if(cnt_3k==5)
        {
            FILE *fptr1 = fopen("plot/sample3k_c1.txt", "w");
            if (fptr1 == NULL)
                {
                    printf("Could not open file");
                    return 0;
                }
        for(struct node *last=pt1_3k; last!=NULL;last=last->next)
        {
            //x=last->con;
            for(int l1=0;l1<last->ipc_cnt;l1++)
            {
                fprintf(fptr1,"(%s) %d\n",last->con ,last->ipc[l1]);
                //y= last->ipc[l1]
                //store (x,y)
            }
        }
        fclose(fptr1);
            FILE *fptr2 = fopen("plot/sample3k_c2.txt", "w");
            if (fptr2 == NULL)
                {
                    printf("Could not open file");
                    return 0;
                }
        for(struct node *last=pt2_3k; last!=NULL;last=last->next)
        {
            //x=last->con;
            for(int l1=0;l1<last->ipc_cnt;l1++)
            {
                fprintf(fptr2,"(%s) %d\n",last->con ,last->ipc[l1]);
                //y= last->ipc[l1]
                //store (x,y)
            }
        }
        fclose(fptr2);
        FILE *fptr3 = fopen("plot/sample3k_c3.txt", "w");
            if (fptr3 == NULL)
                {
                    printf("Could not open file");
                    return 0;
                }
        for(struct node *last=pt3_3k; last!=NULL;last=last->next)
        {
            //x=last->con;
            for(int l1=0;l1<last->ipc_cnt;l1++)
            {
                fprintf(fptr3,"(%s) %d\n",last->con ,last->ipc[l1]);
                //y= last->ipc[l1]
                //store (x,y)
            }
        }
        fclose(fptr3);
        }
        pt1_3k=NULL;
        pt2_3k=NULL;
        pt3_3k=NULL;
        *cn+=1;
        printf("starting again\n");
}
