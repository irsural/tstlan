#ifndef ERRORH
#define ERRORH

#include <irsdefs.h>

#include <irserror.h>

#include <irsfinal.h>

#define TL4_DEBUG

#ifdef TL4_DEBUG

#define TL4_ASSERT(assert_expr) IRS_ASSERT(assert_expr)
#define TL4_ASSERT_EX(assert_expr, msg) IRS_ASSERT_EX(assert_expr, msg)
#define TL4_ASSERT_MSG(msg) IRS_ASSERT_MSG(msg)

#define TL4_ERROR(error_code, msg) IRS_ERROR(error_code, msg)
#define TL4_ERROR_IF(assert_expr, error_code, msg)\
  IRS_ERROR_IF(assert_expr, error_code, msg)

#define TL4_DBG_RAW_MSG(msg) IRS_DBG_RAW_MSG(msg)
#define TL4_DBG_MSG(msg) IRS_DBG_MSG(msg)

#else //TL4_DEBUG

#define TL4_ASSERT(assert_expr)
#define TL4_ASSERT_EX(assert_expr, msg)
#define TL4_ASSERT_MSG(msg)

#define TL4_ERROR(error_code, msg)
#define TL4_ERROR_IF(assert_expr, error_code, msg)

#define TL4_DBG_RAW_MSG(msg)
#define TL4_DBG_MSG(msg)

#endif //TL4_DEBUG


#endif //ERRORH

