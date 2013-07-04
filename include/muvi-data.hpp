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

#ifndef MUVI_DATA_H
#define MUVI_DATA_H

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/variant.hpp>
using namespace std;

/**
 * Type definitions
 */
class 										MuviValues;
class 										MuviNeighbours;
typedef boost::shared_ptr<MuviValues> 		MuviValuesPtr;
typedef boost::shared_ptr<MuviNeighbours> 	MuviNeighboursPtr;
//typedef boost::variant<int, float, double>	MuviValue;
typedef MuviValuesPtr						MuviDataValues;
typedef MuviValuesPtr 						MuviIndexValues;
typedef float								MuviValue;

/**
 * Project-wide presicion variable
 */
#define muviNumber	 						double

/**
 * A series of values
 */
class MuviValues {
public:
	
	/**
	 * Constructor and copy
	 */
	MuviValues() : values(), errors() { };
	MuviValues( const MuviValues& v ) : values(v.values), errors(v.errors) { };
	MuviValues( int elements ) : values(), errors() {
		for (int i=0; i<elements; i++) {
			values.push_back(0.0); errors.push_back(1.0);
		}
	};
	virtual ~MuviValues() { };

	/** 
     * MuviValues class contains a list of values
	 */
	vector<MuviValue>	values;

	/**
	 * The errors of the given values
	 */
	vector<float>		errors;

	/**
	 * Store a value in the muvi values store
	 */
	void				add( const MuviValue& v, float error = 1.0 );

	/**
	 * Update a value in the muvi values store
	 */
	void				set( int index, const MuviValue& v, float error = 1.0 );

	/**
	 * Get the value at the given index
	 */
	MuviValue 			at( int index );

	/**
	 * Append the specified value at the given index and return the result
	 */
	MuviValue 			append( int index, const MuviValue& v, float error = 1.0 );

	/**
	 * Get the number of elements inside
	 */
	int 				size();

	// Debug function to dump the contents to stdout
	void				dump();

};

/**
 * A list of nearby Neighbours of a value
 */
class MuviNeighbours {
public:

	MuviNeighbours() : neighbourData(), neighbourIndex() { };
	virtual ~MuviNeighbours() { };

	/**
	 * The nearby index and values
	 */
	vector<MuviDataValues>	neighbourData;
	vector<MuviIndexValues>	neighbourIndex;

	/**
	 * Store the given neighbor/index information in the database
	 */
	void				add( const MuviDataValues& data, const MuviIndexValues& index );

	/**
	 * Get the number of elements inside
	 */
	int 				size();

};

#endif /* End of include guard */
