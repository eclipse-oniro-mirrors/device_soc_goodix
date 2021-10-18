import os
from os import path
import sys


shell_script =  '''arm-none-eabi-size {inputfile}
arm-none-eabi-objcopy -O binary -S {inputfile} {outputfile}'''.format(inputfile=sys.argv[1],outputfile = sys.argv[2])
print(shell_script)
cmd_output = os.system(shell_script)
print(cmd_output)
print("Hello newworld")