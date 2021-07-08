#include "integrator.h"

state_vector_map integrator::integrate(std::shared_ptr<dynamical_system> sys)
{
    integrate_method_has_been_called = true;

    if (check_adaptive_compatible && !sys->is_adaptive_compatible()) {
        return handle_adaptive_incompatibility(sys);
    } else {
        sys->reset_ncalls();
        return do_integrate(sys);
    }
}
