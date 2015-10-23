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

#include "muvi-store-lsh.hpp"
#include "muvi-neighbour-bin.hpp"

#include <cmath>
#include <sstream>
#include <string>

#include <boost/make_shared.hpp>

using namespace std;

/**
 * int-sized structure for fast conversion between integer value
 * and its 6-byte base64 representation.
 */
typedef union {
	struct {
		unsigned char 	a:6;
		unsigned char 	b:6;
		unsigned char 	c:6;
		unsigned char 	d:6;
		unsigned char 	e:6;
		unsigned char 	f:2;
	} b64;
	int 				value;
} fast_b64;

/**
 * Fast calculation of the checksum
 */
string MuviStoreLSH::calculateHash( const MuviIndexValues& index ) {

	// We use a slightly modified base64 character set
	static const char b64_table[65] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ+_";
	static fast_b64 fastb;

	// Preallocate the string
	string ans; ans.resize( index->values.size() * 6 );

	// Build the checksum
	int j=0;
	for (vector<MuviValue>::const_iterator i = index->values.begin(); i != index->values.end(); i++, j+=6) {
		MuviValue v = *i;

		// Fast conversion to base-64
		fastb.value = (int)floor( v / this->resolution );
		ans[j]   = b64_table[fastb.b64.a];
		ans[j+1] = b64_table[fastb.b64.b];
		ans[j+2] = b64_table[fastb.b64.c];
		ans[j+3] = b64_table[fastb.b64.d];
		ans[j+4] = b64_table[fastb.b64.e];
		ans[j+5] = b64_table[fastb.b64.f];

	}

	// Return base-64 answer
	return ans;
}

/**
 * Write a value in the store
 */
void MuviStoreLSH::place( const MuviIndexValues& index, const MuviDataValues& values ) {

	// Find the index key of the given values
	string key = this->calculateHash( index );

	// Initialize bin
	MuviNeighboursPtr neighbours = boost::make_shared<MuviNeighbours>();

	// Populate bin if we have previous data there
	istream * iStreamPtr = this->adapter->openReadStream( key );
	if (iStreamPtr != NULL) {
		MuviNeighbourBin::loadFromStream( neighbours, iStreamPtr );
		this->adapter->closeStream( iStreamPtr );
		iStreamPtr = NULL;
	}

	// Append the given data
	neighbours->add( values, index );

	// Save
	ostream * oStreamPtr = this->adapter->openWriteStream( key );
	if (oStreamPtr != NULL) {
		MuviNeighbourBin::saveToStream( neighbours, oStreamPtr );
		this->adapter->closeStream( oStreamPtr );
		oStreamPtr = NULL;
	}

};

/**
 * Find the given nearest neighbours
 * (For now, just pick the neighbors of the bucket)
 */
MuviNeighbours MuviStoreLSH::findNearestNeighbours( const MuviIndexValues& index, int count ) {

}
