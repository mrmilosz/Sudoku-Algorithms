#include <exception>

namespace Sudoku
{
   class Exception : public std::exception {};

   class BadGridSizeException : public Exception
   {
      virtual const char* what() const throw()
      {
         return "Bad grid size given in Sudoku Grid constructor";
      }
   };

   class InvalidGridArrayException : public Exception
   {
      virtual const char* what() const throw()
      {
         return "Invalid array given in Sudoku Grid constructor";
      }
   };

   class RowIndexOutOfBoundsException : public Exception
   {
      virtual const char* what() const throw()
      {
         return "Given row index out of bounds for Sudoku Grid";
      }
   };

   class ColumnIndexOutOfBoundsException : public Exception
   {
      virtual const char* what() const throw()
      {
         return "Given column index out of bounds for Sudoku Grid";
      }
   };

   class CellValueOutOfBoundsException : public Exception
   {
      virtual const char* what() const throw()
      {
         return "Given cell value out of bounds for Sudoku Grid";
      }
   };
}

