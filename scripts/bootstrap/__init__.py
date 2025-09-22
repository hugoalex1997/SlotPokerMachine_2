import sys

import scripts.utils as utils

dependencies_path = "external"


def _install_packages(packages):
    for package in packages:
        utils.run_command("sudo", "apt", "install", "-y", package)

def _install_conan():

    system_dependencies = [
        "pipx",
        "build-essential",
        "pkg-config",
        "libudev-dev",
        "libgl-dev",
        "libx11-dev",
        "libx11-xcb-dev",
        "libfontenc-dev",
        "libice-dev",
        "libsm-dev",
        "libxau-dev",
        "libxaw7-dev",
        "libxcomposite-dev",
        "libxcursor-dev",
        "libxdamage-dev",
        "libxfixes-dev",
        "libxi-dev",
        "libxinerama-dev",
        "libxkbfile-dev",
        "libxmuu-dev",
        "libxrandr-dev",
        "libxrender-dev",
        "libxres-dev",
        "libxss-dev",
        "libxtst-dev",
        "libxv-dev",
        "libxxf86vm-dev",
        "libxcb-glx0-dev",
        "libxcb-render0-dev",
        "libxcb-render-util0-dev",
        "libxcb-xkb-dev",
        "libxcb-icccm4-dev",
        "libxcb-image0-dev",
        "libxcb-keysyms1-dev",
        "libxcb-randr0-dev",
        "libxcb-shape0-dev",
        "libxcb-sync-dev",
        "libxcb-xfixes0-dev",
        "libxcb-xinerama0-dev",
        "libxcb-dri3-dev",
        "uuid-dev",
        "libxcb-cursor-dev",
        "libxcb-dri2-0-dev",
        "libxcb-dri3-dev",
        "libxcb-present-dev",
        "libxcb-composite0-dev",
        "libxcb-ewmh-dev",
        "libxcb-res0-dev",
        "libx11-dev",
        "libx11-xcb-dev",
        "libfontenc-dev",
        "libice-dev",
        "libsm-dev",
        "libxau-dev",
        "libxaw7-dev",
    ]

    conan_dependencies = [
        "cmake",
        ]

    _install_packages(system_dependencies)
    _install_packages(conan_dependencies)
    utils.run_command("pipx", "ensurepath")
    utils.run_command("pipx", "install", "conan")

def install_dependencies():
    _install_conan()

if __name__ == "__main__":

    install_dependencies()
