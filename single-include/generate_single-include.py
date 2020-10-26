# Description :
# Combines the entire Charbrary into a single source file (using quom) and separates the result in two files (.h and .cpp)

import os
import sys
import importlib
from importlib import util


# Settings
source_path = '..\source\Charbrary\main.cpp'
quom_output_file = 'charbrary_single-include.hpp' 
charbrary_header_file = 'charbrary.h'
charbrary_implementation_file = 'charbrary.cpp'
header_and_implementation_separation_symbol = 'BEGIN CHARBRARY.CPP'

# Making sure quom is installed and exiting the script if it's not
quom_spec = importlib.util.find_spec('quom')
if quom_spec is None:
	sys.exit('ERROR: Required module "quom" not installed. You can install it using "python -m pip install quom".')

# Running quom (https://github.com/Viatorus/quom) to combine all the charbrary code into one file
os.system('python -m quom "'+source_path+'" -s "~> implementation <~" ' + quom_output_file)

# Two lists; One for the lines that will be written in the .h and the other for the lines in the .cpp
header = []
implementation = []

# Necessary include at the top of charbrary.cpp
implementation.append('#include "'+charbrary_header_file+'"\n')

# Reading the file generated by quom
code = open(quom_output_file, 'r')
lines = code.readlines()
code.close()

# Delete the file generated by quom
os.remove(quom_output_file)

# Separating the declaration from the implementation (.h and .cpp).
target = 'h'
for line in lines:
	if header_and_implementation_separation_symbol in line:
		target = 'cpp'
	if target == 'h':
		header.append(line)
	elif target == 'cpp':
		implementation.append(line) 

# Saving the declaration and implementation into 2 different files (.h and .cpp)
charbrary_header = open(charbrary_header_file, 'w+')
charbrary_header.writelines(header)
charbrary_header.close()

charbrary_impl = open(charbrary_implementation_file, 'w+')
charbrary_impl.writelines(implementation)
charbrary_impl.close()