
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1500
#define POP_ELEMENT 4
#define CTRY_ELEMENT 5

typedef struct {
    int population;
    char *city;
    char *country;
} ROW;

ROW *cities;

int length;
void readRow(char *filename) {
    
    FILE *fp = fopen("cities.csv" , "r");
    char line[MAX_SIZE];

    /*gets the num of lines in the file*/
    length = 0;
    int ch = 0;
    while(!feof(fp)) {
        ch = fgetc(fp);
        if(ch == '\n')
        length++;
    }
    length--; /*remove 1 for title*/

    rewind(fp);

    cities = malloc(length * sizeof(ROW));
    fgets(line, MAX_SIZE, fp); /*rm first line (title)*/

    int i = 0;
    char *value;
    while (fgets(line, MAX_SIZE, fp)){
        char *temp = strdup(line);

        if (!temp) return;

        value = strtok(temp, ",");
        cities[i].city = value; 

        int counter = 1;
        while (value){
            value = strtok(NULL, ",");
            if (counter == POP_ELEMENT) cities[i].population = atoi(value);
            if (counter == CTRY_ELEMENT) cities[i].country = value;
            counter++;
        }
        i++;
    }

    fclose(fp);
    
    return;
}

int compare (const void *p, const void *q){  
    ROW *p1 = (ROW *)p;
    ROW *q1 = (ROW *)q;
    return (q1->population - p1->population); 
} 

int main () {
    FILE *fp = fopen("sorted.csv", "w");

    readRow("cities.csv");

    qsort(cities, length, sizeof(cities[0]), compare);

    fprintf(fp, "city population country\n");
    int i;
    for (i = 0; i < length; i++) {
        fprintf(fp, "%s,%d,%s \n", cities[i].city, cities[i].population, cities[i].country);
    }

    fclose(fp);
    free(cities);
    return 0;
}

