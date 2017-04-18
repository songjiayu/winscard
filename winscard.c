/*
 * Copyright 2007 Mounir IDRASSI  (mounir.idrassi@idrix.fr, for IDRIX)
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include "config.h"
#include <stdarg.h>

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "windef.h"
#include "winbase.h"
#include "wine/debug.h"
#include "winscard.h"
#include "winternl.h"


#define IN_WINE_SC

#include "winscard_impl.h"
#include <wchar.h>
WINE_DEFAULT_DEBUG_CHANNEL(winscard);

static HANDLE g_startedEvent = NULL;

const SCARD_IO_REQUEST g_rgSCardT0Pci = { SCARD_PROTOCOL_T0, 8 };
const SCARD_IO_REQUEST g_rgSCardT1Pci = { SCARD_PROTOCOL_T1, 8 };
const SCARD_IO_REQUEST g_rgSCardRawPci = { SCARD_PROTOCOL_RAW, 8 };


BOOL WINAPI DllMain (HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    TRACE("%p,%x,%p\n", hinstDLL, fdwReason, lpvReserved);

    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            DisableThreadLibraryCalls(hinstDLL);
            /* FIXME: for now, we act as if the pcsc daemon is always started */
            g_startedEvent = CreateEventA(NULL,TRUE,TRUE,NULL);
            break;
        case DLL_PROCESS_DETACH:
            if (lpvReserved) break;
            CloseHandle(g_startedEvent);
            break;
    }

    return TRUE;
}

VOID WINAPI MyFree(LPVOID lpMem)
{
    HeapFree(GetProcessHeap(), 0, lpMem);
}

LPVOID WINAPI MyMalloc(DWORD dwSize)
{
    return HeapAlloc(GetProcessHeap(), 0, dwSize);
}

LPWSTR WINAPI MultiByteToUnicode(LPCSTR lpMultiByteStr, UINT uCodePage)
{
    LPWSTR lpUnicodeStr;
    int nLength;

    nLength = MultiByteToWideChar(uCodePage, 0, lpMultiByteStr,
                                  -1, NULL, 0);
    if (nLength == 0)
    {
    	fprintf(stderr,"MultiByteToWideChar  return length :%d \n", nLength);
        return NULL;
    }
    lpUnicodeStr = MyMalloc(nLength * sizeof(WCHAR));
    if (lpUnicodeStr == NULL)
    {
    	fprintf(stderr,"MultiByteToWideChar  malloc fail \n");
    	return NULL;
    }


    if (!MultiByteToWideChar(uCodePage, 0, lpMultiByteStr,
                             nLength, lpUnicodeStr, nLength))
    {
    	fprintf(stderr,"MultiByteToWideChar  fail \n");
        MyFree(lpUnicodeStr);
        return NULL;
    }

    return lpUnicodeStr;
}

LPSTR WINAPI UnicodeToMultiByte(LPCWSTR lpUnicodeStr, UINT uCodePage)
{
    LPSTR lpMultiByteStr;
    int nLength;

    nLength = WideCharToMultiByte(uCodePage, 0, lpUnicodeStr, -1,
                                  NULL, 0, NULL, NULL);
    if (nLength == 0)
        return NULL;

    lpMultiByteStr = MyMalloc(nLength);
    if (lpMultiByteStr == NULL)
        return NULL;

    if (!WideCharToMultiByte(uCodePage, 0, lpUnicodeStr, -1,
                             lpMultiByteStr, nLength, NULL, NULL))
    {
        MyFree(lpMultiByteStr);
        return NULL;
    }

    return lpMultiByteStr;
}

HANDLE WINAPI SCardAccessStartedEvent(void)
{
    return g_startedEvent;
}

LONG WINAPI SCardAddReaderToGroupA(SCARDCONTEXT context, LPCSTR reader, LPCSTR group)
{
    LONG retval;
    UNICODE_STRING readerW, groupW;

    if(reader) RtlCreateUnicodeStringFromAsciiz(&readerW,reader);
    else readerW.Buffer = NULL;
    if(group) RtlCreateUnicodeStringFromAsciiz(&groupW,group);
    else groupW.Buffer = NULL;

    retval = SCardAddReaderToGroupW(context, readerW.Buffer, groupW.Buffer);

    RtlFreeUnicodeString(&readerW);
    RtlFreeUnicodeString(&groupW);

    return retval;
}

