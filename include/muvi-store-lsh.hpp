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

#ifndef MUVI_STORE_LSH_H
#define MUVI_STORE_LSH_H

#include <vector>
#include "muvi-data.hpp"
#include "muvi-store.hpp"

using namespace std;

/**
 * Public interface to Multi-Variate-Interpolation data store
 */
class MuviStoreLSH : public MuviStore {
public:

	MuviStoreLSH() : MuviStore() { };
	MuviStoreLSH( 
			const MuviStoreAdapterPtr& adapter 
		) : MuviStore(adapter), resolution(0.01) { };
	MuviStoreLSH( 
			const MuviStoreAdapterPtr& adapter,				/* The I/O Adapter */
			muviNumber				   resolution 			/* The resolution of the grid */
		) : MuviStore(adapter), resolution(resolution) { };
	virtual ~MuviStoreLSH() { };

	/**
	 * Lookup nearest Neighbours around the given index
	 * @param count The number of nearest Neighbours to return. If 0, the number of dimentions of the values is used.
	 */
	virtual MuviNeighbours	findNearestNeighbours( const MuviIndexValues& index, int count = 0 );

	/**
	 * Write a value in the store
	 */
	virtual void			place( const MuviIndexValues& index, const MuviDataValues& values );

private:

	/**
	 * Calculate the hash of the given index
	 */
	string					calculateHash( const MuviIndexValues& index );

	/**
	 * Local variables
	 */
	muviNumber				resolution;

};


#endif /* End of include guard */
