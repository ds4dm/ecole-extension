#define FORCE_IMPORT_ARRAY

#include <ecole/scip/model.hpp>
#include <ecole/python/auto-class.hpp>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <xtensor-python/pytensor.hpp>

#include "{{cookiecutter.cpp_namespace_name}}/some-observation.hpp"


namespace py = pybind11;
using namespace {{cookiecutter.cpp_namespace_name}};

// Here we create a new python module {{cookiecutter.python_module_name}} associated with a variable `m`.
PYBIND11_MODULE({{cookiecutter.python_module_name}}, m) {
	// Module docstring.
	m.doc() = R"str(
		{{cookiecutter.project_short_description}}
	)str";

	// NumPy and Ecole need to be imported by the extension module.
	xt::import_numpy();
	auto const ecole = py::module_::import("ecole");

	// Here we start binding a class similar to 'py::class_`.
	// We use `ecole::python::auto_class` our helper around `py::class_`
	ecole::python::auto_class<SomeObservation>(m, "SomeObservation")
		// Enable copy.deepcopy methods.
		.def_auto_copy()
		// Enable pickle. Attributes used for picking need to be listed here.
		.def_auto_pickle(std::array{"features"})
		// Binding a property on an xtensor attribute needs our special function.
		.def_readwrite_xtensor("features", &SomeObservation::features, "A vector of data.");

	// Binding another class.
	ecole::python::auto_class<SomeObservationFunction>(m, "SomeObservationFunction")
		// Enable copy.deepcopy methods.
		.def_auto_copy()
		// We bind a constructor with no arguments.
		.def(py::init<>())
		// We bind some methods
		.def(
			// Name of the method in Python.
			"before_reset",
			// Pointer to the C++ method to bind.
			&SomeObservationFunction::before_reset,
			// We can have named argumets (even default values).
			py::arg("model"),
			// We release the GIL during this function call.
			py::call_guard<py::gil_scoped_release>())
		.def(
			"extract",
			&SomeObservationFunction::extract,
			py::arg("model"), py::arg("done"),
			py::call_guard<py::gil_scoped_release>()
		);

	// Keep on binding classes, functions... Check the Pybind11 doc for usage.
}
