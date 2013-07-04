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

#ifndef MUVI_INTERPOLATOR_H
#define MUVI_INTERPOLATOR_H

#include "muvi-data.hpp"

/**
 * Base class of the Muvi Interpolator
 */
class MuviInterpolator {
public:

	MuviInterpolator() { };
	virtual ~MuviInterpolator() { };

	/**
	 * Interpolation function
	 */
	virtual int 			interpolate( const MuviNeighboursPtr& Neighbours, const MuviIndexValues& index, MuviDataValues ans ) = 0;

};

#endif /* End of include guard */
