/* Single include file to define CPU clock frequency (F_CPU) which is used for several built in functions
such as delays.

usage:

select appropriate value below use:

#include "F_cpu_lib.h"

in other header / C source files as necessary to define the value of F_CPU
*/

#ifndef F_cpu_LIB_H_
#define F_cpu_LIB_H_


#define F_CPU   8000000ul   // factory defalut speed for ATMEGA128 4P using internal clock 
//#define F_CPU   8000000ul   // fast speed using internal clock - set divide by 8 fuse = -
//#define F_CPU  11059200ul   // Crystal oscillator speed used for LTU controller board - this value
                            // works well to get the serial I/O frequency to come out evenly at
                            // typical baud rates

#endif