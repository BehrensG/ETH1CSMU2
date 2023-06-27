/*
 * TCP_Package.h
 *
 *  Created on: May 12, 2023
 *      Author: grzegorz
 */

#ifndef BSP_INC_TCP_PACKAGE_H_
#define BSP_INC_TCP_PACKAGE_H_

#define TCP_PACKGE_SIZE 9000

char* TCP_Package(float* meas, uint16_t start, uint16_t size);

#endif /* BSP_INC_TCP_PACKAGE_H_ */
