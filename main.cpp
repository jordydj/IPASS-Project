#include "hwlib.hpp"
#include "Gesturesensor.hpp"
#include "Muis.hpp"

int main(){	 
	auto scl = hwlib::target::pin_oc(hwlib::target::pins::scl);
	auto sda = hwlib::target::pin_oc(hwlib::target::pins::sda);
	hwlib::i2c_bus_bit_banged_scl_sda bus(scl, sda);
	
	uint8_t offset_u = 0b00001011;
	uint8_t offset_d = 0b00000101;  
	uint8_t offset_l = 0b00001101;
	uint8_t offset_r = 0b00000101;
	
	Gesturesensor sensor(bus);
	sensor.setGoffset_u(offset_u);
	sensor.setGoffset_d(offset_d);
	sensor.setGoffset_l(offset_l);
	sensor.setGoffset_r(offset_r);
	
	Muis muis(bus);
	
		hwlib::cout << sensor.readGconf4();
	if (sensor.readGconf4() == 1){
		hwlib::cout << "Gesture state machine is running.";
		for (;;){
//			char result = sensor.readGesture();
//			hwlib::cout << result << "\n \n";
			muis.sendToLeonardo();
		}
	}
	
	

}