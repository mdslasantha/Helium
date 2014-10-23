#include <Halide.h>
using namespace Halide;

int main(int argc, char **argv) {

    ImageParam input(UInt(8), 2);
    Func output("output");
	Var x("x"), y("y");
    
    // The algorithm
    output(x,y) = input(y,x);
    output.compile_to_file("halide_rotate_gen", input); 

    return 0;
}
