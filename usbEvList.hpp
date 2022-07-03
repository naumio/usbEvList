#ifndef USBEVLIST_HPP
#define USBEVLIST_HPP

#include <vector>
#include <string>

//*****************************************************************************
//***** Types                                                             *****
//*****************************************************************************
typedef struct
{
    std::string              name; 
    std::vector<std::string> evLst; 
    std::string              vendor; 
    std::string              product;
} STR_USB_EV_DEV;

//*****************************************************************************
//***** Classes                                                           *****
//*****************************************************************************

class usbEvList
{
    private:
    
    public:
        usbEvList();
        ~usbEvList();
        // Functions 
        int getUsbEvents();

        // Data
        std::vector<STR_USB_EV_DEV> items;
};




#endif // USBEVLIST_HPP