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

#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include "muvi-adapter-disk.hpp"

 using namespace std;

/**
 * Returns true if the given file exists and is readable
 */
inline bool file_exists( const string& path_to_file )
 { return ifstream( (const char*)path_to_file.c_str()) ; };

/**
 * Open and start reading the given chunk
 */
istream * MuviAdapterDisk::openReadStream( const string& index ) {
	string fName = this->baseDir + "/" + index + ".chunk";
	if (!file_exists(fName)) {
		return NULL;
	} else {
		return new ifstream( fName.c_str(), ifstream::binary );
	}
}

/**
 * Set indexed chunk
 */
ostream * MuviAdapterDisk::openWriteStream( const string& index ) {
	string fName = this->baseDir + "/" + index + ".chunk";
	return new ofstream( fName.c_str(), ofstream::binary );
}

/**
 * Close a stream oppened with open*Stream
 */
void MuviAdapterDisk::closeStream( ios * stream ) {

	// Delete stream (this also closes the file.. i hope?)
	delete stream;

}