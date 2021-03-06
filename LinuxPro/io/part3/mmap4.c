/* Shows how to use mmap sys call
Version : 1.0
Author : Team -C
Note : All modern OS supports memory mapping of files.
*/

# include <unistd.h>
# include <sys/types.h>
# include <sys/mman.h>
# include <fcntl.h>
# include <stdio.h>

main(){
	int fd,i;
	unsigned char *filedata= NULL,*temp;
	fd = open("test.file",O_RDWR);
	filedata = (char *) mmap((void*)0,100,PROT_READ,\
			MAP_SHARED,fd,0);	
	if(filedata == NULL){
		perror("Maping Failed");
		exit(1);
	}
	// now we can access the content of the file as if it is part of
	// our process starting from the memory pointed by filedata.
	temp = filedata;

	for(i=0;i<100;i++,filedata++)
		printf("%c",*filedata);

	printf("pid %d\n",getpid()); 
	getchar();
	mprotect(temp, 100, PROT_WRITE);
	filedata-=100;
	for(i=0;i<100;i++,filedata++)
		*filedata = (char)(i+65);
	if(msync(temp,100,MS_SYNC)!=0)
		perror("msync : ");
	
	i = munmap(temp,100);
	if( i != 0)
		printf(" failed to unmap\n");
}
