#include <signal.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <stdio.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/wait.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <dirent.h>
#include <signal.h>
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLUE    "\x1b[34m"


int pinfo(char ** command);
char* getInput();
char** parseInput(char* in, int flag);
int process(char** args);
int runCd(char** args);
int runPwd(char** args);
int runEcho(char** args);
int runLs(char **args);
int runLs_l(char **args);
int main();
int isRedircet(char** args);
char** redirect (char ** args);
int isPipe(char** args);
int handlePipe (char** args, int cnt);
void sigHandle(int sig);
int setenvHandle(char** args);
int unsetenvHandle(char** args);
int fgHandle(char** args);
int bgHandle(char** args);
int jobsHandle(char** args);
int kjobHandle(char** args);
int overkillHandle(char** args);

char hd[110];

int bg_proc_num;

typedef struct  background_process
{
	int pid;
	char name[1000];
} background_process;
background_process *bg_proc[10000];

