#include "dirwalk.h"


int main(int argc,char** argv){
    bool l_opt = false;
    bool d_opt = false;
    bool f_opt = false;
    bool s_opt = false;
    int opt;

    struct option long_options[] = {
        {"l", no_argument, 0, 'l'},
        {"d", no_argument, 0, 'd'},
        {"f", no_argument, 0, 'f'},
        {"s", no_argument, 0, 's'},
        {0, 0, 0, 0}
    };

    while ((opt = getopt_long(argc, argv, "ldfs", long_options, NULL)) != -1) {
        switch (opt) {
            case 'l':
                l_opt = true;
                break;
            case 'd':
                d_opt = true;
                break;
            case 'f':
                f_opt = true;
                break;
            case 's':
                s_opt = true;
                break;
            default:
                return 0;
                break;
        }
    }
    bool haveName = false;
    char* path;

    for (int i = 1; i < argc ; i++){
        if(argv[i][0] != '-'){
            if (haveName == true){
                printf("incorrect syntax");
                return 0;
            }
            else {
                haveName = true;
                path = argv[i];
            }
        }
    }
    if (haveName)
        dirwalkStdout(path,l_opt,d_opt,f_opt,s_opt);
    else
        dirwalkStdout("./",l_opt,d_opt,f_opt,s_opt);
    return 0;
}