LONG WINAPI SCardAddReaderToGroupW(SCARDCONTEXT context, LPCWSTR reader, LPCWSTR group)
{
    FIXME("%x %s %s\n", (unsigned int) context, debugstr_w(reader), debugstr_w(group));
    return SCARD_S_SUCCESS;
}

/*LONG WINAPI SCardEstablishContext(DWORD dwScope, LPCVOID pvReserved1,
    LPCVOID pvReserved2, LPSCARDCONTEXT phContext)
{

	FIXME("(%x,%p,%p,%p) stub\n", dwScope, pvReserved1, pvReserved2, phContext);
	SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
	return SCARD_F_INTERNAL_ERROR;

	return wine_SCardEstablishContext(dwScope,  pvReserved1,
           pvReserved2,  phContext);
}*/

/*LONG WINAPI SCardIsValidContext(SCARDCONTEXT context)
{
    return wine_SCardIsValidContext(context);
}*/

LONG WINAPI SCardListCardsA(SCARDCONTEXT hContext, LPCBYTE pbAtr, LPCGUID rgguidInterfaces, 
	DWORD cguidInterfaceCount, LPSTR mszCards, LPDWORD pcchCards)
{
    FIXME(": stub\n");
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return SCARD_F_INTERNAL_ERROR;
}

LONG WINAPI SCardListCardsW(SCARDCONTEXT hContext, LPCBYTE pbAtr, LPCGUID rgguidInterfaces,
	DWORD cguidInterfaceCount,LPWSTR mszCardsw,LPDWORD pcchCards)
{
    FIXME(": stub\n");
    SetLastError(ERROR_CALL_NOT_IMPLEMENTED);
    return SCARD_F_INTERNAL_ERROR;
}

/*LONG WINAPI SCardReleaseContext(SCARDCONTEXT context)
{
    return wine_SCardReleaseContext(context);
}*/

LONG WINAPI SCardStatusA(SCARDHANDLE context, LPSTR szReaderName, LPDWORD pcchReaderLen,
	LPDWORD pdwState, LPDWORD pdwProtocol, LPBYTE pbAtr, LPDWORD pcbAtrLen)
{
   return wine_SCardStatus(context, szReaderName, pcchReaderLen,
	 pdwState, pdwProtocol, pbAtr, pcbAtrLen);
}

LONG WINAPI SCardStatusW(SCARDHANDLE context, LPWSTR szReaderName, 
	LPDWORD pcchReaderLen, LPDWORD pdwState,LPDWORD pdwProtocol,LPBYTE pbAtr,LPDWORD pcbAtrLen)
{
    LONG ret;
    LPSTR szReaderNameA;
    szReaderNameA = UnicodeToMultiByte(szReaderName,CP_ACP);
	
	ret = SCardStatusA( context, szReaderNameA, pcchReaderLen, pdwState, pdwProtocol, pbAtr, pcbAtrLen);

    szReaderName = MultiByteToUnicode(szReaderNameA,CP_ACP);
	return ret;
}

void WINAPI SCardReleaseStartedEvent(void)
{
    FIXME("stub\n");
}


LONG WINAPI SCardListReadersA(SCARDCONTEXT context, const CHAR *groups, CHAR *readers, DWORD *buflen)
{
	LONG ret;
    fprintf(stderr,"SCardListReadersA context:%d buflen: %d\n",context,  *buflen);

    ret = wine_SCardListReaders(context, groups, readers, buflen);
	int i = 0,p = 0;
	if(NULL !=&readers[i])
	{
		for (i = 0; i+1 < *buflen; i++)
		{
			++p;
			fprintf(stderr, "ReaderA %02d: %s\n" , p, debugstr_a(&readers[i]));
			while (readers[++i] != 0) ;
		}
	}

    fprintf(stderr,"SCardListReadersA  ret:%d ***************end\n",ret);
	return ret;
}

