#pragma once
template <typename T>
class limitvalue{
    private:
    T c_value;
    T min_value;
    T max_value;
    void xianfu(){
        if(c_value<min_value)
        c_value=min_value;
        if(c_value>max_value)
        c_value=max_value;
    }

public:
    limitvalue(T v, T mi, T ma) :
    c_value(v), min_value(mi), max_value(ma) { xianfu(); }
    limitvalue& operator=(T v) { c_value = v; xianfu(); 
    return *this; }
    limitvalue& operator+=(T v) { c_value += v; xianfu(); 
    return *this; }
    T val() { return c_value; }
};
