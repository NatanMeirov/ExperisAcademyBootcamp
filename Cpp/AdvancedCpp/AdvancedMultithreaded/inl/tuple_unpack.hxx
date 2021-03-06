#ifndef NM_META_TUPLE_UNPACK_HXX
#define NM_META_TUPLE_UNPACK_HXX


#include <cstddef> // size_t
#include <tuple> // std::tuple_size, std::get, std::tuple_size


namespace nm
{

namespace meta
{

// A sequence holder (to be used with sizeof...(Args) - to count the number of the variadic template [0..N]) {Example: Sequence<> is empty}
template <size_t ...>
struct Sequence
{
};


// A Sequence "expander", to extract the sequence in each instantiation (...Seq can be none) -> SequenceExpander<N> is valid {Example: SequenceExpander<3>::type == Sequence<0, 1, 2>} [ Reference to deeper explanation: https://stackoverflow.com/questions/36612596/tuple-to-parameter-pack ]
template <size_t N, size_t ...Seq>
struct SequenceExpander : public SequenceExpander<N - 1, N - 1, Seq...>
{
};


// A SequenceExpander specialization to be used as a stopping condition - all other SequenceExpanders inherits from it (in the top of that inheritance list), so type is declared inside them as well
template <size_t ...Seq>
struct SequenceExpander<0, Seq...>
{
    typedef Sequence<Seq...> SequenceType;
};


template <typename RetT, typename Func, typename Tuple, size_t ...Seq>
RetT ExpandedFuncCall(Func a_func, Tuple a_tuple, Sequence<Seq...>)
{
    return a_func(std::get<Seq>(a_tuple) ...);
}


template <typename RetT, typename Func, typename ...Args>
RetT UnpackTupleAndCallFunc(Func a_func, std::tuple<Args...> a_tuple)
{
    return ExpandedFuncCall<RetT, Func>(a_func, a_tuple, typename SequenceExpander<std::tuple_size<std::tuple<Args...>>::value>::SequenceType());
};

} // meta

} // nm


#endif // NM_META_TUPLE_UNPACK_HXX
