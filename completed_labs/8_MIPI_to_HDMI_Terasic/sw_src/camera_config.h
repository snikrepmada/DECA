/*
 * camera_config.h
 *
 *  Created on: 2015/3/27
 *      Author: User
 */

#ifndef CAMERA_CONFIG_H_
#define CAMERA_CONFIG_H_

#define MIPI_I2C_ADDR   0x6C

#define BYD_MODE_SELECT   0x0100
#define BYD_SOFTWARE_SET  0x0103
#define BYD_STREAMING     0x301A

void BYD_CONFIG_1024x768_RAW8(bool bScale, bool bTestMode);

#endif /* CAMERA_CONFIG_H_ */
