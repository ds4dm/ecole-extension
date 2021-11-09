#define FORCE_IMPORT_ARRAY

#include <ecole/scip/model.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <xtensor-python/pytensor.hpp>

#include "{{cookiecutter.cpp_namespace_name}}/some-observation.hpp"


namespace py = pybind11;

PYBIND11_MODULE({{cookiecutter.python_module_name}}, m) {
	m.doc() = R"str(
		{{cookiecutter.project_short_description}}
	)str";

	// NumPy and Ecole need to be imported by the extension module.
	xt::import_numpy();
	auto const ecole = py::module_::import("ecole");

	py::class_<{{cookiecutter.cpp_namespace_name}}::SomeObservationFunction>(m, "SomeObservationFunction")
		.def(py::init<>())
		.def(
			"before_reset",
			&{{cookiecutter.cpp_namespace_name}}::SomeObservationFunction::before_reset,
			py::arg("model"),
			py::call_guard<py::gil_scoped_release>()
		);

}
