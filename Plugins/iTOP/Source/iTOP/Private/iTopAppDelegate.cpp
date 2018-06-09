
#include "iTopAppDelegate.h"

iTopAppDelegate& iTopAppDelegate::GetInstance()
{
    static iTopAppDelegate instance;
    return instance;
}

iTopAppDelegate::iTopAppDelegate()
{
}


