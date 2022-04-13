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
    char name[40];
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
    }

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

    return EXIT_SUCCESS;
}
