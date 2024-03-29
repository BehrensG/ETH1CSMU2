/*
 * TCP_Package.c
 *
 *  Created on: May 12, 2023
 *      Author: grzegorz
 */
#include <stdio.h>
#include <string.h>
#include "BSP.h"
#include "TCP_Package.h"

char* TCP_Package(float* meas, uint16_t start, uint16_t size)
{
	int32_t ptr = 0;
	uint32_t last = 0;
	last = size - 1;
	static char tcp_package[TCP_PACKGE_SIZE];

	memset(tcp_package,0,sizeof tcp_package);

	for (uint32_t x = 0; x < size; x++)
	{
		if((x == last) && (size > 1)) // for the last loop
		{
			ptr += snprintf(tcp_package + ptr, sizeof(tcp_package) - ptr, "%.4f", meas[start+x]);
		}
		else if((0 == x) && (size > 1)) // for the first loop
		{
			ptr += snprintf(tcp_package + ptr, sizeof(tcp_package), "%.4f,", meas[start+x]);

		}
		else if(1 == size) // only one sample
		{
			ptr += snprintf(tcp_package + ptr, sizeof(tcp_package), "%.4f", meas[start+x]);

		}
		else // for the rest
		{
			ptr += snprintf(tcp_package + ptr, sizeof(tcp_package) - ptr, "%.4f,", meas[start+x]);
		}

	}
	//ptr += snprintf(tcp_package + ptr, sizeof(tcp_package), "\r\n", 2);

	return tcp_package;
}
