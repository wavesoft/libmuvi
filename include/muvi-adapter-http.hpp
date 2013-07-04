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
#ifndef MUVI_ADAPTER_HTTP_H
#define MUVI_ADAPTER_HTTP_H

#include <curl/curl.h>
#include <vector>

#include "muvi-data.hpp"
#include "muvi-store.hpp"

using namespace std;

/**
 * Simple file-based disk store
 */
class MuviAdapterHTTP: 
	public MuviStoreAdapter {
public:

	MuviAdapterHTTP( const string& baseDir );
	virtual ~MuviAdapterHTTP();

	/**
	 * Open and start reading the given chunk
	 */
	virtual istream *		openReadStream( const string& index );

	/**
	 * Set indexed chunk
	 */
	virtual ostream *		openWriteStream( const string& index );

	/**
	 * Close a stream oppened with open*Stream
	 */
	virtual void 			closeStream( ios * stream );

private:

	/**
	 * Curl object to perform I/O
	 */
	CURL *					curl;

};

#endif /* End of include guard */

