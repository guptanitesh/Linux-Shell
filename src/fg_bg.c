#include <header.h>


int bgHandle(char** args)
{

    int i;
	for(i=0; args[i]!=NULL; i++);
	
	if (i != 2)
    	perror("Wrong Arguments given to bg \nUsage: bg <job number>\n");

	else
	{
		int jobNo = atoi(args[1]);
		jobNo--;

		if (bg_proc[jobNo] == NULL)
			perror("No job with given job number exist\n");
	
		else
		{
			if (!kill(bg_proc[jobNo]->pid, 18))
				perror("Error occured");
		}
	}

	return 1;
}


int fgHandle(char** args)
{

    int i;
	for(i=0; args[i]!=NULL; i++);

    if (i != 2)
    	perror("Wrong Arguments given to bg \nUsage: bg <job number>\n");
    
    else
    {
    	int jobNo = atoi(args[1]);
    	jobNo--;

		if (bg_proc[jobNo] == NULL)
			perror("No job with given job number exist\n");
		else
		{
			if (kill(bg_proc[jobNo]->pid, 18) == 0)
			{
				int pid = (bg_proc[jobNo] -> pid), status;
				bg_proc[jobNo] = NULL;
				waitpid(pid, &status, WUNTRACED);
			}
			else
				perror("Error occured");
		}
	}

	return 1;
}