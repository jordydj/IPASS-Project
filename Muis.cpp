//          Copyright Jordy de jong 2022
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "Muis.hpp"

Muis::Muis(hwlib::i2c_bus_bit_banged_scl_sda &bus):
 bus(bus),
 sensor(bus)
{
}

void Muis::sendToLeonardo(){
	uint8_t offset_u = 0b00001111;
	uint8_t offset_d = 0b00001001;  
	uint8_t offset_l = 0b00001111;
	uint8_t offset_r = 0b00001001;
	

	sensor.setGoffset_u(offset_u);
	sensor.setGoffset_d(offset_d);
	sensor.setGoffset_l(offset_l);
	sensor.setGoffset_r(offset_r);
	char Result = sensor.readGesture();
	hwlib::cout << Result;
	{ hwlib::i2c_write_transaction wLeonardo = ((hwlib::i2c_bus*)(&bus))->write(address);
	wLeonardo.write(Result);}
	  

}


