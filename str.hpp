# pragma once
//new comment for new_branch
template <typename T, typename Seq, T Begin>
struct make_integer_range_impl;

template <typename T, T... Ints, T Begin>
struct make_integer_range_impl<T, std::integer_sequence<T, Ints...>, Begin> {
  using type = std::integer_sequence<T, Begin + Ints...>;
};

template <std::size_t Begin, std::size_t End>
using make_index_range = typename make_integer_range_impl<std::size_t, std::make_integer_sequence<std::size_t, End - Begin>, Begin>::type;


template <std::size_t N>
class STR{
public:
    void print_sequence() const{
        //std::cout<<N;
        for(size_t i = 0; i<N - 1; ++i)
            std::cout << arr[i];
    }

    template <typename... Elements>
    constexpr STR( Elements... elements )
        : arr{ elements... }{

    }

    template<std::size_t ..._N>
    constexpr STR( const char(&rhs)[N], const std::index_sequence<_N...> )
        : STR( rhs[_N]... ){

    }

    template<std::size_t _N>
    constexpr STR( const char(&a)[_N] )
        : STR( a, std::make_index_sequence<_N-1>{} ){

    }

    constexpr STR( const char(&a)[N] )
        : STR( a, std::make_index_sequence<N-1>{} ){

    }

    constexpr char operator[]( const std::size_t pos ) const{
        return pos < N ? arr[pos] : throw std::out_of_range("Index out of range");
    }

    constexpr std::size_t length() const {
        return N-1;
    }


    constexpr std::size_t size() const {
        return N-1;
    }
    
    constexpr bool empty() const{
        return this->size() == 0;
    }

    constexpr STR(const char* a, std::size_t size)
        : arr{}{
        for (std::size_t i = 0; i < size; ++i) {
            arr[i] = a[i];
        }
    }

    template<std::size_t start>
    constexpr auto substr() const{
        if( start >= N - 1 )
            throw std::out_of_range("Index out of range");
        STR<N-start> ans(arr + start, N-start-1);
        return ans;
    }


    template<std::size_t start, std::size_t length>
    constexpr auto substr() const{
        if( start >= N - 1 || start + length >= N )
            throw std::out_of_range("Index out of range");
        STR<length+1> ans(arr + start, length);
        return ans;
    }
    
    template<typename S>
    constexpr bool starts_with(const S& s) const{
        if(sizeof(s) > sizeof(this))
            return false;
        for(std::size_t i=0; i<sizeof(s) - 1; ++i){
            if(s[i] != arr[i])
                return false;
        }
        return true;
    }

    template<typename S>
    constexpr bool ends_with(const S& s) const{
        std::size_t size = sizeof(s);
        std::size_t end = this->size();
        if(size > end+1)
            return false;
        for(std::size_t i=0; i<size - 1; ++i){
            if(s[size-2-i] != arr[end - 1 - i]){
                return false;
            }
        }
        return true;
    }
    
private:
    char arr[N];
};



template <std::size_t Left, std::size_t Right, class L, class R>
constexpr auto Equal(const L& lhs, const R& rhs){
    if( Left != Right )
        return false;
    for(std::size_t i = 0; i < Left; ++i){
        if(lhs[i] != rhs[i])
            return false;
    }
    return true;
}

template <typename L, typename R>
constexpr bool operator==( const L& lhs, const R& rhs ){
    return Equal<sizeof(lhs), sizeof(rhs)>( lhs, rhs );
}


template <typename L, typename R, std::size_t... posL, std::size_t... posR>
constexpr auto Add( const L& lhs, const R& rhs, std::index_sequence<posL...>, std::index_sequence<posR...>){
    return STR<sizeof...(posL) + sizeof...(posR)>( lhs[posL]..., rhs[posR]... );
}

template <typename L, typename R>
constexpr auto operator+( const L& lhs, const R& rhs ){
    return Add( lhs, rhs, std::make_index_sequence<sizeof(lhs)-1>{}, std::make_index_sequence<sizeof(rhs)>{} );
}
