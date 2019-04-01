//
// Exception.cpp
//
// Library: Foundation
// Package: Core
// Module:  Exception
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/Exception.h"
#include "Poco/NestedDiagnosticContext.h"
#include <typeinfo>


namespace Poco {


Exception::Exception(int otherCode): _pNested(0), _code(otherCode)
{
	addBacktrace();
}


Exception::Exception(const std::string& msg, int otherCode):
	_msg(msg),
	_pNested(0),
	_code(otherCode)
{
	addBacktrace();
}


Exception::Exception(const std::string& msg, const std::string& arg, int otherCode):
	_msg(msg),
	_pNested(0),
	_code(otherCode)
{
	if (!arg.empty())
	{
		_msg.append(": ");
		_msg.append(arg);
	}
	addBacktrace();
}


Exception::Exception(const std::string& msg, const Exception& nestedException, int otherCode):
	_msg(msg),
	_pNested(nestedException.clone()),
	_code(otherCode)
{
	addBacktrace();
}


Exception::Exception(const Exception& exc):
	std::exception(exc),
	_msg(exc._msg),
	_code(exc._code)
{
	_pNested = exc._pNested ? exc._pNested->clone() : 0;
}


Exception::~Exception() throw()
{
	delete _pNested;
}


Exception& Exception::operator = (const Exception& exc)
{
	if (&exc != this)
	{
		Exception* newPNested = exc._pNested ? exc._pNested->clone() : 0;
		delete _pNested;
		_msg     = exc._msg;
		_pNested = newPNested;
		_code    = exc._code;
	}
	return *this;
}


const char* Exception::name() const throw()
{
	return "Exception";
}


const char* Exception::className() const throw()
{
	return typeid(*this).name();
}


const char* Exception::what() const throw()
{
	return msg().c_str();//name();
}


std::string Exception::displayText() const
{
	std::string txt;
	if (!_msg.empty()) txt.append(msg());
	else txt = name();
	return txt;
}


void Exception::extendedMessage(const std::string& arg)
{
	if (!arg.empty())
	{
		if (!_msg.empty()) _msg.append(": ");
		_msg.append(arg);
	}
}


void Exception::addBacktrace()
{
#ifdef POCO_EXCEPTION_BACKTRACE
	if (NDC::hasBacktrace())
	{
		_msg.append(1, '\n').append(NDC::backtrace(2, 3));
	}
#endif
}


Exception* Exception::clone() const
{
	return new Exception(*this);
}


void Exception::rethrow() const
{
	throw *this;
}


POCO_IMPLEMENT_EXCEPTION(LogicException, Exception, "Logic exception")
POCO_IMPLEMENT_EXCEPTION(AssertionViolationException, LogicException, "Assertion violation")
POCO_IMPLEMENT_EXCEPTION(NullPointerException, LogicException, "Null pointer")
POCO_IMPLEMENT_EXCEPTION(NullValueException, LogicException, "Null value")
POCO_IMPLEMENT_EXCEPTION(BugcheckException, LogicException, "Bugcheck")
POCO_IMPLEMENT_EXCEPTION(InvalidArgumentException, LogicException, "Invalid argument")
POCO_IMPLEMENT_EXCEPTION(NotImplementedException, LogicException, "Not implemented")
POCO_IMPLEMENT_EXCEPTION(RangeException, LogicException, "Out of range")
POCO_IMPLEMENT_EXCEPTION(IllegalStateException, LogicException, "Illegal state")
POCO_IMPLEMENT_EXCEPTION(InvalidAccessException, LogicException, "Invalid access")
POCO_IMPLEMENT_EXCEPTION(SignalException, LogicException, "Signal received")
POCO_IMPLEMENT_EXCEPTION(UnhandledException, LogicException, "Unhandled exception")

POCO_IMPLEMENT_EXCEPTION(RuntimeException, Exception, "Runtime exception")
POCO_IMPLEMENT_EXCEPTION(NotFoundException, RuntimeException, "Not found")
POCO_IMPLEMENT_EXCEPTION(ExistsException, RuntimeException, "Exists")
POCO_IMPLEMENT_EXCEPTION(TimeoutException, RuntimeException, "Timeout")
POCO_IMPLEMENT_EXCEPTION(SystemException, RuntimeException, "System exception")
POCO_IMPLEMENT_EXCEPTION(RegularExpressionException, RuntimeException, "Error in regular expression")
POCO_IMPLEMENT_EXCEPTION(LibraryLoadException, RuntimeException, "Cannot load library")
POCO_IMPLEMENT_EXCEPTION(LibraryAlreadyLoadedException, RuntimeException, "Library already loaded")
POCO_IMPLEMENT_EXCEPTION(NoThreadAvailableException, RuntimeException, "No thread available")
POCO_IMPLEMENT_EXCEPTION(PropertyNotSupportedException, RuntimeException, "Property not supported")
POCO_IMPLEMENT_EXCEPTION(PoolOverflowException, RuntimeException, "Pool overflow")
POCO_IMPLEMENT_EXCEPTION(NoPermissionException, RuntimeException, "No permission")
POCO_IMPLEMENT_EXCEPTION(OutOfMemoryException, RuntimeException, "Out of memory")
POCO_IMPLEMENT_EXCEPTION(DataException, RuntimeException, "Data error")

POCO_IMPLEMENT_EXCEPTION(InterruptedException, RuntimeException, "Interrupted")
POCO_IMPLEMENT_EXCEPTION(IndexOutOfBoundsException, RuntimeException, "Index out of bounds")
POCO_IMPLEMENT_EXCEPTION(UnsupportedOperationException, RuntimeException, "Unsupported operation")
POCO_IMPLEMENT_EXCEPTION(EmptyStackException, RuntimeException, "Empty stack")
POCO_IMPLEMENT_EXCEPTION(StackOverflowException, RuntimeException, "Stack overflow")
POCO_IMPLEMENT_EXCEPTION(ArithmeticException, RuntimeException, "Arithmetic error")

POCO_IMPLEMENT_EXCEPTION(DataFormatException, DataException, "Bad data format")
POCO_IMPLEMENT_EXCEPTION(SyntaxException, DataException, "Syntax error")
POCO_IMPLEMENT_EXCEPTION(CircularReferenceException, DataException, "Circular reference")
POCO_IMPLEMENT_EXCEPTION(PathSyntaxException, SyntaxException, "Bad path syntax")
POCO_IMPLEMENT_EXCEPTION(IOException, RuntimeException, "I/O error")
POCO_IMPLEMENT_EXCEPTION(ProtocolException, IOException, "Protocol error")
POCO_IMPLEMENT_EXCEPTION(FileException, IOException, "File access error")
POCO_IMPLEMENT_EXCEPTION(FileExistsException, FileException, "File exists")
POCO_IMPLEMENT_EXCEPTION(FileNotFoundException, FileException, "File not found")
POCO_IMPLEMENT_EXCEPTION(PathNotFoundException, FileException, "Path not found")
POCO_IMPLEMENT_EXCEPTION(FileReadOnlyException, FileException, "File is read-only")
POCO_IMPLEMENT_EXCEPTION(FileAccessDeniedException, FileException, "Access to file denied")
POCO_IMPLEMENT_EXCEPTION(CreateFileException, FileException, "Cannot create file")
POCO_IMPLEMENT_EXCEPTION(OpenFileException, FileException, "Cannot open file")
POCO_IMPLEMENT_EXCEPTION(WriteFileException, FileException, "Cannot write file")
POCO_IMPLEMENT_EXCEPTION(ReadFileException, FileException, "Cannot read file")
POCO_IMPLEMENT_EXCEPTION(DirectoryNotEmptyException, FileException, "Directory not empty")
POCO_IMPLEMENT_EXCEPTION(UnknownURISchemeException, RuntimeException, "Unknown URI scheme")
POCO_IMPLEMENT_EXCEPTION(TooManyURIRedirectsException, RuntimeException, "Too many URI redirects")
POCO_IMPLEMENT_EXCEPTION(URISyntaxException, SyntaxException, "Bad URI syntax")

POCO_IMPLEMENT_EXCEPTION(ApplicationException, Exception, "Application exception")
POCO_IMPLEMENT_EXCEPTION(BadCastException, RuntimeException, "Bad cast exception")


} // namespace Poco