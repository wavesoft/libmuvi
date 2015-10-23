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

#include "muvi-exceptions.hpp"
#include "muvi-neighbour-bin.hpp"

/**
 * Load from the given stream
 */
void MuviNeighbourBin::appendFromStream( MuviNeighboursPtr& neighbours, istream * streamptr ) {

	// Validate magic signature
	char m1,m2; // For making sure the data were written by us
	unsigned short m3; // To validate the endianess of the platform
	streamptr->read( &m1, 1 );
	streamptr->read( &m2, 1 );
	streamptr->read( (char *)&m3, sizeof(unsigned short) );
	if ((m1 != MAGIC_HDR_1) || (m2 != MAGIC_HDR_2) || (m3 != MAGIC_VER))
		throw MuviDataException("Incompatible data found in the stream");

	// Prepare store buffers
	unsigned int numNeighbors;
	unsigned int numDimensions;

	// Read the number of neighbours in the chunk
	streamptr->read( (char*)&numNeighbors, sizeof(unsigned int) );

	// Resize neighbour buffer
	neighbours->neighbourData.resize( neighbours->neighbourData.size() + numNeighbors);
	neighbours->neighbourIndex.resize( neighbours->neighbourIndex.size() + numNeighbors);

	// Start reading neighbor data
	for (unsigned int i=neighbours->neighbourIndex.size(); i<neighbours->neighbourIndex.size()+numNeighbors; i++) {

		// Allocate values & index buffer
		MuviDataValues dValues = boost::make_shared<MuviValues>();
		MuviIndexValues dIndex = boost::make_shared<MuviValues>();

		// Read the *INDEX* dimentions
		streamptr->read( (char*)&numDimensions, sizeof(unsigned int) );

		// Allocate and read the entire value & error vector
		dIndex->values.resize( numDimensions );
		dIndex->errors.resize( numDimensions );
		streamptr->read( (char*)dIndex->values.data(), numDimensions * sizeof(MuviValue) );
		streamptr->read( (char*)dIndex->errors.data(), numDimensions * sizeof(float) );

		// Read the *DATA* dimentions
		streamptr->read( (char*)&numDimensions, sizeof(unsigned int) );

		// Allocate and read the entire value & error vector
		dValues->values.resize( numDimensions );
		dValues->errors.resize( numDimensions );
		streamptr->read( (char*)dValues->values.data(), numDimensions * sizeof(MuviValue) );
		streamptr->read( (char*)dValues->errors.data(), numDimensions * sizeof(float) );

		// Store on neighbor store
		neighbours->neighbourData[i] = dValues;
		neighbours->neighbourIndex[i] = dIndex;
	}

}

/**
 * Load from the given stream
 */
void MuviNeighbourBin::loadFromStream( MuviNeighboursPtr& neighbours, istream * streamptr ) {

	// Reset neighbour buffer
	neighbours->neighbourData.clear();
	neighbours->neighbourIndex.clear();

	// Append neighbors
	this->appendFromStream( neighbours, streamptr );

}


/**
 * Save the given stream
 */
void MuviNeighbourBin::saveToStream( const MuviNeighboursPtr& neighbours, ostream * streamptr ) {
	vector<MuviValue>::iterator iv;
	vector<float>::iterator de;

	// Write magic signature
	char m1=MAGIC_HDR_1, m2=MAGIC_HDR_2; unsigned short m3=MAGIC_VER;
	streamptr->write( &m1, 1 );
	streamptr->write( &m2, 1 );
	streamptr->write( (char*)&m3, sizeof(unsigned short) );

	// Prepare store buffers
	unsigned int numNeighbors;
	unsigned int numDimensions;

	// Store the number of neighbors
	numNeighbors = neighbours->size();
	streamptr->write( (char*)&numNeighbors, sizeof(unsigned int) );

	// Start reading neighbor data
	vector<MuviDataValues>::iterator di = neighbours->neighbourData.begin();
	vector<MuviIndexValues>::iterator ii = neighbours->neighbourIndex.begin();
	for (; di != neighbours->neighbourData.end(); di++, ii++ ) {

		// Allocate items
		MuviDataValues dValues = *di;
		MuviIndexValues dIndex = *ii;

		// Store the *INDEX* dimentions
		numDimensions = dIndex->size();
		streamptr->write( (char*)&numDimensions, sizeof(unsigned int) );

		// Store the entire values & error vector in the stream
		streamptr->write( (char*)dIndex->values.data(), numDimensions * sizeof(MuviValue) );
		streamptr->write( (char*)dIndex->errors.data(), numDimensions * sizeof(float) );

		// Store the *DATA* dimentions
		numDimensions = dValues->size();
		streamptr->write( (char*)&numDimensions, sizeof(unsigned int) );

		// Store the entire values & error vector in the stream
		streamptr->write( (char*)dValues->values.data(), numDimensions * sizeof(MuviValue) );
		streamptr->write( (char*)dValues->errors.data(), numDimensions * sizeof(float) );

	}

}
