#include <win_kernel/process.h>
#include <win_kernel/memory_manager.h>
#include <win_kernel/kernel_objects.h>
#include <debug.h>

STATUS PspMarkProcessProtected(IN QWORD eprocess, IN BYTE protectionLevel, IN BYTE signLevel, 
    IN BYTE sectionSignLevel)
{
    QWORD pid;
    
    if(WinMmCopyMemoryToGuest(eprocess + EPROCESS_SIGN_LEVEL, &signLevel, sizeof(BYTE)) != STATUS_SUCCESS)
    {
        Print("Could not mark process as protected!\n");
        return STATUS_PROTECTED_PROCESS_FAILED;
    }
    if(WinMmCopyMemoryToGuest(eprocess + EPROCESS_SECTION_SIGN_LEVEL, &sectionSignLevel, sizeof(BYTE)) 
        != STATUS_SUCCESS)
    {
        Print("Could not mark process as protected!\n");
        return STATUS_PROTECTED_PROCESS_FAILED;
    }
    if(WinMmCopyMemoryToGuest(eprocess + EPROCESS_PROTECTION, &protectionLevel, sizeof(BYTE)) 
        != STATUS_SUCCESS)
    {
        Print("Could not mark process as protected!\n");
        return STATUS_PROTECTED_PROCESS_FAILED;
    }
    ObjGetObjectField(EPROCESS, eprocess, EPROCESS_PID, &pid);
    Print("Successfully marked process %d as protected with a protection level of: %d\n", pid, protectionLevel);
    return STATUS_SUCCESS;
}