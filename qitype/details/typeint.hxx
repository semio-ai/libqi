#pragma once
/*
**  Copyright (C) 2013 Aldebaran Robotics
**  See COPYING for the license
*/

#ifndef _QITYPE_DETAILS_TYPEINT_HXX_
#define _QITYPE_DETAILS_TYPEINT_HXX_
#include <boost/type_traits/is_signed.hpp>

#include <qitype/typeinterface.hpp>

namespace qi {

  template<typename T>
  class IntTypeInterfaceImpl: public IntTypeInterface
  {
  public:
    typedef typename detail::TypeImplMethodsBySize<T>::type ImplType;

    virtual int64_t get(void* value) const
    {
      return *(T*)ImplType::Access::ptrFromStorage(&value);
    }

    virtual void set(void** storage, int64_t value)
    {
      *(T*)ImplType::Access::ptrFromStorage(storage) = (T)value;
    }

    virtual unsigned int size() const
    {
      return sizeof(T);
    }

    virtual bool isSigned() const
    {
      return boost::is_signed<T>::value;
    }

    _QI_BOUNCE_TYPE_METHODS(ImplType);
  };

  template<typename T> class TypeBoolImpl: public IntTypeInterface
  {
  public:
    typedef typename detail::TypeImplMethodsBySize<T>::type ImplType;

    virtual int64_t get(void* value) const
    {
      return *(T*)ImplType::Access::ptrFromStorage(&value);
    }

    virtual void set(void** storage, int64_t value)
    {
      *(T*)ImplType::Access::ptrFromStorage(storage) = (T)(value != 0);
    }

    virtual unsigned int size() const
    {
      return 0;
    }

    virtual bool isSigned() const
    {
      return 0;
    }

    _QI_BOUNCE_TYPE_METHODS(ImplType);
  };

}


namespace qi {


  template<typename T>
  class FloatTypeInterfaceImpl: public FloatTypeInterface
  {
  public:
    typedef typename detail::TypeImplMethodsBySize<T>::type ImplType;

    virtual double get(void* value) const
    {
      return *(T*)ImplType::Access::ptrFromStorage(&value);
    }

    virtual void set(void** storage, double value)
    {
      *(T*)ImplType::Access::ptrFromStorage(storage) = (T)value;
    }

    virtual unsigned int size() const
    {
      return sizeof(T);
    }

    _QI_BOUNCE_TYPE_METHODS(ImplType);
  };

}



#endif  // _QITYPE_DETAILS_TYPEINT_HXX_
