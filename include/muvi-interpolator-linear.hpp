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
#ifndef MUVI_INTERPOLATOR_LINEAR_H
#define MUVI_INTERPOLATOR_LINEAR_H

#include "muvi-interpolator.hpp"

/**
 * Linear interpolator
 */

class MuviLinearInterpolator :
	 public MuviInterpolator {
public:

	MuviLinearInterpolator() : MuviInterpolator() { };
	virtual ~MuviLinearInterpolator() { };

	/**
	 * Perform linear interpolation using the given Neighbours and index
	 */
	virtual int 			interpolate( const MuviNeighboursPtr& Neighbours, const MuviIndexValues& index, MuviDataValues ans );

};

#endif /* End of include guard */
