import argparse
import glob
import sys

import _utils as utils


def _parser():
    parser = argparse.ArgumentParser(description="Build helper script")

    parser.add_argument(
        "--check",
        action="store_true",
        help="Check if files are correctly formatted without changing them",
    )

    return parser.parse_args()


def _get_folder_files(folder: str, filter: list[str] = None) -> list[str]:
    files = []
    for extension in filter:
        files.extend(glob.glob(f"{folder}/**/*{extension}", recursive=True))

    return files


def run_clang_format(files: list[str]) -> None:
    for file in files:
        utils.run_command("clang-format", "-i", file)
    print("project files are now formatted!")


def run_clang_format_check(files: list[str]) -> bool:
    for file in files:
        result = utils.run_command("clang-format", "--dry-run", "--Werror", file)

        if result == False:
            print("PLEASE FORMAT THE PROJECT FILES!")
            return result

    print("project files are correctly formatted!")
    return True


if __name__ == "__main__":

    args = _parser()

    files: list[str] = []

    files += _get_folder_files("backend", filter=[".cpp", ".hpp", ".h"])
    files += _get_folder_files("frontend", filter=[".cpp", ".hpp", ".h"])
    files += _get_folder_files("sdk", filter=[".cpp", ".hpp", ".h"])
    files += _get_folder_files("test", filter=[".cpp", ".hpp", ".h"])

    if args.check:
        if not run_clang_format_check(files):
            sys.exit(1)
        sys.exit(0)

    run_clang_format(files)
