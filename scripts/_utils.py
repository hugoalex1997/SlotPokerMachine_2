import subprocess as sp
import sys

def run_command(*args, **kwargs):
    print("[Run Trace] ", " ".join(list(args)))
    try:
        return sp.check_call(list(args), **kwargs) == 0
    except sp.CalledProcessError:
        # Command failed, return False instead of raising
        return False