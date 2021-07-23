//Jai Shri Ram // Om Hum Hanumate Namah

// Sunjeet Jena
// CSE522 Real Time Embedded Systems Spring 2021 - Arizona State University
// Assignment 2
#include <i2c.h>
#include <init.h>
#include <misc/__assert.h>
#include <misc/byteorder.h>
#include <sensor.h>
#include <string.h>
#include <pinmux.h>
#include <logging/log.h>
#include <gpio.h>
#include <pwm.h>
#include "hcsr04.h"
#include <misc/printk.h>
#include "../boards/x86/galileo/board.h"
#include "../boards/x86/galileo/pinmux_galileo.h"
#include "../drivers/gpio/gpio_dw_registers.h"
#include "../drivers/gpio/gpio_dw.h"
#include <stdlib.h>

#define DEBUG 

#if defined(DEBUG) 
	#define DPRINTK(fmt, args...) printk("DEBUG: %s():%d: " fmt, \
   		 __func__, __LINE__, ##args)
#else
 	#define DPRINTK(fmt, args...) /* do nothing if not defined*/
#endif

#define EDGE_FALLING    (GPIO_INT_EDGE | GPIO_INT_ACTIVE_LOW)
#define EDGE_RISING		(GPIO_INT_EDGE | GPIO_INT_ACTIVE_HIGH)

/* change this to enable pull-up/pull-down */
#define PULL_UP 0

/* Sleep time */
#define SLEEP_TIME	1000

//Defining the Thread Priority and the Stack Size
#define MY_STACK_SIZE 1024


//--------------------------Variables Initialization/Declaration Space -------------------------------
static struct gpio_callback gpio_cb_0;	// Declaring Call back struct for the echo interrupt of HCSR0 device 
static struct gpio_callback gpio_cb_1;		// Declaring Call back struct for the echo interrupt of HCSR1 device
// static struct device* gpio_echo_0;		// Variable to get the device binding to be used for interrupt callback of HCSR0 device
static struct device* gpio_echo_1;			// Variable to get the device binding to be used for interrupt callback of HCSR1 device

// struct k_sem triggerEcho_sem;
//----------------------------------------------------------------------------------------------------


// RDTSC Function to get Time Stamp-------------------------------------------
static __inline__ unsigned long long rdtsc(void){
    unsigned int hi, lo;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return (((unsigned long long)lo) | (((unsigned long long)hi) << 32));
}
//---------------------------------------------------------------------------


