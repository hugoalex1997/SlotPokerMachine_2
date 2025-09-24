import argparse
import glob
import json
import os
import sys
import subprocess as sp
import _utils as utils


def _parser():
    parser = argparse.ArgumentParser(description="run previously built binary")

    parser.add_argument("-d", "--debug", help="enable debug mode", action="store_true")
    parser.add_argument("forward", help="args to forward to binary", nargs="*")

    return parser.parse_args()

if __name__ == "__main__":

    args = _parser()

    cmd: list[str] = []

    with open(".variables.json") as f:
        variables = json.load(f)

    cmake_binary_dir = variables.get("cmake_binary_dir", "build")
    launcher = os.path.join(cmake_binary_dir, "frontend", "frontend")
    print("Running application with binary: " +  os.path.relpath(launcher))
    
        
    dbg = ("gdb", "-ex", "run", "--args") if args.debug else ()
    process = sp.Popen([*dbg, launcher, *args.forward])
    process.wait()
