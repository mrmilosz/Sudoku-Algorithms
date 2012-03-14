#include <cstring>

#include <Grid.hpp>
#include <Exception.hpp>

namespace Sudoku
{
   Grid::Grid(int n)
   {
      int gridSize;

      if (sNMin <= n && n <= sNMax)
      {
         mN = n;
         mBoardLength = n * n;
         mGridLength = sValidGridLengths[n];

         gridSize = mGridLength * sCellSize;
         mCells = (Cell *) new char[gridSize];
         std::memset(mCells, 0, gridSize);
      }
      else
      {
         throw BadGridSizeException();
      }
   }

   Grid::Grid(const Cell * cells, int gridLength)
   {
      int n, gridSize, row, column;
      bool gridLengthIsValid;

      gridLengthIsValid = false;
      for (n = 2; !gridLengthIsValid && n <= sNMax; ++n)
      {
         if (gridLength == sValidGridLengths[n])
         {
            gridLengthIsValid = true;
            --n;
         }
      }

      if (gridLengthIsValid)
      {
         mN = n;
         mBoardLength = n * n;
         mGridLength = gridLength;

         gridSize = mGridLength * sCellSize;
         mCells = (Cell *) new char[gridSize];
         std::memset(mCells, 0, gridSize);

         for (row = 0; row < mBoardLength; ++row)
         {
            for (column = 0; column < mBoardLength; ++column)
            {
               const Cell & cell = *(cells + (row * mBoardLength + column));
               if (cell < 0 || cell > mBoardLength)
               {
                  throw InvalidGridArrayException();
               }
               if (!canSetCell(row, column, cell))
               {
                  throw InvalidGridArrayException();
               }
               *(mCells + (row * mBoardLength + column)) = cell;
            }
         }
      }
      else
      {
         throw InvalidGridArrayException();
      }
   }

   Grid::~Grid()
   {
      delete [] mCells;
   }

   void Grid::copy(const Grid & grid)
   {
      int gridSize;
      
      mN = grid.mN;
      mBoardLength = grid.mBoardLength;
      mGridLength = grid.mGridLength;

      gridSize = grid.mGridLength * sCellSize;
      if (mCells != NULL)
      {
         delete [] mCells;
      }
      mCells = (Cell *) new char[gridSize];
      memcpy(mCells, grid.mCells, gridSize);
   }

   bool Grid::canSetCell(int row, int column, Cell cell) const
   {
      int rowOffset, boardRowOffset, boardColumnOffset, i;

      if (row < 0 || row >= mBoardLength)
      {
         throw RowIndexOutOfBoundsException();
      }

      if (column < 0 || column >= mBoardLength)
      {
         throw ColumnIndexOutOfBoundsException();
      }

      if (cell < 0 || cell > static_cast<Cell>(mBoardLength))
      {
         throw CellValueOutOfBoundsException();
      }

      if (cell != 0)
      {
         rowOffset = row * mBoardLength;
         boardRowOffset = mN * (row / mN);
         boardColumnOffset = mN * (column / mN);
         for (i = 0; i < mBoardLength; ++i)
         {
            if (
               *(mCells + (rowOffset + i)) == cell || // check row
               *(mCells + (i * mBoardLength + column)) == cell || // check column
               *(mCells + ((boardRowOffset + i / mN) * mBoardLength + (boardColumnOffset + i % mN))) == cell // check board
            )
            {
               return false;
            }
         }
      }

      return true;
   }

   bool Grid::setCell(int row, int column, Cell cell)
   {
      if (row < 0 || row >= mBoardLength)
      {
         throw RowIndexOutOfBoundsException();
      }

      if (column < 0 || column >= mBoardLength)
      {
         throw ColumnIndexOutOfBoundsException();
      }

      if (cell < 0 || cell > static_cast<Cell>(mBoardLength))
      {
         throw CellValueOutOfBoundsException();
      }

      *(mCells + (row * mBoardLength + column)) = cell;
      return true;
   }

   Cell Grid::getCell(int row, int column) const
   {
      if (row < 0 || row >= mBoardLength)
      {
         throw RowIndexOutOfBoundsException();
      }

      if (column < 0 || column >= mBoardLength)
      {
         throw ColumnIndexOutOfBoundsException();
      }

      return *(mCells + (row * mBoardLength + column));
   }

   int Grid::sCellSize = sizeof(Cell);
   int Grid::sNMin = 2;
   int Grid::sNMax = 8;
   int Grid::sValidGridLengths[] = { NULL, NULL, 16, 81, 256, 625, 1296, 2401, 4096 }; // n^4 ; sNMin <= n <= sNMax
}

