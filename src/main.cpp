#include <iostream>
#include "List.h"

int main()
{
    List<int> i_list = List<int>;
    i_list.put(4, 0);
    i_list.put(0, 1);
    i_list.put_front(2, 1);
    i_list.put(9, 3);
    i_list.put_behind(6, 2);
    std::cout << i_list.get_repr() << std::endl;
    std::cout << "Time wasted..." << std::endl;
}


