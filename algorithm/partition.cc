/*
ʹ��STL::partition��stable_partition
*/
#include <algorithm>
#include <iostream>
#include <iterator>

bool isOdd(int x)
{
  return x % 2 != 0;  // x % 2 == 1 is WRONG // ���ע���е���˼
}

void moveOddsBeforeEvens()
{
  int oddeven[] = { 1, 2, 3, 4, 5, 6 };
  std::partition(oddeven, oddeven+6, &isOdd);
  std::copy(oddeven, oddeven+6, std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl;
}

int main()
{
  moveOddsBeforeEvens();

  int oddeven[] = { 1, 2, 3, 4, 5, 6 };
  std::stable_partition(oddeven, oddeven+6, &isOdd);
  std::copy(oddeven, oddeven+6, std::ostream_iterator<int>(std::cout, ", "));
  std::cout << std::endl;
}
