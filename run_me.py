import sys
import os

from click import command

sys.path.append("scripts")
import bootstrap
import formatter
import utils


def help_print():
    print("-r, --run                   run binary")
    print("-s, --setup                 install project dependencies")
    print("-b, --build                 build project")
    print("-f, --full                  run a clean build")
    print("--check                     code formatter check")
    print("--format                    code formatter")


def run_binary():
    command = "./build/frontend/frontend"
    utils.run_command(command)


def build_project(build_type="Debug"):
    if not os.path.exists("build"):
        full_build_project(build_type)
        return

    result = utils.run_command("cmake", "--build", "build", "--config", build_type)

    if result == False:
        print("Build failed!")
        sys.exit(1)

    print("Build success!")


def full_build_project(build_type="Debug"):
    compiler = "compiler.libcxx=libstdc++11"

    utils.run_command(
        "conan",
        "install",
        ".",
        "--output-folder=build",
        "--build=missing",
        "--settings",
        compiler,
        "--settings",
        f"build_type={build_type}",
    )

    utils.run_command(
        "cmake",
        "--preset",
        "conan-" + build_type.lower(),
        "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
    )
    result = utils.run_command("cmake", "--build", "build", "--config", build_type)

    if result == False:
        print("Build failed!")
        sys.exit(1)

    print(f"Build success! ({build_type})")


if __name__ == "__main__":

    help = ["-h", "--help"]
    run = ["-r", "--run"]
    setup = ["-s", "--setup"]
    build = ["-b", "--build"]
    full = ["-f", "--full"]
    check = ["--check"]
    format = ["--format"]
    release = ["--release"]
    options = help + run + setup + build + full + check + format + release

    if len(sys.argv) == 1:
        help_print()
        sys.exit(0)

    mode = sys.argv[1]

    if mode in help:
        help_print()
        sys.exit(0)

    if mode in setup:
        bootstrap.install_dependencies()
        sys.exit(0)

    if mode in full:
        build_type = "Release" if ("--release") in sys.argv else "Debug"
        full_build_project(build_type)
        sys.exit(0)

    if mode in build:
        build_type = "Release" if ("--release") in sys.argv else "Debug"
        build_project(build_type)
        sys.exit(0)

    if mode in run:
        run_binary()
        sys.exit(0)

    if mode in check:
        formatter.run_clang_format_check()
        sys.exit(0)

    if mode in format:
        formatter.run_clang_format()
        sys.exit(0)

    help_print()
    sys.exit(0)
