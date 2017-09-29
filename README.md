# Interactive Shell
* An interactive user defined shell in C

## Runnig the Shell 
* At first complile the codes using the following command :

  ```make```


* After compiling, execute the shell ushing the following command:

  ```./cshell```

## Features
### General
* Works almost like a normal shell.
* Coloured prompt 
* The directory where the shell is executed becomes the home directory of the shell.
* Every non-bulletin command runs by creating a new process using fork() system call.
* Proper Error Handling is done.
* Code is written in a modular fashion.

### Background Processes
* Commands which have '&' appended, run in background.
* When background process exits, shell displays a message with its exit status.

### Redirection
* Output of running one (or more) commands can be redirected to a file.
* Similarly, a command might be prompted to read input data from a file and asked to write output to another file.
* If output file does not exist it creates one with permissions of 644.

### Piping

* A pipe is identified by "|".
* One or more commands can be piped.
* Shell supports any number of pipes.
* Piping and redirection both can be done in the same command.

### Built-in Commands

Following commands are implemented as a part of the shell :
* pwd
* echo
* cd
* ls (ls, ls -l, ls -al, ls -a, ls -la, ls -a -l, ls -l -a, Can also take diretory name as an argument)
* pinfo
  * It returns process related information like pid, process status, memory, etc.
* setenv:  ```setenv var [value]```
  * If environment variable var does not exist, then the shell create it.
  * Shell sets the value of var to value, or to the empty string if value is omitted.
  * It can also change the value of an existing variable.
* unsetenv:  ```unsetenv var```
  * Shell destroys the environment variable var.
* jobs
  * Prints a list of all currently running background jobs along with their pid in order of their creation.
* kjob:  ```kjob <jobNumber> <signalNumber>```
  * Takes the job id of a running job and sends a signal value to that process.
* fg:  ```fg <jobNumber>```
  * Brings a running or a stopped background job with given job number to foreground.
* bg:  ```bg <jobNumber>```
  * Changes a stopped background job to a running background job.
* overkill
  * Kills all background process at once.
* quit
  * Exits the shell. Shell exits only if the user types this "quit" command. It ignores any other signal from user like : CTRL-D, CTRL-C, SIGINT, SIGCHLD etc.