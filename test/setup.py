import os

def before_each():
  # blank file
  open('blank', 'w').close()

  # with headers and comments
  with open('headers', 'w') as headers:
    headers.write('total,date\n')
    headers.write('00:15:00,1970-01-01T00:00:00\n')
    headers.write('this is a comment\n')

def after_each():
  os.remove('blank')
  os.remove('headers')
