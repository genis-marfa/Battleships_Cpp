#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>


class board
{
friend std::ostream & operator << (std::ostream &out, board &M);
    
private:
    int n_rows{0};
    int n_cols{0};
    int *board_data;
    
public:
    // Default constructor.
    board() {board_data=0;}
    
    // Param. constructor:
    board(int nRows, int nCols);
    
    // (Deep) copy and move constructors:
    board (board&);
    board (board&&);
    
    // Element access operator () overload :
    int & operator() (int i, int j);
 
    // Asignment operator = overload:
    board& operator = (board&);       // Copy asignement
    board& operator = (board&&);      // Move asignment
    
    // Member fucntion to return matrix size.
    int size(){return n_rows*n_cols;}
    
    
    // Destructor (using delete)
    ~board(){delete board_data;} // std::cout<<"Destructor called"<<std::endl;}
};

// Param. constructor:
board::board (const int nRows, const int nCols)
{
    assert(nRows > 0 && nCols > 0);
    int size = nRows*nCols;
    n_rows = nRows;
    n_cols = nCols;
    
    // Dynamic Memory allocation:
    board_data = new int[size];
    // Initialise entries to 0.
    for(int i=0; i<size; i++) board_data[i] = 0;
}

// Copy constructor for deep copying
board::board (board &M)
{
  // Copy dimension and declare new matrix
n_rows = M.n_rows;
n_cols = M.n_cols;
int size  {M.size()};
    
if(size >0) {
    board_data = new int[size];
    for (int i{}; i<size; i++) board_data[i] = M.board_data[i];
    }
}

// Assignment operator for deep copying
board & board::operator = (board &M)
{
  if(&M == this) return *this; // Handle self-assignment
  
  // First delete this object's array
  delete[] board_data; board_data=0; n_rows=0; n_cols=0;
  
  // Now copy dimension and declare new array
  n_rows = M.n_rows;
  n_cols = M.n_cols;
  int size = M.size();
    
  if(size > 0)
    {
      board_data = new int[size];
      // Copy values into new array
      for(int i=0; i < size; i++) board_data[i] = M.board_data[i];
    }
  return *this;
}

// Move constructor:
board::board(board &&M)
{ // steal the data
  std::cout << "move constructor\n";
  n_cols = M.n_cols;
  n_rows = M.n_rows;
  board_data = M.board_data;
  
  M.n_rows= 0; M.n_cols = 0;
  M.board_data = nullptr;
}

// Move assignment operator
board & board::operator=(board&& M)
{
  std::cout << "move assignment\n";
  std::swap(n_rows,M.n_rows);
  std::swap(n_cols,M.n_cols);
  std::swap(board_data, M.board_data);
  return *this; // Special pointer!!!
}

// Overloaded element acess () operator:
int & board::operator() (int i, int j)
{
      assert(i > 0 && j > 0);
      return board_data[j-1+(i-1)*n_cols];
}

// Overload insertion operator:
std::ostream & operator << (std::ostream &out, board &M)
{
    int nRows {M.n_rows};
    int nCols {M.n_cols};
    
    out << '\n';
    out << "     1 2 3 4 5 6 7 8 9 10" << std::endl;
    out << "    ----------------------" << std::endl;
    
    std::vector<std::string> letters{"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};
    
    for (int i{1}; i<=nRows; i++){
       out << letters[i-1] << "  | ";
        
        for (int j{1}; j<=nCols; j++){
        
        std::string output;
            if      (M(i,j) == 1) output = "X";
            else if (M(i,j) == 2) output = ".";
            else if (M(i,j) == 0) output = "O";
            out << output << " " ;
        }
        out << "|" << '\n';
    }
    out << "    ----------------------" << std::endl;
    return out;
}
