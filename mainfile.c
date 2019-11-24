#include <stdio.h>
#include <string.h>
#include <stdlib.h>
float totaldata=1477;
struct info{
	char name[80];
	char constituency[70];
	char party[50];
	int crica;	//crica:criminal case
	char edu[80];//edu:education
	unsigned int assets;
	unsigned int liab;//liab:liability
	int ipc[11];
	int ip_count[11];
	int No_ipc;
	int total_count;
}o[682];
#include "2k.h"
#include "3k.h"
#include "4k.h"
int top11ipc[11]={147,148,149,323,332,34,341,420,427,504,506};
int ipcseccount[11]={210,154,153,173,89,100,113,82,99,133,171};
void read_csv(){
    printf("Processing......\n");
	FILE *file;
	file = fopen("data1.txt", "r");

	int i = 0,k,x=0;//
    char line[4098];
	while (fgets(line, 4098, file)!= NULL)
    {
    	// double row[ssParams->nreal + 1];
        char* tmp = strdup(line);
		k=0;
	    int j = 0;
	     char* tok;

	    tok = strtok(line, "/");
	 //    printf("1");
	    strcpy(o[x].name,tok);
	    tok = strtok(NULL, "/");
	//	printf("2");
		strcpy(o[x].constituency,tok);
	    tok = strtok(NULL, "/");
	//	printf("3");
		strcpy(o[x].party,tok);
		tok = strtok(NULL, "/");
	//	printf("4");
		sscanf(tok,"%d",&j);
		o[x].crica=j;
	    tok = strtok(NULL, "/");
	//	printf("5");
		strcpy(o[x].edu,tok);
	    tok = strtok(NULL, "/");
	//	printf("6");
		sscanf(tok,"%d",&j);
		o[x].assets=j;

	    tok = strtok(NULL, "/");
	  //  printf("7");
		sscanf(tok,"%d",&j);
		o[x].liab=j;
		tok = strtok(NULL, "/");
		printf("8");
		char * t;
		for(t=strtok(tok,",");t&&*t;k++,t= strtok(NULL, ","))
		{
			o[x].ipc[k]=atoi(t);;
		}
	    tok = strtok(NULL, "/");
	    o[x].No_ipc=k;

		//printf("\nname=%s;constituency=%s;party=%s;crica=%d;edu=%s;assets=%u;liab=%u;ipc_count=%d;",o[x].name,o[x].constituency,o[x].party,o[x].crica,o[x].edu,o[x].assets,o[x].liab,o[x].No_ipc);
		int z,y;
		//for(z=0;z<k;z++)
		//{
		//printf("%d,",o[x].ipc[z]);
		//}


        o[x].total_count=0;
		for(z=0;z<=k;z++)
		{
			for(y=0;y<11;y++)
				{
					if(o[x].ipc[z]==top11ipc[y])
					{
						o[x].ip_count[z]=ipcseccount[y];
						break;
					}
				}
		}
		/*Adding ipc count value in to one variable*/

			for(y=0;y<(o[x].No_ipc);y++)
				{
					o[x].total_count+=o[x].ip_count[y];
				}


		//for(z=0;z<k;z++)
		//{
		//printf("+%d",o[x].ip_count[z]);
		//}


	//    printf("#\n");

       free(tmp);
        i++;
        x++;

    }
    //printf("%d",x);
    fclose(file);

    printf("\t\t#####<<<Successfully Transfered the Data>>>#####\n");


}

int main()
{
printf("\t\t##########<<<WECOME TO K-MEANS CODE>>>##########\n");
read_csv();
int x,z;
for(x=0;x < 682;x++)
{
	printf("\n %s ; %s ; %s ; %d ; %s ; %u ; %u ;",o[x].name,o[x].constituency,o[x].party,o[x].crica,o[x].edu,o[x].assets,o[x].liab);
	for(z=0;z<o[x].No_ipc;z++)
		{
		printf(" %d ",o[x].ipc[z]);
		}
}
printf("\n\n<<<Data Successfully Compiled>>>\n\n");
int cluster=0;
printf("Select number of cluster from: 2 or 3 or 4:\t");
scanf("%d",&cluster);
if(cluster==2)
{
kmean_2k(o);
}
else if(cluster==3)
{
kmean_3k(o);
}
else if(cluster==4)
{
kmean_4k(o);
}
else
    {printf("\nYou have entered Wrong Value... Kindly Start from start...\n");}



	return 0;
}

