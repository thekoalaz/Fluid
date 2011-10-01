#include "FluidGrid.h"

using namespace Fluid;

template <class T>
void advectForwardEuler(Cells<T> & data, Cells<arma::vec> & velocity, double timestep)
{
    for(int i=0; i<data->_n_x; i++)
    {
    for(int j=0; j<data->_n_y; j++)
    {
    for(int k=0; j<data->_n_z; k++)
    {
        Coordinate coord = Coordinate(i,j,k);
        data(advect
    }
    }
    }
}