/* Test for decoding SMS on Nokia 6510 driver */

#include <gammu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "common.h"

#include "../libgammu/protocol/protocol.h" /* Needed for GSM_Protocol_Message */
#include "../libgammu/gsmstate.h" /* Needed for state machine internals */

#include "../helper/message-display.h"

unsigned char data[] = {
	0x00, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x91, 0x00, 0x5B, 0x00, 0x42,
	0x00, 0x75, 0x00, 0x67, 0x00, 0x20, 0x00, 0x32, 0x00, 0x31, 0x00, 0x33, 0x00, 0x36, 0x00, 0x33,
	0x00, 0x39, 0x00, 0x5D, 0x00, 0x20, 0x00, 0x52, 0x00, 0x65, 0x00, 0x3A, 0x00, 0x20, 0x00, 0x50,
	0x00, 0x72, 0x00, 0x6F, 0x00, 0x62, 0x00, 0x6C, 0x00, 0x65, 0x00, 0x6D, 0x00, 0x20, 0x00, 0x77,
	0x00, 0x69, 0x00, 0x74, 0x00, 0x68, 0x00, 0x20, 0x00, 0x49, 0x00, 0x44, 0x00, 0x45, 0x00, 0x20,
	0x00, 0x44, 0x00, 0x56, 0x00, 0x44, 0x00, 0x2D, 0x00, 0x52, 0x00, 0x57, 0x00, 0x00, 0x00, 0x62,
	0x00, 0x69, 0x00, 0x67, 0x00, 0x6C, 0x00, 0x40, 0x00, 0x61, 0x00, 0x66, 0x00, 0x66, 0x00, 0x2E,
	0x00, 0x63, 0x00, 0x6F, 0x00, 0x6D, 0x00, 0x2E, 0x00, 0x70, 0x00, 0x6C, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x01, 0x00, 0xDE, 0x01, 0x00, 0x01, 0x00, 0x08, 0x00, 0x01, 0x00, 0x0E, 0x00, 0x01, 0x00, 0x0B,
	0x00, 0x01, 0x00, 0x06, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x09, 0x00, 0x04, 0x00, 0x00, 0x00,
	0x00, 0x27, 0x00, 0x01, 0x00, 0x23, 0x00, 0x04, 0x00, 0x00, 0x09, 0xA6, 0x26, 0x00, 0x01, 0x00,
	0x04, 0x00, 0x20, 0x00, 0x62, 0x00, 0x69, 0x00, 0x67, 0x00, 0x6C, 0x00, 0x40, 0x00, 0x61, 0x00,
	0x66, 0x00, 0x66, 0x00, 0x2E, 0x00, 0x63, 0x00, 0x6F, 0x00, 0x6D, 0x00, 0x2E, 0x00, 0x70, 0x00,
	0x6C, 0x00, 0x00, 0x07, 0x00, 0x01, 0x00, 0x05, 0x00, 0x01, 0x00, 0x12, 0x00, 0x04, 0x35, 0xEA,
	0x6E, 0xD2, 0x24, 0x00, 0x01, 0x00, 0x04, 0x00, 0x36, 0x00, 0x72, 0x00, 0x75, 0x00, 0x73, 0x00,
	0x6C, 0x00, 0x61, 0x00, 0x6E, 0x00, 0x2E, 0x00, 0x6C, 0x00, 0x65, 0x00, 0x76, 0x00, 0x69, 0x00,
	0x74, 0x00, 0x73, 0x00, 0x6B, 0x00, 0x69, 0x00, 0x79, 0x00, 0x40, 0x00, 0x67, 0x00, 0x6D, 0x00,
	0x61, 0x00, 0x69, 0x00, 0x6C, 0x00, 0x2E, 0x00, 0x63, 0x00, 0x6F, 0x00, 0x6D, 0x00, 0x00, 0x07,
	0x00, 0x01, 0x00, 0x05, 0x00, 0x01, 0x00, 0x12, 0x00, 0x04, 0x35, 0xEA, 0x6E, 0xD2, 0x24, 0x00,
	0x01, 0x01, 0x22, 0x00, 0x01, 0x84, 0x25, 0x00, 0x0E, 0x00, 0x4C, 0x00, 0x65, 0x00, 0x73, 0x00,
	0x7A, 0x00, 0x65, 0x00, 0x6B, 0x00, 0x00, 0x20, 0x00, 0x17, 0x47, 0x6D, 0x61, 0x69, 0x6C, 0x49,
	0x64, 0x31, 0x31, 0x63, 0x31, 0x33, 0x30, 0x31, 0x32, 0x39, 0x31, 0x33, 0x64, 0x30, 0x61, 0x66,
	0x37,
	};

const char text[] = "Orthop. KH Gersthof\nWielemansg. 28, 1180\nstation A, Zi. 110\nwerde voraussichtl. Morgen Op. & freu mich, wenn ihr Zeit habt.";

/* This is not part of API! */
extern GSM_Error N6510_DecodeFilesystemSMS(GSM_StateMachine *s, GSM_MultiSMSMessage *sms, GSM_File *FFF, int location);

int main(int argc UNUSED, char **argv UNUSED)
{
	GSM_Debug_Info *debug_info;
	GSM_StateMachine *s;
	GSM_File file;
	GSM_Error error;
	GSM_MultiSMSMessage sms;

	debug_info = GSM_GetGlobalDebug();
	GSM_SetDebugFileDescriptor(stderr, FALSE, debug_info);
	GSM_SetDebugLevel("textall", debug_info);

	/* Allocates state machine */
	s = GSM_AllocStateMachine();
	test_result (s != NULL);

	debug_info = GSM_GetDebug(s);
	GSM_SetDebugGlobal(TRUE, debug_info);

	/* Init file */
	file.Buffer = malloc(sizeof(data));
	memcpy(file.Buffer, data, sizeof(data));
	file.Used = sizeof(data);
	file.ID_FullName[0] = 0;
	file.ID_FullName[1] = 0;
	GSM_GetCurrentDateTime(&(file.Modified));

	/* Parse it */
	error = N6510_DecodeFilesystemSMS(s, &sms, &file, 0);

	/* Display message */
	DisplayMultiSMSInfo(&sms, FALSE, TRUE, NULL, NULL);
	DisplayMultiSMSInfo(&sms, TRUE, TRUE, NULL, NULL);

	/* Free state machine */
	GSM_FreeStateMachine(s);

	/* Check expected text */
	test_result(strcmp(text, DecodeUnicodeString(sms.SMS[0].Text)) == 0);

	gammu_test_result(error, "N6510_DecodeFilesystemSMS");

	return 0;
}

/* Editor configuration
 * vim: noexpandtab sw=8 ts=8 sts=8 tw=72:
 */
