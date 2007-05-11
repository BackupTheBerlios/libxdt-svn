#include <xdt/bit_box/basic_bit_box.h>

int main() {
	xdt::bit_box::basic_bit_box<char> c1(0);
	xdt::bit_box::basic_bit_box<const char> c2(0);

	xdt::bit_box::basic_bit_box<char> c3(c1);
	xdt::bit_box::basic_bit_box<const char> c4(c1);
	xdt::bit_box::basic_bit_box<char> c5(c2);
	xdt::bit_box::basic_bit_box<const char> c6(c2);

	return -1;
}
