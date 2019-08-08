#ifndef PENMAN_MONTEITH_LEAF_TEMPERATURE_H
#define PENMAN_MONTEITH_LEAF_TEMPERATURE_H

#include "../modules.h"

class penman_monteith_leaf_temperature : public SteadyModule {
	public:
		penman_monteith_leaf_temperature(const std::unordered_map<std::string, double>* input_parameters, std::unordered_map<std::string, double>* output_parameters) :
			// Define basic module properties by passing its name to its parent class
			SteadyModule("penman_monteith_leaf_temperature"),
			// Get pointers to input parameters
			slope_water_vapor_ip(get_ip(input_parameters, "slope_water_vapor")),
			psychrometric_parameter_ip(get_ip(input_parameters, "psychrometric_parameter")),
			latent_heat_vaporization_of_water_ip(get_ip(input_parameters, "latent_heat_vaporization_of_water")),
			leaf_boundary_layer_conductance_ip(get_ip(input_parameters, "leaf_boundary_layer_conductance")),
			leaf_stomatal_conductance_ip(get_ip(input_parameters, "leaf_stomatal_conductance")),
			leaf_net_irradiance_ip(get_ip(input_parameters, "leaf_net_irradiance")),
			vapor_density_deficit_ip(get_ip(input_parameters, "vapor_density_deficit")),
			temp_ip(get_ip(input_parameters, "temp")),
			// Get pointers to output parameters
			leaf_temperature_op(get_op(output_parameters, "leaf_temperature"))
		{}
		static std::vector<std::string> get_inputs();
		static std::vector<std::string> get_outputs();
	private:
		// Pointers to input parameters
		const double* slope_water_vapor_ip;
		const double* psychrometric_parameter_ip;
		const double* latent_heat_vaporization_of_water_ip;
		const double* leaf_boundary_layer_conductance_ip;
		const double* leaf_stomatal_conductance_ip;
		const double* leaf_net_irradiance_ip;
		const double* vapor_density_deficit_ip;
		const double* temp_ip;
		// Pointers to output parameters
		double* leaf_temperature_op;
		// Main operation
		void do_operation() const;
};

std::vector<std::string> penman_monteith_leaf_temperature::get_inputs() {
	return {
		"slope_water_vapor",
		"psychrometric_parameter",
		"latent_heat_vaporization_of_water",
		"leaf_boundary_layer_conductance",
		"leaf_stomatal_conductance",
		"leaf_net_irradiance",
		"vapor_density_deficit",
		"temp"
	};
}

std::vector<std::string> penman_monteith_leaf_temperature::get_outputs() {
	return {
		"leaf_temperature"
	};
}

void penman_monteith_leaf_temperature::do_operation() const {
	// Collect input parameters and make calculations
	double slope_water_vapor = *slope_water_vapor_ip;		// kg / m^3 / K
	double psychr_parameter = *psychrometric_parameter_ip;	// kg / m^3 / K
	double LHV = *latent_heat_vaporization_of_water_ip;		// J / kg
	double ga = *leaf_boundary_layer_conductance_ip;		// m / s
	double air_temperature = *temp_ip;						// C
	double leaf_stomatal_conductance = *leaf_stomatal_conductance_ip;
	double leaf_net_irradiance = *leaf_net_irradiance_ip;	// W / m^2. Leaf area basis.
	double vapor_density_deficit = *vapor_density_deficit_ip;
	
	// From Thornley and Johnson 1990. pg 418. equation 14.11e.
	double constexpr volume_of_one_mole_of_air = 24.39e-3;  // m^3 / mol. TODO: This is for about 20 degrees C at 100000 Pa. Change it to use the model state. (1 * R * temperature) / pressure
	
	double const gc = leaf_stomatal_conductance * 1e-3 * volume_of_one_mole_of_air;  // m / s
	
	double const delta_t = (leaf_net_irradiance * (1 / ga + 1 / gc) - LHV * vapor_density_deficit)
		/
		(LHV * (slope_water_vapor + psychr_parameter * (1 + ga / gc)));  // K. It is also degrees C because it's a change in temperature.
	
	double leaf_temperature = air_temperature + delta_t;
	
	// Update the output parameter list
	update(leaf_temperature_op, leaf_temperature);
}

#endif
