import os
import pathlib
import shlex
from typing import List

import skbuild
import ecole

__dir__ = pathlib.Path(__file__).resolve().parent


def get_file_content(file: pathlib.Path) -> str:
    """Extract all lines from a file."""
    with open(file, "r") as f:
        return f.read()


def get_env_cmake_args() -> List[str]:
    """Return the list of extra CMake arguments from the environment.

    When called through conda-build (environment variable `CONDA_BUILD` is set), the `CMAKE_INSTALL_<>`
    are filtered out as they
    """
    cmake_args = shlex.split(os.environ.get("CMAKE_ARGS", ""))
    if "CONDA_BUILD" in os.environ:
        install_re = re.compile(r"-D\s*CMAKE_INSTALL.*")
        cmake_args = [a for a in cmake_args if not install_re.search(a)]
    return cmake_args


skbuild.setup(
    name="{{cookiecutter.python_package_name}}",
    author="{{cookiecutter.full_name}}",
    version="0.1.0",
    description="{{cookiecutter.project_short_description}}",
    long_description=get_file_content(__dir__ / "README.md"),
    license="{{cookiecutter.open_source_license}}",
    packages=["{{cookiecutter.python_package_name}}"],
    package_dir={"": "src"},
    cmake_languages=["CXX"],
    cmake_minimum_required_version="3.15",
    cmake_source_dir="src/{{cookiecutter.python_package_name}}/{{cookiecutter.python_module_name}}",
    # FIXME No way to pass cmake argument to scikit-build through pip (for now)
    # https://github.com/scikit-build/scikit-build/issues/479
    # So we read them from an environment variable
    cmake_args=get_env_cmake_args(),
    zip_safe=False,
    python_requires=">=3.6",
    install_requires=[f"ecole=={ecole.__version__}", "numpy"],
)
