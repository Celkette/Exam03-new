# picoshell
## authorized function
close, fork, wait, exit, execvp, dup2, pipe
## information
Write the following function :
```
int picoshell(char **cmds[]);
```
The goal of this function is to exectue a pipeline.
It must execute each commands at cmds and connect the output of one to the input of the next command (just like shell).
Cmd contains a pull_terminated list of valid commands.
Each rows of ends are an argv array directly usable for a call to execvp.
It any arror occur, the functions must return1 (you must of course close allthe open fds before).
Other wise the function must wait allchild processesand return 0, even if execvp returned an error.

for exemple this should be work:
```
./picoshell /bin/ls "|" /usr/bin/grep picoshell
> picoshell
./picoshell echo "squalala!" "|" cat "|" sed 'g|a|b|g'
squblblb!
```
