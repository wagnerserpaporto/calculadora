cmake_minimum_required(VERSION 3.20)
project(calculadora C)

add_executable(calculadora main.c
        convertein_posfixa.c
        convertepos_infixa.c
        expressao.c
)
