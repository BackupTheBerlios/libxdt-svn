1.  Требования

Необхоимо: механизм запаковывания произвольного числа линейных (непрерывных) блоков памяти (байт-массивов) в один линейный блок, с возможностью последующей распаковки.

Направление использования: передача произвольного числа разнотипных данных разного размера в одном непрерывном блоке данных по pipe-подобным каналам.

Идеология: контейнер, способный хранить не связанные массивы байтов произвольной длинны в линейном (непрерывном) блоке памяти.

Поддерживаемые операции:
	- добавление в конец нового блока данных
	- последовательный перебор хранимых блоков данных

2.  Интерфейс
	
class bit_box_basic {
public:
	// types -------------------------------------------------------------------

	//! \brief Type for one byte (8 bits) - minimal unit of information for
	//!	bit_box
	typedef unsigned char byte_t;

	//!	\brief Type for size
	typedef unsigned int sz_t;
	
	//!	\brief Type type identifier
	typedef unsigned int type_t;
	
	//!	\brief One item of bit_box data (item header)
	#pragma pack(4, push)
	struct item_t {
		sz_t sz;
		type_t type;
	};
	#pragma pack(pop)
	
	// constants ---------------------------------------------------------------

	//! \brief bit_box data types
	enum types {
		bbt_bitbox,
		bbt_binary,
		bbt_int32,
		bbt_uint32,
		bbt_string,
		bbt_wstring
	};

protected:
private:
};
	
class reader: public bit_box_basic {
public:
	class const_iterator {
	};
	class iterator {
	};

	reader(const reader &r);
	reader(const byte_t *const bits);
	reader(const byte_t *const bits, const sz_t sz);
	
	const_iterator begin() const;
	iterator begin() const;
	const_iterator end() const;
	iterator end() const;

	bool empty() const;
	
	sz_t size() const;	// slow - returns number of elements

protected:
	void _set(const byte_t *const bits) {
		const item_t &item = *((item_t *)bits);
		assert(bbt_bitbox == item.type);
		_bits = bits + sizeof(item_t);
		_bite\\
	}

	void _set(const byte_t *const bits, const sz_t sz) {
		_bits = bits;
		_sz = sz;
	}

private:
	// private data ------------------------------------------------------------

	//! \brief Pointer to bit_box data storage
	const byte_t *_bits;

	//! \brief Size of bit_box storage in bytes
	sz_t _sz;

};

class composer: public bit_box_basic {
};

class bit_box {
public:
	// types -------------------------------------------------------------------

	// public methods ----------------------------------------------------------

	//! \brief Default constructor
	/*!	Creates empty bit_box object
	*/
	bit_box();

	//!	\brief Copy constructor
	/*!
	*/
	bit_box(const bit_box &bb);

	bit_box(const byte_t *const bits);

	bit_box(const byte_t *const bits, const sz_t sz);

	//!	\brief Destructor
	~bit_box();
protected:
private:
}

xdt::bit_box::composer composer;
composer.put(ptr, sz, type);
composer.cpy(ptr);
composer.store(ptr);
composer.sz();
composer.storage_sz();
composer.storage_sz();

xdt::bit_box::reader(ptr, sz)
xdt::bit_box::reader(ptr)
	