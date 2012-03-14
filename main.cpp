#include <cmath>
#include <iostream>
#include <iomanip>
#include <list>

#include <Grid.hpp>
#include <Exception.hpp>

typedef std::list<Sudoku::Cell> CandidateList;
typedef CandidateList::const_iterator CandidateIterator;

void printGrid(const Sudoku::Grid *);
Sudoku::Grid * solve(Sudoku::Grid);

int main()
{
   Sudoku::Cell cells[] =
   {
      0, 0, 5,  3, 0, 0,  0, 0, 0,
      8, 0, 0,  0, 0, 0,  0, 2, 0,
      0, 7, 0,  0, 1, 0,  5, 0, 0,

      4, 0, 0,  0, 0, 5,  3, 0, 0,
      0, 1, 0,  0, 7, 0,  0, 0, 6,
      0, 0, 3,  2, 0, 0,  0, 8, 0,

      0, 6, 0,  5, 0, 0,  0, 0, 9,
      0, 0, 4,  0, 0, 0,  0, 3, 0,
      0, 0, 0,  0, 0, 9,  7, 0, 0
   };

   const int gridLength = sizeof(cells) / sizeof(Sudoku::Cell);

   try
   {
      Sudoku::Grid grid(cells, gridLength);
      printGrid(&grid);
      Sudoku::Grid * pSolvedGrid = solve(grid);
      printGrid(pSolvedGrid);
      delete pSolvedGrid;
   }
   catch (Sudoku::Exception & e)
   {
      std::cerr << e.what() << std::endl;
   }
}

Sudoku::Grid * solve(Sudoku::Grid grid)
{
   int i, j, k, n, candidateRow, candidateColumn, leastNumberOfCandidates;
   Sudoku::Grid * pRecursiveSolution;
   n = grid.boardLength();
   CandidateList recursionCandidates;
   CandidateIterator iter;

   do
   {
      leastNumberOfCandidates = n + 1;
      for (i = 0; i < n; ++i)
      {
         for (j = 0; j < n; ++j)
         {
            if (grid.getCell(i, j) == 0)
            {
               CandidateList candidates;
               for (k = 1; k <= n; ++k)
               {
                  if (grid.canSetCell(i, j, static_cast<Sudoku::Cell>(k)))
                  {
                     candidates.push_back(static_cast<Sudoku::Cell>(k));
                  }
               }
               if (candidates.size() == 0)
               {
                  return reinterpret_cast<Sudoku::Grid *>(NULL);
               }
               else if (candidates.size() == 1)
               {
                  grid.setCell(i, j, *candidates.begin());
               }
               
               if (static_cast<int>(candidates.size()) < leastNumberOfCandidates)
               {
                  leastNumberOfCandidates = candidates.size();
                  recursionCandidates = candidates;
                  candidateRow = i;
                  candidateColumn = j;
               }
            }
         }
      }
      if (leastNumberOfCandidates == n + 1) // All cells are filled
      {
         return new Sudoku::Grid(grid);
      }
   }
   while (leastNumberOfCandidates < 2);

   for (iter = recursionCandidates.begin(); iter != recursionCandidates.end(); ++iter)
   {
      grid.setCell(candidateRow, candidateColumn, *iter);
      pRecursiveSolution = solve(grid);
      if (pRecursiveSolution != reinterpret_cast<Sudoku::Grid *>(NULL))
      {
         return pRecursiveSolution;
      }
   }

   return reinterpret_cast<Sudoku::Grid *>(NULL);
}

void printGrid(const Sudoku::Grid * pGrid)
{
   int i, j, cellDisplayWidth;
   std::cout << std::endl;
   if (pGrid == reinterpret_cast<Sudoku::Grid *>(NULL))
   {
      std::cout << "NULL" << std::endl;
   }
   else
   {
      cellDisplayWidth = static_cast<int>(std::floor(std::log10(pGrid->boardLength()))) + 2;
      for (i = 0; i < pGrid->boardLength(); ++i)
      {
         if (i % pGrid->n() == 0)
         {
            std::cout << std::endl;
         }
         for (j = 0; j < pGrid->boardLength(); ++j)
         {
            if (j % pGrid->n() == 0)
            {
               std::cout << " ";
            }
            std::cout << std::setw(cellDisplayWidth) << pGrid->getCell(i, j);
         }
         std::cout << std::endl;
      }
   }
   std::cout << std::endl;
}