// --------------------Defining Function for Echo Interrupt Callback ------------------------ 
void echo_interrupt_cb(struct device *gpiob, struct gpio_callback *cb, u32_t pins){

	// // Reading Time Stamp of the echo interrupt Callback;
	// u32_t timeStamp=rdtsc();
	// // Declaring the required variables
	// int ret;
	// // Read the value of the Input that caused the interrupt
	// u32_t val;
	// gpio_pin_read(gpiob, CONFIG_HCSR04_DEV1_ECHO_PIN, &val);
	// struct device *dev=device_get_binding(CONFIG_HCSR04_1_NAME);
	// struct hcsr_data* dev_data=dev->driver_data;
	// printk("%d \n", val);
	// // If val==1, the interrupt was caused by a rising edge.
	// if(val==1){
	// 	printk("Rising Edge Interrupt was detected \n");
	// 	// If rising edge interrupt was detected we configure the pin to take a falling edge interrupt the next time
	// 	ret=gpio_pin_configure(gpiob, CONFIG_HCSR04_DEV1_ECHO_PIN, PULL_UP| GPIO_DIR_IN | GPIO_INT | EDGE_FALLING ); 
	// 	if(ret<0){
	// 		DPRINTK("Failed to Configure %d GPIO PIN during Echo Interrupt Callback: While Reconfiguring from EDGE_RISING to EDGE_FALLING.\n", CONFIG_HCSR04_DEV1_ECHO_PIN);
	// 		return;
	// 	}
	// }
	// // Otherwise, the interrupt was caused by a falling edge
	// else{
	// 	dev_data->data2=timeStamp;
	// 	printk("Falling Edge Interrupt was detected \n");
	// 	// If falling edge interrupt was detected we configure the pin to take a rising edge interrupt the next time
	// 	ret=gpio_pin_configure(gpiob, CONFIG_HCSR04_DEV1_ECHO_PIN, PULL_UP| GPIO_DIR_IN | GPIO_INT | EDGE_RISING  ); 
	// 	if(ret<0){
	// 		DPRINTK("Failed to Configure %d GPIO PIN during Echo Interrupt Callback: While Reconfiguring from EDGE_FALLING to EDGE_RISING.\n", CONFIG_HCSR04_DEV1_ECHO_PIN);
	// 		return;
	// 	}
	// 	// k_sem_give(&triggerEcho_sem);
	// }
}
//--------------------Initialization Function for HCSR0 devices------------------------------------------
// Can be done using a single function. Used two functions for better readibility
// HCSR0 Device initialization------------------------------------------
int HCSR0_init(struct device *dev)
{	
		// Variable to check return values
	int ret;

	//Getting the address to HCSR0 device config struct
	struct device_config* dev_Config=dev->config;
	// Getiing the address to HCSR0 device config_data struct(hcsr_config_data type); 
	struct hcsr_config_data* dev_config_info=dev_Config->config_info;

	// Getting the device struct for pinmux through device binding
	static struct device *pinmux; 
	pinmux=device_get_binding(CONFIG_PINMUX_NAME);

	// Setting the Pinmux for Trigger Pin ------------------------------------------------------------
	// Reading the trigger GPIO Pin
	u32_t t_Pin= dev_config_info->triggerPin;

	// Setting the pinmux
	// ret=pinmux_pin_set(pinmux,1,PINMUX_FUNC_A); //IO1 -- gpio4 -- Output

	// Condition to check if the set was successful
	if(ret<0){
		DPRINTK("Error setting pin for IO1 -- GPIO4 for device: %s \n", dev_Config->name);
		return -1;
	}
	struct galileo_data *dev_test = pinmux->driver_data;
	//retrieving gpio_dw driver struct from pinmux driver
	struct device *gpiob=dev_test->gpio_dw;
	// Storing the pointer to the gpio_dw config data in in device gpiob_trigger 			
	dev_config_info->gpiob_trigger=gpiob;
	// -----------------------------------------------------------------------------------------------

	// Setting the Echo Pin in Pinmux and callback function for HCSR0 device-------------------------
	// Getting the echo pin for HCSR0 device
	u32_t e_Pin=dev_config_info->echoPin;		

	// Setting the pinmux
	// ret=pinmux_pin_set(pinmux,3,PINMUX_FUNC_B); //IO 3 -- gpio6 -- Input
	// Condition to check if the set was successful
	if(ret<0){
		DPRINTK("Error setting pin for IO3 -- GPIO6 for device: %s \n", dev_Config->name);
	}

	// Configuring the Echo Pin PIN for taking Edge Rising Input Interrupt
	ret=gpio_pin_configure(gpiob, e_Pin, PULL_UP| GPIO_DIR_IN | GPIO_INT | EDGE_RISING); 
	// Condition to check the pin was configured properly
	if(ret<0){
		DPRINTK("Failed to Configure %d GPIO PIN during HCSR0 initialization.\n", e_Pin);
		return -1;
	}

	// Initialzing the Callback function for e_Pin PIN
	// gpio_init_callback(&gpio_cb_0, echo_interrupt_cb, BIT(e_Pin));
	// // Adding the callback function to the gpiob set of functions
	// ret=gpio_add_callback(gpiob, &gpio_cb_0);
	// if(ret<0){
	// 	DPRINTK("Error adding callback function to %d PIN during HCSR0 initialization.\n", e_Pin);
	// 	return -1;
	// }
	// //Enabling the callback for the echo pin
	// ret=gpio_pin_enable_callback(gpiob, e_Pin);
	// if(ret<0){
	// 	DPRINTK("Error Enabling callback for %d PIN during HCSR0 initialization.\n", e_Pin);
	// 	return -1;
	// }
	return 0;

}

// HCSR1 Device initialization---------------------------------------------------------------------------
int HCSR1_init(struct device *dev)
{	

	// Variable to check return values
	// int ret;

	// //Getting the address to HCSR1 device config struct
	// struct device_config* dev_Config=dev->config;
	// // Getiing the address to HCSR1 device config_data struct(hcsr_config_data type); 
	// struct hcsr_config_data* dev_config_info=dev_Config->config_info;

	// // Getting the device struct for pinmux through device binding
	// static struct device *pinmux; 
	// pinmux=device_get_binding(CONFIG_PINMUX_NAME);

	// // Setting the Pinmux for Trigger Pin ------------------------------------------------------------
	// // Reading the trigger GPIO Pin
	// u32_t t_Pin= dev_config_info->triggerPin;

	// Setting the pinmux
	// ret=pinmux_pin_set(pinmux,7,PINMUX_FUNC_A); //IO 10 -- gpio2 -- Output

	// // Condition to check if the set was successful
	// if(ret<0){
	// 	DPRINTK("Error setting pin for IO10 -- GPIO2 for device: %s \n", dev_Config->name);
	// }
	// struct galileo_data *dev_test = pinmux->driver_data;
	// //retrieving gpio_dw driver struct from pinmux driver
	// struct device *gpiob=dev_test->gpio_dw;
	// // Storing the pointer to the gpio_dw config data in in device gpiob_trigger 			
	// dev_config_info->gpiob_trigger=gpiob;
	//-----------------------------------------------------------------------------------------------

	// // Setting the Echo Pin in Pinmux and callback function for HCSR1 device-------------------------
	// // Getting the echo pin for HCSR1 device
	// u32_t e_Pin=dev_config_info->echoPin;		

	// // Setting the pinmux
	// ret=pinmux_pin_set(pinmux,12,PINMUX_FUNC_B); //IO 12 -- gpio7 -- Input
	// // Condition to check if the set was successful
	// if(ret<0){
	// 	DPRINTK("Error setting pin for IO12 -- GPIO7 for device: %s \n", dev_Config->name);
	// }

	// // Configuring the Echo Pin PIN for taking Edge Rising Input Interrupt
	// ret=gpio_pin_configure(gpiob, e_Pin, PULL_UP| GPIO_DIR_IN | GPIO_INT | EDGE_RISING); 
	// // Condition to check the pin was configured properly
	// if(ret<0){
	// 	DPRINTK("Failed to Configure %d GPIO PIN during HCSR1 initialization.\n", e_Pin);
	// 	return -1;
	// }

	// // Initialzing the Callback function for e_Pin PIN
	// gpio_init_callback(&gpio_cb_1, echo_interrupt_cb, BIT(e_Pin));
	// // Adding the callback function to the gpiob set of functions
	// ret=gpio_add_callback(gpiob, &gpio_cb_1);
	// if(ret<0){
	// 	DPRINTK("Error adding callback function to %d PIN during HCSR1 initialization.\n", e_Pin);
	// 	return -1;
	// }
	// //Enabling the callback for the echo pin
	// ret=gpio_pin_enable_callback(gpiob, e_Pin);
	// if(ret<0){
	// 	DPRINTK("Error Enabling callback for %d PIN during HCSR1 initialization.\n", e_Pin);
	// 	return -1;
	// }
	return 0;
}

