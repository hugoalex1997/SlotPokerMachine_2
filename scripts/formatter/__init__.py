import glob
import sys

import scripts.utils as utils

cpp_files = glob.glob("src/*.cpp")
hpp_files = glob.glob("src/*.hpp")
all_files = cpp_files + hpp_files
    
def run_clang_format():
    for file_path in all_files:
        utils.run_command("clang-format", "-i", file_path) #Space in -i error in the original code...

    print("project files are now formatted!")


def run_clang_format_check():
    for file_path in all_files:
        result = utils.run_command("clang-format", "--dry-run", "-Werror ", file_path)

        if result == False:
            print("PLEASE RUN 'python clang_format.py --format'")
            return result

    print("project files are correctly formatted!")
    return True
