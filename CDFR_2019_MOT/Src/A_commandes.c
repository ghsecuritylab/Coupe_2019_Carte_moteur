/*
 * A_commandes.c
 *
 *  Created on: 5 août 2018
 *      Author: guillaume
 */

#include "A_commandes.h"


/**
 *
 */
void F_Process_Command(struct tcp_command s_cmd_received, struct tcp_answer *s_cmd_answer)
{
	uint8_t status = STATUS_OK;

	s_cmd_answer->id = s_cmd_received.id; 	// same ID as the received command
	s_cmd_answer->nb_octet = NB_OCTETS_CMD;
	s_cmd_answer->cmd = s_cmd_received.cmd;	// recall the command executed

	// Process the command depending on the command number
	switch(s_cmd_received.cmd)
	{
		// Get info
		case CMD_INFO:
			break;

		// Set LED
		case CMD_SET_LED:
			status = F_Cmd_SetLED(s_cmd_received, s_cmd_answer);
			break;

		// Get distances from sensors
		case CMD_GET_DISTANCES:
			break;

		// Set robot's position
		case CMD_SET_POSITION:
			break;

		// get robot's position
		case CMD_GET_POSITION:
			break;

		// Start navigation
		case CMD_GO:
			break;

		// Add a new point to the list of points
		case CMD_ADD_POINT:
			break;

		// Remove one point from the list of points
		case CMD_REMOVE_POINT:
			break;

		// Get the list of points
		case CMD_GET_LIST_POINTS:
			break;

		// Error, unknown command
		default:
			break;

	}


}



/**
 * Get the info and build the TCP packet accordingly
 */
void F_Cmd_Info()
{

}

/**
 * Set the on board LEDs
 */
uint8_t F_Cmd_SetLED(struct tcp_command s_cmd_received, struct tcp_answer *s_cmd_answer)
{
	uint8_t status = STATUS_OK;
	// All LEDs
	if(s_cmd_received.params[0] == 0)
	{
		F_GPIO_SetLedRed(s_cmd_received.params[1]);
		F_GPIO_SetLedBlue(s_cmd_received.params[1]);
		F_GPIO_SetLedGreen(s_cmd_received.params[1]);
	}
	// Red
	else if(s_cmd_received.params[0] == 1)
	{
		F_GPIO_SetLedRed(s_cmd_received.params[1]);
	}
	// blue
	else if(s_cmd_received.params[0] == 2)
	{
		F_GPIO_SetLedBlue(s_cmd_received.params[1]);
	}
	// Green
	else if(s_cmd_received.params[0] == 3)
	{
		F_GPIO_SetLedGreen(s_cmd_received.params[1]);
	}
	else
	{
		status = STATUS_ERROR_PARAM;
	}

	s_cmd_answer->code_retour = status;
	s_cmd_answer->reponse[0] = 0;
	s_cmd_answer->reponse[1] = 0;
	s_cmd_answer->reponse[2] = 0;
	s_cmd_answer->reponse[3] = 0;

	return status;
}
