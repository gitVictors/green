#pragma once

template <typename T>
auto GetPerimeter(T a ){
    return a*4;
}


template<typename T, typename D>
auto GetPerimeter(T a, D b){
    return ( a + b )*2;
}

template<typename T, typename D, typename C, typename K >
auto GetPerimeter (T a, D b, C c, K d){
    return a + b + c + d;
}
