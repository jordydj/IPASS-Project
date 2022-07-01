//          Copyright Jordy de jong 2022
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

/// @file

#ifndef GESTURESENSOR_HPP
#define GESTURESENSOR_HPP

#include "hwlib.hpp"
#include <bitset>
#include <string>

class Gesturesensor
{
private:
  hwlib::i2c_bus_bit_banged_scl_sda &bus;

//test variable. 
//1 = tests are running and values are shown
//0 = tests are off
  int test = 0;
  
//register adresses
  uint_fast8_t address = 0x39; //adress of apds 9960 done
  uint_fast8_t Enable_reg = 0x80; // done
  uint_fast8_t gconf1 = 0xA2;
  uint_fast8_t gconf2 = 0xA3;
  uint_fast8_t gconf3 = 0xAA;
  uint_fast8_t gconf4 = 0xAB;
  uint_fast8_t gpenth = 0xA0;
  uint_fast8_t gexth = 0xA1;
  uint_fast8_t goffset_u = 0xA4;
  uint_fast8_t goffset_d = 0xA5;
  uint_fast8_t goffset_l = 0xA7;
  uint_fast8_t goffset_r = 0xA9;
  uint_fast8_t gpulse = 0xA6;
  
//default values
  uint_fast8_t enable_gesture = 0b01000101;
  uint_fast8_t enable_gmode = 0b00000011;
  uint_fast8_t gconfig1_values = 0b00000010;
  uint_fast8_t gconfig3_values = 0b00000011;
  uint_fast8_t gconfig2_values = 0b01001001;
  uint_fast8_t gpulse_values = 0b11000111;
  uint_fast8_t gpenth_values = 0b00000000;
  uint_fast8_t gexth_values = 0b00000000;
  uint_fast8_t goffset_u_value = 0b00000000;
  uint_fast8_t goffset_d_value = 0b00000000;  
  uint_fast8_t goffset_l_value = 0b00000000;
  uint_fast8_t goffset_r_value = 0b00000000;
  
public:
	/// \brief
	/// Constructor
	/// \details
	/// This constructor creates a gesturesensor with default values 
	/// from an hwlib::i2c_bus_bit_banged_scl_sda bus
	Gesturesensor(hwlib::i2c_bus_bit_banged_scl_sda &bus);
	
	/// \brief
	/// Writes to registers in sensor
	/// \details
	/// Function writes given data to given register address
	virtual void write(uint8_t reg_address, uint8_t byte);
	
	/// \brief
	/// Reads register in sensor
	/// \details
	/// Function reads data from given register address
	virtual uint8_t read(uint8_t reg_address); 
	
	/// \brief
	/// Set the Gesture configuration 1 register
	/// \details
	/// Sets the value of Gesture config 1 register from
	/// 2 bits Gesture FIFO threshold value
	/// 4 bits Gesture exit mask value
	/// 2 bits Gesture exit persistence value
	void setGconf1(uint8_t & gexPers, uint8_t & gexMsk, uint8_t & gfifoTh);
	
	
	/// \brief
	/// Set the Gesture configuration 2 register
	/// \details
	/// Sets the value of Gesture config 2 register from
	/// 2 bits Gesture gain value
	/// 2 bits led drive strength value
	/// 3 bits Gesture wait time value
	void setGconf2(uint8_t & gGain, uint8_t &glDrive, uint8_t &gwTime);

	/// \brief
	/// Set the Gesture configuration 3 register
	/// \details
	/// Sets the value of Gesture config 3 register from
	/// 2 bit Gesture dimension select value 
	void setGconf3(uint8_t & gDims);
	
	/// \brief
	/// Reads the Gesture configuration 4 register
	/// \details
	/// Reads the Gesture config 4 register and returns if sensor is in Gesture mode
	/// 1 = on
	/// 0 = off
	uint8_t readGconf4();
	
	/// \brief
	/// Sets the Gesture proximity enter threshold register
	/// \details
	/// Sets the value of Gesture proximity enter threshold register from
	/// 8 bits Proximity enter threshold value
	void setGpenth(uint8_t & gPenth);
	
	/// \brief
	/// Sets the Gesture exit threshold register
	/// \details
	/// Sets the Gesture exit threshold register from
	/// 8 bits exit threshold value
	void setGexth(uint8_t & gExth);
	
	/// \brief
	/// Sets the Gesture offset up register
	/// \details
	/// Sets the Gesture offset up register from
	/// 8 bits offset value
	void setGoffset_u(uint8_t & gOffset_u);

	/// \brief
	/// Sets the Gesture offset down register
	/// \details
	/// Sets the Gesture offset down register from
	/// 8 bits offset value
	void setGoffset_d(uint8_t & gOffset_d);

	/// \brief
	/// Sets the Gesture offset left register
	/// \details
	/// Sets the Gesture offset left register from
	/// 8 bits offset value
	void setGoffset_l(uint8_t & gOffset_l);

	/// \brief
	/// Sets the Gesture offset right register
	/// \details
	/// Sets the Gesture offset right register from
	/// 8 bits offset value
	void setGoffset_r(uint8_t & gOffset_r);

	/// \brief 
	/// Sets Gesture pulse count and length register
	/// \details
	/// Sets Gesture pulse count and length register from
	/// 2 bits Gesture pulse length value
	/// 6 bits Gesture pulse count value
	void setGpulse(uint8_t & gPlen, uint8_t & gPulse);

	/// \brief 
	/// reads Gesture reading data from Gesture fifo data registers
	/// \details
	/// reads Gesture data from registers 0xFC to 0xFF and returns
	/// corresponding to movements like UP, DOWN, LEFT, RIGHT
	char readGesture();
	
	

};

#endif // GESTURESENSOR_HPP
