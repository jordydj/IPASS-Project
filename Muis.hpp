//          Copyright Jordy de jong 2022
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

/// @file
#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Gesturesensor.hpp"

class Muis
{
private:
	uint8_t address = 127;
	hwlib::i2c_bus_bit_banged_scl_sda &bus;
	Gesturesensor sensor;
	
public:
	/// \brief
	/// Constructor
	/// \details
	/// This constructor creates a Mouse from an hwlib::i2c_bus_bit_banged_scl_sda bus
	Muis(hwlib::i2c_bus_bit_banged_scl_sda &bus);
	
	/// \brief
	/// This function sends information to Arduino Leonardo
	/// \details
	/// This function receives data from gesturesensor sensor
	/// and sends the data to the Arduino Leonardo via I2C
	 
	void sendToLeonardo();
	
};

#endif // MOUSE_HPP
