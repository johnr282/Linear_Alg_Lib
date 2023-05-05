#include <getopt.h>
#include <iostream>
#include "matrix.h"
#include "tests.h"


int	main(int argc, char* argv[]) {
	testDenseMatrix();

	std::cout << "Tests complete\n";
}
