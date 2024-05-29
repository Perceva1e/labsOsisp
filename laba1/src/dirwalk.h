#ifndef LABA1_H
#define LABA1_H
#include <dirent.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>

#include <getopt.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <linux/stat.h>
#include <sys/sysmacros.h>
#include <locale.h>
int locale_strcmp(const struct dirent **a, const struct dirent **b) {
    return strcoll((*a)->d_name, (*b)->d_name);
}


void dirwalkStdout(char *path, bool l_opt, bool d_opt, bool f_opt,bool s_opt){

    struct dirent* dirEntry;
    struct stat sb;
    char fullpath[256];
    struct dirent **namelist;
 
    int numb = scandir(path,&namelist,NULL,s_opt ? locale_strcmp: NULL);
    if (numb<0){
        perror("scandir");
        return;
    }

    for(size_t k = 0; k < numb; k++){
        dirEntry = namelist[k];
        if ((strcmp(dirEntry->d_name,".") == 0 ) || (strcmp(dirEntry->d_name,"..") == 0 )){
            free(namelist[k]);
            continue;
        }
        memset(fullpath, '\0', 256);        
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, dirEntry->d_name);

        if (lstat(fullpath,&sb) == -1){
            printf("ERROR");
            continue;
        }
        switch(__S_IFMT & sb.st_mode) {
            case __S_IFDIR:
                if (d_opt)
                    printf("\n DIR: %s",fullpath);
                dirwalkStdout(fullpath,l_opt,d_opt,f_opt,s_opt);
                break;
            case __S_IFLNK:
                if(l_opt)
                    printf("\nLNK: %s",fullpath);
                break;
            case __S_IFREG:
                if(f_opt)
                    printf("\nFILE: %s",fullpath);
                break;
            default: break;
        }
        free(namelist[k]);   
    }
}
#endif