#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
int main(){
	int a,j;
	char ch[50],b[50];
	int fd=open("a1.txt",O_CREAT|O_RDWR,0777);
	int n=read(fd,b,40);
	//write(1,b,n);
	j=(n-1)-10;
	for(int i=0;i<n;i++){
		ch[i]=b[j];
		j++;
	}
	write(1,ch,n);
	
	
}									
