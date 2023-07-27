#include "HODLR.hpp"
//using namespace std;

// Example to solve least squares system Ax = b (Work In Progress)

class Kernel: public HODLR_Matrix
{
  private:
    
    int dim;
  public:
    Vec x;

    Kernel(int N, int dim): HODLR_Matrix(N)
    {
      // In Toeplitz Matrix (of size N x dim), we have entries from t(- dim + 1) to t(N - 1)
      x = (Vec::Random(N + dim - 1)).real();
      this->dim = dim;
    }

    dtype getMatrixEntry(int i, int j) 
    {
        return x(i - j + dim - 1);
    }

    void display_matrix()
    {
      for(int i = 0; i < this->N; i++)
      {
        for(int j = 0; j < this->dim; j++)
        {
          std::cout << this->getMatrixEntry(i, j) << "  ";
        }
        std::cout << std::endl; 
      }
    }

    void printX()
    {
      for (int i = 0; i < this->x.size(); i++) {
          std::cout << this->x(i) << ' ';
      }
    }


    // Destructor:
    ~Kernel() {};
};

int main(int argc, char* argv[])
{
  int N, dim;
  double tolerance;

  if(argc < 4)
  {
      std::cout << "All arguments weren't passed to executable!" << std::endl;
      std::cout << "Using Default Arguments:" << std::endl;
      // Size of the Matrix in consideration:
      N          = 10;
      // Dimensionality of the problem
      dim        = 5;
      // Tolerance of problem
      tolerance  = pow(10, -12);
  }

  else
  {
      // Size of the Matrix in consideration:
      N          = atoi(argv[1]);
      // Dimensionality of the problem
      dim        = atoi(argv[2]);
      // Tolerance of problem
      tolerance  = pow(10, -atoi(argv[3]));
  }

  std::cout << "========================= Problem Parameters =========================" << std::endl;
  std::cout << "Matrix Size :" << N << " x " << dim << std::endl;
  std::cout << "Tolerance   :" << tolerance << std::endl << std::endl;

  // Declaration of HODLR_Matrix object that abstracts data in Matrix:
  Kernel* K = new Kernel(N, dim);
  // Mat B = K->getMatrix(0, 0, N, dim);
  
  // Display matrix contents
  std::cout << "Actual Toeplitz matrix: " << std::endl;
  K->display_matrix();

  // Display x
  std::cout << "x: " << std::endl;
  K->printX();
  return 0;
}
