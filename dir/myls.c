#include <stdio.h>
#include <dirent.h>

int main(int argv, char *argc[])
{
    DIR *dp;
    struct dirent *dirp;

    if(argv > 2){
        printf("usage: ./ls -path\n");
        return 1;
    }

    if(argv == 1){
        dp = opendir("./");
    }else if((dp = opendir(argc[1])) == NULL){
        perror("opendir");
    }

    printf("%-8s %-8s %-8s %-8s\n", "type", "ino", "dirent", "name");
    while((dirp = readdir(dp)) != NULL)
        printf("%-8d %-8ld %-8d %-8s\n", dirp->d_type, dirp->d_ino, dirp->d_reclen, dirp->d_name);


    return 0;
}
