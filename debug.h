/*
   american fuzzy lop - debug / error handling macros
   --------------------------------------------------

   Written and maintained by Michal Zalewski <lcamtuf@google.com>

   Copyright 2013, 2014 Google Inc. All rights reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at:

     http://www.apache.org/licenses/LICENSE-2.0

 */

#ifndef _HAVE_DEBUG_H
#define _HAVE_DEBUG_H

#include "types.h"
#include "config.h"

/* Terminal colors */

#ifdef USE_COLOR

#  define cBLK "\x1b[0;30m"
#  define cRED "\x1b[0;31m"
#  define cGRN "\x1b[0;32m"
#  define cBRN "\x1b[0;33m"
#  define cBLU "\x1b[0;34m"
#  define cMGN "\x1b[0;35m"
#  define cCYA "\x1b[0;36m"
#  define cNOR "\x1b[0;37m"
#  define cGRA "\x1b[1;30m"
#  define cLRD "\x1b[1;31m"
#  define cLGN "\x1b[1;32m"
#  define cYEL "\x1b[1;33m"
#  define cLBL "\x1b[1;34m"
#  define cPIN "\x1b[1;35m"
#  define cLCY "\x1b[1;36m"
#  define cBRI "\x1b[1;37m"
#  define cRST "\x1b[0m"

#else

#  define cBLK ""
#  define cRED ""
#  define cGRN ""
#  define cBRN ""
#  define cBLU ""
#  define cMGN ""
#  define cCYA ""
#  define cNOR ""
#  define cGRA ""
#  define cLRD ""
#  define cLGN ""
#  define cYEL ""
#  define cLBL ""
#  define cPIN ""
#  define cLCY ""
#  define cBRI ""
#  define cRST ""

#endif /* ^USE_COLOR */

/* Box drawing sequences */

#ifdef FANCY_BOXES

#  define bSTART  "\x1b(0"        /* Enter box drawing mode    */
#  define bSTOP   "\x1b(B"        /* Exit box drawing mode     */
#  define bH      "q"             /* Horizontal line           */
#  define bV      "x"             /* Vertical line             */
#  define bLT     "l"             /* Left top corner           */
#  define bRT     "k"             /* Right top corner          */
#  define bLB     "m"             /* Left bottom corner        */
#  define bRB     "j"             /* Right bottom corner       */
#  define bX      "n"             /* Cross                     */
#  define bVR     "t"             /* Vertical, branch right    */
#  define bVL     "u"             /* Vertical, branch left     */
#  define bHT     "v"             /* Horizontal, branch top    */
#  define bHB     "w"             /* Horizontal, branch bottom */

#else

#  define bSTART  ""
#  define bSTOP   ""
#  define bH      "-"
#  define bV      "|"
#  define bLT     "+"
#  define bRT     "+"
#  define bLB     "+"
#  define bRB     "+"
#  define bX      "+"
#  define bVR     "+"
#  define bVL     "+"
#  define bHT     "+"
#  define bHB     "+"

#endif /* ^FANCY_BOXES */

/* Misc terminal codes */

#define TERM_HOME     "\x1b[H"
#define TERM_CLEAR    TERM_HOME "\x1b[2J"
#define cEOL          "\x1b[0K"

/* Debug & error macros */

#ifdef MESSAGES_TO_STDOUT
#  define SAYF(x...)    printf(x)
#else 
#  define SAYF(x...)    fprintf(stderr, x)
#endif /* ^MESSAGES_TO_STDOUT */

#define WARNF(x...) do { \
    SAYF(cYEL "[!] " cBRI "WARNING: " cNOR x); \
    SAYF(cRST "\n"); \
  } while (0)

#define OKF(x...) do { \
    SAYF(cLGN "[+] " cNOR x); \
    SAYF(cRST "\n"); \
  } while (0)

#define ACTF(x...) do { \
    SAYF(cLBL "[*] " cNOR x); \
    SAYF(cRST "\n"); \
  } while (0)

#define BADF(x...) do { \
    SAYF(cLRD "\n[-] " cNOR x); \
    SAYF(cRST "\n"); \
  } while (0)

#define FATAL(x...) do { \
    SAYF(cLRD "\n[-] PROGRAM ABORT : " cBRI x); \
    SAYF(cLRD "\n         Location : " cNOR "%s(), %s:%u\n\n" cRST, \
         __FUNCTION__, __FILE__, __LINE__); \
    exit(1); \
  } while (0)

#define ABORT(x...) do { \
    SAYF(cLRD "\n[-] PROGRAM ABORT : " cBRI x); \
    SAYF(cLRD "\n    Stop location : " cNOR "%s(), %s:%u\n\n" cRST, \
         __FUNCTION__, __FILE__, __LINE__); \
    abort(); \
  } while (0)

#define PFATAL(x...) do { \
    SAYF(cLRD "\n[-]  SYSTEM ERROR : " cBRI x); \
    SAYF(cLRD "\n    Stop location : " cNOR "%s(), %s:%u\n", \
         __FUNCTION__, __FILE__, __LINE__); \
    fflush(stdout); \
    perror(cLRD "       OS message " cNOR); \
    SAYF(cRST "\n"); \
    exit(1); \
  } while (0)

#endif /* ! _HAVE_DEBUG_H */
