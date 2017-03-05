#include <stdarg.h>
#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"
#include "winternl.h"

typedef ULONG_PTR SCARDCONTEXT, *PSCARDCONTEXT, *LPSCARDCONTEXT;


LONG WINAPI wine_SCardEstablishContext(DWORD dwScope, LPCVOID pvReserved1,
    LPCVOID pvReserved2, LPSCARDCONTEXT phContext);

