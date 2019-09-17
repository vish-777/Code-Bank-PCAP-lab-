#include<stdio.h>
#include<string.h>
#include <stdlib.h>
int main()
{
    char seen[100][32] = {{ 0 }};
    int freq[100]={0};
    int id=0;
    FILE *fp;
    char filename[15]="cool.txt";
    fp = fopen(filename, "r");
    char word[32];
    if(fscanf (fp, " %32[^ ,.\t\n]%*c", word) == 1)
    {
    	strcpy(seen[id],word);
    	freq[id]++;
    	id++;
    }
    while(fscanf (fp, " %32[^ ,.\t\n]%*c", word) == 1)
    {
    	int found=0;
    	for (int i=0;i<id;i++)
    	{
    		if(strcmp(word,seen[i])==0)
    		{
    			freq[i]++;
    			found=1;
    		}
    	}
    	if(!found)
    	{
    		strcpy(seen[id],word);
    		freq[id]++;
    		id++;
    	}
    }

    char temp1[32];
    for(int i=0;i<id;i++)
    {
    	for(int j=0;j<id-1-i;j++)
    	{
    		if(freq[j]<freq[j+1])
    		{
    			int temp=freq[j];
    			freq[j]=freq[j+1];
    			freq[j+1]=temp;
    			strcpy(temp1,seen[j]);
    			strcpy(seen[j],seen[j+1]);
    			strcpy(seen[j+1],temp1);
    		}
    	}
    }
    for(int i=0;i<id;i++)
    {
    	for(int j=0;j<freq[i];j++)
    	{
    		printf("%s\n",seen[i]);
    	}
    }
}

