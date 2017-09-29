#include <header.h>


int runPwd(char** args)
{
    char cwd[110];
    if(getcwd(cwd, sizeof(cwd)) != NULL)
        printf("%s\n",cwd);  
    else
        perror("error in finding current directory\n");
    return 1;
}