LONG WINAPI SCardListReadersW(SCARDCONTEXT context, const WCHAR *groups, LPWSTR readers, DWORD *buflen)
{
    fprintf(stderr,"SCardListReadersW \n");
    LONG ret;
	CHAR *groupsA = NULL, *readersA = NULL;
	if(readers != NULL)readersA = UnicodeToMultiByte(readers, CP_ACP);
    ret = SCardListReadersA( context,groupsA, readersA, buflen);

	/*change out param to W*/
    if(readersA != NULL)readers = MultiByteToUnicode( readersA ,CP_ACP);

	int p = 0, i = 0;
	if(NULL !=&readers[i])
	{
		for (i = 0; i+1 < *buflen; i++)
		{
			++p;
			FIXME("ReaderW %02d: %s  buflen=%d\n" , p,debugstr_w(&readers[i]) , *buflen);
			while (readers[++i] != 0) ;
		}
	}

	return ret;
}

LONG WINAPI SCardConnectA(SCARDCONTEXT hContext,LPCSTR szReader,DWORD dwShareMode,DWORD dwPreferredProtocols,
				LPSCARDHANDLE phCard,LPDWORD pdwActiveProtocol)
{
    return wine_SCardConnect( hContext, szReader, dwShareMode, dwPreferredProtocols,
				 phCard, pdwActiveProtocol);
}

LONG WINAPI SCardConnectW(SCARDCONTEXT hContext,LPCWSTR szReaderW, DWORD dwShareMode, DWORD dwPreferredProtocols,
	LPSCARDHANDLE phCard, LPDWORD pdwActiveProtocol)
{
	LPCSTR szReaderA;
    szReaderA = UnicodeToMultiByte(szReaderW,CP_ACP);

    return SCardConnectA(hContext, szReaderA, dwShareMode, dwPreferredProtocols, phCard, pdwActiveProtocol);
}

/*LONG WINAPI SCardControl(SCARDHANDLE hCard,DWORD dwControlCode,LPCVOID pbSendBuffer,DWORD cbSendLength,
	LPVOID pbRecvBuffer,DWORD cbRecvLength,LPDWORD lpBytesReturned)
{

    return wine_SCardControl( hCard, dwControlCode, pbSendBuffer, cbSendLength,pbRecvBuffer, cbRecvLength, lpBytesReturned);

}*/

/*LONG WINAPI SCardDisconnect(SCARDHANDLE context,DWORD dwDisposition)
{
    return wine_SCardDisconnect(context, dwDisposition);
}*/

/*LONG WINAPI SCardEndTransaction(SCARDHANDLE hCard,DWORD dwDisposition)
{
    return wine_SCardEndTransaction(hCard, dwDisposition);
}*/

/*LONG WINAPI SCardFreeMemory(SCARDCONTEXT hContext,LPCVOID pvMem)
{
    return wine_SCardFreeMemory(hContext,pvMem);
}*/

/*LONG WINAPI SCardGetAttrib(SCARDHANDLE hCard,DWORD dwAttrId,LPBYTE pbAttr,LPDWORD pcbAttrLen)
{
    return wine_SCardGetAttrib( hCard, dwAttrId, pbAttr, pcbAttrLen);
}*/

LONG WINAPI SCardGetStatusChangeA(SCARDCONTEXT hContext,DWORD dwTimeout,
	LPSCARD_READERSTATEA p_rgReaderStates,DWORD cReaders)
{
    fprintf(stderr,"SCardGetStatusChangeA  \n");
    return wine_SCardGetStatusChange( hContext, dwTimeout, p_rgReaderStates, cReaders);
}


