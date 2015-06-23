#!/usr/bin/python

import sys

# It's defined for raising custom errors.
class CustomError(Exception):
    ERROR_WRONG_ARGS = 11           # wrong arguments
    ERROR_PATH_NOT_FOUND = 12       # path not found
    ERROR_BUILD_FAILED = 13         # build failed
    ERROR_RUNNING_CMD = 14          # error when running command
    ERROR_CMD_NOT_FOUND = 15        # command not found
    ERROR_ENV_VAR_NOT_FOUND = 16    # environment variable not found
    ERROR_TOOLS_NOT_FOUND = 17      # depend on tools not found
    ERROR_PARSE_FILE = 18           # error when parse files
    ERROR_WRONG_CONFIG = 19         # configuration is wrong

    def __init__(self, err_args, err_no=1):
        super(CustomError, self).__init__(err_args)
        self.error_no = err_no

    def get_error_no(self):
        return self.error_no


class Logging:
    # TODO maybe the right way to do this is to use something like colorama?
    RED = '\033[31m'
    GREEN = '\033[32m'
    YELLOW = '\033[33m'
    MAGENTA = '\033[35m'
    RESET = '\033[0m'

    @staticmethod
    def _print(s, color=None):
        if color and sys.stdout.isatty() and sys.platform != 'win32':
            print(color + s + Logging.RESET)
        else:
            print(s)

    @staticmethod
    def debug(s):
        Logging._print(s, Logging.MAGENTA)

    @staticmethod
    def info(s):
        Logging._print(s, Logging.GREEN)

    @staticmethod
    def warning(s):
        Logging._print(s, Logging.YELLOW)

    @staticmethod
    def error(s):
        Logging._print(s, Logging.RED)
