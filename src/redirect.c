#include <header.h>



int isRedirect(char** args)
{
    int i;
    for(i=1;args[i]!=NULL;i++)
        if((strcmp(args[i],">") == 0) || (strcmp(args[i],"<") == 0) || (strcmp(args[i],">>") == 0))
            return 1;
    return 0;
}


char** redirect (char ** args)
{

    int i, fd;
    char tp[100010];

    for(i=0; args[i]!=NULL; i++)
    {
        if(!strcmp(args[i],">"))
        {
            args[i] = NULL;
            if(args[i+1]==NULL)
            {	
                fprintf(stderr,"Output file not mentioned\n");
                exit(0);
            }
            strcpy(tp, args[i+1]);
            printf("dsfa");
            fd = open(tp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
            if(fd<0){
                perror("Can not open the output file");
                exit(0);
            }
            dup2(fd,1);
            close(fd);
        }

        else if(!strcmp(args[i],">>"))
        {
            args[i] = NULL;
            if(args[i+1]==NULL)
            {	
                fprintf(stderr,"Output file not mentioned\n");
                exit(0);
            }
            strcpy(tp, args[i+1]);
            fd = open (tp, O_APPEND | O_CREAT | O_WRONLY, 0644);
            if(fd<0){
                perror("Could not open the output file");
                exit(0);
            }
            dup2(fd,1);
            close(fd);
        }

        else if(!strcmp(args[i],"<"))
        {
            args[i] = NULL;
            if(args[i+1]==NULL)
            {	
                fprintf(stderr,"Input file not mentioned\n");
                exit(0);
            }
            strcpy(tp, args[i+1]);
            fd = open(tp, O_RDONLY,0);
            if(fd < 0){
                perror("Can not open the input file");
                exit(0);
            }
            dup2(fd,0);
            close(fd);
        }
    }

    return args;
}
