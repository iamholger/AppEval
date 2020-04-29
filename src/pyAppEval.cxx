#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>
#include "AppEval.h"


namespace py = pybind11;
using namespace Apprentice;
using namespace Eigen;

PYBIND11_MODULE(appeval, m)
{
  m.doc() = "Apprentice plugin";
  py::class_<AppEval>(m, "AppEval")
    .def(py::init<ArrayXXd,ArrayXXd,ArrayXXi,ArrayXXd,ArrayXXd,ArrayXXd>())
    .def("eval", &AppEval::eval)
    .def("dim", &AppEval::dim)
    .def("__repr__",
        [](const AppEval &a) {
            return "<appeval.AppEval in dimensions>";
        }
        )

;
}

