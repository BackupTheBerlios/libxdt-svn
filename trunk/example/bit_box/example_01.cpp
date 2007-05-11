#include <xdt/bit_box/basic_bit_box.h>


int main() {
	xdt::bit_box::basic_bit_box<const xdt::byte_t *> bb1(0);
	xdt::bit_box::basic_bit_box<xdt::byte_t *> bb2(0);

	*(bb1.bits()) = 0;
	*(bb2.bits()) = 0;

	xdt::bit_box::basic_bit_box<const xdt::byte_t *> bb3(bb1);
	xdt::bit_box::basic_bit_box<xdt::byte_t *> bb4(bb1);
	xdt::bit_box::basic_bit_box<const xdt::byte_t *> bb5(bb2);
	xdt::bit_box::basic_bit_box<xdt::byte_t *> bb6(bb2);

	return -1;
}
