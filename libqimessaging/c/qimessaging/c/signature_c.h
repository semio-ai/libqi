/*
**
** Author(s):
**  - Cedric GESTES <gestes@aldebaran-robotics.com>
**
** Copyright (C) 2010, 2011 Aldebaran Robotics
*/

#ifndef _QIMESSAGING_SIGNATURE_H_
# define _QIMESSAGING_SIGNATURE_H_

# include <qimessaging/c/api_c.h>

# ifdef __cplusplus
extern "C"
{
# endif

enum qi_signature_type {
  QI_NONE       = 0,
  QI_BOOL       = 'b',

  QI_VOID       = 'v',

  QI_CHAR       = 'c',
  QI_UCHAR      = 'C',

  QI_SHORT      = 'w',
  QI_USHORT     = 'W',

  QI_INT        = 'i',
  QI_UINT       = 'I',

  QI_LONG       = 'l',
  QI_ULONG      = 'L',

  QI_FLOAT      = 'f',
  QI_DOUBLE     = 'd',

  QI_STRING     = 's',
  QI_LIST       = '[',
  QI_LIST_END   = ']',

  QI_MAP        = '{',
  QI_MAP_END    = '}',

  QI_TUPPLE     = '(',
  QI_TUPPLE_END = ')',

  QI_MESSAGE    = 'm',

  QI_RAW        = 'r',

  QI_UNKNOWN    = 'X',
  QI_POINTER    = '*'
};

typedef struct qi_signature_t_s qi_signature_t;

QIMESSAGING_API qi_signature_t*        qi_signature_create(const char *signature);
QIMESSAGING_API qi_signature_t*        qi_signature_create_subsignature(const char *signature);
QIMESSAGING_API void                   qi_signature_destroy(qi_signature_t *sig);

QIMESSAGING_API int                    qi_signature_count(qi_signature_t *sig);
QIMESSAGING_API int                    qi_signature_next(qi_signature_t *sig);
QIMESSAGING_API const char*            qi_signature_current(qi_signature_t *sig);
QIMESSAGING_API enum qi_signature_type qi_signature_current_type(qi_signature_t *sig);
QIMESSAGING_API int                    qi_signature_is_pointer(const qi_signature_t *sig);
QIMESSAGING_API int                    qi_signature_get_name(const char *complete_sig, char *buffer, int size);
QIMESSAGING_API int                    qi_signature_get_return(const char *complete_sig, char *buffer, int size);
QIMESSAGING_API int                    qi_signature_get_params(const char *complete_sig, char *buffer, int size);


# ifdef __cplusplus
}
# endif

#endif  // _QIMESSAGING_SIGNATURE_H_
