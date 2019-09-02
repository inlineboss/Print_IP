
#include <out_byte.h>
#include <vector>
#include <list>

int main()
{
	  print_ip(char{-1});
	  print_ip(short{0});
	  print_ip(int{2130706433});
	  print_ip(long{8875824491850138409});
	  print_ip(std::string {"127.0.0.1"});
	  print_ip(std::vector<int> {127, 0, 0, 1});
	  print_ip(std::list<int> {127, 0, 0, 1});
	  print_ip(std::make_tuple(127, 0, 0, 1));

    return 0;
}
