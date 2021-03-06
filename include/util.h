#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdbool.h>
#include <assert.h>

#include "boost/preprocessor/punctuation/comma_if.hpp"
#include "boost/preprocessor/seq/for_each_i.hpp"
#include "boost/preprocessor/variadic/to_seq.hpp"

#define PARENTHESIS_COMMA_SEP(r, token, i, e) BOOST_PP_COMMA_IF(i) token(e)
#define WRAP(token, ...) BOOST_PP_SEQ_FOR_EACH_I(PARENTHESIS_COMMA_SEP, token, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define CAT_BACK_(r, data, i, elem) BOOST_PP_COMMA_IF(i) BOOST_PP_CAT(data, elem)
#define CAT_BACK(token, ...) BOOST_PP_SEQ_FOR_EACH_I(CAT_BACK_, token, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define EQUAL_(r, data, i, elem) BOOST_PP_COMMA_IF(i) elem = data + i // BOOST_PP_CAT(elem, data)
#define EQUAL(token, ...) BOOST_PP_SEQ_FOR_EACH_I(EQUAL_, token, BOOST_PP_VARIADIC_TO_SEQ(__VA_ARGS__))

#define __NARG__(...)  __NARG_I_(__VA_ARGS__,__RSEQ_N())
#define __NARG_I_(...) __ARG_N(__VA_ARGS__)
#define __ARG_N( \
      _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
     _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
     _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
     _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
     _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
     _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
     _61,_62,_63,N,...) N
#define __RSEQ_N() \
     63,62,61,60,                   \
     59,58,57,56,55,54,53,52,51,50, \
     49,48,47,46,45,44,43,42,41,40, \
     39,38,37,36,35,34,33,32,31,30, \
     29,28,27,26,25,24,23,22,21,20, \
     19,18,17,16,15,14,13,12,11,10, \
     9,8,7,6,5,4,3,2,1,0

#define internal static

typedef void* address; // intended to store the address af any variable

#endif