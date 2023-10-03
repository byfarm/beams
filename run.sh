#!/bin/bash

./beams
python3 analyze_data.py
python3 display_data.py
wslview plot.png
