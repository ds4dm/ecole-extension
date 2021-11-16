#pragma once

#include <optional>

#include <xtensor/xtensor.hpp>
#include <ecole/scip/model.hpp>


namespace {{cookiecutter.cpp_namespace_name}} {

/** Observation object extracted by the observation function */
struct SomeObservation {
	using value_type = double;

	xt::xtensor<value_type, 1> features;
};


class SomeObservationFunction {
public:

	auto before_reset(ecole::scip::Model& model) -> void;
	auto extract(ecole::scip::Model& model, bool done) -> std::optional<SomeObservation>;

private:
	double some_data = 0;
};

}
