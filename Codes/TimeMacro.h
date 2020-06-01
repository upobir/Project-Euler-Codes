# include <iostream>
# include <chrono>


# define Time(f) auto _st = std::chrono::high_resolution_clock::now(); \
{ \
    f \
} \
auto _fn = std::chrono::high_resolution_clock::now(); \
auto _duration = std::chrono::duration_cast<std::chrono::milliseconds>(_fn - _st).count(); \
std::cout<<"\nTime taken: "<< _duration / 1000.0<<" seconds\n";
