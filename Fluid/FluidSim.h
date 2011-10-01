#include "stdafx.h"
#include "FluidGrid.h"

namespace Fluid
{
    template <class T>
    void advectForwardEuler(Cells<T> & data, Cells<T> & prevData, double timestep);
}