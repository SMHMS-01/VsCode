#include <iostream>
#include <windows.h>

using namespace std;

bool hasPath(char *matrix, int rows, int cols, char *str)
{
   if (!matrix || rows < 1 || cols < 1 || !str)
      return false;

   bool *visited = new bool[rows * cols];
   memset(visited, 0, rows * cols);

   int pathLength = 0;
   for (int row = 0; row < rows; ++row)
      for (int row = 0; row < rows; ++row)
      {
      }
}

bool hasPathCore(const char *matrix, int rows, int cols, int row, int col, const char *str, int &pathLength, bool *visited)
{

   if (str[pathLength] == '\0')
      return true;

   bool hasPath = false;
   if (row >= 0 && row < rows && col >= 0 && col < cols && matrix[row * cols + col] == str[pathLength] && !visited[row * cols + col])
   {
   }
}
int main()
{
   SetConsoleOutputCP(65001);
   system("pause");
   return 0;
}
