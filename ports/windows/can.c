#include "py/nlr.h"
#include "py/obj.h"
#include "py/runtime.h"
#include "py/binary.h"
#include "can_lib.h"
#include <string.h>
#include <stdio.h>


static TPCANHandle can_channel;
static TPCANStatus can_status;


STATIC mp_obj_t can_init(mp_obj_t channel) {

	if(load_dll() != 0){
		printf("Error loading dll\n");
		return 0;
	}

	TPCANHandle ch;

	switch(mp_obj_get_int(channel)) {
		case 1:
			can_channel = PCAN_USBBUS1;
		break;
		case 2:
			can_channel = PCAN_USBBUS2;
		break;
	}

	//TODO: init other stuff
	can_status = lib_initialize(can_channel, PCAN_BAUD_500K, 0, 0, 0);

	return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_1(can_init_obj, can_init);


STATIC mp_obj_t can_write(mp_obj_t id, mp_obj_t str, mp_obj_t len) {

	TPCANMsg send_message_buffer;

	send_message_buffer.ID = mp_obj_get_int(id);
	send_message_buffer.LEN = mp_obj_get_int(len);
	send_message_buffer.MSGTYPE = PCAN_MESSAGE_STANDARD;

	char *msg = mp_obj_str_get_str(str);
	for(int i = 0; i < send_message_buffer.LEN; i++){
		send_message_buffer.DATA[i] = (int) msg[i];
	} 

	can_status = lib_write(can_channel, &send_message_buffer);

    return mp_const_none;
}
STATIC MP_DEFINE_CONST_FUN_OBJ_3(can_write_obj, can_write);


STATIC const mp_map_elem_t can_globals_table[] = {
	{ MP_OBJ_NEW_QSTR(MP_QSTR___name__), MP_OBJ_NEW_QSTR(MP_QSTR_can) },
	{ MP_OBJ_NEW_QSTR(MP_QSTR_init), (mp_obj_t)&can_init_obj },
    { MP_OBJ_NEW_QSTR(MP_QSTR_write), (mp_obj_t)&can_write_obj },

};

STATIC MP_DEFINE_CONST_DICT(mp_module_can_globals, can_globals_table);

const mp_obj_module_t mp_module_can = {
    .base = { &mp_type_module },
    .globals = (mp_obj_dict_t*)&mp_module_can_globals,
};
