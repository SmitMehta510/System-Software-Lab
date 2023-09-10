/*
============================================================================
Name : 9.c
Author : Smit Mehta
Description : C program to display information regarding the given file.
Date: 25th Aug, 2023.
============================================================================
*/

#include<stdio.h>
#include <sys/stat.h>

int main(int argc, char const *argv[])
{
	struct stat filestat;

	stat("dest.txt",&filestat);

	printf("Inode number = %ld\n",filestat.st_ino);
	printf("Number of hardlinks = %ld\n",filestat.st_nlink);
	printf("uid = %d\n",filestat.st_uid);
	printf("gid = %d\n",filestat.st_gid);
	printf("File size = %ld \n",filestat.st_size);
	printf("Block size = %ld \n",filestat.st_blksize);
	printf("Number of blocks= %ld\n",filestat.st_blocks);
	printf("Time of last access= %ld\n",filestat.st_atime);
	printf("Time of last modification = %ld\n",filestat.st_mtime);
	printf("Time of last change = %ld\n",filestat.st_ctime);
	return 0;
}