//Jai Shri Ram // Om Hum Hanumate Namah

// Sunjeet Jena
// CSE522 Real Time Embedded Systems Spring 2021 - Arizona State University

#ifndef ZEPHYR_DRIVERS_SENSOR_HCSR04
#define ZEPHYR_DRIVERS_SENSOR_HCSR04

#include <device.h>
#include <misc/util.h>
#include <zephyr/types.h>
#include <gpio.h>

struct hcsr_data {
	u64_t data1;
	u64_t data2;
};
struct hcsr_config_data{

	u32_t triggerPin;
	u32_t echoPin;
	struct device *gpiob_trigger;
	struct device *gpiob_echo;

};
#endif
