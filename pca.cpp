#include "pca.h"
#include "Eigen/Dense"

pca::pca(){}

pca::~pca(){}
//sets the january numbers into a list
void pca::set_jan(){
  std::ifstream afile("january.txt", std::ios::in);
  if (afile.is_open()) {
    std::string line;
    while (std::getline(afile, line)) {
      this->january.push_back(std::stod(line));
    }
    afile.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
}
//sets july
void pca::set_july(){
  std::ifstream afile("july.txt", std::ios::in);
  if (afile.is_open()) {
    std::string line;
    while (std::getline(afile, line)) {
      this->july.push_back(std::stod(line));
    }
    afile.close();
  }
  else {
    std::cerr << "Unable to open file\n";
  }
}

//print out january and july values
void pca::to_string(){

  std::cout << "january" << '\n';

  for (size_t i = 0; i < this->january.size(); i++) {
    std::cout << this->january[i] << '\n';
  }

  std::cout << "july" << '\n';

  for (size_t i = 0; i < this->july.size(); i++) {
    std::cout << this->july[i] << '\n';
  }

  std::cout << "covariance matrix" << '\n';

  for (size_t i = 0; i < this->covariance_matrix.size(); i++) {
    for (size_t j = 0; j < this->covariance_matrix[i].size(); j++) {
      std::cout << this->covariance_matrix[i][j] << ' ';
    }
    std::cout << '\n';
  }
}

//finds the mean
void pca::min_mean() {
  double sum = std::accumulate(
    this->january.begin(),
    this->january.end(),
    0
  );

  double mean = sum / this->january.size();
  for (size_t i = 0; i < this->january.size(); i++) {
    this->january[i]=mean-this->january[i];
  }

  sum = std::accumulate(
    this->july.begin(),
    this->july.end(),
    0
  );

  mean = sum / this->july.size();
  for (size_t i = 0; i < this->july.size(); i++) {
    this->july[i]=mean-this->july[i];
  }
}

//finds the covariance of the matrix
double pca::covariance(std::vector<double> v, std::vector<double> y){
  double product = 0;

  for (size_t i = 0; i < v.size(); i++) {
    product+=v[i]*y[i];
  }
  return (product)/63;
}

//set the matrix
void pca::set_cor_matrix() {
  std::vector<double> v;
  v.push_back(
    covariance(
      this->january,
      this->january
    )
  );

  v.push_back(
    covariance(
      this->january,
      this->july
    )
  );

  this->covariance_matrix.push_back(v);

  v.clear();

  v.push_back(
    covariance(
      this->july,
      this->january
    )
  );

  v.push_back(
    covariance(
      this->july,
      this->july
    )
  );

  this->covariance_matrix.push_back(v);
}

//set the eigen values
void pca::set_eigen(){
	std::ofstream myfile;
  myfile.open("out.txt");
  if(myfile.is_open()){
  Matrix2f A;
  A <<
  this->covariance_matrix[0][0],
  this->covariance_matrix[0][1],
  this->covariance_matrix[1][0],
  this->covariance_matrix[1][1];
  
  SelfAdjointEigenSolver<Matrix2f> eigensolver(A);
  if (eigensolver.info() != Success) abort();
  myfile << "The eigenvalues are:\n" << eigensolver.eigenvalues() << std::endl;
  myfile << "Eigenvectors :\n"<< eigensolver.eigenvectors() << std::endl; 
  myfile << "Matrix :\n" << A << std::endl;
  myfile << "variance :\n" << eigensolver.eigenvalues() << std::endl;
  myfile << "the variance explain all the principal component\n" << eigensolver.eigenvalues() << std::endl;
}
}
