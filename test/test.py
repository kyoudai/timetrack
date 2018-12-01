from setup import before_each, after_each
from runner import run, app_name, app_version
import unittest

class TestTimeTrack(unittest.TestCase):
  def setUp(self):
    before_each()

  def tearDown(self):
    after_each()

  def test_use_default(self):
    (stdout, result) = run(['blank'])

    self.assertEqual(stdout, 'No entry found, using 00:00:00\n\n  00:00:00\n', 'use default')

  def test_use_default_write(self):
    (stdout, result) = run(['blank', '15:00'])

    self.assertEqual(stdout, 'No entry found, using 00:00:00\n\n  00:00:00\n +00:15:00\n  --------\n  00:15:00\n\nWrote to \'blank\'.\n', 'use default')
    self.assertEqual(result[:8], '00:15:00', 'write correctly')

  def test_difference_write(self):
    (stdout, result) = run(['single', '2:30', '5:00', '-1:25'])
    (first, second, ignored) = result.split('\n')

    self.assertEqual(second[:8], '00:21:05', 'write second total correctly')
    self.assertEqual(second[9:17], '00:06:05', 'write second change correctly')

  def test_difference_write_zero_sum(self):
    (stdout, result) = run(['single', '2:30', '-2:30'])
    (first, second, ignored) = result.split('\n')

    self.assertEqual(second[:8], '00:15:00', 'write second total correctly')
    self.assertEqual(second[9:17], '00:00:00', 'write second change correctly')

  def test_ignore_invalid(self):
    (stdout, result) = run(['headers'])

    self.assertEqual(stdout, '\n  00:15:00\n', 'read correctly')

  def test_ignore_invalid_write(self):
    (stdout, result) = run(['headers', '87'])
    lines = result.split('\n')

    self.assertEqual(stdout, '\n  00:15:00\n +00:01:27\n  --------\n  00:16:27\n\nWrote to \'headers\'.\n', 'read correctly')
    self.assertEqual(lines[0], 'total,date', 'first line')
    self.assertEqual(lines[1], '00:15:00,00:15:00,1970-01-01T00:00:00', 'second line')
    self.assertEqual(lines[2], 'this is a comment', 'third line')
    self.assertEqual(lines[3][:8], '00:16:27', 'write correctly')

  def test_app_version(self):
    (stdout, result) = run(['--version', 'ignored', 'arguments'])

    self.assertEqual(stdout, f'timetrack {app_version()}\nCopyright (C) 2018 Andrei Nemes\nThis is free software; see the source for copying conditions.  There is NO\nWARRANTY; not even for MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n')

  def test_app_help(self):
    (noArg, result) = run()
    (arg, result) = run(['--help', 'ignored', 'arguments'])

    usageText = f'Usage: {app_name()} [options] file [time1 time2 ...]\nOptions:\n  --version         Display program version and exit.\n  --help            Display usage information and exit.\nExample:\n  {app_name()} log.txt 1:27 -11:01 +2:15:23 127\n'

    self.assertEqual(noArg, usageText)
    self.assertEqual(arg, usageText)

if __name__ == '__main__':
  unittest.main()
