#pragma once

#include <vector>

namespace KrylovLib {

template<class KrylovImpl, class VectorType>
class KrylovBase {

    protected:
        int max_nvectors;
        std::vector<VectorType> krylov_vectors;

    protected:
        virtual void build_subspace_impl(){};

    public:
        KrylovBase();
        ~KrylovBase();
        void build_subspace();
};


template<typename KrylovImpl, typename VectorType>
KrylovBase<KrylovImpl, VectorType>::KrylovBase(){}

template<typename KrylovImpl, typename VectorType>
KrylovBase<KrylovImpl, VectorType>::~KrylovBase(){}

template<typename KrylovImpl, typename VectorType>
void KrylovBase<KrylovImpl, VectorType>::build_subspace(){
    static_cast<KrylovImpl*>(this)->build_subspace_impl();
}

}
