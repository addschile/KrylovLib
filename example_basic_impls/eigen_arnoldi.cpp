#include <cmath>
#include <iostream>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Eigenvalues>

int main(){

    const int m = 1000;

    Eigen::MatrixXd x(m, m);
    for (auto row_ind : Eigen::VectorXi::LinSpaced(m, 0 , m-1)){
        for (auto col_ind : Eigen::VectorXi::LinSpaced(m, 0 , m-1)){
            x(row_ind, col_ind) = row_ind + col_ind;
        }
    }

    auto eigvals = x.eigenvalues();
    std::cout << eigvals[0] <<  "\n\n";
    std::cout << eigvals[m-1] <<  "\n\n";

    /* do lanczos algorithm */

    // size of krylov subspace
    const int nkrylov = 20;

    // krylov subspace vectors
    std::vector<Eigen::Vector<double, m> >  V;
    V.push_back( Eigen::Vector<double, m>{} );
    V[0].setZero();
    for (const auto i : Eigen::VectorXi::LinSpaced(m, 0, m-1)){
        V[0][i] = i;
    }
    V[0].normalize();

    // ritz coefficients
    Eigen::MatrixXd T(nkrylov, nkrylov);

    for (const auto iter : Eigen::VectorXi::LinSpaced(nkrylov-1, 0, nkrylov-2)){

        // apply matrix to previous vector
        V.push_back( x*V[iter] );

        // compute alpha
        auto inner = V[iter+1].dot(V[iter]);
        T(iter, iter) = inner;

        // gram-schmidt orthogonalize
        V[iter+1] -= T(iter, iter)*V[iter];
        if (iter > 0){
             V[iter+1] -= T(iter-1, iter)*V[iter-1];
        }

        // normalize
        double norm = V[iter+1].norm();
        V[iter+1] /= norm;

        // set beta
        T(iter, iter+1) = T(iter+1, iter) = norm;
    }

    auto krylov_eigvals = T.eigenvalues();
    std::cout << krylov_eigvals[0] <<  "\n\n";
    std::cout << krylov_eigvals[nkrylov-1] <<  "\n\n";

}
