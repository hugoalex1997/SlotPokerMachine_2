import argparse
import multiprocessing
import os
import subprocess
import sys
import _utils as utils

_nproc = multiprocessing.cpu_count()


def _parser():
    parser = argparse.ArgumentParser(description="Build helper script")

    parser.add_argument("-c", "--clean", action="store_true", help="clean build")
    parser.add_argument(
        "-b",
        "--build",
        choices=["debug", "release"],
        default="debug",
        help="build type [default: debug]",
    )
    parser.add_argument(
        "--no-bootstrap", help="do not bootstrap conan", action="store_false"
    )

    return parser.parse_args()


def _get_build_type(build):
    build_type_map = {
        "debug": "Debug",
        "release": "Release",
    }
    return build_type_map.get(build, "Debug")


def _run_conan(data):
    if utils.run_command("conan", "profile", "show") == 0:
        utils.run_command("conan", "profile", "detect")

    opts = (
        "--build",
        "missing",
        "--settings",
        "compiler.libcxx=libstdc++11",
        "--settings",
        "build_type=%s" % _get_build_type(data.build),
        "--output-folder",
        data.output,
    )

    if not utils.run_command("conan", "install", os.getcwd(), *opts):
        return False

    return True


def _link_compile_commands(data):
    # link compile_commands.json to root
    compile_commands = os.path.join(data.output, "compile_commands.json")

    if os.path.islink("compile_commands.json"):
        os.remove("compile_commands.json")

    os.symlink(compile_commands, "compile_commands.json")
    print("Symlinked compile_commands.json to %s", os.getcwd())


# ====================== Main ======================#

if __name__ == "__main__":
    args = _parser()

    args.output = "build/cmake-" + args.build

    if args.clean:
        print("Starting clean build...")
        utils.run_command("rm", "-rf", args.output)

    utils.run_command("mkdir", "-p", args.output)

    _link_compile_commands(args)

    if args.no_bootstrap:
        _run_conan(args)

    utils.run_command(
        "cmake",
        "--preset",
        "conan-" + args.build,
        "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
    )

    build_result = utils.run_command("cmake", "--build", args.output)

    if build_result == False:
        print("Build failed!")
        sys.exit(1)

    print(f"Build success! ")
    sys.exit(0)
