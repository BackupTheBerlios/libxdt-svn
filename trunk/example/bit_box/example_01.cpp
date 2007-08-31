#include <xdt/bit_box/basic_bit_box.h>
// #include <xdt/bit_box/bit_box.h>
#include <list>

int main()
{
	// size of fake bit_box
	static const xdt::uint32_t fake_bit_box_sz = 1024;
	xdt::byte_t *const = malloc();
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
