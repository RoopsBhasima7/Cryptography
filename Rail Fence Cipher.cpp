#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
int k;
char mat[10][100];
int main()
{
	printf("Type 1 to Encrypt your text or Type 2 to Decrpyt your text.");
	printf("\nType any number to exit.");	
		while(1)
		{
			int choice;
			printf("\n\nEnter your choice:");
			scanf("%d",&choice);
			if(choice==1)
			{
				fflush(stdin);
				for(int i=0;i<10;i++){
					for(int j=0;j<100;j++){
						mat[i][j]=' ';
					}
				}
				char pt[100];
				int flag=0;
				int r=0;
				printf("\n\tEnter a Plain text: ");
				gets(pt);
				printf("\tEnter the value of key:");
				scanf("%d",&k);
				printf("\n\tThe Encrypted Text is: ");
				for(int i=0;i<strlen(pt);i++)
				{
					char ch=pt[i];
					if(flag==0)
					{
						mat[r][i]=ch;
						r++;
						if(r==k)
						{
							r=r-2;
							flag=1;
						}
					}
					else
					{
						mat[r][i]=ch;
						r--;
						if(r==-1)
						{
							r=r+2;
							flag=0;
						}
					}
				}
					for(int i=0;i<k;i++){
					for(int j=0;j<strlen(pt);j++){
					if(mat[i][j]!=' ')
					printf("%c",mat[i][j]);
					}
				}		
			}	
			else if(choice==2)
			{
				fflush(stdin);
				for(int i=0;i<10;i++){
					for(int j=0;j<100;j++){
						mat[i][j]=' ';
					}
				}
				char pt[100];
				int flag=0;
				int r=0;
				int m=0;
				printf("\n\tEnter a Cipher text: ");
				gets(pt);
				printf("\tEnter the value of key:");
				scanf("%d",&k);
				printf("\n\tThe Decrypted Text is: ");
				for(int i=0;i<strlen(pt);i++)
				{
					if(flag==0)
					{
						mat[r][i]='*';
						r++;
						if(r==k)
						{
							r=r-2;
							flag=1;
						}
					}
					else
					{
						mat[r][i]='*';
						r--;
						if(r==-1)
						{
							r=r+2;
							flag=0;
						}
					}
				}
				for(int i = 0; i < k; ++i)
        		for(int j = 0; j < strlen(pt); ++j)
            if(mat[i][j] == '*')
                mat[i][j] = pt[m++];
				
				for(int i=0;i<strlen(pt);i++)
				{
					if(flag==0)
					{
						printf("%c",mat[r][i]);
						r++;
						if(r==k)
						{
							r=r-2;
							flag=1;
						}
					}
					else
					{
						printf("%c",mat[r][i]);
						r--;
						if(r==-1)
						{
							r=r+2;
							flag=0;
						}
					}
				}
			}
		else
		{
				printf("\n\nExiting...................................");
				exit(0);
		}
	}
}
