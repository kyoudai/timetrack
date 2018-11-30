import subprocess
import os
import sys

def app_name():
  if (sys.platform == 'windows'):
    return 'timetrack.exe'

  return 'timetrack'

def app_version():
  f = open('../VERSION', 'r')
  version = f.read()
  f.close()

  return version

def run(args=[]):
  stdout = subprocess.check_output([os.path.abspath(f'../{app_name()}')] + args).decode('UTF-8').replace('\r', '')
  result = None

  if (len(args) > 0 and args[0][:1] != '-'):
    f = open(args[0], 'r')
    result = f.read()
    f.close()

  return (stdout, result)
