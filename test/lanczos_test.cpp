#include "../KrylovLib/lanczos.hpp"
#include <Eigen/Core>

int main() {

    const int m = 100;
    using vectortype = Eigen::Vector<double, m>;

    KrylovLib::Lanczos<vectortype> lanczos_solver{};

}
