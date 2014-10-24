/*
   american fuzzy lop - vaguely configurable bits
   ----------------------------------------------

   Written and maintained by Michal Zalewski <lcamtuf@google.com>

   Copyright 2013, 2014 Google Inc. All rights reserved.

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at:

     http://www.apache.org/licenses/LICENSE-2.0

 */

#ifndef _HAVE_CONFIG_H
#define _HAVE_CONFIG_H

#include "types.h"

/******************************************************
 *                                                    *
 *  Settings that may be of interest to power users:  *
 *                                                    *
 ******************************************************/

/* Uncomment this to compile afl-gcc and afl-as to compile 64-bit binaries. */

// #define USE_64BIT

/* Comment out to disable terminal colors: */

#define USE_COLOR

/* Comment out to disable fancy boxes and use poor man's drawings: */

#define FANCY_BOXES

/* Default timeout for fuzzed code (milliseconds): */

#define EXEC_TIMEOUT        1000

/* Default memory limit for child process (MB): */

#define MEM_LIMIT           100

/* Number of calibration cycles per every new test case, and for cases
   where variable execution paths are detected: */

#define CAL_CYCLES          10
#define CAL_CYCLES_LONG     100

/* Maximum number of subsequent hangs before abandoning an input file: */

#define HANG_LIMIT          250

/* Number of samples per unique hang or crash to keep: */

#define KEEP_SAMPLES        10

/* Maximum number of unique hangs or crashes to record: */

#define KEEP_UNIQUE_HANG    1000
#define KEEP_UNIQUE_CRASH   5000

/* Number of random tweaks during a single 'havoc' stage: */

#define HAVOC_CYCLES        5000

/* Maximum multiplier for the above while new findings are being made
   (should be a power of two, and beware of 32-bit int overflows): */

#define HAVOC_MAX_MULT      16

/* Maximum stacking for havoc-stage tweaks is calculated like this: 

   n = random between 0 and HAVOC_STACK_POW2
   stacking = 2^n

   In other words, the default value produces 1, 2, 4, 8, 16, 32, or 64
   stacked tweaks: */

#define HAVOC_STACK_POW2    7

/* Caps on block sizes for cloning and deletion operations. These ranges
   have an equal probability of getting picked. */

#define HAVOC_BLK_SMALL     32
#define HAVOC_BLK_MEDIUM    128
#define HAVOC_BLK_LARGE     1500

/* Likelihood of using non-favored inputs within one fuzzing
   cycle, in percent: */

#define SKIP_TO_NEW_PROB    99
#define SKIP_NFAV_PROB      94

/* Splicing cycle count: */

#define SPLICE_CYCLES       20

/* Nominal per-splice havoc cycle length: */

#define SPLICE_HAVOC        500

/* Maximum value for integer addition / subtraction stages: */

#define ARITH_MAX           35

/* List of interesting values to use in fuzzing. */

#define INTERESTING_8 \
  -128,          /* Overflow signed 8-bit when decremented  */ \
  -1,            /*                                         */ \
   0,            /*                                         */ \
   1,            /*                                         */ \
   16,           /* One-off with common buffer size         */ \
   32,           /* One-off with common buffer size         */ \
   64,           /* One-off with common buffer size         */ \
   100,          /* One-off with common buffer size         */ \
   127           /* Overflow signed 8-bit when incremented  */

#define INTERESTING_16 \
  -32768,        /* Overflow signed 16-bit when decremented */ \
  -129,          /* Overflow signed 8-bit                   */ \
   128,          /* Overflow signed 8-bit                   */ \
   255,          /* Overflow unsig 8-bit when incremented   */ \
   256,          /* Overflow unsig 8-bit                    */ \
   512,          /* One-off with common buffer size         */ \
   1000,         /* One-off with common buffer size         */ \
   1024,         /* One-off with common buffer size         */ \
   4096,         /* One-off with common buffer size         */ \
   32767         /* Overflow signed 16-bit when incremented */

#define INTERESTING_32 \
  -2147483648LL, /* Overflow signed 32-bit when decremented */ \
  -100663046,    /* Large negative number (endian-agnostic) */ \
  -32769,        /* Overflow signed 16-bit                  */ \
   32768,        /* Overflow signed 16-bit                  */ \
   65535,        /* Overflow unsig 16-bit when incremented  */ \
   65536,        /* Overflow unsig 16 bit                   */ \
   100663045,    /* Large positive number (endian-agnostic) */ \
   2147483647    /* Overflow signed 32-bit when incremented */

/***********************************************************
 *                                                         *
 *  Really exotic stuff you probably don't want to touch:  *
 *                                                         *
 ***********************************************************/

/* Call count interval between reseeding the libc PRNG from /dev/urandom: */

#define RESEED_RNG          10000

/* Maximum line length passed from GCC to 'as': */

#define MAX_AS_LINE         8192

/* Environment variable used to pass SHM ID to the called program. */

#define SHM_ENV_VAR         "__AFL_SHM_ID"

/* Distinctive exit code used to indicate failed execution: */

#define EXEC_FAIL           0x55

/* Designated file desciptors for forkserver commands (the application will
   use FORKSRV_FD and FORKSRV_FD + 1): */

#define FORKSRV_FD          198

/* Fork server init timeout multiplier: we'll wait the user-selected
   timeout plus this much for the fork server to spin up. */

#define FORK_WAIT_MULT      10

/* Calibration timeout multiplier (%). */

#define CAL_TMOUT_PERC      150

/* Map size for the traced binary (2^MAP_SIZE_POW2). Must be greater than
   2; keep it under 16 or so for performance reasons. You need to recompile
   the target binary after changing this - otherwise, SEGVs may ensue. */

#define MAP_SIZE_POW2       14
#define MAP_SIZE            (1<<MAP_SIZE_POW2)

/* Maximum allocator request size (keep well under INT_MAX): */

#define MAX_ALLOC           0x40000000

/* Maximum size of input file (keep under 100MB): */

#define MAX_FILE            (1 * 1000 * 1000)

/* UI refresh frequency (Hz): */

#define UI_TARGET_HZ        4

/* Uncomment this to use inferior coverage-based instrumentation. Note that
   you need to recompile the target binary for this to have any effect! */

// #define COVERAGE_ONLY

/* Uncomment this to use instrumentation data, but ignore newly discovered
   paths. This is useful for comparing the coverage attainable using the
   standard algorithm with that possible with dumb fuzzing. */

// #define IGNORE_FINDS

#endif /* ! _HAVE_CONFIG_H */
