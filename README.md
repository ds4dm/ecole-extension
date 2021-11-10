# Ecole Extension Template
This is a template repository for using Ecole C++ library from Python.
You can easily define a new reward function, observation function, or environment in C++
without having editing Ecole source code.

> :warning: **This is project is in beta**

> :warning: **The Ecole C++ library is unstable**: API changes can be introduced in any minor version.

> :warning: **This project requires ecole>=0.8 wich is not released yet.**
> You can install Ecole development version with
> ```bash
> conda install -c conda-forge/label/ecole_dev ecole
> ```

## Usage
### Create a new extension
Install [CookieCutter](https://cookiecutter.readthedocs.io) and create your new project
```bash
python -m pip install cookiecutter
python -m cookiecutter https://github.com/ds4dm/ecole-extension
```

CookieCutter will prompt you for information such as the name of your project to replace
it in the template.
CookieCutter is no longer required from now on.

Optionally, you can initialize the newly created folder as a git repository with
[`git init`](https://git-scm.com/docs/git-init).

### Installing your extension
#### In a Conda environment
If you wish to get the dependencies (including Ecole and SCIP) through `conda`, then first install
them with
```bash
conda env create --name my-ecole-extension --file environment.yaml
```
Then install your extension with
```bash
python -m pip install --no-deps --no-build-isolation .
```

#### Directly with Pip
You can install your extension directly with `pip`, it will fetch Ecole and all dependencies with
```bash
python -m pip install .
```
However, installing Ecole through `pip` may not be straightforward, as it curretly need to access
a compiler and an existing installation of SCIP.
For an interative installation, install all dependencies and then install your extension with
```bash
python -m pip install --no-deps --no-build-isolation .
```
**See Also**: [Ecole installation instructions](https://doc.ecole.ai/py/en/stable/installation.html)

### Editing the extension
Eventually, you will want to make your own changes.
There is no simple explanation of all the modifications that you will need to make, as it is mostly
case dependent.
Be sure to check the following files in your extension:
 - `CMakeLists.txt` contains the list of C++ files to compile. If you add or rename C++ files,
   you will need to edit the list there.
 - `bindings.cpp` contains the [PyBind11](https://pybind11.readthedocs.io/) code to interface
   C++ code to Python.
   It contains the name of classes, functions, and methods.
   If you change or add any of them, be sure to add the changes there.
 - Python submodule such as `__init__.py` may import the code from the C++ extension to have nicer
   module names.
   If your code is not imported how you like, check these files as well.
 - `setup.py` contains the path the extension submodules.
   Unless you restructure the whole project, you should not need to make any changes there.
