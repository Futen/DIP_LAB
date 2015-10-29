#! /usr/bin/env python

import subprocess
import glob

s = 'g++ -Wall -O3 lab2.cpp main.cpp -lm -lopencv_core -lopencv_highgui'
subprocess.call(s,shell=True)
