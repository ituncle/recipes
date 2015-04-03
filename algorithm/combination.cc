/*
prev_permutation,next_permutation会执行全排列
此过程，使用全排列来生成组合(combination)
*/
#include <assert.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

int main()
{
  int values[] = { 1, 2, 3, 4, 5, 6, 7 };
  int elements[] = { 1, 1, 1, 0, 0, 0, 0 };
  const size_t N = sizeof(elements)/sizeof(elements[0]);
  assert(N == sizeof(values)/sizeof(values[0]));
  std::vector<int> selectors(elements, elements + N);

  int count = 0;
  do
  {
    std::cout << ++count << ": ";
    for (size_t i = 0; i < selectors.size(); ++i)
    {
      if (selectors[i])
      {
        std::cout << values[i] << ", ";
      }
    }
    std::cout << std::endl;
  } while (prev_permutation(selectors.begin(), selectors.end()));
  return 0;
}
