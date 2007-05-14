#include <xdt/bit_box/basic_bit_box.h>
// #include <xdt/bit_box/bit_box.h>
#include <list>

int main() {
	/*
	typedef std::list<int>::iterator iter_t;
	typedef std::list<int>::const_iterator citer_t;
	std::list<int> list;
	iter_t i1 = list.begin();
	citer_t i2 = list.begin();
	i1 = i2;
	i2 = i1;
	citer_t i3(i2);
	*/

	xdt::bit_box::basic_bit_box<char> bb1(0);
	xdt::bit_box::basic_bit_box<const char> bb2(0);

	xdt::bit_box::basic_bit_box<char> bb3(0, 1);
	xdt::bit_box::basic_bit_box<const char> bb4(0, 1);

	xdt::bit_box::basic_bit_box<char> bb5(bb1);
	xdt::bit_box::basic_bit_box<const char> bb6(bb1);
	//xdt::bit_box::basic_bit_box<char> bb7(bb2);
	xdt::bit_box::basic_bit_box<const char> bb8(bb2);
	/*
	xdt::bit_box::bit_box<xdt::byte_t> bb(0);
	xdt::bit_box::bit_box<xdt::byte_t>::iterator i(0);

	xdt::bit_box::bit_box<const xdt::byte_t>::iterator j = bb.begin();
	*/

	return -1;
}
