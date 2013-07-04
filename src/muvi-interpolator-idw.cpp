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

#include <cmath>
#include <boost/make_shared.hpp>

#include "muvi-exceptions.hpp"
#include "muvi-interpolator-idw.hpp"

/**
 * Calculate the Shepard's interpolation weight of point A and B, using the power parameter p
 */
muviNumber __weightAt (const MuviIndexValues& a, const MuviIndexValues& b, int p ) {

	// (Using static to optimize performance)
	vector<MuviValue>::const_iterator iterA = a->values.begin();
	vector<MuviValue>::const_iterator iterB = b->values.begin();
	
	// Calculate distance
	muviNumber ans = 0.0;

	for (; iterA != a->values.end(); iterA++, iterB++ ) {
		MuviValue valA = *iterA;
		MuviValue valB = *iterB;
		ans += pow( valB - valA , 2);
	}
	ans = sqrt( ans );

	// If distance is 0, return 0
	if (ans == 0) return 0;

	// Return 1/(d^p)
	return 1.0 / pow(ans, p);

}

/**
 * Linear interpolation of the given data
 */
int MuviIDWInterpolator::interpolate( const MuviNeighboursPtr& Neighbours, const MuviIndexValues& index, MuviDataValues ans ) {

	// Validate some sizes
	if (Neighbours->neighbourData.size() < 1)
		throw MuviException("Invalid Neighbours data size");
	if (Neighbours->neighbourIndex.size() < 1)
		throw MuviException("Invalid Neighbours index size");

	// Calculate data dimentions in the Neighbours (pick first one, assume everything is the same)
	MuviDataValues nFirstData = Neighbours->neighbourData[0];
	MuviDataValues nFirstIndex = Neighbours->neighbourIndex[0];
	int dataDimentions = nFirstData->values.size();
	int indexDimentions = nFirstIndex->values.size();

	// Validate indices
	if (dataDimentions != ans->size())
		throw MuviException("Answer buffer has not the same dimentions as Neighbours's");
	if (indexDimentions != index->size())
		throw MuviException("Index dimentions are not the same as neighbor's");

	// Iterators
	int i;
	vector<MuviDataValues>::const_iterator dnb;
	vector<MuviIndexValues>::const_iterator inb;
	vector<MuviValue>::iterator diter;

	// Calculate the Σ[j=0->N] of Wj(X)
	muviNumber total = 0.0;
	inb = Neighbours->neighbourIndex.begin();
	for (; inb != Neighbours->neighbourIndex.end(); inb++ ) {
		total += __weightAt( *inb, index, p );
	}

	// Build the response data vector
	bool * maxedOut = new bool[ dataDimentions ];
	for (i=0; i< dataDimentions; i++ ) {
		maxedOut[i] = false;
		ans->set(i, 0);
	}

	// Calculate the values of the data points
	dnb = Neighbours->neighbourData.begin();
	inb = Neighbours->neighbourIndex.begin();
	for (; inb != Neighbours->neighbourIndex.end(); inb++, dnb++ ) {

		// Fetch the neighbor data
		MuviDataValues nData = *dnb;

		// Iterate over neighbor data and update interpolated data
		i=0; diter = nData->values.begin();
		for (; diter != nData->values.end(); diter++, i++ ) {
			if (total != 0) { // Avoid division by zero errors
				muviNumber w = __weightAt( *inb, index, p );
				if (!maxedOut[i]) {
					if (w == 0) {
						ans->set(i, *diter);
						maxedOut[i] = true;
					} else {
						ans->append( i, ( w * *diter ) / total );
					}
				}
			}
		}

	}

	// Cleanup temp buffers
	delete maxedOut;

	// Succeeded
	return 0;

}