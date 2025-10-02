#include "defs.h"

void Log(const char* text, ...)
{
    va_list(args);
    va_start(args, text);
    vDbgPrintExWithPrefix("[ HandleEnum ] ", 0, 0, text, args);
    va_end(args);
}
void Walk(_HANDLE_TABLE* ObjectTable) {
    if (!ObjectTable)
        return;
    ULONG i;
    for (i = 0; i < ObjectTable->TableCode; i++)
    {
        _HANDLE_TABLE_FREE_LIST* freeList = &ObjectTable->FreeLists[i];
        if (!freeList)
            continue;
        KIRQL oldIrql;
        ExAcquirePushLockExclusive((PULONG_PTR)&freeList->FreeListLock);
        PVOID current = freeList->FirstFreeHandleEntry;
        while (current)
        {
            _HANDLE_TABLE_ENTRY* entry = (_HANDLE_TABLE_ENTRY*)current;
            Log("Handle Entry: 0x%p\n", entry);
            current = entry->NextFreeHandleEntry;
        }
        ExReleasePushLockExclusive((PULONG_PTR)&freeList->FreeListLock);
    }
}

NTSTATUS DriverEntry() {
    PEPROCESS Sigmaprocess;
    PsLookupProcessByProcessId((HANDLE)696741, &Sigmaprocess); // Proc ID or something
    Walk((_HANDLE_TABLE*)((PUCHAR)Sigmaprocess + 0x570)); //ObjectTable for Win10 22H2 64x
    return STATUS_SUCCESS;
}