LONG WINAPI SCardGetStatusChangeW(SCARDCONTEXT hContext,DWORD dwTimeout,
	LPSCARD_READERSTATEW rgReaderStates,DWORD cReaders)
{
    //TRACE_JASON_FUNC_CALL();
    LONG ret;
    int cReadersIndex = 0;
    fprintf(stderr,"SCardGetStatusChangeW(readers number:%d)\n",cReaders);
    LPSCARD_READERSTATEA rgReaderStatesA;
    rgReaderStatesA = HeapAlloc(GetProcessHeap(),0,sizeof(SCARD_READERSTATEA)*cReaders);
    for(cReadersIndex = 0; cReadersIndex < cReaders; cReadersIndex++)
    {
    	fprintf(stderr, "rgReaderStates[%d].szReader: %s\n", cReadersIndex , debugstr_w(rgReaderStates[cReadersIndex].szReader));
	    //int cReadersIndexA = cReaders - cReadersIndex - 1;
        if(rgReaderStates[cReadersIndex].szReader != NULL)rgReaderStatesA[cReadersIndex].szReader = UnicodeToMultiByte(rgReaderStates[cReadersIndex].szReader,CP_ACP);
        if(rgReaderStates[cReadersIndex].pvUserData != NULL)
        {
        	 rgReaderStatesA[cReadersIndex].pvUserData = rgReaderStates[cReadersIndex].pvUserData;
        }else{
        	 rgReaderStatesA[cReadersIndex].pvUserData = NULL;
        }
        rgReaderStatesA[cReadersIndex].dwCurrentState = rgReaderStates[cReadersIndex].dwCurrentState;
        rgReaderStatesA[cReadersIndex].dwEventState = rgReaderStates[cReadersIndex].dwEventState;
        rgReaderStatesA[cReadersIndex].cbAtr = rgReaderStates[cReadersIndex].cbAtr;

        fprintf(stderr,"rgReaderStatesA[%d].cbAtr %d \n",cReadersIndex,  rgReaderStates[cReadersIndex].cbAtr);
	    int rgbAtrIndex = 0;
	    if(rgReaderStates[cReadersIndex].cbAtr > 0)
	    {
	        for(rgbAtrIndex = 0; rgbAtrIndex < rgReaderStates[cReadersIndex].cbAtr; rgbAtrIndex++)
	        {
	        	//fprintf(stderr,"%d:BYTE[%d]  %d \n",cReadersIndex, rgbAtrIndex,  rgReaderStates[cReadersIndex].rgbAtr[rgbAtrIndex]);
	            rgReaderStatesA[cReadersIndex].rgbAtr[rgbAtrIndex] = rgReaderStates[cReadersIndex].rgbAtr[rgbAtrIndex];
	        }
	    }else{
	    	  for(rgbAtrIndex = 0; rgbAtrIndex < rgReaderStates[cReadersIndex].cbAtr; rgbAtrIndex++)
	         {
					//fprintf(stderr,"%d:BYTE[%d]  %d \n",cReadersIndex, rgbAtrIndex,  rgReaderStates[cReadersIndex].rgbAtr[rgbAtrIndex]);
					rgReaderStatesA[cReadersIndex].rgbAtr[rgbAtrIndex] = 0;
	    	 }
	    }

    }

    ret = SCardGetStatusChangeA(hContext,dwTimeout,rgReaderStatesA,cReaders);
    for(cReadersIndex = 0; cReadersIndex < cReaders; cReadersIndex++)
    {
        //fprintf(stderr,"SCardGetStatusChangeW - index:%d-- reader:%s  -- CurrentState %d\n",cReadersIndex,rgReaderStatesA[cReadersIndex].szReader,rgReaderStatesA[cReadersIndex].dwCurrentState);
        rgReaderStates[cReadersIndex].dwCurrentState = rgReaderStatesA[cReadersIndex].dwCurrentState;
        rgReaderStates[cReadersIndex].dwEventState = rgReaderStatesA[cReadersIndex].dwEventState;
        rgReaderStates[cReadersIndex].cbAtr = rgReaderStatesA[cReadersIndex].cbAtr;

	    fprintf(stderr,"rgReaderStatesA[%d].cbAtr %d \n",cReadersIndex,  rgReaderStates[cReadersIndex].cbAtr);
        int rgbAtrIndex = 0;
        for(rgbAtrIndex = 0; rgbAtrIndex <  rgReaderStates[cReadersIndex].cbAtr; rgbAtrIndex++)
        {
        	fprintf(stderr,"%d:BYTE[%d]  %d \n",cReadersIndex, rgbAtrIndex,  rgReaderStatesA[cReadersIndex].rgbAtr[rgbAtrIndex]);
           rgReaderStates[cReadersIndex].rgbAtr[rgbAtrIndex] = rgReaderStatesA[cReadersIndex].rgbAtr[rgbAtrIndex];
        }
    }
    //HeapFree(GetProcessHeap(), 0 , rgReaderStatesA );
    //TRACE_JASON_FUNC_RET();
    fprintf(stderr,"SCardGetStatusChangeW - wokakakak %d\n",ret);
    return ret;
}

