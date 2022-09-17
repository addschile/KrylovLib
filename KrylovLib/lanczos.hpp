#pragma once

#include <boost/range/irange.hpp>
#include "krylovbase.hpp"
#include <iostream>

namespace KrylovLib {

template<typename VectorType>
class Lanczos : protected KrylovBase<Lanczos<VectorType>, VectorType>
{
    public:
        Lanczos();
        ~Lanczos();
    private:
        void build_subspace_impl();
};

template<typename VectorType>
Lanczos<VectorType>::Lanczos() : KrylovBase<Lanczos<VectorType>, VectorType>(){};

template<typename VectorType>
Lanczos<VectorType>::~Lanczos(){}

template<typename VectorType>
void Lanczos<VectorType>::build_subspace_impl(){
    for (const auto i : boost::irange(0, this->max_nvectors)){
        this->krylov_vectors.push_back( VectorType{} );
    }
}

}
