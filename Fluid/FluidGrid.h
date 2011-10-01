#include "stdafx.h"
#include <unordered_map>

namespace Fluid
{

typedef struct Coordinate {
    int x, y, z;
} Coordinate;

template <class T>
class Cells;

class MACGrid
{
public:
    MACGrid(int n_x, int n_y, int n_z) : _n_x(n_x),_n_y(n_y), _n_z(n_z)
    { init(); }

    MACGrid(std::string infile, std::string outfile) : _infile(infile), _outfile(outfile)
    { init(_infile, _outfile); }
    
    
private:
    void init();
    void init(std::string _infile, std::string _outfile);
    int _n_x;
    int _n_y;
    int _n_z;
    std::string _infile;
    std::string _outfile;

    Cells<double> * _pressure;
    Cells<arma::vec> * _velocity;
    Cells<arma::vec> * _velocityPos;
    Cells<arma::vec> * _prevVelocity;
};


template <class T>
class Cells
{
public:
    Cells(int n_x, int n_y, int n_z) : _n_x(n_x), _n_y(n_y), _n_z(n_z) { init(); };


private:
    void init();

    std::unordered_map<Coordinate, T> _data;

    double _time;
    int _n_x;
    int _n_y;
    int _n_z;
};

}