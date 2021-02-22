#ifndef FP_FORMAT_H
#define FP_FORMAT_H

#include <string>

namespace fp {
  /**
   * @brief Insert all parameter into a formated string
   */
/*
  template<typename T>
  struct m_is_pointer { static const bool value = false; };

  template<typename T>
  struct m_is_pointer<T*> { static const bool value = true; };
*/
  std::string format(const std::string& formatString){
    std::string stringFormated;
    size_t i = 0;
    while(i < formatString.length()){
      char c = formatString[i];
      if(c == '%'){
        if(formatString[i+1] == '%'){
          stringFormated += c;
          i++;
        }else{
          // TODO : Throw exception because no more arguments
          stringFormated += c; // To remove
        }
      }else{
        stringFormated += c;
      }
      i++;
    }
    return stringFormated;
  }

  template<typename T, typename... Targs>
  std::string format(const std::string& formatString, T value, Targs ... Fargs) {
    std::string stringFormated;
    size_t i = 0;
    while(i < formatString.length()){
      char c = formatString[i];

      if(c == '%'){
        char type = formatString[i+1];
        if constexpr (std::is_null_pointer<T>::value){
          if(type == 'p'){
            stringFormated += "0x0";
          }else{
            // ERROR : NO POINTER REQUIRE BUT POINTER GIVEN
          }
        }else if constexpr (std::is_pointer<T>::value){
          if(type == 'p'){
            std::ostringstream get_the_address; 
            get_the_address << value;
            std::string address =  get_the_address.str();
            stringFormated += address;
          }else{
            // ERROR : NO POINTER REQUIRE BUT POINTER GIVEN
          }
        }else{
          switch (type){
            case 'i':
            case 'd':
              // TODO : Check the type typeid ?
              stringFormated += std::to_string(value);
              break;
            case 'f':
              // TODO : Check the type typeid ?
              stringFormated += std::to_string(value);
              break;
            case 'b':
              // TODO : Check the type typeid ?
              if(value)
                stringFormated += "true";
              else
                stringFormated += "false";
              break;
            case 's':
              // TODO : Check the type typeid ?
              stringFormated += value;
              break;
            case 'c':
              // TODO : Check the type typeid ?
              stringFormated += value;
              break;
            case 'p':
              // ERROR : Not a pointer !
              break;
            case 'x':{
              // TODO : Check the type typeid ?
              std::stringstream stream;
              stream << std::hex << value;
              std::string result(stream.str());
              stringFormated += "0x";
              stringFormated += result;
              break;
            }
            case '%':
              stringFormated += type;
              stringFormated += formatString.substr(i+3,formatString.length());
              return format(stringFormated, value, Fargs...);
            default:
              break;
          }
        }
        stringFormated += formatString.substr(i+2,formatString.length());
        return format(stringFormated, Fargs...);
      }else{
        stringFormated += c;
      }
      i++;
    }
    return stringFormated;
  }

}


#endif // FP_FORMAT_H
