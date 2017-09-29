#include <header.h>


int pinfo(char ** command)
{
	int fileMem;
	char procLoc[1024];
	char garb1[100], garb2[100], status[100];
	char path_file[1024], locx[100];

	strcpy(locx, "/proc/");
	
	if(command[1]==NULL)
	{
		pid_t pid = getpid();
		printf("pid : %d\n", pid);
		strcat(locx,"self");
	}
	else
	{
		printf("pid : %s\n", command[1]);
		strcat(locx, command[1]);
	}

	FILE *mem;
	
	strcpy(path_file, locx);
	strcat(path_file, "/stat");
	mem = fopen(path_file, "r");
	fscanf(mem, "%s %s %s", garb1, garb2, status);
	printf("Process Status : %s\n", status);
	
	strcpy(path_file, locx);
	strcat(path_file, "/statm");
	mem = fopen(path_file, "r");
	fscanf(mem, "%d", &fileMem);
	printf("Memory : %d\n", fileMem);
	
	strcpy(path_file, locx);
	strcat(path_file, "/exe");
	int rt = readlink(path_file, procLoc, sizeof(procLoc));
	if(rt <= 0)
	{
		fprintf(stderr,"Executable Path : ");
		perror("error");
		return 1;
	}
	procLoc[rt] = '\0';
	printf("Executable Path : %s\n",procLoc);
	return 1;
}
