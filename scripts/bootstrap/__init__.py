import sys

import scripts.utils as utils

dependencies_path = "external"


def _install_packages(packages):
    for package in packages:
        utils.run_command("sudo", "apt", "install", "-y", package)

def _install_conan():

    conan_dependencies = [
        "cmake",
    ]

    _install_packages(conan_dependencies)

def install_dependencies():
    _install_conan()

if __name__ == "__main__":

    install_dependencies()
