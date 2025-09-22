import glob

import scripts.utils as utils

# TODO(hg): improve file search
cpp_files = glob.glob("backend/**/*.cpp", recursive=True)
hpp_files = glob.glob("backend/**/*.hpp", recursive=True)
h_files = glob.glob("backend/**/*.h", recursive=True)

backend_files = cpp_files + hpp_files + h_files

main = ["frontend/main.cpp"]
cpp_files = glob.glob("frontend/**/*.cpp", recursive=True)
hpp_files = glob.glob("frontend/**/*.hpp", recursive=True)
h_files = glob.glob("frontend/**/*.h", recursive=True)

frontend_files = main + cpp_files + hpp_files + h_files

main = ["test/main.cpp"]
cpp_files = glob.glob("test/**/*.cpp", recursive=True)
hpp_files = glob.glob("test/**/*.hpp", recursive=True)
h_files = glob.glob("test/**/*.h", recursive=True)

test_files = main + cpp_files + hpp_files + h_files

all_files = backend_files + frontend_files + test_files


def run_clang_format():
    for file_path in all_files:
        utils.run_command(
            "clang-format", "-i", file_path
        )  # Space in -i error in the original code...

    print("project files are now formatted!")


def run_clang_format_check():
    for file_path in all_files:
        result = utils.run_command("clang-format", "--dry-run", "-Werror ", file_path)

        if result == False:
            print("PLEASE RUN 'python clang_format.py --format'")
            return result

    print("project files are correctly formatted!")
    return True
