from setup import before_each, after_each
from runner import run
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

if __name__ == '__main__':
  unittest.main()
