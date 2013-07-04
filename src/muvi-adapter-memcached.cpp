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

#include <streambuf>
#include <iostream>
#include <sstream>

#include "muvi-adapter-memcached.hpp"

using namespace std;

/**
 * Memcache I/O buffer
 */
class memcachebuf : public streambuf
{
public:

	/**
	 * Constructor of the memcache I/O buffer
	 */
	memcachebuf( memcached_st* memc, const string& key ) :
		memc(memc), key(key.c_str()), sbuf("") { }

	/**
	 * Synchronize on destructor
	 */
	virtual ~memcachebuf() {
		this->sync();
	}

	/**
	 * OUT: Write data to the given buffer
	 */
	streamsize xsputn (const char* s, streamsize n) {
		sbuf.append(s,n);
		return n;
	}

	/**
	 * Syncrhonize key
	 */
	int sync() {
		memcached_return_t rc= memcached_set(memc, key, strlen(key), sbuf.c_str(), sbuf.length(), (time_t)0, (uint32_t)0);
		if (rc != MEMCACHED_SUCCESS) {
			return -1;
		} else {
			return 0;
		}
	}


private:

	/**
	 * Local properties
	 */
	memcached_st* 	memc;
	const char *	key;
	string			sbuf;

};

/**
 * Constructor and connect to memcache server
 */
MuviAdapterMemcached::MuviAdapterMemcached( const string& config ) 
	: MuviStoreAdapter(), config(config)
{
	memc = memcached( config.c_str(), config.length() );
};

/**
 * Destruct and cleanup
 */
MuviAdapterMemcached::~MuviAdapterMemcached() {
	memcached_free(memc);
}

/**
 * Open and start reading the given chunk
 */
istream * MuviAdapterMemcached::openReadStream( const string& index ) {
	memcached_return_t rc = memcached_exist(memc, index.c_str(), index.length());
	if (rc == MEMCACHED_SUCCESS) {

		// Try to fetch data
		size_t size;
		uint32_t flags;
		char * data = memcached_get( memc, index.c_str(), index.length(), &size, &flags, &rc );

		// If we are good, store it to a new string
		if (rc == MEMCACHED_SUCCESS) {

			// Return a string buffer
			string buffer; buffer.append( data, size );
			stringbuf * strBuf = new stringbuf( buffer );
			return new istream( strBuf );

		} else {
			return NULL;
		}

	} else {
		return NULL;
	}
}

/**
 * Set indexed chunk
 */
ostream * MuviAdapterMemcached::openWriteStream( const string& index ) {
	return new ostream( new memcachebuf( memc, index ) );
}

/**
 * Close a stream oppened with open*Stream
 */
void MuviAdapterMemcached::closeStream( ios * stream ) {
	delete stream->rdbuf();
	delete stream;
}

