#include "SystemSolverFactory.hpp"
#include "boost_solvers.h"
#include "homemade_euler.h"
#include "auto_solver.h"

SystemSolverFactory::system_solver_creator_map SystemSolverFactory::system_solver_creators = {
    { "Gro",                createSystemSolver<auto_solver<preferred_state_type>> },
    { "Gro_euler",          createSystemSolver<homemade_euler_solver<preferred_state_type>> },
    { "Gro_euler_odeint",   createSystemSolver<boost_euler_system_solver<preferred_state_type>> },
    { "Gro_rsnbrk",         createSystemSolver<boost_rsnbrk_system_solver> },
    { "Gro_rk4",            createSystemSolver<boost_rk4_system_solver<preferred_state_type>> },
    { "Gro_rkck54",         createSystemSolver<boost_rkck54_system_solver<preferred_state_type>> },
};

std::unique_ptr<system_solver> SystemSolverFactory::operator()(
    std::string const& system_solver_name,
    double step_size,
    double rel_error_tolerance,
    double abs_error_tolerance,
    int max_steps) const
{
    try {
        return this->system_solver_creators.at(system_solver_name)(step_size, rel_error_tolerance, abs_error_tolerance, max_steps);
    } catch (std::out_of_range) {
        auto message = std::string("\"") + system_solver_name +
                       std::string("\"") +
                       std::string(" was given as a system_solver name, ") +
                       std::string("but no system_solver with that name could be found.\n.");

        throw std::out_of_range(message);
    }
}

std::vector<std::string> SystemSolverFactory::get_solvers()
{
    std::vector<std::string> solver_name_vector;
    for (auto const& x : system_solver_creators) {
        solver_name_vector.push_back(x.first);
    }
    return solver_name_vector;
}

SystemSolverFactory system_solver_factory;
