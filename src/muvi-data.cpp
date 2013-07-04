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

#include <cstdarg>
#include <iostream>
#include "muvi-data.hpp"
using namespace std;

/**
 * Add a value to the MuviValues store
 */
void MuviValues::add( const MuviValue& v, float error) {
	this->values.push_back(v);
	this->errors.push_back(error);
};

/**
 * Set a value to the MuviValues store on the given index
 */
void MuviValues::set( int index, const MuviValue& v, float error) {
	this->values[index] = v;
	this->errors[index] = error;
};

/**
 * Return the value at the given index
 */
MuviValue MuviValues::at( int index ) {
	return this->values[index];
};

/**
 * Append data 
 */
MuviValue MuviValues::append( int index, const MuviValue& v, float error ) {
	this->errors[index] += error;
	return this->values[index] += v;
};

/**
 * Return the size of the value map
 */
int MuviValues::size() {
	return this->values.size();
}


/**
 * Visually dump the contents of the MuviValues object
 */
void MuviValues::dump() {
	vector<MuviValue>::iterator vit = this->values.begin();
	vector<float>::iterator uit = this->errors.begin();
	cout << "=[ MuviValues Object ]====================" << endl;
	for (; vit != this->values.end(); vit++, uit++) {
		float u = *uit;
		MuviValue v = *vit;

		cout << "- " << v << " (errors=" << u << ")" << endl;
	}
};

/**
 * Add a new neighbor information on the Neighbours list
 */
void MuviNeighbours::add( const MuviDataValues& data, const MuviIndexValues& index ) {
	this->neighbourData.push_back( data );
	this->neighbourIndex.push_back( index );
};

/**
 * Return the size of the neighbourData vector
 */
int MuviNeighbours::size() {
	return this->neighbourData.size();
}
