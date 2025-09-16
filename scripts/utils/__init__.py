import subprocess as sp
import sys

def run_command(*args, **kwargs):
    print("[Run Trace] ", " ".join(list(args)))
    return sp.check_call(list(args), **kwargs) == 0