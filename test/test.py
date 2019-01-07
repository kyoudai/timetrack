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

    self.assertEqual(stdout, '\n  00:00:00\n', 'use default')

  def test_use_default_write(self):
    (stdout, result) = run(['blank', '15:00'])

    self.assertEqual(stdout, '\n  00:00:00\n +00:15:00\n  --------\n  00:15:00\n\nWrote to \'blank\'.\n', 'use default')
    self.assertEqual(result[:25], '00:15:00,00:15:00,900,900', 'write correctly')

  def test_difference_write(self):
    (stdout, result) = run(['single', '2:30', '5:00', '-1:25'])
    (first, second, ignored) = result.split('\n')

    self.assertEqual(second[:26], '00:21:05,00:06:05,1265,365', 'write second entry correctly')

  def test_difference_write_zero_sum(self):
    (stdout, result) = run(['single', '2:30', '-2:30'])
    (first, second, ignored) = result.split('\n')

    self.assertEqual(second[:23], '00:15:00,00:00:00,900,0', 'write second entry correctly')

  def test_ignore_invalid(self):
    (stdout, result) = run(['headers'])

    self.assertEqual(stdout, '\n  00:15:00\n', 'read correctly')

  def test_ignore_invalid_not_negative(self):
    (stdout, result) = run(['negative'])

    self.assertEqual(stdout, '\n -00:27:00\n', 'read correctly')

  def test_ignore_invalid_write(self):
    (stdout, result) = run(['headers', '87'])
    lines = result.split('\n')

    self.assertEqual(stdout, '\n  00:15:00\n +00:01:27\n  --------\n  00:16:27\n\nWrote to \'headers\'.\n', 'read correctly')
    self.assertEqual(lines[0], 'total,date', 'first line')
    self.assertEqual(lines[1], '00:15:00,00:15:00,900,900,1970-01-01T00:00:00', 'second line')
    self.assertEqual(lines[2], 'this is a comment', 'third line')
    self.assertEqual(lines[3][:24], '00:16:27,00:01:27,987,87', 'write correctly')

  def test_verbose(self):
    # test all combinations
    # 000
    (stdout, result) = run(['blank', '-v'])
    self.assertEqual(stdout, 'The current total is zero.\n')

    # 100
    (stdout, result) = run(['blank', '2:00:00'])
    (stdout, result) = run(['blank', '-v'])
    self.assertEqual(stdout, 'The current total is exactly 2 hours.\n')

    # 010
    (stdout, result) = run(['blank', '-1:12:00'])
    (stdout, result) = run(['blank', '-v'])
    self.assertEqual(stdout, 'The current total is exactly 48 minutes.\n')

    # 110
    (stdout, result) = run(['blank', '1:00:00'])
    (stdout, result) = run(['blank', '-v'])
    self.assertEqual(stdout, 'The current total is 1 hour and 48 minutes.\n')

    # 001
    (stdout, result) = run(['blank', '-1:47:33'])
    (stdout, result) = run(['blank', '-v'])
    self.assertEqual(stdout, 'The current total is 27 seconds.\n')

    # 001
    (stdout, result) = run(['blank', '8:00:00'])
    (stdout, result) = run(['blank', '-v'])
    self.assertEqual(stdout, 'The current total is 8 hours and 27 seconds.\n')

    # 011
    (stdout, result) = run(['blank', '-7:50:00'])
    (stdout, result) = run(['blank', '-v'])
    self.assertEqual(stdout, 'The current total is 10 minutes and 27 seconds.\n')

    # 011
    (stdout, result) = run(['blank', '3:00:00'])
    (stdout, result) = run(['blank', '-v'])
    self.assertEqual(stdout, 'The current total is 3 hours, 10 minutes, and 27 seconds.\n')

  def test_verbose_negative(self):
    (stdout, result) = run(['negative', '-v'])

    self.assertEqual(stdout, 'The current total is exactly negative 27 minutes.\n')

  def test_app_version(self):
    (stdout, result) = run(['--version', 'ignored', 'arguments'])

    self.assertEqual(stdout, f'timetrack {app_version()}\n')

  def test_app_help(self):
    (noArg, result) = run()
    (arg, result) = run(['--help', 'ignored', 'arguments'])

    usageText = f'Usage: {app_name()} [options] file [options] [time1 time2 ...]\nOptions:\n  --version         Print program version and exit.\n  --help            Print usage information and exit.\n  -v                Verbose; print the current total in a human friendly way.\n                    It\'s only active when reading.\nExample:\n  {app_name()} log.txt 1:27 -11:01 +2:15:23 127\n'

    self.assertEqual(noArg, usageText)
    self.assertEqual(arg, usageText)

if __name__ == '__main__':
  unittest.main()
