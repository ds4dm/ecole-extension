#pragma once

#include <optional>

#include <xtensor/xtensor.hpp>
#include <ecole/observation/abstract.hpp>
#include <ecole/scip/model.hpp>


namespace {{cookiecutter.cpp_namespace_name}} {

/** Observation object extracted by the observation function */
struct SomeObservation {
	using value_type = double;

	xt::xtensor<value_type, 1> features;
};


class SomeObservationFunction : public ecole::observation::ObservationFunction<std::optional<SomeObservation>> {
public:

	void before_reset(ecole::scip::Model& model) override;

	std::optional<SomeObservation> extract(ecole::scip::Model& model, bool done) override;

private:
	int some_data = 0;
};

}
