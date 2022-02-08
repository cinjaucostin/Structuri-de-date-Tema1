#include "utils.h"

int main()
{
    FILE *inputFile, *outputFile;
    TList pachet;
    char *cerinta;
    inputFile = fopen("in", "r");
    outputFile = fopen("out", "w");
    cerinta = malloc(100 * sizeof(char));
    pachet = initializare_pachet();
    fgets(cerinta, 100, inputFile);
    if (strncmp(cerinta, "amestecare", strlen(cerinta) - 2) == 0)
    {
        pachet = amesteca(pachet, inputFile);
        afisare_lista(pachet, outputFile);
        freeTList(pachet);
        fclose(inputFile);
        fclose(outputFile);
    }
    else if (strncmp(cerinta, "razboi", strlen(cerinta) - 2) == 0)
    {
        razboi(pachet, inputFile, outputFile);
        fclose(inputFile);
        fclose(outputFile);
    }
    else if (strncmp(cerinta, "rollingstone", strlen(cerinta) - 2) == 0)
    {
        rollingstone(pachet, inputFile, outputFile);
        fclose(inputFile);
        fclose(outputFile);
    }
    free(cerinta);
    return 0;
}