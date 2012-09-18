/*
**
** Copyright (C) 2012 Aldebaran Robotics
*/

#include <qimessaging/metamethod.hpp>

namespace qi {


  MetaFunctionResult callFunction(GenericFunction val,
    const MetaFunctionParameters& parameters)
  {
    if (parameters.getMode() == MetaFunctionParameters::Mode_GenericValue)
    {
      // Let call() handle conversion
      GenericValue res = val.call(parameters.getValues());
      return MetaFunctionResult(res);
    }
    else
    {
      IDataStream in(parameters.getBuffer());
      const std::vector<Type*>& argTypes = val.type->argumentsType();
      std::vector<GenericValue> args;
      for (unsigned i=0; i<argTypes.size(); ++i)
      {
        GenericValue v;
        v.type = argTypes[i];
        v.value = v.type->deserialize(in);
        args.push_back(v);
      }
      GenericValue res = val.call(args);
      for (unsigned i=0; i<args.size(); ++i)
        args[i].destroy();
      return MetaFunctionResult(res);
    }
  }

  MetaFunctionResult callMethod(GenericMethod val,
    GenericValue instance, const MetaFunctionParameters& parameters)
  {
    if (parameters.getMode() == MetaFunctionParameters::Mode_GenericValue)
    {
      const std::vector<GenericValue>& v = parameters.getValues();
      std::vector<GenericValue> bindSelf;
      bindSelf.push_back(instance);
      bindSelf.insert(bindSelf.end(), &v[0], &v[v.size()]);

      // Let call() handle conversion
      GenericValue res = val.toFunction().call(bindSelf);
      return MetaFunctionResult(res);
    }
    else
    {
      IDataStream in(parameters.getBuffer());
      const std::vector<Type*>& argTypes = val.type->argumentsType();
      std::vector<GenericValue> args;
      args.push_back(instance);
      for (unsigned i=1; i<argTypes.size(); ++i)
      {
        GenericValue v;
        v.type = argTypes[i];
        v.value = v.type->deserialize(in);
        args.push_back(v);
      }
      GenericValue res = val.toFunction().call(args);
      for (unsigned i=1; i<args.size(); ++i)
        args[i].destroy();
      return MetaFunctionResult(res);
    }
  }

  MetaCallable makeCallable(GenericFunction value)
  {
    return boost::bind(&callFunction, value, _1);
  }

  MetaMethod::MetaMethod(unsigned int uid,
    const std::string& sigret,
    const std::string& signature)
  : _uid(uid)
  , _signature(signature)
  , _sigreturn(sigret)
  {}

  std::string MetaMethod::signature() const
  {
    return _signature;
  }

  std::string MetaMethod::sigreturn() const
  {
    return _sigreturn;
  }

  unsigned int       MetaMethod::uid() const
  {
    return _uid;
  }

  qi::ODataStream &operator<<(qi::ODataStream &stream, const MetaMethod &meta) {
    stream << meta.signature()
           << meta.sigreturn()
           << meta.uid();
    return stream;
  }

  qi::IDataStream &operator>>(qi::IDataStream &stream, MetaMethod &meta) {
    unsigned int uid;
    std::string signature, sigret;
    stream >> signature >> sigret >> uid;
    meta = MetaMethod( uid, sigret, signature);
    return stream;
  }

  qi::SignatureStream &operator&(qi::SignatureStream &stream, const MetaMethod &meta) {
    stream & meta.signature();
    stream & meta.sigreturn();
    stream & meta.uid();
    return stream;
  }

};
