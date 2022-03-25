#!/bin/bash

make debug
valgrind --tool=memcheck --leak-check=yes ./prog