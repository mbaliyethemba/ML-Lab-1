#include "pca.h"
#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char const *argv[]) {
  pca p;
  p.set_jan();
  p.set_july();
  p.min_mean();
  p.set_cor_matrix();
  p.set_eigen();
  return 0;
}
