//Jai Shri Ram // Om Hum Hanumate Namah
// Sunjeet Jena
// CSE522 Real Time Embedded Systems Spring 2021 - Arizona State University
// Assignment 2

//-----------------Including the required libraries----------------------
#include <zephyr.h>
#include <device.h>
#include <gpio.h>
#include <pwm.h>
#include <misc/util.h>
#include <misc/printk.h>
#include <shell/shell.h>
#include <shell/shell_uart.h>
#include <version.h>
#include <pinmux.h>
#include "../boards/x86/galileo/board.h"
#include "../boards/x86/galileo/pinmux_galileo.h"
#include "../drivers/gpio/gpio_dw_registers.h"
#include "../drivers/gpio/gpio_dw.h"
#include <stdlib.h>
#include <sensor.h>

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

/*Defining Sleep Time between two measurements */
#define SLEEP_TIME_MEASUREMENTS 500

//Defining the Thread Priority and the Stack Size
#define MY_STACK_SIZE 1024

// Intializing the variables
int intno=0;				
u32_t start_Time=0;			
u32_t end_Time=0;			
u32_t diff1=0;				
u32_t diff2=0;				
int start_measurement_timestamp=0; // Recording the start time when measurement was started;

// Declaring the struct Variables
struct device *gpiob; 					// For GPIO_dw



struct sensor_value sense_val; //Variable to store sensor val

// RDTSC Function to get Time Stamp-----------------------------------------------
static __inline__ unsigned long long rdtsc(void){
    unsigned int hi, lo;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    return (((unsigned long long)lo) | (((unsigned long long)hi) << 32));
}
//--------------------------------------------------------------------------------



//--------------------------Function for selection of devices ----------------------
static int select_devices(const struct shell *shell, size_t argc, char **argv){

	// Getting the option value
	int option_config=atoi(*(argv+1));

	// Selecting 0 Devices
	if(option_config==0){
		printk("No devices have been selected \n");
	}
	// Selecting HCSR_0 device
	else if(option_config==1){
		printk("HCSR_0 device been selected \n");
	}
	// Selecting HCSR_1 device
	else if(option_config==2){
		printk("HCSR_0 device been selected \n");
	}
	// Selecting HCSR_0 and HCSR_1 device
	else if(option_config==3){
		printk("HCSR_0 and HCSR_1 devices been selected \n");
	}
	// Condition to handle invalid option
	else{
		printk("Please Select a Value Between 0-3 \n");
	}
	return 0;
}
//----------------------------------------------------------------------------------

//------------------------Function for starting the measurements--------------------
static int start_measurement(const struct shell *shell, size_t argc, char **argv){

	// Getting the parameters for number of measurements to be collected
	int numberofMeasurements_=atoi(*(argv+1));
	printk("Measurement Collection Started......\n");
	
	// Defining required Variables
	// int ret;

	// Recording the time when measurement was started;
	start_measurement_timestamp=rdtsc();


	// struct device *dev=device_get_binding(CONFIG_HCSR04_1_NAME);
	// sensor_sample_fetch(dev);
	// sensor_channel_get(dev,SENSOR_CHAN_DISTANCE, &sense_val);
	return 0;
}
//----------------------------------------------------------------------------------

//-----------------------Function to print/dump data ------------------------------
static int dump_data(const struct shell *shell, size_t argc, char **argv){


	return 0;
}
//------------------------------------------------------------------------------------------

//-------------------------Function to clear internal data-----------------------------------
static int clear_buffer(const struct shell *shell, size_t argc, char **argv){

	return 0;
}

//---------------------------------------------------------------------------------------------



//----------------------------------------Registering Shell Commands----------------------------
SHELL_STATIC_SUBCMD_SET_CREATE(exp,
	SHELL_CMD(select, NULL, "Number of HCSR Devices to be Set", select_devices),
	SHELL_CMD(start, NULL, "Start the Measurements", start_measurement),
	SHELL_CMD(dump,  NULL, "Print out the data", dump_data),
	SHELL_CMD(clear,  NULL, "Clear the Internal Buffer", clear_buffer),
	SHELL_SUBCMD_SET_END /* Array terminated. */
);

SHELL_CMD_REGISTER(HCSR, &exp, "Select a Function", NULL);
//----------------------------------------------------------------------------------------------


//-----------------------------------Main Function-----------------------------------------
void main(void)
{	



	// int a=dev_config->triggerPin;
	// printk("%d", a);

}
