import glob

import scripts.utils as utils


def get_folder_files(folder: str, filter: list[str] = None) -> list[str]:
    files = []
    for extension in filter:
        files.extend(glob.glob(f"{folder}/**/*{extension}", recursive=True))

    return files


all_files = []

all_files += get_folder_files("backend", filter=[".cpp", ".hpp", ".h"])
all_files += get_folder_files("frontend", filter=[".cpp", ".hpp", ".h"])
all_files += get_folder_files("sdk", filter=[".cpp", ".hpp", ".h"])
all_files += get_folder_files("test", filter=[".cpp", ".hpp", ".h"])


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
