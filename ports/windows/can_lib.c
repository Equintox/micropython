#include "can_lib.h"

<<<<<<< HEAD
=======

>>>>>>> b7a000461adf8b32b2d0cafe7dd439094c0e673d
//Function declarations
int load_dll();
int unload_dll();
int load_functions(HINSTANCE h_module);

//typedef of functions
typedef TPCANStatus(__stdcall *PCAN_Initialize)(TPCANHandle Channel, TPCANBaudrate Btr0Btr1, TPCANType HwType, DWORD IOPort, WORD Interrupt);
typedef TPCANStatus(__stdcall *PCAN_Uninitialize)(TPCANHandle Channel);
typedef TPCANStatus(__stdcall *PCAN_Reset)(TPCANHandle Channel);
typedef TPCANStatus(__stdcall *PCAN_GetStatus)(TPCANHandle Channel);
typedef TPCANStatus(__stdcall *PCAN_Read)(TPCANHandle Channel, TPCANMsg* MessageBuffer, TPCANTimestamp* TimestampBuffer);
typedef TPCANStatus(__stdcall *PCAN_Write)(TPCANHandle Channel, TPCANMsg* MessageBuffer);
typedef TPCANStatus(__stdcall *PCAN_FilterMessages)(TPCANHandle Channel, DWORD FromID, DWORD ToID, TPCANMode Mode);
typedef TPCANStatus(__stdcall *PCAN_GetValue)(TPCANHandle Channel, TPCANParameter Parameter, void* Buffer, DWORD BufferLength);
typedef TPCANStatus(__stdcall *PCAN_SetValue)(TPCANHandle Channel, TPCANParameter Parameter, void* Buffer, DWORD BufferLength);
typedef TPCANStatus(__stdcall *PCAN_GetErrorText)(TPCANStatus Error, WORD Language, LPSTR Buffer);


//declaration
PCAN_Initialize g_CAN_Initialize;
PCAN_Uninitialize g_CAN_Uninitialize;
PCAN_Reset g_CAN_Reset;
PCAN_GetStatus  g_CAN_GetStatus;
PCAN_Read g_CAN_Read;
PCAN_Write  g_CAN_Write;
PCAN_FilterMessages  g_CAN_FilterMessages;
PCAN_GetValue  g_CAN_GetValue;
PCAN_SetValue  g_CAN_SetValue;
PCAN_GetErrorText  g_CAN_GetErrorText;


//DLL instance Handle
HINSTANCE dll_instance;

//helper functions

int load_dll(void) {

	if (dll_instance == NULL) {

		dll_instance = LoadLibrary("PCANBasic.dll"); //Use L"PCANBasic.dll" for Windows ???

		if (dll_instance == NULL) {
			printf("Error: cannot load dll\n");
			return -1;
		}
		else {

			if (load_functions(dll_instance)) {
				printf("Successfully loaded functions from dll\n");
			}
			else {
				printf("Error: can not load Function Adresses\n");
				return -2;
			}
		}
	}
	return 0;
}

int unload_dll(void) {
	if (dll_instance) {
		FreeLibrary(dll_instance);
		g_CAN_Initialize = NULL;
		g_CAN_Uninitialize = NULL;
		g_CAN_Reset = NULL;
		g_CAN_GetStatus = NULL;
		g_CAN_Read = NULL;
		g_CAN_Write = NULL;
		g_CAN_FilterMessages = NULL;
		g_CAN_GetValue = NULL;
		g_CAN_SetValue = NULL;
		g_CAN_GetErrorText = NULL;
	}
	return 0;
}

int load_functions(HINSTANCE h_module) {

	if (h_module == NULL)
		return 0;

	g_CAN_Initialize = (PCAN_Initialize)GetProcAddress(h_module, "CAN_Initialize");
	if (g_CAN_Initialize == NULL)
		return 0;

	g_CAN_Uninitialize = (PCAN_Uninitialize)GetProcAddress(h_module, "CAN_Uninitialize");
	if (g_CAN_Uninitialize == NULL)
		return 0;

	g_CAN_Reset = (PCAN_Reset)GetProcAddress(h_module, "CAN_Reset");
	if (g_CAN_Reset == NULL)
		return 0;

	g_CAN_GetStatus = (PCAN_GetStatus)GetProcAddress(h_module, "CAN_GetStatus");
	if (g_CAN_GetStatus == NULL)
		return 0;

	g_CAN_Read = (PCAN_Read)GetProcAddress(h_module, "CAN_Read");
	if (g_CAN_Read == NULL)
		return 0;

	g_CAN_Write = (PCAN_Write)GetProcAddress(h_module, "CAN_Write");
	if (g_CAN_Write == NULL)
		return 0;

	g_CAN_FilterMessages = (PCAN_FilterMessages)GetProcAddress(h_module, "CAN_FilterMessages");
	if (g_CAN_FilterMessages == NULL)
		return 0;

	g_CAN_GetValue = (PCAN_GetValue)GetProcAddress(h_module, "CAN_GetValue");
	if (g_CAN_GetValue == NULL)
		return 0;

	g_CAN_SetValue = (PCAN_SetValue)GetProcAddress(h_module, "CAN_SetValue");
	if (g_CAN_SetValue == NULL)
		return 0;

	g_CAN_GetErrorText = (PCAN_GetErrorText)GetProcAddress(h_module, "CAN_GetErrorText");
	if (g_CAN_GetErrorText == NULL)
		return 0;

	return 1;
}

//public functions
TPCANStatus lib_initialize(TPCANHandle channel, TPCANBaudrate baudrate, TPCANType HwType _DEF_ARG, DWORD IOPort _DEF_ARG, WORD Interrupt _DEF_ARG) {
	return g_CAN_Initialize(channel, baudrate, HwType, IOPort, Interrupt);
}

TPCANStatus lib_uninitialize(TPCANHandle channel) {
	return g_CAN_Uninitialize(channel);
}

TPCANStatus lib_get_status(TPCANHandle channel) {
	return g_CAN_GetStatus(channel);
}

TPCANStatus lib_write(TPCANHandle channel, TPCANMsg *buffer) {
	return g_CAN_Write(channel, buffer);
}

TPCANStatus lib_read(TPCANHandle channel, TPCANMsg *buffer, TPCANTimestamp *timestamp_buffer) {
	return g_CAN_Read(channel, buffer, timestamp_buffer);
}

TPCANStatus lib_filter_messages(TPCANHandle channel, DWORD fromID, DWORD toID, TPCANMode mode) {
	return g_CAN_FilterMessages(channel, fromID, toID, mode);
}
//TODO: Implements status, read, filter_messages

