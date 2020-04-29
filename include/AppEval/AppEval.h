#pragma once
#include <Eigen/Eigen>

using namespace Eigen;

namespace Apprentice
{

  class AppEval
  {
    public:
      AppEval(
          ArrayXXd const & pc,
          ArrayXXd const & qc,
          ArrayXXi const & structure,
          ArrayXXd const & offset,
          ArrayXXd const & xmin,
          ArrayXXd const & scaleterm
          ) : _pc(pc), _qc(qc), _structure(structure), _offset(offset), _xmin(xmin), _scaleterm(scaleterm), _order(_structure.maxCoeff()), _dim(_xmin.rows()) {}

      static AppEval  readHDF(const char* fname);

      ArrayXd eval(VectorXd const & x);

      std::tuple<ArrayXd, ArrayXd> readData(const char* fname);

      double calcChi2(VectorXd const & P, ArrayXd const & Y, ArrayXd const & E);

      int dim() {return _dim;}

    private:
      inline VectorXd _scale(Eigen::ArrayXXd const & xin)
      {
          return _scaleterm * (xin - _xmin) + _offset;
      }
      
      ArrayXXd const _pc;
      ArrayXXd const _qc;
      ArrayXXi const _structure;
      ArrayXXd const _offset;
      ArrayXXd const _xmin;
      ArrayXXd const _scaleterm;
      int const _order;
      int const _dim;
  };
};
