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
    printf("\n");
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

FortniteItem* fortniteArrayCopy(FortniteItem arr[], int arrLength)
{
    FortniteItem* arrCopy = (FortniteItem*) malloc(sizeof(FortniteItem) * arrLength);
    for(int i=0; i<arrLength; i++)
    {
        arrCopy[i] = arr[i];
    }   
    return arrCopy;
}

FortniteItem* fortniteFindFreeItems(FortniteItem arr[], int arrLength, int *itemSize)
{
    FortniteItem* freeItems = NULL;
    int count = 0;
    for(int i=0; i<arrLength; i++)
    {
        if(arr[i].vbucks == 0)
        {
            freeItems = (FortniteItem*)realloc(freeItems, sizeof(FortniteItem) * (count+1));
            freeItems[count++] = arr[i];
        }
    }
    *itemSize = count;
    return freeItems;
}

FortniteItem* fortniteFindRarityItems(FortniteItem arr[], int arrLength, const char* rarity, int *itemSize)
{
    FortniteItem* rarityItems = NULL;
    int count = 0;
    for(int i=0; i<arrLength; i++)
    {
        if(strcasecmp(arr[i].rarity, rarity) == 0)
        {
            rarityItems = (FortniteItem*)realloc(rarityItems, sizeof(FortniteItem) * (count+1));
            rarityItems[count++] = arr[i];
        }
    }
    *itemSize = count;
    return rarityItems;
}

