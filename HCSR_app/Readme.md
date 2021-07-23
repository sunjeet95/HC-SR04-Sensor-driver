################################### READ ME FILE FOR PROJECT 1: CSE522 Spring 2021-Real Time Embedded Systems #############################################

NAME: Sunjeet Jena
ASUID: 1218420294

##################### Building the source files #####################################################

Unzip the the folder RTES-Jena-Sunjeet_01.zip and copy the folder the zephyr/samples

Assuming the source files and the SDK has been exported. 
Go inside the folder and run the following command in the terminal:

$ mkdir build && cd build

Inside the build folder run the following commands in the terminals

$ cmake -GNinja -DBOARD=galileo ..

$ ninja


After this copy the zephyr.strip file from the /build/zephyr/zephyr.strip and place it in the /SDCARD/kernel folder

Assuming that that the grub has already been copied, use the instructions below to run required experiments

#################### Commands to run the experiments #################################################

Assuming that the Galileo board has been booted

--------------Running the RGB-Display Experiment  ----------------------------------

In the command line run the command

project1 RGB-display r1 g1 b1

Replace r1,g1, b1 with the required duty cycles in % for the PWM (eg: 20 40 60)

You should see the led blinking

According to the project description it has been assumed that PCA9685’s PWM3, PWM5, and PWM7 are connected to the R, G, and B pins of the led.



------------- Runing the Interrupt Latency Experiment ------------------------------

In the command line run the following command to get the Interrupt latency in Nanoseconds over 'n' measurements

project1 int-latency n

Replace 'n' with the required number of measurements

There will be an output everytime Interrupt Callback is called and the final output will show the average latency delay.


The latency here is being measured using rdtsc() stamp counter difference and then multiplying with 2.5.

*NOTE: You might see that you are getting an average of 0 the first time you run this experiment. This shouldn't happen in succesor experiments.




------------- Runing the Context Switch Latency Experiment ------------------------------

In the command line run the following command to get the Context Switch Latency in Nanoseconds over 'n' measurements

project1 cs-latency n

Replace 'n' with the required number of measurements

The latency here is being measured using rdtsc() stamp counter difference and then multiplying with 2.5.

*NOTE: There is One(1) second sleep inside every thread function, so giving higher 'n' values shall increase the time to get the required output. 


















