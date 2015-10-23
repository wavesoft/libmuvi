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

#ifndef MUVI_NEIGHBOUR_BIN_H
#define MUVI_NEIGHBOUR_BIN_H

#include <istream>
#include <ostream>

#include "muvi-data.hpp"

using namespace std;

/**
 * Magic header signature for the binary data
 */
#define MAGIC_HDR_1	'M'
#define MAGIC_HDR_2	'b'
#define MAGIC_VER	1

/**
 * Storage I/O Class that dumps or reads MuviNeighbours structures
 * WARNING! This class stores data in platform-dependant binary encoding!
 */
class MuviNeighbourBin {
public:

	/**
	 * Load from the given stream
	 */
	static void 				loadFromStream( MuviNeighboursPtr& neighbours, istream * streamptr );

	/**
	 * Append neighbors from the given stream
	 */
	static void 				appendFromStream( MuviNeighboursPtr& neighbours, istream * streamptr );

	/**
	 * Save the given stream
	 */
	static void					saveToStream( const MuviNeighboursPtr& neighbours, ostream * streamptr );

private:

	/**
	 * Private constructor -> Cannot instantiate
	 */
	MuviNeighbourBin() { };

};

#endif