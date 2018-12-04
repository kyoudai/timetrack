import os

def before_each():
  # blank file
  open('blank', 'w').close()

  # with headers and comments
  with open('headers', 'w') as headers:
    headers.write('total,date\n')
    headers.write('00:15:00,00:15:00,1970-01-01T00:00:00\n')
    headers.write('this is a comment\n')

  # with one entry
  with open('single', 'w') as headers:
    headers.write('00:15:00,00:15:00,1970-01-01T00:00:00\n')

  # with one entry (negative)
  with open('negative', 'w') as headers:
    headers.write('-00:27:00,-00:27:00,1970-01-01T00:00:00\n')

def after_each():
  os.remove('blank')
  os.remove('headers')
  os.remove('single')
  os.remove('negative')
