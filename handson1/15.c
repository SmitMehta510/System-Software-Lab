#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	extern char **environ;
	int i = 0;
	while(environ[i]) {
	  printf("%s\n", environ[i++]);
	}
}