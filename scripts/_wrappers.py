import os
import subprocess as sp
import sys

import _utils as utils


class ClangFormatWrapper:

    def _get_version(self):
        try:
            info = sp.check_output(
                [sys.executable, "-m", "pip", "show", "clang-format"]
            ).decode("utf-8")
            for line in info.split("\n"):
                if not line.startswith("Version: "):
                    continue
                return line.split(" ")[1]
        except:
            return None
        return None

    def _get_binary(self):
        try:
            from clang_format import _get_executable

            return _get_executable("clang-format")
        except ImportError:
            pass

        if not self.verify_version():
            return None

        from clang_format import _get_executable

        return _get_executable("clang-format")

    def verify_version(self):
        current = self._get_version()
        expected_version = "18.1.6"

        if current != expected_version:
            return utils.run_command(
                [
                    sys.executable,
                    "-m",
                    "pip",
                    "install",
                    "clang-format==%s" % expected_version,
                ]
            )

        return True

    def call(self, *args):
        binary = self._get_binary()

        if not binary:
            print("Failed to call clang-format binary")
            return False

        to_print = [os.path.basename(binary), *args]

        return utils.run_command(binary, *args)


class CmakeFormatterWrapper:

    def _get_version(self):
        try:
            info = sp.check_output(
                [sys.executable, "-m", "pip", "show", "cmakelang"]
            ).decode("utf-8")
            for line in info.split("\n"):
                if not line.startswith("Version: "):
                    continue
                return line.split(" ")[1]
        except:
            return None
        return None

    def verify_version(self):
        current = self._get_version()
        expected_version = "0.6.13"

        if current != expected_version:
            return utils.run_command(
                [
                    sys.executable,
                    "-m",
                    "pip",
                    "install",
                    "cmakelang==%s" % expected_version,
                ]
            )

        return True

    def call(self, *args):
        to_print = ["cmake-format", *args]
        return utils.run_command("cmake-format", *args)


class BlackFormatterWrapper:

    def _get_version(self):
        try:
            info = sp.check_output(
                [sys.executable, "-m", "pip", "show", "black"]
            ).decode("utf-8")
            for line in info.split("\n"):
                if not line.startswith("Version: "):
                    continue
                return line.split(" ")[1]
        except:
            return None
        return None

    def verify_version(self):
        current = self._get_version()
        expected_version = "25.1.0"

        if current != expected_version:
            return utils.run_command(
                [
                    sys.executable,
                    "-m",
                    "pip",
                    "install",
                    "black==%s" % expected_version,
                ]
            )

        return True

    def call(self, *args):
        to_print = ["black", *args]
        return utils.run_command("black", *args)
