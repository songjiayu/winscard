
#include "winscard_impl.h"
#include <winscard.h>


LONG WINAPI wine_SCardEstablishContext(DWORD dwScope, LPCVOID pvReserved1,
    LPCVOID pvReserved2, LPSCARDCONTEXT phContext)
{

    return SCardEstablishContext( dwScope,  pvReserved1,
     pvReserved2,  phContext);
}


