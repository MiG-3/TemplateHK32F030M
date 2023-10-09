/*
 * Range.hpp
 *
 *  Created on: 29 ���. 2021 �.
 *      Author: SpitsynAV
 */

#ifndef UTILS_RANGE_HPP_
#define UTILS_RANGE_HPP_


namespace Utils {

  template<typename Type>
  struct Range {
      static_assert(std::is_arithmetic<Type>::value, "Arithmetic not possible on this type");
      Type min;
      Type max;
      Type step;

      bool validate() {
        return (min < max) && (step < (max - min));
      }
  };

}  // namespace Utils


#endif /* UTILS_RANGE_HPP_ */
