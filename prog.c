#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX 100

char *get_filename_ext(char *filename)
{
    char *dot = strrchr(filename, '.');
    if (!dot || dot == filename)
        return "";
    return dot + 1;
}

void changeName(int n, char **fileNames, char *newFileName)
{
    char *extension = (char *)malloc(MAX * sizeof(char));
    extension = get_filename_ext(fileNames[1]);
    printf("\n* Files are type of: %s\n\n", extension);

    char temp[100];
    char counter[100];
    for (int i = 0; i < n; i++)
    {
        strcpy(temp, newFileName);

        sprintf(counter, "%d", i);

        strncat(temp, counter, MAX);
        strncat(temp, ".", 1);
        strncat(temp, extension, MAX);

        printf("%s\n", temp);
        rename(fileNames[i], temp);
    };
};

int main()
{
    char *newFileName = (char *)malloc(MAX * sizeof(char));
    printf("** FILE RENAMER 1.0\n* All files have to be in the same directory as prog.c file, and all of them have to be the same type!\n");
    printf("* Enter file name (without extension): ");
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

            if (!strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..") || !strcmp(dir->d_name, "dirent.h") ||
                !strcmp(dir->d_name, "a.out") || !strcmp(dir->d_name, "prog.c") || !strcmp(dir->d_name, ".gitignore")
                || !strcmp(dir->d_name, ".git") || !strcmp(dir->d_name, "README.md"))
                continue;

            // printf("%s\n", dir->d_name);

            fileNames[numberOfFiles] = dir->d_name;
            numberOfFiles++;
        }
        closedir(d);
    }

    changeName(numberOfFiles, fileNames, newFileName);

    printf("\n* DONE!:)\n");

    return 0;
}