//          Copyright Jordy de jong 2022
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#include "Gesturesensor.hpp"


Gesturesensor::Gesturesensor(hwlib::i2c_bus_bit_banged_scl_sda &bus):
	bus(bus)
{
	{ hwlib::i2c_write_transaction setgpenth = ((hwlib::i2c_bus*)(&bus))->write(address);
      setgpenth.write(gpenth);
	  setgpenth.write(gpenth_values);}
	  
  { hwlib::i2c_write_transaction setgexth = ((hwlib::i2c_bus*)(&bus))->write(address);
      setgexth.write(gexth);
	  setgexth.write(gexth_values);}

  { hwlib::i2c_write_transaction setgconfig1 = ((hwlib::i2c_bus*)(&bus))->write(address);
      setgconfig1.write(gconf1);
	  setgconfig1.write(gconfig1_values);}

  { hwlib::i2c_write_transaction setgconfig3 = ((hwlib::i2c_bus*)(&bus))->write(address);
      setgconfig3.write(gconf3);
	  setgconfig3.write(gconfig3_values);}
	  
  { hwlib::i2c_write_transaction setgconfig2 = ((hwlib::i2c_bus*)(&bus))->write(address);
      setgconfig2.write(gconf2);
	  setgconfig2.write(gconfig2_values);}
  
  { hwlib::i2c_write_transaction setgpulse = ((hwlib::i2c_bus*)(&bus))->write(address);
      setgpulse.write(gpulse);
	  setgpulse.write(gpulse_values);}
	  
  { hwlib::i2c_write_transaction setoffset_u = ((hwlib::i2c_bus*)(&bus))->write(address);
      setoffset_u.write(goffset_u);
	  setoffset_u.write(goffset_u_value);}

  { hwlib::i2c_write_transaction setoffset_d = ((hwlib::i2c_bus*)(&bus))->write(address);
      setoffset_d.write(goffset_d);
	  setoffset_d.write(goffset_d_value);}
	  
  { hwlib::i2c_write_transaction setoffset_l = ((hwlib::i2c_bus*)(&bus))->write(address);
      setoffset_l.write(goffset_l);
	  setoffset_l.write(goffset_l_value);}
	  
  { hwlib::i2c_write_transaction setoffset_r = ((hwlib::i2c_bus*)(&bus))->write(address);
      setoffset_r.write(goffset_r);
	  setoffset_r.write(goffset_r_value);}
	  
  { hwlib::i2c_write_transaction genable = ((hwlib::i2c_bus*)(&bus))->write(address);
      genable.write(Enable_reg);
	  genable.write(enable_gesture);}
	  
  { hwlib::i2c_write_transaction gmodeenable = ((hwlib::i2c_bus*)(&bus))->write(address);
      gmodeenable.write(gconf4);
	  gmodeenable.write(enable_gmode);}
}
	
