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

#ifndef MUVI_STORE_H
#define MUVI_STORE_H

#include <ios>
#include <sstream>
#include <istream>
#include <ostream>
#include <vector>

#include "muvi-data.hpp"

using namespace std;

class MuviStoreAdapter;
class MuviStore;
typedef boost::shared_ptr<MuviStore> 			MuviStorePtr;
typedef boost::shared_ptr<MuviStoreAdapter> 	MuviStoreAdapterPtr;


/**
 * Key/Value store adapter
 */
class MuviStoreAdapter {
public:

	MuviStoreAdapter() { };
	virtual ~MuviStoreAdapter() { };

	/**
	 * Open and start reading the given chunk
	 */
	virtual istream *		openReadStream( const string& index ) = 0;

	/**
	 * Set indexed chunk
	 */
	virtual ostream *		openWriteStream( const string& index ) = 0;

	/**
	 * Close a stream oppened with open*Stream
	 */
	virtual void 			closeStream( ios * stream ) = 0;

};

/**
 * Public interface to Multi-Variate-Interpolation data store
 */
class MuviStore {
public:

	MuviStore() : adapter() { };
	MuviStore( const MuviStoreAdapterPtr& adapter ) : adapter(adapter) { };
	virtual ~MuviStore() { };

	/**
	 * Lookup nearest Neighbours around the given index
	 * @param count The number of nearest Neighbours to return. If 0, the number of dimentions of the values is used.
	 */
	virtual MuviNeighbours	findNearestNeighbours( const MuviIndexValues& index, int count = 0 ) = 0;

	/**
	 * Write a value in the store
	 */
	virtual void			place( const MuviIndexValues& index, const MuviDataValues& values ) = 0;

protected:

	/**
	 * The adapter is accessible only internally
	 */
	MuviStoreAdapterPtr		adapter;

};


#endif /* End of include guard */
