# HC-SR04-Sensor-driver
This code repository contains a device driver for HCSR04 Ultrasonic sensor and an application to successfully run two HCSR04 sensors using that device driver in ZEPHYR RTOS and Intel Galileo Board 2. The devices work only in one shot mode and the output are the distances in centimeters, the timestamp of the measurement in microseconds and the device name.

-Requirements:

  -Zephyr RTOS Version 1.14.1 (https://docs.zephyrproject.org/1.14.1/).
  -Intel Galileo Board 2.
  -Two HC-SR04 sensors.

## Patching the source file and Building the Source Code ##

**Unzip the the folder RTES-Jena-Sunjeet_02.zip and copy the patch file hcsr04.patch to the directory where the zephyr folder is location. Make sure that hcsr04.patch and zephyr root directory are located in the same folder.**

1) Patch the source code using the command:

`
$ patch -p1 < hcsr04.patch 
`

Assuming the source files and the SDK has been exported. 

2) Go inside the sample folder in the zephyr and then to HCSR_app folder run the following command in the terminal:

`$ mkdir build && cd build
`

3) Inside the build folder run the following commands in the terminals

`$ cmake -GNinja -DBOARD=galileo ..
`

`$ ninja
`

4) After this copy the **zephyr.strip** file from the** /build/zephyr/zephyr.strip** and place it in the **/SDCARD/kernel** folder.

5) Assuming that that the grub has already been copied, use the instructions below to run required experiments.

## Commands to run the experiments

Assuming that the Galileo board has been booted

**Please note that it has been assumed that HCSR0 trigger pin is IO1 and its echo pin is IO3. Similarly it has been assumed that HCSR1 trigger pin IO10 and its echo pin is IO12. Incase these are changed, its respective GPIO pins must be changed in the Kconfig file in the hc-sr04 folder and the IO pins must be updated in the hcsr.c file.**

###### Selecting the number of devices

In the command line run the command :

`$ HCSR start n
`

Replace n with 0, 1, 2, 3

0 - No Devices Selected
1- HCSR0 device was selected
2- HCSR1 device was selected
3- Both devices were selected

###### Collecting samples

In the command line run the following command to collect 'n' measurements in centimeters:

`$ HCSR start n
`

Replace 'n' with the required number of measurements.

Incase there is a timeout in any of the devices, you may see "Error" messages in the terminal.

The distances measured by the devices are in centimeters.

*Note: 'n' shoudld be less than or equal to 256.


###### Printing the collected samples

In the command line run the following command :

`$ HCSR dump n1 n2
`

Replace 'n1' with the start Index and 'n2' with the end index. Indexing in the samples starts from 0, so the last output shall show 0;

The output variables are Device names, distance in centimeters and the time stamp of the measurements in microseconds since the beginning the measurement collection was started.

###### Clearing the internal buffer

In the command line run the following command to clear the internal buffer of both the devices:

`$ HCSR clear
`

