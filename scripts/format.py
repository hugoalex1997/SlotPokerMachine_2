import argparse
import glob
import os
import sys

import _utils as utils
from _wrappers import BlackFormatterWrapper, ClangFormatWrapper, CmakeFormatterWrapper


def _parser():
    parser = argparse.ArgumentParser(description="Build helper script")

    parser.add_argument(
        "--check",
        action="store_true",
        help="Check if files are correctly formatted",
    )

    return parser.parse_args()


def _get_folder_files(folder: str, filter: list[str] = None) -> list[str]:
    files = []
    for extension in filter:
        files.extend(glob.glob(f"{folder}/**/*{extension}", recursive=True))

    return files


def _format_cpp_files(args):

    files: list[str] = []

    files += _get_folder_files("backend", filter=[".cpp", ".hpp", ".h"])
    files += _get_folder_files("frontend", filter=[".cpp", ".hpp", ".h"])
    files += _get_folder_files("sdk", filter=[".cpp", ".hpp", ".h"])
    files += _get_folder_files("test", filter=[".cpp", ".hpp", ".h"])

    formatter = ClangFormatWrapper()
    formatter.verify_version()

    cmd = args.check and ["--dry-run", "-Werror"] or ["-i"]

    for file in files:
        if not formatter.call(*cmd, file):
            return False

    return True


def _format_cmake_files(args):
    formatter = CmakeFormatterWrapper()
    formatter.verify_version()

    cmake_files = [
        "CMakeLists.txt",
        "sdk/CMakeLists.txt",
        "frontend/CMakeLists.txt",
        "backend/CMakeLists.txt",
        "cmake/ConfigureFiles.cmake",
    ]

    cmd = args.check and ["--check"] or ["-i"]

    for file in cmake_files:
        if not formatter.call(*cmd, file):
            return False

    return True


def _format_python_files(args):
    formatter = BlackFormatterWrapper()
    formatter.verify_version()

    scripts = os.path.join(os.getcwd(), "scripts")
    cmd = [scripts]

    if args.check:
        cmd.append("--check")

    return formatter.call(*cmd)


if __name__ == "__main__":

    args = _parser()

    if not _format_cpp_files(args):
        sys.exit(1)

    if not _format_cmake_files(args):
        sys.exit(1)

    if not _format_python_files(args):
        sys.exit(1)

    print("All files are correctly formatted!")
    sys.exit(0)
