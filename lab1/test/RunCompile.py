#! /usr/bin/env python

import subprocess
import glob

s = 'g++ -W  -I/usr/include/opencv main.cpp test.cpp  -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_ml -lopencv_video -lopencv_features2d -lopencv_calib3d -lopencv_objdetect -lopencv_contrib -lopencv_legacy -lopencv_flann'
subprocess.call(s,shell=True)