//-----------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------
	
	void Gesturesensor::write(uint8_t reg_address, uint8_t byte){
	  { hwlib::i2c_write_transaction setgconfig1 = ((hwlib::i2c_bus*)(&bus))->write(address);
      setgconfig1.write(reg_address);
	  setgconfig1.write(byte);}
	}
	
	uint8_t Gesturesensor::read(uint8_t reg_address){
		uint8_t result;
		
	  { hwlib::i2c_write_transaction write_reg = ((hwlib::i2c_bus*)(&bus))->write(address);
      write_reg.write(reg_address);}
	  
      { hwlib::i2c_read_transaction read_reg = ((hwlib::i2c_bus*)(&bus))->read(address);
		read_reg.read(result);}
		return result;
		}
	
	void Gesturesensor::setGconf1(uint8_t & gexPers, uint8_t & gexMsk, uint8_t & gfifoTh){
		uint8_t byte = (gfifoTh << 6) | (gexMsk << 2) | gexPers;
		write(gconf1, byte);
	}
	
	void Gesturesensor::setGconf2(uint8_t & gGain, uint8_t &glDrive, uint8_t &gwTime){
		uint8_t byte = (0 << 7) | (gGain << 5) | (glDrive << 3) | gwTime;
		write(gconf2, byte);
	}

	void Gesturesensor::setGconf3(uint8_t & gDims){
		uint8_t byte = gDims;
		write(gconf3, byte);
	}
	
	uint8_t Gesturesensor::readGconf4(){
	  uint8_t gmode = read(gconf4);
	  return (gmode >> 1);
	}
	
	void Gesturesensor::setGpenth(uint8_t & gPenth){
	  uint8_t byte = gPenth;
	  write(gpenth, byte);
	}
	
	void Gesturesensor::setGexth(uint8_t & gExth){
	  uint8_t byte = gExth;
	  write(gexth, byte);
	}
	
	void Gesturesensor::setGoffset_u(uint8_t & gOffset_u){
		uint8_t byte = gOffset_u;
		write(goffset_u, byte);
	}
	
	void Gesturesensor::setGoffset_d(uint8_t & gOffset_d){
		uint8_t byte = gOffset_d;
		write(goffset_d, byte);
	}
	
	void Gesturesensor::setGoffset_l(uint8_t & gOffset_l){
		uint8_t byte = gOffset_l;
		write(goffset_l, byte);
	}
	
	void Gesturesensor::setGoffset_r(uint8_t & gOffset_r){
		uint8_t byte = gOffset_r;
		write(goffset_r, byte);
	}
	
	void Gesturesensor::setGpulse(uint8_t & gPlen, uint8_t & gPulse){
		uint8_t byte = (gPlen << 6) | gPulse;
		write(gpulse, byte);
	}
	
	char Gesturesensor::readGesture(){
	uint8_t result[4];
	char up = 'u';
	char down = 'd';
	char left = 'l';
	char right = 'r';

	for(;;){
	
	hwlib::wait_ms(100);
	
	{ hwlib::i2c_write_transaction wtrans = ((hwlib::i2c_bus*)(&bus))->write(address);
      wtrans.write(0xFC);}
	  
    { hwlib::i2c_read_transaction rtrans = ((hwlib::i2c_bus*)(&bus))->read(address);
		rtrans.read(result, 4);}
		
    if (test == 0){
	if (result[0] > result[1] && result[0] > result[2] && result[0] > result[3]){
		hwlib::wait_ms(1000);
		return up;
	}

	else if (result[1] > result[0] && result[1] > result[2] && result[1] > result[3]){
		hwlib::wait_ms(1000);
		return down;
	}
	
	else if (result[2] > result[0] && result[2] > result[1] && result[2] > result[3]){
		hwlib::wait_ms(1000);
		return left;
	}
	
	else if (result[3] > result[0] && result[3] > result[1] && result[3] > result[2]){
		hwlib::wait_ms(1000);
		return right;
	}
	}
	else if (test == 1){
		
		hwlib::cout << "up:" << result[0] << "\n";
		hwlib::cout << "down:" << result[1] << "\n";
		hwlib::cout << "left:" << result[2] << "\n";
		hwlib::cout << "right:" << result[3] << "\n" << "\n";
	
	if (result[0] > result[1] && result[0] > result[2] && result[0] > result[3]){
		hwlib::cout << "UP" << "\n" << "\n";
		hwlib::wait_ms(1000);
	}
	
	else if (result[1] > result[0] && result[1] > result[2] && result[1] > result[3]){
		hwlib::cout << "DOWN" << "\n" << "\n";
		hwlib::wait_ms(1000);
	}
		
	else if (result[2] > result[0] && result[2] > result[1] && result[2] > result[3]){
		hwlib::cout << "LEFT" << "\n" << "\n";
		hwlib::wait_ms(1000);
	}
		
	else if (result[3] > result[0] && result[3] > result[1] && result[3] > result[2]){
		hwlib::cout << "RIGHT" << "\n" << "\n";
		hwlib::wait_ms(1000);
	}
	
	}
	
	}
}
	
