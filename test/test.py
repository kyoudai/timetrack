from setup import before_each, after_each
from runner import run, app_name
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

  def test_ignore_invalid(self):
    (stdout, result) = run(['headers'])

    self.assertEqual(stdout, '\n  00:15:00\n', 'read correctly')

  def test_ignore_invalid_write(self):
    (stdout, result) = run(['headers', '87'])
    lines = result.split('\n')

    self.assertEqual(stdout, '\n  00:15:00\n +00:01:27\n  --------\n  00:16:27\n\nWrote to \'headers\'.\n', 'read correctly')
    self.assertEqual(lines[0], 'total,date', 'first line')
    self.assertEqual(lines[1], '00:15:00,1970-01-01T00:00:00', 'second line')
    self.assertEqual(lines[2], 'this is a comment', 'third line')
    self.assertEqual(lines[3][:8], '00:16:27', 'write correctly')

  def test_app_basename(self):
    (stdout, result) = run()

    self.assertEqual(stdout, f'Usage: {app_name()} file [time1 time2 ...]\n')

if __name__ == '__main__':
  unittest.main()
