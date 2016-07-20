/* 23-DEC-94 George J. Carrette.

   This is a SIOD main program with additional command-line processing
   functionality. See slib.c and siod.html for more information.

 $Id: siod.c,v 1.8 1997/05/05 12:49:09 gjc Exp $

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _DEBUG
#   include <crtdbg.h>
#endif
#include "siod.h"

static char *siod_argv[] =
{
  "siod",
  "-h100000:10",
  "-g0",
  "-o1000",
  "-s200000",
  "-n2048"
};

int main(int argc, char **argv, char **env)
{
    int nargc = argc;
    char **nargv = argv;

#if 0
#ifdef _DEBUG
        int tmpflag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

        tmpflag |= _CRTDBG_ALLOC_MEM_DF;
        tmpflag |= _CRTDBG_CHECK_ALWAYS_DF;
        tmpflag |= _CRTDBG_LEAK_CHECK_DF;

        _CrtSetDbgFlag (tmpflag);

        _CrtSetBreakAlloc(0x88);
#endif
#endif

    if (nargc > 0)
        siod_shuffle_args(&nargc,&nargv);

    process_cla(sizeof(siod_argv)/sizeof(char*), siod_argv, 1);

    return(siod_main(nargc, nargv, env, 0));
}

