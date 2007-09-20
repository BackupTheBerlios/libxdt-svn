#include <xdt/bit_box/basic_chest.h>
#include <xdt/bit_box/basic_iterator.h>
#include <iostream>
// #include <xdt/bit_box/bit_box.h>

/*
class writer
{
public:
	put(sz, type_id, ptr);
	box put(sz);
	unget(box &what);

protected:
private:
};
*/


int main()
{

	void *vptr = 0;
	const int *iptr = 0;
	if (iptr == vptr) return 0;

	typedef xdt::bit_box::basic_chest<char, int> rw_chest;
	typedef xdt::bit_box::basic_chest<const char, const int> r_chest;


	char *const ptr = new char[rw_chest::solid_sz(sizeof(int))];

	const rw_chest ch1(ptr, sizeof(int), rw_chest::bbt_sint32);

	(*ch1.bits()) = 4;

	const r_chest ch2(ch1);

	// (*ch2.bits()) = 4;

	const r_chest ch3(ch1.solid_ptr());

	std::cout << (*ch3.bits()) << std::endl;

	xdt::bit_box::basic_iterator<rw_chest> rw_iter;
	xdt::bit_box::basic_iterator<const r_chest> r_iter;
	rw_iter->bits();

	delete[] ptr;

	// size of fake bit_box
	/*
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
	*/
	/*
	xdt::bit_box::bit_box<xdt::byte_t> bb(0);
	xdt::bit_box::bit_box<xdt::byte_t>::iterator i(0);

	xdt::bit_box::bit_box<const xdt::byte_t>::iterator j = bb.begin();
	*/

	return -1;
}
