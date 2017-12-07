#ifndef __INCLUDES_H
#define __INCLUDES_H

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <intrinsics.h>

#include "arm_comm.h"
#include "arm_math.h"
#include "stm32f10x.h"
#include "main.h"
#include "functions.h"
#include "decoder.h"
#include "init.h"
   
#include "drv_glcd_cnfg.h"
#include "drv_glcd.h"
#include "glcd_ll.h"
#include "joels.h"

#include "i2c1_drv.h"

extern FontType_t Terminal_6_8_6;
extern FontType_t Terminal_9_12_6;
extern FontType_t Terminal_18_24_12;

#endif /* __INCLUDES_H */