//------------------------Defining the API Functions-------------------------------------------------
static inline int hcsr04_sample_fetch(struct device *dev, enum sensor_channel chan){
	// printk("sample_fetch was called\n");

	// // // Variable to check return values
	// int ret;

	// //Getting the address to the HCSR device config struct
	// struct device_config* dev_Config=dev->config;

	// // Getiing the address to HCSR device config_data struct(hcsr_config_data type); 
	// struct hcsr_config_data* dev_config_info=dev_Config->config_info;

	// //----------------------------------------------
	// // Getting the trigger pin variable of the device and writing to the trigger PIN
	// u32_t t_Pin= dev_config_info->triggerPin;

	// // Writing on the the respective trigger Pin
	// // "dev_config_info->gpiob_trigger" is the pointer to the respective GPIO device pointer stored in device configuration data  
	// ret=gpio_pin_write(dev_config_info->gpiob_trigger, t_Pin, 1);
	// ret=gpio_pin_write(dev_config_info->gpiob_trigger, t_Pin, 0);

	// // Condtion for handling error
	// if(ret<0){
	// 	DPRINTK("Error writing to %d PIN during hcsr04_sample_fetch operation in device:%s \n", dev_config_info->triggerPin, dev_Config->name);
	// 	return -1;
	// }
	// // k_sleep(SLEEP_TIME);
	// // k_sem_take(&triggerEcho_sem,K_FOREVER);
	return 0;
}

static inline int  hcsr04_channel_get(struct device *dev, enum sensor_channel chan, struct sensor_value* sense_val){
	// printk("channel_get was called\n");

	// //Getting the address to the HCSR device config struct
	// struct device_config* dev_Config=dev->config;
	// // Getiing the address to HCSR device config_data struct(hcsr_config_data type); 
	// struct hcsr_config_data* dev_config_info=dev_Config->config_info;

	// struct hcsr_data* dev_data=dev->driver_data;

	// // sensor_val->val1=dev_data->data1;
	// // sensor_val->val2=dev_data->data2;

	// printk("%lld \n", dev_data->data1);
	// printk("%lld \n", dev_data->data2);
	// printk("-----------------------\n");
	return 0;
}

static inline int  hcsr04_attr_set(struct device *dev, enum sensor_channel chan, enum sensor_attribute sensorAttr, const struct sensor_value *val){
	printk("attr_set was called\n");
	return 0;
}

//------------------------------------------------------------------------------------------------------
static struct sensor_driver_api hcsr04_driver_api={
	.sample_fetch= hcsr04_sample_fetch,
	.channel_get= hcsr04_channel_get,
	.attr_set= hcsr04_attr_set
};

//----------------- Filling the configuration data of both the sensor devices---------------------------
struct hcsr_config_data hcsr0_config_data={

	.triggerPin=CONFIG_HCSR04_DEV0_TRIGGER_PIN,
	.echoPin=CONFIG_HCSR04_DEV0_ECHO_PIN
};

struct hcsr_config_data hcsr1_config_data={
	
	.triggerPin=CONFIG_HCSR04_DEV1_TRIGGER_PIN,
	.echoPin=CONFIG_HCSR04_DEV1_ECHO_PIN
};

// -----------------------------------------------------------------------------------------------------
struct hcsr_data hcsr0_driver={
	.data1=0,
	.data2=0,
};
struct hcsr_data hcsr1_driver={
	.data1=0,
	.data2=0,
};
// HCSR0 and HCSR1 device API initialization
DEVICE_AND_API_INIT(HCSR0, CONFIG_HCSR04_0_NAME, HCSR0_init, &hcsr0_driver,
		    &hcsr0_config_data, POST_KERNEL, 6,
		    &hcsr04_driver_api);

DEVICE_AND_API_INIT(HCSR1, CONFIG_HCSR04_1_NAME, HCSR1_init, &hcsr1_driver,
		    &hcsr1_config_data, POST_KERNEL, 6,
		    &hcsr04_driver_api);
