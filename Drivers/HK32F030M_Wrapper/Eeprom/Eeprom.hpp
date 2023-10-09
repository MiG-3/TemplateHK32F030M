/*
 * Eeprom.hpp
 *
 *  Created on: 4 окт. 2023 г.
 *      Author: SpitsynAV
 */

#ifndef HK32F030M_WRAPPER_EEPROM_EEPROM_HPP_
#define HK32F030M_WRAPPER_EEPROM_EEPROM_HPP_

#include <hk32f030m_flash.h>
#include <Libs/Utils/Singletone.hpp>
#include <Libs/Containers/buffer.hpp>
#include <cstring>


namespace Drivers {

  class Eeprom : public Singletone<Eeprom> {
    public:
      template<typename Data>
      bool read(uint32_t address, Data& data) {
        if((address + sizeof(Data)) > _size) {
          DEBUG_STOP;
          return false;
        }
        memcpy( &data, ((void*)(_begin + address)), sizeof(Data) );
        return true;
      }

      template<typename Data>
      bool write(uint32_t address, const Data& data) {
        if((address + sizeof(Data)) > _size) {
          DEBUG_STOP;
          return false;
        }
        address +=_begin;
        const uint8_t* ptrData = reinterpret_cast<const uint8_t*>(&data);
        FLASH_Unlock();
        for (uint32_t i = 0; i < sizeof(Data); ++i) {
          if( EEPROM_EraseByte(address) != FLASH_COMPLETE ) {DEBUG_STOP; return false;}
          if( EEPROM_ProgramByte(address, *ptrData) != FLASH_COMPLETE ) {DEBUG_STOP; return false;}
          ptrData++; address++;
        }
        FLASH_Lock();
        return true;
      }
    private:
      static constexpr uint32_t _begin {0x0C000000};
      static constexpr uint32_t _end {0x0C0001C0};
      static constexpr uint32_t _size {448};

      friend Singletone<Eeprom>;
      Eeprom() : Singletone<Eeprom>() {}
  };

}  // namespace Drivers

#endif /* HK32F030M_WRAPPER_EEPROM_EEPROM_HPP_ */
