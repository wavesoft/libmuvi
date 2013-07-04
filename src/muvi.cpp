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
#include <ctime>
#include <cstdio>
#include <iostream>
#include <Magick++.h> 

#include <boost/make_shared.hpp>

#include "muvi-data.hpp"
#include "muvi-store-lsh.hpp"
#include "muvi-adapter-disk.hpp"
#include "muvi-adapter-memcached.hpp"
#include "muvi-interpolator-idw.hpp"

using namespace Magick; 

void render2D( const MuviNeighboursPtr& Neighbours, MuviInterpolator& ip ) {
	InitializeMagick( NULL );

	MuviIndexValues index = boost::make_shared<MuviValues>(32);
	MuviDataValues dat = boost::make_shared<MuviValues>(84);

	Image image("100x100", "white");
	for (int y=0; y<100; y++) {
		index->set(1, y/100.0f);
		for (int x=0; x<100; x++) {
			index->set(0, x/100.0f);
			ip.interpolate( Neighbours, index, dat );
			image.pixelColor(x,y, ColorRGB ( dat->at(0), dat->at(1), dat->at(2) ));
		}
	}

	image.write( "interpolation.png" ); 

}

/**
 * Test function entry point
 */
int main(int argc, char ** argv) {

	srand (time(NULL));

	MuviStoreAdapterPtr memcached = boost::make_shared<MuviAdapterMemcached>( "--BINARY-PROTOCOL --SERVER=localhost" );
	MuviStoreAdapterPtr disk = boost::make_shared<MuviAdapterDisk>("/home/devin/develop/muvi/build/data");
	
	MuviStoreLSH  		store( memcached, 0.5f );

	MuviDataValues 		data = boost::make_shared<MuviValues>(84);
	MuviIndexValues 	index = boost::make_shared<MuviValues>(20);

	// Populate the data store with random data
	for (int j=0; j<50000; j++) {
		
		for (int i=0; i<84; i++) {
			data->set(i, 1-((float)rand()/(float)RAND_MAX)*2 );
		}
		for (int i=0; i<20; i++) {
			index->set(i, 1-((float)rand()/(float)RAND_MAX)*2 );
		}

		store.place( index, data );
	}

	return 0;
}