#include <stdio.h> 
#include <stdlib.h>
#include "input.h"
#include "fortnite.h"

int main() 
{
    FortniteItem shop[100];

    int shopSize = fortniteLoadShop(shop, 100);
    printf("Imported %d fortnite items:\n", shopSize);
    fortniteArrayPrint(shop, shopSize);

    //NIVEL 1 & 2
    /*char name[40];
    printf("\nItem you'd like to buy: \n");
    readString(name, sizeof(name)-1);
    bool success = fortniteItemBuy(name, shop, shopSize);
    if(success)
    {
        printf("\n\n");
        fortniteArrayPrint(shop, shopSize);
    }
    else
    {
        printf("\nItem not found\n");
    }*/

    //NIVEL 3
    FortniteItem* shopCopy = fortniteArrayCopy(shop, shopSize);
    if(shopCopy != NULL)
    {
        fortniteArrayPrint(shopCopy, shopSize);
    }
    else
    {
        printf("\nShop copy failed (no memory)\n");
    }
    free(shopCopy);

    //NIVEL 4
    int freeCount;
    FortniteItem* freeItems = fortniteFindFreeItems(shop, shopSize, &freeCount);
    if(freeItems != NULL)
    {
        printf("\nFree Items:\n");
        fortniteArrayPrint(freeItems, freeCount);
    }
    else
    {
        printf("\nOperation failed (no memory)\n");
    }
    printf("\nBuying all free items...\n\n");
    for(int i=0; i<freeCount; i++)
    {
        fortniteItemBuy(freeItems[i].name, shopCopy, shopSize);
    }
    fortniteArrayPrint(shopCopy, shopSize);

    int rarityCount;
    FortniteItem* items = fortniteFindRarityItems(shopCopy, shopSize, "rare", &rarityCount);
    if(items != NULL)
    {
        printf("\nRARITY ITEMS\n\n\tRarity count: %d\n\n", rarityCount);
        fortniteArrayPrint(items, rarityCount);
    }
    else
    {
        printf("\nOperation failed (no memory)\n");
    }

    return EXIT_SUCCESS;
}
