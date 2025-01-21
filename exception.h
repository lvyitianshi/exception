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
#define catch(record, context) __except(__default_filter(GetExceptionInformation(), record, context))
#define ULPA(v) (ULONG_PTR[]){v}
#define ULP(v) (ULONG_PTR)(v)
#define throw(code, num, args) RaiseException(code, EXCEPTION_NONCONTINUABLE, num, args)
#define finally __finally
#define leave __leave
#define abnormal _abnormal_termination()

#endif // _EXCEPTION_H_