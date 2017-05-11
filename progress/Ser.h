#pragma once

#include <stdint.h>

#include <memory>
#include <vector>

#define APP(buf, item) \
  buf.push_back(item); \

#define SER_UINT32(buf, var) \
  { \
    uchar_t *ptr = (uchar_t *)&var; \
    buf.push_back(ptr[0]); \
    buf.push_back(ptr[1]); \
    buf.push_back(ptr[2]); \
    buf.push_back(ptr[3]); \
  } \

#define SER_DATA(buf, data, size) \
  { \
    SER_UINT32(buf, size) \
    for (uint32_t i = 0; i < size; i++) { \
      APP(buf, data[i]); \
    } \
  } \

#define SER_STRING(buf, var) \
  { \
    uint32_t size = var.size(); \
    SER_DATA(buf, var.c_str(), size); \
  } \

#define SER_VEC_OF_UINT32(buf, var) \
  { \
    uint32_t size = var.size(); \
    SER_UINT32(buf, size); \
    for (uint32_t i = 0; i < var.size(); i++) { \
      SER_UINT32(buf, var[i]) \
    } \
  } \

#define SER_VEC_OF_STRING(buf, var) \
  { \
    uint32_t size = var.size(); \
    SER_UINT32(buf, size); \
    for (uint32_t i = 0; i < var.size(); i++) { \
      SER_STRING(buf, var[i]) \
    } \
  } \

#define DESER_UINT32(buf, cntr, var) \
  { \
    uchar_t *ptr = (uchar_t *)&var; \
    ptr[0] = buf[cntr++]; \
    ptr[1] = buf[cntr++]; \
    ptr[2] = buf[cntr++]; \
    ptr[3] = buf[cntr++]; \
  } \

#define DESER_DATA(buf, cntr, var) \
  { \
    var##_len = 0; \
    DESER_UINT32(buf, cntr, var##_len); \
    var##_data = new uchar_t[var##_len]; \
    for (uint32_t i = 0; i < var##_len; i++) { \
      var##_data[i] = buf[cntr++]; \
    } \
  } \

#define DESER_STRING(buf, cntr, var) \
  { \
    uint32_t f_len = 0; \
    uchar_t *f_data = nullptr; \
    DESER_DATA(buf, cntr, f) \
    var = ::std::string((char_t *)f_data, f_len); \
    delete [] f_data; \
  } \

#define DESER_VEC_OF_UINT32(buf, cntr, var) \
  { \
    uint32_t vec_size = 0; \
    DESER_UINT32(buf, cntr, vec_size); \
    for (uint32_t i = 0; i < vec_size; i++) { \
      uint32_t value; \
      DESER_UINT32(buf, cntr, value); \
      var.push_back(value); \
    } \
  } \

#define DESER_VEC_OF_STRING(buf, cntr, var) \
  { \
    uint32_t vec_size = 0; \
    DESER_UINT32(buf, cntr, vec_size); \
    for (uint32_t i = 0; i < vec_size; i++) { \
      ::std::string value; \
      DESER_STRING(buf, cntr, value); \
      var.push_back(value); \
    } \
  } \

typedef char char_t;
typedef unsigned char uchar_t;

struct Buffer
{
  uchar_t *data = nullptr;
  uint32_t len = 0;

  static const Buffer fromVector(::std::vector<uchar_t> vec)
  {
    Buffer to_ret;
    to_ret.len = vec.size();
    to_ret.data = new uchar_t[to_ret.len];
    for (uint32_t i = 0; i < to_ret.len; i++)
    {
      to_ret.data[i] = vec[i];
    }
    return to_ret;
  }
};
