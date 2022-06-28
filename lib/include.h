
#ifndef INCLUDE_H_
#define INCLUDE_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "TM4C1294NCPDT.h"
//////////////////////PRESCALADOR
// fin  = fxtal / [(Q+1) * (N+1)]
//      = 25MHz / [(0+1) * (4+1)] = 5MHz
// fvoc = fin * MDIV
//      = 5MHz * 96.00 = 480MHz
// fsyclk = fvco / (PSYSDIV + 1)
//        = 480 / (3 + 1 ) = 120MHz
//        = 480 / (x + 1) = 80MHz, x = 5, se modifica en linea 26 PSYSDIV


#define MINT    96
#define MFRAC   0
#define N       4
#define Q       0
#define PSYSDIV 5 //para 80MHz

#define FBCHT   0x6
#define EBCHT   0x6
#define FBCE    0
#define EBCE    0
#define FWS     0x5
#define EWS     0x5
#define MB1     0x00100010


#include "../PLL/PLL.h"
#include "../UART/UART.h"




#endif /* INCLUDE_H_ */
