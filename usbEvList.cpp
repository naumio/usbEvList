#include <iostream>
#include <fstream>

#include "usbEvList.hpp"

//*****************************************************************************
//***** Enums                                                             *****
//*****************************************************************************
typedef enum
{
    UNKNOWN,
    INFO,
    NAME,
    HANDLERS
} E_TOKEN;


//*****************************************************************************
//***** Functions                                                         *****
//*****************************************************************************
E_TOKEN getToken(std::string& line);
int getName(std::string& line, STR_USB_EV_DEV& item);
int getEvents(std::string& line, STR_USB_EV_DEV& item);
int getInfo(std::string& line, STR_USB_EV_DEV& item);



int usbEvList::getUsbEvents()
{
    std::ifstream input("/proc/bus/input/devices");
    std::string line;
    std::string token;

    // Clear current list of items
    items.clear();

    // In case the file could not be opened, return early
    if (!input.is_open())
        return -1;

    items.push_back(STR_USB_EV_DEV());

    // Parse line by line. Empty line signifies a new entry
    while(getline(input, line))
    {
        switch (getToken(line))
        {

        case INFO:
            items.push_back(STR_USB_EV_DEV());
            getInfo(line, items.back());
            break;

        case NAME:
            getName(line, items.back());
            break;
        
        case HANDLERS:
            getEvents(line, items.back());
            break;

        default:
            break;
        }
    }

    return 0;
}

usbEvList::usbEvList()
{
}

usbEvList::~usbEvList()
{
}


E_TOKEN getToken(std::string& line)
{
    E_TOKEN token;
    std::string subStr;

    subStr = line.substr(0, line.find(": "));

    if (subStr == "I")
    {
        token = INFO;
    }
    else if (subStr == "N")
    {
        token = NAME;
    }
    else if (subStr == "H")
    {
        token = HANDLERS;
    }
    else
    {
        token = UNKNOWN; 
    }

    return token;
}

int getName(std::string& line,  STR_USB_EV_DEV& item)
{
    std::string delim = "Name=";
    item.name = line.substr(line.find(delim) + delim.length());
    return 0;
}

int getEvents(std::string& line, STR_USB_EV_DEV& item)
{
    std::string handlers;

    // Remove characters up to first delimiter "="
    handlers = line.substr(line.find("=") + 1);

    // Get each event handler (event file)
    while (handlers.length() > 0)
    {
        item.evLst.push_back(handlers.substr(0, handlers.find(" ")));    
        handlers = handlers.substr(handlers.find(" ") + 1);
    }

    return 0;
}

int getInfo(std::string& line, STR_USB_EV_DEV& item)
{
    std::string val;
    std::string delim;

    // Get vendor as string
    delim = "Vendor=";

    val = line.substr(line.find(delim) + delim.length(), 4);
    item.vendor = val;

    // Get product as string
    delim = "Product=";

    val = line.substr(line.find(delim) + delim.length(), 4);
    item.product = val;

    return 0;
}