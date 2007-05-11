#include <xdt/bit_box/basic_bit_box.h>
#include <xdt/bit_box/bit_box.h>

int main() {
	xdt::bit_box::bit_box<xdt::byte_t> bb(0);
	xdt::bit_box::bit_box<xdt::byte_t>::iterator i(0);

	xdt::bit_box::bit_box<const xdt::byte_t>::iterator j = bb.begin();

	return -1;
}
