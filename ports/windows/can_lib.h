#include <conio.h>
#include <string.h>
#include <windows.h>
#include "pcanbasic.h"

#ifndef CAN_LIB_H
#define CAN_LIB_H

int load_dll(void);

TPCANStatus lib_write(TPCANHandle channel, TPCANMsg *buffer);

TPCANStatus lib_uninitialize(TPCANHandle channel);

TPCANStatus lib_initialize(TPCANHandle channel, TPCANBaudrate baudrate, TPCANType HwType _DEF_ARG, DWORD IOPort _DEF_ARG, WORD Interrupt _DEF_ARG);


#endif
