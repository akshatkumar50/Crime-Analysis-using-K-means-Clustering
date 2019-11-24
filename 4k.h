#include <stdio.h>
#include <stdlib.h>
int cnt_4k=1;
double mean1_4k=0.0,mean2_4k=0.0, mean3_4k=0.0, mean4_4k=0.0;
struct info c1, c2, c3, c4;
struct node_4k
{
    char con[70];
    int ipc[11];
    int total_count;
    int ipc_cnt;
    struct node_4k *next;
};
struct node_4k *pt1_4k=NULL, *pt2_4k=NULL, *pt3_4k=NULL, *pt4_4k=NULL;
int kmean_4k(struct info o[])
{

    int s=683;
        for(int i=0;i<6;i++)
        {
        kmeans4k(o,s,cnt_4k);
        }
    return 0;
}
void kmeans4k(struct info o[],int s, int cnt_4k)
{
    int i,j,k,l;
    int coa=0,cob=0, coc=0, cod=0;
    int a,b,c,d;
    if(cnt_4k==1)
    {
    j=((2*rand())%s);
    i=((3*rand())%s);
    k=((4*rand())%s);
    l=((5*rand())%s);
    }
    else
    {
    i= mean1_4k;
    printf("\nmean val1: %f\n",mean1_4k);
    j= mean2_4k;
    printf("\nmean val2: %f\n",mean2_4k);
    k=mean3_4k;
    printf("\nmean val3: %f\n", mean3_4k);
    l=mean4_4k;
    printf("\nmean val4: %f\n",mean4_4k);
    }
    a=i;
    printf("\nFirst centroid is: (%s,%d(total count))",o[i].constituency,o[i].total_count);
    b=j;
    printf("\nSecond centroid is: (%s,%d(total count))\n",o[j].constituency,o[j].total_count);
    c=k;
    printf("\nThird centroid is: (%s,%d(total count))\n",o[k].constituency,o[k].total_count);
    d=l;
    printf("\nFourth centroid is: (%s, %d(total count))\n",o[l].constituency,o[l].total_count);
    distance4k(o,s,a,b,o[i],o[j],o[k],o[l],cnt_4k);
}
void distance4k(struct info o[],int s,int a,int b,struct info c11, struct info c22,struct info c33,struct info c44,int cnt_4k)
{
    double cov=0, cou=0, cox=0, coy=0,num1=0, num2=0, num3=0, num4=0;
    double inm=0, *one=&mean1_4k, *two=&mean2_4k, *three=&mean3_4k, *four=&mean4_4k;
    struct info *gc1= &c1, *gc2= &c2, *gc3= &c3, *gc4= &c4;
    *gc1= c11;
    *gc2= c22;
    *gc3= c33;
    *gc4= c44;
        for(int x=0;x<s;x++)
        {
            double a1=(totaldata-o[x].total_count)/totaldata;
            double b1=(totaldata-c1.total_count)/totaldata;
            double b2=(totaldata-c2.total_count)/totaldata;
            double b3=(totaldata-c3.total_count)/totaldata;
            double b4=(totaldata=c4.total_count)/totaldata;
            printf("dist:%f, %f, %f, %f\n",fabs(a1-b1),fabs(a1-b2),fabs(a1-b3), fabs(a1-b4)); //check logic!!!!!
            if(fabs((a1-b1)) <= fabs((a1-b2)) && fabs(a1-b1) <= fabs(a1-b3) && fabs(a1-b1) <= fabs(a1-b4))
            {
                if(a1==0)
                {
                    cov+=0.0;
                }
                else
                {
                cov+=fabs(a1);
                }
                num1+=1.0;
                createForpt1_4k(o[x]);
                printf("1\n");
            }
            else if(fabs((a1-b1)) >= fabs((a1-b2)) && fabs(a1-b3) >= fabs(a1-b2) && fabs(a1-b4) >= fabs(a1-b2))
            {
                if(a1==0)
                {
                    cou+=0.0;
                }
                else
                {
                   cou+=fabs(a1);
                }
                num2+=1.0;
                createForpt2_4k(o[x]);
                printf("2\n");
            }
            else if(fabs(a1-b3) <= fabs(a1-b1) && fabs(a1-b3) <= fabs(a1-b2) && fabs(a1-b3) <= fabs(a1-b4))
            {
                if(a1==0)
                {
                    cox+=0.0;
                }
                else
                {
                   cox+=fabs(a1);
                }
                num3+=1.0;
                createForpt3_4k(o[x]);
                printf("3\n");
            }
            else if(fabs(a1-b4) <= fabs(a1-b1) && fabs(a1-b4) <= fabs(a1-b2) && fabs(a1-b4) <= fabs(a1-b3))
            {
                if(a1==0)
                {
                    coy+=0.0;
                }
                else
                {
                   coy+=fabs(a1);
                }
                num4+=1.0;
                createForpt4_4k(o[x]);
                printf("4\n");
            }
        }
        inm=(cov/num1);
        *one=fabs(round(inm+0));
        printf("value of cov:%f\n",cov);
        printf("value of num1:%f\n",num1);
        inm=(cou/num2);
        *two=fabs(round(inm+2));
        printf("value of cou:%f\n",cou);
        printf("value of num2:%f\n",num2);
        inm=(cox/num3);
        *three=fabs(round(inm+4));
        printf("value of cox:%f\n",cox);
        printf("value of num3:%f\n",num3);
        inm=(coy/num4);
        *four=fabs(round(inm+6));
        printf("value of coy:%f\n",coy);
        printf("value of num4:%f\n",num4);
    printf("\nFor round %d:\n",cnt_4k);
    printf("Cluster-1\n");
    for(struct node_4k* l=pt1_4k;l!=NULL;l=l->next)
    {
        printf("(x:%s y(total count):%d)\t",l->con, l->total_count);
    }
    printf("\nCluster-2\n");
    for(struct node_4k* m=pt2_4k;m!=NULL;m=m->next)
    {
        printf("(x:%s,y (total count):%d)\t",m->con, m->total_count);
    }
    printf("\nCluster-3\n");
    for(struct node_4k *n=pt3_4k;n!=NULL;n=n->next)
    {
        printf("(x:%s,y (total count):%d)\t",n->con,n->total_count);
    }
    printf("\nCluster-4\n");
    for(struct node_4k *t=pt4_4k;t!=NULL;t=t->next)
    {
        printf("(x:%s,y (total count):%d)\t",t->con,t->total_count);
    }
    cnt_4k+=1;
    callFree4k();

}
void createForpt1_4k(struct info a)
{
    struct node_4k *n= (struct node_4k *)(malloc(sizeof(struct node_4k)));
    strcpy(n->con,a.constituency); // array copy nahi ho raha
    n->total_count= a.total_count;
    n->ipc_cnt=a.No_ipc;
    for(int xy=0;xy<a.No_ipc;xy++)
    {
        n->ipc[xy]= a.ipc[xy];
    }
    n->next=NULL;
    if(pt1_4k==NULL)
    {
        pt1_4k=n;
    }
    else
    {
        struct node_4k *p;
        for(p=pt1_4k;(p->next!=NULL);p=p->next)
        {
        }
        p->next=n;
    }
}
void createForpt2_4k(struct info a)
{
    struct node_4k *m= (struct node_4k *)(malloc(sizeof(struct node_4k)));
    strcpy(m->con,a.constituency);
    m->total_count= a.total_count;
    m->ipc_cnt=a.No_ipc;
    for(int xy=0;xy<a.No_ipc;xy++)
    {
        m->ipc[xy]= a.ipc[xy];
    }
    m->next=NULL;
    if(pt2_4k==NULL)
    {
        pt2_4k=m;
    }
    else
    {
        struct node_4k *q;
        for(q=pt2_4k;q->next!=NULL;q=q->next)
        {
        }
        q->next=m;
    }
}
void createForpt3_4k(struct info a)
{
    struct node_4k *n= (struct node_4k *)(malloc(sizeof(struct node_4k)));
    strcpy(n->con,a.constituency);
    n->total_count= a.total_count;
    n->ipc_cnt=a.No_ipc;
    for(int xy=0;xy<a.No_ipc;xy++)
    {
        n->ipc[xy]= a.ipc[xy];
    }
    n->next=NULL;
    if(pt3_4k==NULL)
    {
        pt3_4k=n;
    }
    else
    {
        struct node_4k *q;
        for(q=pt3_4k;q->next!=NULL;q=q->next)
        {
        }
        q->next=n;
    }
}
void createForpt4_4k(struct info a)
{
    struct node_4k *n= (struct node_4k *)(malloc(sizeof(struct node_4k)));
    strcpy(n->con,a.constituency);
    n->total_count= a.total_count;
    n->ipc_cnt=a.No_ipc;
    for(int xy=0;xy<a.No_ipc;xy++)
    {
        n->ipc[xy]= a.ipc[xy];
    }
    n->next=NULL;
    if(pt4_4k==NULL)
    {
        pt4_4k=n;
    }
    else
    {
        struct node_4k *q;
        for(q=pt4_4k;q->next!=NULL;q=q->next)
        {
        }
        q->next=n;
    }
}
void callFree4k()
{
        struct info *m1=&c1, *m2=&c2, *m3=&c3, *m4=&c4;
        int *cn=&cnt_4k;
        struct node_4k *p=pt1_4k,*q=pt2_4k, *r=pt3_4k, *s=pt4_4k;
        double mm1=(mean1_4k), mm2=(mean2_4k), mm3=mean3_4k, mm4=mean4_4k;
        printf("\n%f %f %f %f\n",mm1,mm2,mm3,mm4);
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
        for(float e=0.0; e <= mm4; e+=1.0)
        {
            printf("comparing 4\n");
            s=s->next;
        }
        strcpy(m4->constituency,s->con);
        m4->total_count=s->total_count;
        printf("val updated\n");
        printf("now mean1:%f mean2:%f mean3:%f mean4:%f\n",mean1_4k,mean2_4k,mean3_4k,mean4_4k);
        if(cnt_4k==5)
        {
            FILE *fptr1 = fopen("plot/sample4k_c1.txt", "w");
            if (fptr1 == NULL)
                {
                    printf("Could not open file");
                    return 0;
                }
        for(struct node *last=pt1_4k; last!=NULL;last=last->next)
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
        FILE *fptr2 = fopen("plot/sample4k_c2.txt", "w");
            if (fptr2 == NULL)
                {
                    printf("Could not open file");
                    return 0;
                }
        for(struct node *last=pt2_4k; last!=NULL;last=last->next)
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
        FILE *fptr3 = fopen("plot/sample4k_c3.txt", "w");
            if (fptr3 == NULL)
                {
                    printf("Could not open file");
                    return 0;
                }
        for(struct node *last=pt3_4k; last!=NULL;last=last->next)
        {
            //x=last->con;
            for(int l1=0;l1<last->ipc_cnt;l1++)
            {
                 fprintf(fptr3,"(%s) %d\n",last->con ,last->ipc[l1]);
                //y= last->ipc[l1]
                //store (x,y)
            }
        }
        fclose(fptr2);
        FILE *fptr4 = fopen("plot/sample4k_c4.txt", "w");
            if (fptr4 == NULL)
                {
                    printf("Could not open file");
                    return 0;
                }

        for(struct node *last=pt4_4k; last!=NULL;last=last->next)
        {
            //x=last->con;
            for(int l1=0;l1<last->ipc_cnt;l1++)
            {
                 fprintf(fptr4,"(%s) %d\n",last->con ,last->ipc[l1]);
                //y= last->ipc[l1]
                //store (x,y)
            }
        }
        fclose(fptr4);
        }
        pt1_4k=NULL;
        pt2_4k=NULL;
        pt3_4k=NULL;
        pt4_4k=NULL;
        *cn+=1;
        printf("starting again\n");
}
