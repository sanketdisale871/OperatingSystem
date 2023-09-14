#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#include<unistd.h>

void zombieProcess(){
    pid_t p;

    p=fork();

    if(p==0){
        printf("I am Child Process : %d\n",getpid());
        printf("My parent Process Id : %d\n",getppid());
    }
    else{
        sleep(3); // Parent at this do not know about the Child Process is Terminated or Not , "Run this file `& symbol after a.out` "
        printf("I am Parent : %d\n",getpid());
        printf("My Child proecess Id : %d\n",p);
    }

    /* Output : 
         I am Child Process : 57
        My parent Process Id : 56   -> Child process whose id 57, finished their work
        ps
        PID TTY          TIME CMD
        10 pts/0    00:00:00 bash
        56 pts/0    00:00:00 a.out
        57 pts/0    00:00:00 a.out <defunct> // Here also again Child process exists in the Process Table. (So, Zombie Proecess), By using wait 
        58 pts/0    00:00:00 ps // command we can remove the process from zombie. ("Wait" will make to wait the termination of child process)
    
    */
}


void orphanProcess(){
    pid_t p;

    p=fork();

    if(p==0){
        sleep(3);
        printf("I am Child Process : %d\n",getpid());
        printf("My Parent Process : %d\n",getppid());  
    }
    else{
        printf("I am Parent Process : %d\n",getpid());
        printf("My child Proecss : %d\n",p);
    }

    /*
        I am Parent Process : 122
        My child Proecss : 123   // Parent Process Terminted the his execution
            ps
        PID TTY          TIME CMD
        10 pts/0    00:00:00 bash
        123 pts/0    00:00:00 a.out
        124 pts/0    00:00:00 ps

        I am Child Process : 123 --> Now child process is executing, Prev and now Child id Same
        My Parent Process : 9  --> Different parent process Id printing, Becoz before Child Parent terminated
    */
}

int main(){
    zombieProcess();
    orphanProcess();
}