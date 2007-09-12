#include <xdt/bit_box/basic_chest.h>
// #include <xdt/bit_box/bit_box.h>

template <class bits_t>
class basic_chest
{
public:
	// constructors
	basic_chest(bits_t *const solid_ptr);

	basic_chest(bits_t *const solid_ptr, sz, type_id);

	basic_chest(const basic_box &src);

	template <class from_bits_t>
	basic_chest(const basic_chest<from_bits_t> &from);

	~basic_chest();


	// always const!!!
	const int &sz() const;

	// can be changed when basic_chest is not a constant object
	const int &type_id() const;
	int &type_id();

	// never can alter constant object
	const bits_t *bits() const;
	// can alter only if bits_t not constant type
	bits_t *bits() const;

	const void *solid_ptr() const;

	int solid_sz() const;

	static int solid_sz(sz);

protected:
	struct _header_t
	{
		int sz;
		int type_id;
	};
private:
	_header_t *_header;
	char *_body;
};


////////////////////////////
class writer
{
public:
	put(sz, type_id, ptr);
	box put(sz);
	unget(box &what);

protected:
private:
};

int main()
{
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
