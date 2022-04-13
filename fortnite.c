#include "fortnite.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input.h"

FortniteItem fortniteItemCreate(char *name, char *rarity, int vbucks) {
    FortniteItem item;
    strcpy(item.name, name);
    strcpy(item.rarity, rarity);
    item.vbucks = vbucks;
    item.owned = false;
    return item;
}

void fortniteItemPrint(PtFortniteItem item) {
    printf("%-30s | %-20s | %d | %s\n", item->name, item->rarity, 
            item->vbucks, (item->owned) ? "Owned" : "Buy");
}

void fortniteArrayPrint(FortniteItem arr[], int arrLength) {
    for (int i = 0; i < arrLength; i++) {
        fortniteItemPrint(&arr[i]);
    }    
}

int fortniteLoadShop(FortniteItem arr[], int howMany) {
    FILE* stream = fopen("fortniteshop.csv", "r");

    if(stream == NULL) return -1;

    int count = 0;
    char line[1024];
    while (fgets(line, 1024, stream))
    {
        if(count == howMany) break;

        char* tmp = strdup(line);
        
        char** tokens = splitString(tmp, 3, ",");
        
        int vbucks = atoi(tokens[2]);
        arr[count++] = fortniteItemCreate(tokens[0], tokens[1], vbucks);

	    free(tokens);
        free(tmp);
    }

    fclose(stream);

    return count;
}

bool fortniteItemBuy(const char* name, FortniteItem arr[], int arrLength)
{
    PtFortniteItem item = fortniteItemSearch(name, arr, arrLength);
    if(item != NULL)
    {
        item->owned = true;
        return true;
    }
    else
    {
        return false;
    }
}

PtFortniteItem fortniteItemSearch(const char* name, FortniteItem arr[], int arrLength)
{
    for(int i=0; i<arrLength; i++)
    {
        if(strcasecmp(name,arr[i].name) == 0)
        {
            return &arr[i];
        }
    }
    return NULL;
}


