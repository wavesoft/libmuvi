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
#ifndef MUVI_ADAPTER_HTTP_CONFIG_H
#define MUVI_ADAPTER_HTTP_CONFIG_H

#include <string>
using namespace std;

#define MUVI_HTTP_GET		0
#define MUVI_HTTP_POST		1
#define MUVI_HTTP_PUT		3

/**
 * Base http class configuration
 */
class MuviHTTPConfig {
public:

	/**
	 * Parametrizable get/put URLs
	 */
	string 					putURL;
	string 					getURL;

	/**
	 * I/O Verb for each url
	 */
	unsigned char 			putVerb;
	unsigned char 			gutVerb;

	/**
	 
	 */

};

/**
 * RIAK-Preconfigured HTTP Configuration
 */
class MuviRiakHTTPConfig: 
	public MuviHTTPConfig {
public:

	MuviRiakHTTPConfig( const string& server, const string& bucket ) : MuviHTTPConfig() {
		this->getURL = "http://" + server + "/riak/" + bucket + "/$K";
		this->getVerb = MUVI_HTTP_GET;
		this->putURL = "http://" + server + "/riak/" + bucket + "/$K";
		this->putVerb = MUVI_HTTP_PUT;
	};

};

#endif /* End of include guard */
