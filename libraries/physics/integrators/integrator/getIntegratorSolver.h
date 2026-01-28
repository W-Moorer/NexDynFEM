#ifndef NEXDYNFEM_GETINTEGRATORSOLVER_H
#define NEXDYNFEM_GETINTEGRATORSOLVER_H

namespace nexdynfem
{
// returns the string corresponding to the selected integrator solver
// "solver" must be pre-allocated
// result: PARDISO, SPOOLES or PCG
void GetIntegratorSolver(char * solver);

}//namespace nexdynfem
#endif

