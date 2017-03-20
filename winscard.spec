@ stub ClassInstall32
@ stub SCardAccessNewReaderEvent
@ stub SCardReleaseAllEvents
@ stub SCardReleaseNewReaderEvent
@ stdcall SCardAccessStartedEvent()
@ stdcall SCardAddReaderToGroupA(long str str)
@ stdcall SCardAddReaderToGroupW(long wstr wstr)
@ stub SCardBeginTransaction
@ stub SCardCancel
@ stdcall SCardConnectA(long ptr long long long long)
@ stdcall SCardConnectW(long ptr long long long long)
@ stdcall SCardControl(long long long long long long long)
@ stdcall SCardDisconnect(long long)
@ stdcall SCardEndTransaction(long long)
@ stdcall SCardEstablishContext(long ptr ptr ptr) wine_SCardEstablishContext
@ stub SCardForgetCardTypeA
@ stub SCardForgetCardTypeW
@ stub SCardForgetReaderA
@ stub SCardForgetReaderGroupA
@ stub SCardForgetReaderGroupW
@ stub SCardForgetReaderW
@ stdcall SCardFreeMemory(long long) wine_SCardFreeMemory
@ stdcall SCardGetAttrib(long long long long)
@ stub SCardGetCardTypeProviderNameA
@ stub SCardGetCardTypeProviderNameW
@ stub SCardGetProviderIdA
@ stub SCardGetProviderIdW
@ stdcall SCardGetStatusChangeA(long long long long)
@ stdcall SCardGetStatusChangeW(long long long long)
@ stub SCardIntroduceCardTypeA
@ stub SCardIntroduceCardTypeW
@ stub SCardIntroduceReaderA
@ stub SCardIntroduceReaderGroupA
@ stub SCardIntroduceReaderGroupW
@ stub SCardIntroduceReaderW
@ stdcall SCardIsValidContext(long) wine_SCardIsValidContext
@ stdcall SCardListCardsA(long ptr ptr long str long)
@ stub SCardListCardsW
@ stub SCardListInterfacesA
@ stub SCardListInterfacesW
@ stdcall SCardListReaderGroupsA(long ptr long)
@ stdcall SCardListReaderGroupsW(long ptr long)
@ stdcall SCardListReadersA(long str ptr ptr)
@ stdcall SCardListReadersW(long wstr ptr ptr)
@ stub SCardLocateCardsA
@ stub SCardLocateCardsByATRA
@ stub SCardLocateCardsByATRW
@ stub SCardLocateCardsW
@ stdcall SCardReconnect(long long long long long)
@ stdcall SCardReleaseContext(long) wine_SCardReleaseContext
@ stdcall SCardReleaseStartedEvent()
@ stub SCardRemoveReaderFromGroupA
@ stub SCardRemoveReaderFromGroupW
@ stdcall SCardSetAttrib(long long long long)
@ stub SCardSetCardTypeProviderNameA
@ stub SCardSetCardTypeProviderNameW
@ stub SCardState
@ stdcall SCardStatusA (long str long long long ptr long )
@ stdcall SCardStatusW (long wstr long long long ptr long )
@ stdcall SCardTransmit(long long ptr long long ptr long)
@ extern g_rgSCardRawPci
@ extern g_rgSCardT0Pci
@ extern g_rgSCardT1Pci
