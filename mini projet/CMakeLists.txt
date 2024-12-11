cmake_minimum_required(VERSION 3.25)
project(mini_projet)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(mini_projet
        main.cpp
        PinAsInput.h
        Serial.h
        Serial_Mode_Name.h
        "stm32_wrapper_gpio copy.c"
        "stm32_wrapper_gpio copy.h"
        stm32_wrapper_Serial.c
        stm32_wrapper_Serial.h
        stm32f10x_conf.h
        stm32f10x_it.h
        stm32map.h)
