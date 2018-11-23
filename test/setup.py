import os

def before_each():
  open('blank', 'w').close()

def after_each():
  os.remove('blank')

