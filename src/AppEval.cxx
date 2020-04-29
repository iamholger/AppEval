#include "AppEval.h"
#include <highfive/H5Easy.hpp>



using namespace Apprentice;

AppEval AppEval::readHDF(const char* fname)
{
    H5Easy::File file(fname, H5Easy::File::ReadOnly);
    auto PC        = H5Easy::load<MatrixXd>(file, "pcoeff"   );
    auto QC        = H5Easy::load<MatrixXd>(file, "qcoeff"   );
    auto structure = H5Easy::load<MatrixXi>(file, "structure");
    auto offset    = H5Easy::load<MatrixXd>(file, "a"        );
    auto xmin      = H5Easy::load<MatrixXd>(file, "xmin"     );
    auto scaleterm = H5Easy::load<MatrixXd>(file, "scaleterm");
    return {PC, QC, structure, offset, xmin, scaleterm};
}

std::tuple<ArrayXd, ArrayXd> AppEval::readData(const char* fname)
{
    H5Easy::File file(fname, H5Easy::File::ReadOnly);
    auto Y        = H5Easy::load<MatrixXd>(file, "values"   );
    auto E        = H5Easy::load<MatrixXd>(file, "errors"   );
    return std::make_tuple(Y,E);
}


double AppEval::calcChi2(VectorXd const & P, ArrayXd const & Y, ArrayXd const & E)
{
  return ((this->eval(P) - Y).square()*E).sum();
}

ArrayXd AppEval::eval(VectorXd const & x)
{
    ArrayXXd xs = _scale(x);
    ArrayXXd powerCache(_dim, _order+1);
    powerCache.col(0) = Eigen::ArrayXd::Ones(_dim);

    ArrayXXd recurrence(_structure.rows(), _structure.cols());

    int const ncols = _structure.cols();
    int const nrows = _structure.rows();

    // Caching of all used powers of scaled point
    powerCache.col(1) = xs;
    for (unsigned int i=2;i<_order+1;++i) powerCache.col(i) = xs.pow(i); // FIXME data type conversion here
        
    // Reccurence relation
    for (unsigned int c=0;c<ncols; ++c)
    {
        for (unsigned int r=0;r<nrows; ++r)
        {
            recurrence(r,c) = powerCache(c, _structure(r,c));
        }
    }
    ArrayXd const rec = recurrence.transpose().colwise().prod();
    auto temp = (_pc.rowwise() * rec.transpose());

    ArrayXd ret2  =  ArrayXd(temp.rows());

#pragma omp parallel for
    for (int i=0;i<temp.rows();++i)
    {
      ret2[i]  = temp.row(i).sum();
    }

    return ret2;
}
