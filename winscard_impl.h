



#ifndef WINSCARDIMPL
#define WINSCARDIMPL

#ifdef USR_LINUX  //winscard_impl.c
#include <winscard.h>
#define SCARD_READERSTATE_T SCARD_READERSTATE
#else
#define SCARD_READERSTATE_T SCARD_READERSTATEA
#endif


LONG wine_SCardEstablishContext(DWORD dwScope,
		/*@null@*/ LPCVOID pvReserved1, /*@null@*/ LPCVOID pvReserved2,
		/*@out@*/ LPSCARDCONTEXT phContext);

LONG wine_SCardStatus(SCARDHANDLE hCard,
		/*@null@*/ /*@out@*/ LPSTR mszReaderName,
		/*@null@*/ /*@out@*/ LPDWORD pcchReaderLen,
		/*@null@*/ /*@out@*/ LPDWORD pdwState,
		/*@null@*/ /*@out@*/ LPDWORD pdwProtocol,
		/*@null@*/ /*@out@*/ LPBYTE pbAtr,
		/*@null@*/ /*@out@*/ LPDWORD pcbAtrLen);

LONG wine_SCardIsValidContext(SCARDCONTEXT hContext);

LONG wine_SCardReleaseContext(SCARDCONTEXT hContext);

LONG wine_SCardListReaders(SCARDCONTEXT hContext,
		LPCSTR mszGroups,
		LPSTR mszReaders,
		LPDWORD pcchReaders );

LONG wine_SCardConnect(SCARDCONTEXT hContext,
				LPCSTR szReader,
				DWORD dwShareMode,
				DWORD dwPreferredProtocols,
				LPSCARDHANDLE phCard,
				LPDWORD pdwActiveProtocol);

LONG wine_SCardControl(SCARDHANDLE hCard,
					DWORD dwControlCode,
					LPCVOID pbSendBuffer,
					DWORD cbSendLength,
					LPVOID pbRecvBuffer,
					DWORD cbRecvLength,
					LPDWORD lpBytesReturned 
				);

LONG wine_SCardDisconnect(SCARDHANDLE hCard,
						DWORD dwDisposition);

LONG wine_SCardEndTransaction(SCARDHANDLE hCard,DWORD dwDisposition);	


LONG wine_SCardFreeMemory(SCARDCONTEXT hContext,LPCVOID pvMem);

LONG wine_SCardGetAttrib(SCARDHANDLE hCard,DWORD dwAttrId,LPBYTE pbAttr,LPDWORD pcbAttrLen);

LONG wine_SCardGetStatusChange(SCARDCONTEXT hContext,DWORD dwTimeout,SCARD_READERSTATE_T *rgReaderStates,
		DWORD cReaders);

LONG wine_SCardIsValidContext(SCARDCONTEXT hContext);

LONG wine_SCardListReaderGroups(SCARDCONTEXT hContext,LPSTR mszGroups,LPDWORD pcchGroups);

LONG wine_SCardReconnect(SCARDHANDLE hCard,DWORD dwShareMode,DWORD dwPreferredProtocols,
		DWORD dwInitialization,LPDWORD pdwActiveProtocol);

LONG wine_SCardSetAttrib(SCARDHANDLE hCard,DWORD dwAttrId,LPCBYTE pbAttr,DWORD cbAttrLen);

LONG wine_SCardStatus(SCARDHANDLE hCard,LPSTR szReaderName,LPDWORD  	pcchReaderLen,
		LPDWORD pdwState,LPDWORD pdwProtocol,LPBYTE pbAtr,LPDWORD pcbAtrLen);

LONG wine_SCardTransmit(SCARDHANDLE hCard,const SCARD_IO_REQUEST *pioSendPci,LPCBYTE pbSendBuffer,
				DWORD cbSendLength,SCARD_IO_REQUEST *pioRecvPci,LPBYTE pbRecvBuffer,
				LPDWORD pcbRecvLength);

#endif //WINSCARDIMPL

