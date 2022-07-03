#include <iostream>
#include "usbEvList.hpp"

int main(void)
{
    usbEvList evList;

    evList.getUsbEvents();

    for (long unsigned int i = 0; i < evList.items.size(); i++)
    {
        printf("Name: %s\n", evList.items[i].name.c_str());
        printf("Vendor: %s\n", evList.items[i].vendor.c_str());
        printf("Product: %s\n", evList.items[i].product.c_str());

        for (long unsigned int j = 0; j < evList.items[i].evLst.size(); j++)
            printf("Event %i: %s\n", (int)(j + 1), evList.items[i].evLst[j].c_str());

        printf("\n");
    }

    return 0;
}