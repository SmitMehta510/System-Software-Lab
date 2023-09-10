#include<stdio.h>
#include<unistd.h>

int main(int argc, char const *argv[])
{

	char *path = "/bin/ls";
	char *arg1 = "-Rl";
	char *arg2 = "/home/smit/sslab";

	const char *file ="/bin/ls";

	extern char **environ;

	//1
	//execl(path,path,arg1,arg2,NULL);

	//2
	
	//execlp(file,file,arg1,arg2,NULL);

	//3

	// execle(path,path,arg1,arg2,NULL,environ);

	//4
	//execv(path,argv);

	//5
	execvp(file,argv);

	return 0;
}