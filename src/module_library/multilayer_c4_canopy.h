#ifndef MULTILAYER_C4_CANOPY_H
#define MULTILAYER_C4_CANOPY_H

#include "multilayer_canopy_photosynthesis.h"
#include "multilayer_canopy_properties.h"
#include "c4_leaf_photosynthesis.h"
#include "../state_map.h"

/**
 * @class ten_layer_c4_canopy
 *
 * @brief A child class of multilayer_canopy_photosynthesis where:
 *  - The canopy module is set to the `ten_layer_canopy_properties` module
 *  - The leaf module is set to the `c4_leaf_photosynthesis` module
 *  - The number of layers is set to 10
 * Instances of this class can be created using the module factory.
 */
class ten_layer_c4_canopy : public multilayer_canopy_photosynthesis<ten_layer_canopy_properties, c4_leaf_photosynthesis>
{
   public:
    ten_layer_c4_canopy(
        state_map const& input_quantities,
        state_map* output_quantities)
        : multilayer_canopy_photosynthesis<ten_layer_canopy_properties, c4_leaf_photosynthesis>(
              "ten_layer_c4_canopy",
              ten_layer_c4_canopy::nlayers,
              input_quantities,
              output_quantities)  // Create the base class with the appropriate number of layers
    {
    }
    static string_vector get_inputs();
    static string_vector get_outputs();

   private:
    // Number of layers
    static const int nlayers;
    // Main operation
    void do_operation() const;
};

const int ten_layer_c4_canopy::nlayers = 10;  // Set the number of layers

string_vector ten_layer_c4_canopy::get_inputs()
{
    // Just call the parent class's input function with the appropriate number of layers
    return multilayer_canopy_photosynthesis<ten_layer_canopy_properties, c4_leaf_photosynthesis>::generate_inputs(ten_layer_c4_canopy::nlayers);
}

string_vector ten_layer_c4_canopy::get_outputs()
{
    // Just call the parent class's output function with the appropriate number of layers
    return multilayer_canopy_photosynthesis<ten_layer_canopy_properties, c4_leaf_photosynthesis>::generate_outputs(ten_layer_c4_canopy::nlayers);
}

void ten_layer_c4_canopy::do_operation() const
{
    // Just call the parent class's run operation
    multilayer_canopy_photosynthesis<ten_layer_canopy_properties, c4_leaf_photosynthesis>::run();
}

#endif
