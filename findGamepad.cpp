#include <iostream>
#include "usbEvList.hpp"

int main(void)
{
    usbEvList evList;
    const char *searchTerms[] = 
    {
        "gamepad", 
        "Gamepad", 
        "pad",
        NULL
    };
    unsigned int padCount = 0;

    evList.getUsbEvents();

    printf("\nSearching for gamepads by following keywords:\n");

    for (int i = 0; searchTerms[i] != NULL; i++) 
        printf("    %s\n", searchTerms[i]);    

    // Print event info for gamepads
    for (int i = 0; i < (int)evList.items.size(); i++)
    {
        for (int j = 0; searchTerms[j] != NULL; j++)
        {
            if (evList.items[i].name.find(searchTerms[j]) != std::string::npos)
            {
                printf("\nFound gamepad: %s", evList.items[i].name.c_str());
                
                // Find input events
                for (int e = 0; e < (int)evList.items[i].evLst.size(); e++)
                {
                    if (evList.items[i].evLst[e].find("event") != std::string::npos)
                        printf("\n    Event file: /dev/input/%s", evList.items[i].evLst[e].c_str());
                }

                padCount++;
                break;
            }
        }
    }

    printf("\n\n%i gamepads found.\n\n", padCount);

    return 0;
}