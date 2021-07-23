# Install script for directory: /home/sunjeet/zephyrproject/zephyr

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "TRUE")
endif()

# Set default install directory permissions.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/home/sunjeet/zephyrsdk/i586-zephyr-elf/bin/i586-zephyr-elf-objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/zephyr/arch/cmake_install.cmake")
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/zephyr/lib/cmake_install.cmake")
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/zephyr/soc/x86/intel_quark/quark_x1000/cmake_install.cmake")
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/zephyr/boards/cmake_install.cmake")
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/zephyr/ext/cmake_install.cmake")
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/zephyr/subsys/cmake_install.cmake")
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/zephyr/drivers/cmake_install.cmake")
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/tinycbor/cmake_install.cmake")
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/zephyr/kernel/cmake_install.cmake")
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/zephyr/cmake/flash/cmake_install.cmake")
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/zephyr/cmake/usage/cmake_install.cmake")
  include("/home/sunjeet/zephyrproject/zephyr/samples/HCSR_app/build/zephyr/cmake/reports/cmake_install.cmake")

endif()

