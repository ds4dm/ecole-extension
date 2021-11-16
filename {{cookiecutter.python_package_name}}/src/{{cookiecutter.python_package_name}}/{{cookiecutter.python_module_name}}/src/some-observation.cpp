#include "{{cookiecutter.cpp_namespace_name}}/some-observation.hpp"


namespace {{cookiecutter.cpp_namespace_name}} {

auto SomeObservationFunction::before_reset(ecole::scip::Model& model) -> void {
	// Reinitialize the inner data of the observation function on new episodes.
	this->some_data = 0.;
}

auto SomeObservationFunction::extract(ecole::scip::Model& model, bool done) -> std::optional<SomeObservation> {
	// Return some dummy data
	if(this->some_data++ == 0){
		// This will be a None in Python, because why not.
		return std::nullopt;
	} else {
		// This will be a vector of size 7 filled with zeros.
		return {SomeObservation{decltype(SomeObservation::features)::from_shape({7})}};
	}
}

}
