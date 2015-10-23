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

#include "muvi-adapter-http.hpp"

/**
 * Memcache I/O buffer
 */
class httpbuf : public streambuf
{
public:

	/**
	 * Constructor of the memcache I/O buffer
	 */
	httpbuf( CURL* curl, const MuviHTTPConfig& config ) :
		memc(memc), curl(curl), config(config), sbuf("") { }

	/**
	 * Synchronize on destructor
	 */
	virtual ~httpbuf() {
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
	CURL *					curl;
	const MuviHTTPConfig	config;
	string					sbuf;

};

/**
 * Initialize CURL on constructor
 */
MuviAdapterHTTP::MuviAdapterHTTP( const MuviHTTPConfig& config ) :
	MuviStoreAdapter(), config(config) 
{
	curl = curl_easy_init();
}

/**
 * Cleanup CURL on destructor
 */
MuviAdapterHTTP::~MuviAdapterHTTP() {
	curl_free( curl );
}

