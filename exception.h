#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include <Windows.h>

#define EXCEPTION_SOFTWAR_DEFINED 0xE0000000

static int __default_filter(const PEXCEPTION_POINTERS ep, PEXCEPTION_RECORD record, PCONTEXT context) {
    if (record) *record = *(ep->ExceptionRecord);
    if (context) *context = *(ep->ContextRecord);
    return EXCEPTION_EXECUTE_HANDLER;
}

#define try __try
#define catch(record, context) __except(__default_filter(GetExceptionInformation(), (record), (context)))
#define ULP(v) (ULONG_PTR)(v)

#define throw(code, args) do {\
    const ULONG_PTR _args[] = args;\
    RaiseException(\
        code,\
        EXCEPTION_NONCONTINUABLE,\
        sizeof(_args) / sizeof(ULONG_PTR),\
        _args\
    );\
} while (0)

#define finally __finally
#define leave __leave
#define abnormal _abnormal_termination()

#endif // _EXCEPTION_H_