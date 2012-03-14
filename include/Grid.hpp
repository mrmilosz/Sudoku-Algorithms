namespace Sudoku
{
   typedef int Cell;

   class Grid
   {
      public:
         Grid(int);
         Grid(const Cell *, int);
         Grid(const Grid & grid) : mCells(NULL) { copy(grid); }
         Grid & operator= (const Grid & grid) { copy(grid); return *this; }
         const int & n() const { return mN; }
         const int & boardLength() const { return mBoardLength; }
         const int & gridLength() const { return mGridLength; }
         bool canSetCell(int, int, Cell) const;
         bool setCell(int, int, Cell);
         Cell getCell(int, int) const;
         virtual ~Grid();
      protected:
         void copy(const Grid &);
         int * mCells;
         int mN;
         int mBoardLength;
         int mGridLength;
         static int sCellSize;
         static int sNMin;
         static int sNMax;
         static int sValidGridLengths[];
      private:
         Grid() {}
   };
}

