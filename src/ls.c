#include <header.h>


int runLs(char **args)
{
    int hidden = 0;
    if(args[1] != NULL && strcmp(args[1],"-a")==0)  
        hidden = 1;

    char cwd[2048], target[2048], flag = 1;
    int i,j,k;

    for(i=1;args[i]!=NULL && i<=2;i++)
    {
        if(args[i][0]!='-')
        {
            flag = 0;
            if(args[i][0] == '~')
            {
                strcpy(target, hd);
                j = strlen(hd);
                for(k=1;k<strlen(args[1]);k++)
                    target[j++]=args[1][k];
                target[j] = '\0';
            }
            else
            {
                strcpy(target, args[i]);
                j=strlen(target);
                target[j] = '\0';
            }
            break;
        }
    }
    struct dirent* Dirent;
    DIR* Dir;
    if(flag == 1)
        Dir = opendir(getcwd(cwd, sizeof(cwd)));
    else
        Dir = opendir(target);
    if (Dir == 0) 
    {
        perror ("NO such directory exists");
        return -1;  
    }

    while((Dirent=readdir(Dir))) 
    {
        if(hidden == 0)
            if (((Dirent->d_name)[0] == '.') || (strcmp(Dirent->d_name, ".") == 0) || (strcmp(Dirent->d_name, "..") == 0))
                continue;
        fprintf(stdout,"%s\n",Dirent->d_name);
    }
    return 0;
}

int runLs_l(char **args)
{
    int hidden,i,j,k, flag = 1;
    char cwd[1024] = {0};
    char target[1024];

    /* if((args[1] == NULL) || ((!((strcmp(args[1], "-al")==0) && (args[2] == NULL))) && (!((strcmp(args[1], "-l")==0) && (args[2] == NULL))) && (!((strcmp(args[1], "-la")==0) && (args[2] == NULL)))))
       {
       printf("No such command exists\n");
       return 1;
       }
     */
    if(args[1] == NULL)
        hidden = 0;
    else
    {
        if(((strcmp(args[1], "-a") == 0)) || (strcmp(args[1], "-la") == 0) || (strcmp(args[1], "-al") == 0))
            hidden = 1;
        else
        {
            if(args[2] == NULL)
                hidden = 0;
            else
            {
                if(strcmp(args[2], "-a") == 0)
                    hidden =1;
                else
                    hidden =0;
            }
        }
        for(i=1;args[i]!=NULL && i<=3;i++)
        {
            if(args[i][0]!='-')
            {
                flag = 0;
                if(args[i][0] == '~')
                {
                    strcpy(target, hd);
                    j = strlen(hd);
                    for(k=1;k<strlen(args[i]);k++)
                        target[j++]=args[i][k];
                    target[j] = '\0';
                }
                else
                {
                    strcpy(target, args[i]);
                    j=strlen(target);
                    target[j] = '\0';
                }
                break;
            }
        }
    }

    struct stat inode;

    DIR* Dir;
    if(flag == 1)
        Dir = opendir(getcwd(cwd, sizeof(cwd)));
    else
        Dir = opendir(target);

    if(Dir == 0)
    {
        perror ("Error in opening directory");
        return 0;
    }

    struct dirent *Dirent;

    while((Dirent=readdir(Dir)))
    {
        // checking whether directory or file
        if(hidden == 0)
            if (((Dirent->d_name)[0] == '.') || (strcmp(Dirent->d_name, ".") == 0) || (strcmp(Dirent->d_name, "..") == 0))
                continue;
        char nit[1234];
        if(flag==1)
        sprintf(nit, "%s/%s", cwd, Dirent->d_name);
        else
        sprintf(nit, "%s/%s", target, Dirent->d_name);
        //stat(Dirent->d_name, &inode);
        stat(nit, &inode);
        fprintf(stdout,"%s", (S_ISDIR(inode.st_mode)) ? "d" : "-");  

        // Permissions for user
        fprintf(stdout,"%s", (inode.st_mode & S_IRUSR) ? "r" : "-");
        fprintf(stdout,"%s", (inode.st_mode & S_IWUSR) ? "w" : "-");
        fprintf(stdout,"%s", (inode.st_mode & S_IXUSR) ? "x" : "-");

        // Permissions for groups
        fprintf(stdout,"%s", (inode.st_mode & S_IRGRP) ? "r" : "-");
        fprintf(stdout,"%s", (inode.st_mode & S_IWGRP) ? "w" : "-");
        fprintf(stdout,"%s", (inode.st_mode & S_IXGRP) ? "x" : "-");

        // Permissions for others
        fprintf(stdout,"%s", (inode.st_mode & S_IROTH) ? "r" : "-");
        fprintf(stdout,"%s", (inode.st_mode & S_IWOTH) ? "w" : "-");
        fprintf(stdout,"%s", (inode.st_mode & S_IXOTH) ? "x" : "-");
        printf(" ");

        // Printing number of hard-links
        fprintf(stdout,"%d ", (int)inode.st_nlink);

        // Printing Owner name
        struct passwd *pw = getpwuid(inode.st_uid);
        if (pw!=0)
            fprintf(stdout,"%s ", pw->pw_name);

        // Printing Group name
        struct group  *gr = getgrgid(inode.st_gid);
        if (gr!=0) 
            fprintf(stdout,"%s ", gr->gr_name);

        // Printing the number of size in bytes
        fprintf(stdout,"%d ",(int)inode.st_size);

        // Printing the time of modification
        char buf[110];
        time_t ti = inode.st_mtime;
        struct tm l;
        localtime_r(&ti, &l);
        strftime(buf, sizeof(buf), "%b %d %H:%M ", &l);
        fprintf(stdout,"%s", buf);
        fprintf(stdout,"%s\n", Dirent->d_name);

    }
    return 1;
}
