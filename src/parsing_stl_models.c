#include <stdio.h>
#include <stdlib.h>

static float vertices[1000000];
static int VerticesCnt = 0;

void ReadPath(char *NameModel[])
{
    printf("Enter the name file (.stl): ");
    gets(NameModel);
}

void STL_Read(char NameModel[])
{

    FILE* file = fopen(NameModel, "r");

    if (file == NULL){
        printf("There is no file with this name\n");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    int fileLines = 0;
    for (long i = 0; i < fileSize; i++){
        if (fgetc(file) == '\n') fileLines++;
    }
    rewind(file);

    int triangleCount = 0;
    triangleCount = fileLines / 7;
    while (getc(file) != '\n'); //Skip the file header solid

    char str[80];
    for (int i = 0; i < triangleCount; i++)
    {
        while (getc(file) != '\n');
        while (getc(file) != '\n');
        fscanf(file, "%s %f %f %f", str, &vertices[VerticesCnt], &vertices[VerticesCnt+1], &vertices[VerticesCnt+2]);
        fscanf(file, "%s %f %f %f", str, &vertices[VerticesCnt+3], &vertices[VerticesCnt+4], &vertices[VerticesCnt+5]);
        fscanf(file, "%s %f %f %f", str, &vertices[VerticesCnt+6], &vertices[VerticesCnt+7], &vertices[VerticesCnt+8]);
        VerticesCnt += 9;
        while (getc(file) != '\n');
        while (getc(file) != '\n');
        while (getc(file) != '\n');
    }
    fclose(file);
}

void WritePoints(){
for (int i = 0; i < VerticesCnt; i=i+3)
    {
        printf("%f\n", vertices[i]);
        printf("%f\n", vertices[i+1]);
        printf("%f\n\n", vertices[i+2]);
    }
}

int main()
{
    char NameModel[30];
    ReadPath(&NameModel);
    STL_Read(NameModel);
    WritePoints();
}
