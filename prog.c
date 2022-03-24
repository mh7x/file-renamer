#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX 100

char *get_filename_ext(char *filename) {
    char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void changeName(int n, char **fileNames, char *newFileName)
{
    char *extension = get_filename_ext(fileNames[1]);
    printf("%s\n", extension);
    for (int i = 0; i < n; i++)
    {
        char *temp = malloc(MAX * sizeof(char));
        strcpy(temp, newFileName);
        
        char *counter;
        char buffer[MAX];

        asprintf(&counter, "%d", i);

        strncat(temp, counter, MAX);
        strncat(temp, ".", 1);
        strcat(temp, extension);
        
        printf("%s\n", (temp));
        rename(fileNames[i], temp);
    }
};

int main()
{
    char *newFileName = (char *)malloc(MAX * sizeof(char));
    scanf("%s", newFileName);

    DIR *d;
    struct dirent *dir;
    d = opendir(".");

    int numberOfFiles = 0;
    char **fileNames = (char **)malloc(MAX * sizeof(char *));

    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            // printf("%s\n", dir->d_name);

            if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..") || !strcmp(dir->d_name, "dirent.h") ||
                !strcmp(dir->d_name, "a.out") || !strcmp(dir->d_name, "prog.c"))
                continue;

            fileNames[numberOfFiles] = dir->d_name;
            numberOfFiles++;
        }
        closedir(d);
    }

    changeName(numberOfFiles, fileNames, newFileName);

    return 0;
}