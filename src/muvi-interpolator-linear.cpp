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
#include <boost/make_shared.hpp>
#include "muvi-interpolator-linear.hpp"

/**
 * Linear interpolation of the given data
 */
int MuviLinearInterpolator::interpolate( const MuviNeighboursPtr& Neighbours, const MuviIndexValues& index, MuviDataValues ans ) {
	
	// We assume that the lookup function did good job on finding the
	// proper Neighbours. So we are just doing interpolation over their 2 values.

	// Pick the 2 nearby Neighbours
	MuviDataValues d1 = Neighbours->neighbourData[0];
	MuviDataValues d2 = Neighbours->neighbourData[1];
	MuviIndexValues i1 = Neighbours->neighbourIndex[0];
	MuviIndexValues i2 = Neighbours->neighbourIndex[1];

	// Calculate the mean weight
	float weight = 0;
	int weightVal = 0;

	vector<MuviValue>::iterator it1 = i1->values.begin();
	vector<MuviValue>::iterator it2 = i2->values.begin();
	vector<MuviValue>::const_iterator it3 = index->values.begin();
	for (; it1 != i1->values.end(); it1++, it2++, it3++ ) {

		// Get the indices
		MuviValue v1 = *it1;
		MuviValue v2 = *it2;
		MuviValue v3 = *it3;

		// Calculate the distance from index
		float w =  (v3 - v1) / (v2 - v1);
		weight += w;
		weightVal++;

	}

	// Calculate weight
	weight /= weightVal;

	// Apply interpolation on the values, using the given weight
	bool first = true;
	MuviValue maxW, minW;

	// Calculate min/max for normalization
	it1 = d1->values.begin();
	it2 = d2->values.begin();
	for (; it1 != d1->values.end(); it1++, it2++, it3++ ) {
		MuviValue v1 = *it1;
		MuviValue v2 = *it2;

		// Calculate ranges for normalization
		MuviValue w = v2-v1;
		if (first) {
			minW = w; maxW = w;
		} else {
			if (w<minW) minW=w;
			if (w>maxW) maxW=w;
		}
	}	

	// Run again, calculating the answer
	it1 = d1->values.begin();
	it2 = d2->values.begin();
	for (; it1 != d1->values.end(); it1++, it2++, it3++ ) {
		MuviValue v1 = *it1;
		MuviValue v2 = *it2;

		// Weighted answers
		MuviValue w = v2-v1;


		// Calculate answer
		MuviValue vans = (v2 - v1) * weight + v1;
		ans->add( vans );
	}

	// Everything was OK
	return 0;

}
