#pragma once

#include <stdint.h>

#include <vector>

#define SER_UINT32(buf, var) \
  { \
    uchar_t *ptr = (uchar_t *)&var; \
    buf.push_back(ptr[3]); \
    buf.push_back(ptr[2]); \
    buf.push_back(ptr[1]); \
    buf.push_back(ptr[0]); \
  } \


#define DESER_UINT32(buf, cntr, var) \
  { \
    uchar_t *ptr = (uchar_t *)&var; \
    ptr[3] = buf[cntr++]; \
    ptr[2] = buf[cntr++]; \
    ptr[1] = buf[cntr++]; \
    ptr[0] = buf[cntr++]; \
  } \

typedef unsigned char uchar_t;

struct buf_t {
  ::std::shared_ptr<uchar_t> data;
  uint32_t len;

  buf_t() 
    : data(NULL), len(0) {
  }

  static const buf_t from_vector(::std::vector<uchar_t> vec) {
    buf_t to_ret;
    to_ret.len = vec.size();
    to_ret.data = ::std::shared_ptr<uchar_t>(new uchar_t[to_ret.len]);
    for (uint32_t i = 0; i < to_ret.len; i++) {
      to_ret.data.get()[i] = vec[i];
    }
    return to_ret;
  }
};