LONG WINAPI SCardListReaderGroupsA(SCARDCONTEXT hContext,LPSTR mszGroups,LPDWORD pcchGroups)
{
	LONG ret;
	fprintf(stderr,"SCardListReaderGroupsA  \n");
    wine_SCardListReaderGroups( hContext, mszGroups, pcchGroups);
       int i =0;
    	int p = 0;
    	if(NULL != &mszGroups[i])
    	{
    		for (i = 0; i+1 < *pcchGroups; i++)
    		{
    			++p;
    			printf( "GroupsA %02d : %s\n" , p, &mszGroups[i]);

    			while (mszGroups[++i] != 0) ;
    		}
    	}
    fprintf(stderr,"SCardListReaderGroupsA   end %d \n", *pcchGroups);
    return ret;
}

LONG WINAPI SCardListReaderGroupsW(SCARDCONTEXT hContext,LPWSTR mszGroups,LPDWORD pcchGroups)
{
	fprintf(stderr,"SCardListReaderGroupsW  \n");
   LONG ret;
   LPSTR mszGroupsA;
  // mszGroupsA = HeapAlloc(GetProcessHeap(),0 ,sizeof(char)*(*pcchGroups));

   mszGroupsA = UnicodeToMultiByte(mszGroups, CP_ACP );

   ret = SCardListReaderGroupsA(hContext, mszGroupsA, pcchGroups);

   mszGroups = MultiByteToUnicode(mszGroupsA, CP_ACP);

   int i =0;
	int p = 0;

	if(NULL != &mszGroups[i])
	{
		for (i = 0; i+1 < *pcchGroups; i++)
		{
			++p;
			FIXME("GroupsW %02d : %s\n ",p , debugstr_w(&mszGroups[i]));
			while (mszGroups[++i] != 0) ;
		}
	}

   return ret;
}

/*LONG WINAPI SCardReconnect(SCARDHANDLE hCard,DWORD dwShareMode,DWORD dwPreferredProtocols,DWORD dwInitialization,LPDWORD pdwActiveProtocol)
{
    return wine_SCardReconnect(hCard, dwShareMode, dwPreferredProtocols,
		 dwInitialization, pdwActiveProtocol);
}*/

/*LONG WINAPI SCardSetAttrib(SCARDHANDLE hCard,DWORD dwAttrId,LPCBYTE pbAttr,DWORD cbAttrLen)
{
    return wine_SCardSetAttrib(hCard, dwAttrId, pbAttr, cbAttrLen);
}*/


/*LONG WINAPI SCardTransmit(SCARDHANDLE hCard, LPCSCARD_IO_REQUEST pioSendPci, LPCBYTE pbSendBuffer,
	DWORD cbSendLength,LPSCARD_IO_REQUEST pioRecvPci,LPBYTE pbRecvBuffer,LPDWORD pcbRecvLength)
{
    SCARD_IO_REQUEST *ioSendPci = pioSendPci;
	SCARD_IO_REQUEST *ioRecvPic = pioRecvPci;

    return wine_SCardTransmit( hCard, ioSendPci, pbSendBuffer, cbSendLength,ioRecvPic, pbRecvBuffer, pcbRecvLength);
}*/
