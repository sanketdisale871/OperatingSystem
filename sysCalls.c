#include<unistd.h> // File related operations
#include<stdio.h>
#include<stdlib.h> // Str len
#include<sys/types.h> // get pid,ppid,
#include<sys/stat.h> // Stat realted information showing
// #include <sys/wait.h>
#include<fcntl.h> // Constant file accessing mods (O_RDONLY,O_WRONLY)

void fileSystemCalls(){
    int fd;
    char buffer[10];

    fd = open("hello.txt", O_CREAT | O_RDWR);

    if(fd<0){
        perror("open");
        return;
    }
     // Write data to a file
    int wrritenBytes=write(fd,"Hello, I am Sanket",strlen("Hello, I am Sanket"));

    if(wrritenBytes < 0){
        perror("write");
    }

    lseek(fd,0,SEEK_SET);

    int readBytes=read(fd,buffer,sizeof(buffer));

    

    if(readBytes<0){
        perror("read");
        return ;
    }
    else{
        buffer[readBytes]='\0';
        printf("Read Data : %s\n",buffer);
    }

    // Close the file
    close(fd);

    // Remove the file
    unlink("hello.txt");

}

void processSystemCalls(){
    pid_t p;
    printf("Before fork : ");
    p=fork();
    int status;

    if(p==0){
        printf("I am child having my id : %d\n",getpid());
        printf("I am parent process having id : %d\n",getppid());
    }
    else{
        printf("Parent Id : %d\n",getpid());
        printf("Child id : %d\n",p);
        wait(&status); // Wating to terminate child process
    }

}

void communicationSysCalls(){

/* fd[0] => Reading end fd[1] => Writing End 
    Creates unique pipe
*/
    int fd[2];
    char buffer[100];
    pid_t p;
    pipe(fd);
    p=fork(); 

    if(p>0){
        printf("Passing value to child.\n");
        write(fd[1],"Hello,I am Sanket\n",strlen("Hello,I am Sanket\n"));
    }
    else{
        printf("Child received data.\n");
        int n=read(fd[0],buffer,100);
        write(1,buffer,n);
    }
    wait(NULL); // Wait for to fininsh the child process

    /* Parent Pid : Sender 
      Child proecss : Receiver
    */

}

void informationSysCall(){
    // struct stat fileStat;

    // int d = stat("home.txt",&fileStat);

    // if(d<0){
    //     perror("Stat Error");
    //     return ;
    // }

    // printf("Inofrmation of file : \n");
    // printf("Permission of File : %o\n",fileStat.st_mode);
    // printf("UserID of file : %d\n",fileStat.st_uid);
    // printf("GroupId of file : %d\n",fileStat.st_gid);
    // printf("File size  : %lld bytes.",(long long)fileStat.st_size);

    struct stat fileStat;
    int d = stat("hello.txt",&fileStat);

    printf("File information : \n");
    printf("File Length : %lld bytes.",fileStat.st_size);
    printf("Group Id : %d\n",fileStat.st_gid);
    printf("Permissions: %d\n",fileStat.st_mode);
    printf("User Id: %d\n",fileStat.st_uid);
}

int main(){


    return 0;
}