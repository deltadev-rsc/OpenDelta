#ifndef DLTSH_GENERAL_H
#define DLTSH_GENERAL_H

#include "dltshtypes.h"
#include "chartypes.h"

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#if defined (HAVE_SYS_RESOURCE_H) && defined (RLIMTYPE)
    #if defined (HAVE_SYS_TIME_H)
        #include <sys/time.h>
    #endif
    #include <sys/resource.h>
#endif

#if defined (HAVE_STRING_H)
    #include <string.h>
#else
    #include <strings.h>
#endif /* !HAVE_STRING_H */

#if defined (HAVE_LIMITS_H)
    #include <limits.h>
#endif

#if !defined (_FUNCTION_DEF)
#define _FUNCTION_DEF
    typedef int Function ();
    typedef void VFunction ();
    typedef char *CPFunction ();
    typedef char **CPPFunction ();
#endif

#ifndef DLTSH_FUNCTION_TYPEDEF
#define DLTSH_FUNCTION_TYPEDEF
    typedef int dltsh_intfunc_t __P((int));
    typedef int dltsh_ivoidfunc_t __P((void));
    typedef int dltsh_icpfunc_t __P((char *)); 
    typedef int dltsh_icppfunc_t __P((char **));
#endif 

#ifdef __cplusplus
}
#endif

#endif 
