#ifndef FP_FORMAT_H
#define FP_FORMAT_H

#include <string>

namespace fp {
  /**
   * @brief Insert all parameter into a formated string
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
            // If empty string ?
            // ERROR : NULL POINTER FIND
          }
        }else if constexpr (std::is_pointer<T>::value){
          if(type == 'p'){
            std::ostringstream get_the_address; 
            get_the_address << value;
            std::string address =  get_the_address.str();
            stringFormated += address;
          }else if(type == 's'){
            if constexpr (std::is_same<T,const char*>::value){
              stringFormated += value;
            }else{
              // ERROR : NOT A STRING !
              throw std::runtime_error(std::string("Error : %s was found, but the variable isn't a string"));
            }
          }else{
            // ERROR : NO POINTER REQUIRED BUT POINTER GIVEN
            throw std::runtime_error(std::string("Error : No pointer was required, but a pointer was given"));
          }
        }else{
          switch (type){
            case 'i':
            case 'd':
              if constexpr (std::is_integral<T>::value){
                stringFormated += std::to_string(value);
              }else{
                // ERROR : NOT AN INTEGER
              throw std::runtime_error(std::string("Error : %d or %i was found, but the variable isn't an integer"));
              }
              break;
            case 'f':
              if constexpr (std::is_floating_point<T>::value){
                stringFormated += std::to_string(value);
              }else{
                // ERROR : NOT A FLOAT
                throw std::runtime_error(std::string("Error : %f was found, but the variable isn't a float"));
              }
              break;
            case 'b':
              if constexpr (std::is_same<T,bool>::value){
                if(value){
                  stringFormated += "true";
                }
                else{
                  stringFormated += "false";
                }
              }else{
                // ERROR : NOT A BOOLEAN
                throw std::runtime_error(std::string("Error : %b was found, but the variable isn't a boolean"));
              }
              break;
            case 's':
              if constexpr (std::is_same<T,std::string>::value){
                stringFormated += value;
              }else{
                // ERROR : NOT A STRING
                throw std::runtime_error(std::string("Error : %s was found, but the variable isn't a string"));
              }
              break;
            case 'c':
              if constexpr (std::is_same<T,char>::value){
                stringFormated += value;
              }else{
                // ERROR : NOT A CHAR
                throw std::runtime_error(std::string("Error : %c was found, but the variable isn't a char"));
              }
              break;
            case 'p':
              // ERROR : Not a pointer !
                throw std::runtime_error(std::string("Error : %p was found, but the variable isn't a pointer"));
              break;
            case 'x':{
              if constexpr (std::is_integral<T>::value){
                std::stringstream stream;
                stream << std::hex << value;
                std::string result(stream.str());
                stringFormated += "0x";
                stringFormated += result;
              }else{
                // ERROR : NOT AN INTEGER
                throw std::runtime_error(std::string("Error : %x was found, but the variable isn't an integer"));
              }
              break;
            }
            case '%':
              stringFormated += type;
              stringFormated += formatString.substr(i+3,formatString.length());
              return format(stringFormated, value, Fargs...);
            default:
              throw std::runtime_error(std::string("Error : %") + type + std::string(" was found, but the type is unknown"));
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
