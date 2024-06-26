#include "FunctionsParent.h"
#include <stdlib.h>


void printMenu() 
{
  
    printf("\n- - - - - - - - - - - - - - - - - - - - -");
    printf("\n      Enter '+' if you want use getenv()\n"
           "\n      Enter '*' if you want use envp[] \n"
           "\n      Enter '&' if you want use environ \n"
           "\n      Enter 'q' if you want exit\n");
    printf("\n- - - - - - - - - - - - - - - - - - - - -");
    printf("\n      Your choice   ");
}

int comparator(const void *str1, const void *str2)
{
    return strcmp(*(const char **)str1, *(const char **)str2);
}



void printSortingEnviron (char* environ[])
{
    size_t countEnvironStrings = 0;

    while (environ[countEnvironStrings] != NULL)
    {
      countEnvironStrings++;
    }

    qsort(environ, countEnvironStrings, sizeof(char*), comparator);


    for (size_t i = 0; i < countEnvironStrings; i++)
    {
        printf("%s\n", environ[i]);
    }
       
}


char* parsingEnviron (char * envp[], const char* parametrName)
{
    while (*envp != NULL)
    {
        if (strncmp(*envp, parametrName, strlen(parametrName)) == 0)
        {
            return *envp + strlen(parametrName) + 1;
        }
  
        ++envp;
    }
    
    return NULL;
}

char** createReduceEnv(char * envp[], const char* nameFileWithNamesEnvironParametrs)
{
    FILE* file = fopen(nameFileWithNamesEnvironParametrs, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
   
    char buffer[BUFFER_SIZE];
    char* stringPointer = NULL; 
    char** newEnviron = (char**)calloc(1, sizeof(char*));
    if (newEnviron == NULL)
    {
        perror("Error allocating memory");
        exit(EXIT_FAILURE);
    }

    size_t countEnvironStrings = 0;
    while (fgets(buffer, sizeof(buffer), file))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        stringPointer = getenv(buffer);
        if (stringPointer == NULL)
        {
            printf("Error: environment variable '%s' not found\n", buffer);
            continue;
        }
        size_t len = strlen(buffer) + strlen(stringPointer) + 2;
        newEnviron[countEnvironStrings] = (char*)malloc(len);
        if (newEnviron[countEnvironStrings] == NULL)
        {
            perror("Error allocating memory");
            exit(EXIT_FAILURE);
        }
        snprintf(newEnviron[countEnvironStrings], len, "%s=%s", buffer, stringPointer);
        countEnvironStrings++;
        char** tmp = (char**)realloc(newEnviron, (countEnvironStrings + 1) * sizeof(char*));
        if (tmp == NULL)
        {
            perror("Error reallocating memory");
            exit(EXIT_FAILURE);
        }
        newEnviron = tmp;
    }
    newEnviron[countEnvironStrings] = NULL;
    fclose(file);
    return newEnviron;
}