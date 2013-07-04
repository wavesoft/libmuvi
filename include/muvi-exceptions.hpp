/**
 * This file is part of the Multivariate Interpolation Library.
 *
 * CVMWebAPI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * CVMWebAPI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with CVMWebAPI. If not, see <http://www.gnu.org/licenses/>.
 *
 * Developed by Ioannis Charalampidis 2013
 * Contact: <ioannis.charalampidis[at]cern.ch>
 */

#ifndef MUVI_EXCEPTIONS_H
#define MUVI_EXCEPTIONS_H

#include <string>
#include <exception>
 
using namespace std;

/**
 * Basic exception
 */
class MuviException: public exception {
public:
	
	// Constructor
	MuviException () : exception(), whatStr("") { };
	MuviException (const string& whatStr ) : exception(), whatStr(whatStr) { };
	~MuviException() throw() { };

	// Description fetching	
	virtual const char* what() const throw() { return whatStr.c_str(); };

private:

	// The message of the exception
	string			whatStr;

};


/**
 * Data I/O Exception
 */
class MuviDataException: public MuviException {
public:

	// Constructor
	MuviDataException () : MuviException() { };
	MuviDataException (const string& whatStr ) : MuviException(whatStr) { };
	~MuviDataException() throw() { };

};

/**
 * Data I/O Exception
 */
class MuviUsageException: public MuviException {
public:

	// Constructor
	MuviUsageException () : MuviException() { };
	MuviUsageException (const string& whatStr ) : MuviException(whatStr) { };
	~MuviUsageException() throw() { };

};

#endif