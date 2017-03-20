
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>


#define USR_LINUX
#include "winscard_impl.h"




LONG wine_SCardEstablishContext(DWORD dwScope,
		/*@null@*/ LPCVOID pvReserved1, /*@null@*/ LPCVOID pvReserved2,
		/*@out@*/ LPSCARDCONTEXT phContext)
{
    fprintf(stderr,"wine_SCardEstablishContext: Linux \n");

    return SCardEstablishContext( dwScope, pvReserved1, pvReserved2, phContext);
}

LONG wine_SCardReleaseContext (SCARDCONTEXT hContext)
{
    fprintf(stderr,"wine_SCardReleaseContext: Linux \n");
    return SCardReleaseContext(hContext);
}

LONG wine_SCardListReaders(SCARDCONTEXT hContext,LPCSTR mszGroups,
		LPSTR mszReaders,LPDWORD pcchReaders )
{
	fprintf(stderr,"wine_SCardListReaders: Linux \n");
    LONG ret;
    ret =  SCardListReaders( hContext, mszGroups, mszReaders, pcchReaders );
	//fprintf(stderr,"Readers: <Linux> %s \n", mszReaders);

	return ret;
}

LONG wine_SCardConnect(SCARDCONTEXT hContext, LPCSTR szReader,DWORD dwShareMode,
				DWORD dwPreferredProtocols, LPSCARDHANDLE phCard, LPDWORD pdwActiveProtocol)
{
	fprintf(stderr,"wine_SCardConnect: Linux \n");


    return SCardConnect( hContext, szReader, dwShareMode, dwPreferredProtocols, phCard, pdwActiveProtocol);
}

LONG wine_SCardControl(SCARDHANDLE hCard,DWORD dwControlCode,LPCVOID pbSendBuffer,DWORD cbSendLength,
					LPVOID pbRecvBuffer,DWORD cbRecvLength,LPDWORD lpBytesReturned)
{
	fprintf(stderr,"wine_SCardControl: Linux \n");

    return SCardControl( hCard, dwControlCode, pbSendBuffer, cbSendLength, pbRecvBuffer, cbRecvLength, lpBytesReturned);
}

LONG wine_SCardDisconnect(SCARDHANDLE hCard, DWORD dwDisposition)
{
	fprintf(stderr,"wine_SCardDisconnect: Linux \n");

    return SCardDisconnect( hCard,dwDisposition);
}

LONG wine_SCardEndTransaction(SCARDHANDLE hCard,DWORD dwDisposition)
{
	fprintf(stderr,"wine_SCardEndTransaction: Linux \n");

    return SCardEndTransaction( hCard, dwDisposition);
}

LONG wine_SCardFreeMemory(SCARDCONTEXT hContext,LPCVOID pvMem)
{
	fprintf(stderr,"wine_SCardFreeMemory: Linux \n");

    return SCardFreeMemory( hContext, pvMem);
}

LONG wine_SCardGetAttrib(SCARDHANDLE hCard,DWORD dwAttrId,LPBYTE pbAttr,LPDWORD pcbAttrLen)
{
	fprintf(stderr,"wine_SCardGetAttrib: Linux \n");

    return SCardGetAttrib( hCard, dwAttrId, pbAttr, pcbAttrLen);
}

LONG wine_SCardGetStatusChange(SCARDCONTEXT hContext,DWORD dwTimeout,SCARD_READERSTATE *rgReaderStates,
		DWORD cReaders) 	
{
	fprintf(stderr,"wine_SCardGetStatusChange: Linux \n");

    return SCardGetStatusChange( hContext, dwTimeout, rgReaderStates,cReaders);
}

LONG wine_SCardIsValidContext(SCARDCONTEXT hContext)
{
	fprintf(stderr,"wine_SCardIsValidContext: Linux \n");

    return SCardIsValidContext(hContext);
}

LONG wine_SCardListReaderGroups(SCARDCONTEXT hContext,LPSTR mszGroups,LPDWORD pcchGroups)
{
	fprintf(stderr,"wine_SCardListReaderGroups: Linux \n");

    return  SCardListReaderGroups( hContext, mszGroups, pcchGroups);
}

LONG wine_SCardReconnect(SCARDHANDLE hCard,DWORD dwShareMode,DWORD dwPreferredProtocols,
		DWORD dwInitialization,LPDWORD pdwActiveProtocol)
{
	fprintf(stderr,"wine_SCardReconnect: Linux \n");

    return SCardReconnect(hCard,dwShareMode,dwPreferredProtocols,
		dwInitialization,pdwActiveProtocol);
}

LONG wine_SCardSetAttrib(SCARDHANDLE hCard,DWORD dwAttrId,LPCBYTE pbAttr,DWORD cbAttrLen)
{
	fprintf(stderr,"wine_SCardSetAttrib: Linux \n");

    return SCardSetAttrib( hCard, dwAttrId, pbAttr, cbAttrLen);
}

LONG wine_SCardStatus(SCARDHANDLE hCard,LPSTR szReaderName,LPDWORD  	pcchReaderLen,
		LPDWORD pdwState,LPDWORD pdwProtocol,LPBYTE pbAtr,LPDWORD pcbAtrLen)
{
	fprintf(stderr,"wine_SCardStatus: Linux \n");

    return SCardStatus( hCard, szReaderName,pcchReaderLen, pdwState, pdwProtocol, pbAtr, pcbAtrLen);
}

LONG wine_SCardTransmit(SCARDHANDLE hCard,const SCARD_IO_REQUEST *pioSendPci,LPCBYTE pbSendBuffer,
				DWORD cbSendLength,SCARD_IO_REQUEST *pioRecvPci,LPBYTE pbRecvBuffer,
				LPDWORD pcbRecvLength)
{
	fprintf(stderr,"wine_SCardTransmit: Linux \n");

    return SCardTransmit( hCard,pioSendPci, pbSendBuffer,
				 cbSendLength, pioRecvPci, pbRecvBuffer,pcbRecvLength);
}



