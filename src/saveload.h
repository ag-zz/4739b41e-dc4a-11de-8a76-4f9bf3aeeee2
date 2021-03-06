/*
* saveload.h
* Luabins internal constants and helper macros
* See copyright notice in luabins.h
*/

#ifndef LUABINS_SAVELOAD_H_
#define LUABINS_SAVELOAD_H_

/* Find minimum of two values */
#define luabins_min(a, b) \
  ( ((a) < (b)) ? (a) : (b) )

/* Find maximum of two values */
#define luabins_max(a, b) \
  ( ((a) > (b)) ? (a) : (b) )

/* Find minimum of three values */
#define luabins_min3(a, b, c) \
  ( ((a) < (b)) ? luabins_min((a), (c)) : luabins_min((b), (c)) )

/* Internal error codes */
#define LUABINS_ESUCCESS (0)
#define LUABINS_EFAILURE (1)
#define LUABINS_EBADTYPE (2)
#define LUABINS_ETOODEEP (3)
#define LUABINS_ENOSTACK (4)
#define LUABINS_EBADDATA (5)
#define LUABINS_ETAILEFT (6)
#define LUABINS_EBADSIZE (7)

/* Type bytes */
#define LUABINS_CNIL    '-'
#define LUABINS_CFALSE  '0'
#define LUABINS_CTRUE   '1'
#define LUABINS_CNUMBER 'N'
#define LUABINS_CSTRING 'S'
#define LUABINS_CTABLE  'T'

/*
* PORTABILITY WARNING!
* You have to ensure manually that length constants below are the same
* for both code that does the save and code that does the load.
* Also these constants must be actual or code below would break.
* Beware of endianness and lua_Number actual type as well.
*/
#define LUABINS_LINT      (sizeof(int))
#define LUABINS_LSIZET    (sizeof(size_t))
#define LUABINS_LNUMBER   (sizeof(lua_Number))

/* Derived lengths
* WARNING: Change these if format is changed!
*/

/* One type byte */
#define LUABINS_LTYPEBYTE  (1)

/* Minimal table: type, array size, hash size, no data */
#define LUABINS_LMINTABLE  (LUABINS_LTYPEBYTE + LUABINS_LINT + LUABINS_LINT)

/* Minimal number: type, number value */
#define LUABINS_LMINNUMBER (LUABINS_LTYPEBYTE + LUABINS_LNUMBER)

/* Minimal string: type, length, no data */
#define LUABINS_LMINSTRING (LUABINS_LTYPEBYTE + LUABINS_LSIZET)

/* Minimum large (non-boolean non-nil) value length */
#define LUABINS_LMINLARGEVALUE \
  ( luabins_min3(LUABINS_LMINTABLE, LUABINS_LMINSTRING, LUABINS_LMINSTRING) )

/*
* Lower limit on total table data size is determined as follows:
* -- All entries are always key and value.
* -- Minimum value size is one byte for nil and boolean,
*    but that is two keys maximum (nil can'be the key).
* -- All the rest of key types are mimimum of LUABINS_MINLARGEVALUELEN
*    bytes (type byte plus data bytes).
* -- All values in the table may be booleans.
*
* WARNING: Change this if format is changed!
*
* Note this formula does NOT take in account
* table header (type byte and array/hash sizes).
*/
#define luabins_min_table_data_size(total_size) \
  ( \
    (total_size > 2) \
      ? ( \
          2 * (LUABINS_LTYPEBYTE + LUABINS_LTYPEBYTE) \
        + (total_size - 2) * (LUABINS_LMINLARGEVALUE + LUABINS_LTYPEBYTE) \
      ) \
      : (total_size * (LUABINS_LTYPEBYTE + LUABINS_LTYPEBYTE)) \
  )

#endif /* LUABINS_SAVELOAD_H_ */
