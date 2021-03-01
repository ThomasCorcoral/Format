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
          stringFormated += formatString[i+1];
          i++;
        }else{
          // ERROR : no more arguments
          std::cout << stringFormated << '\n';
          throw std::runtime_error(std::string("Error : %") + formatString[i+1] + std::string("was found, but there is no more argument"));
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
    // browse the strings
    while(i < formatString.length()){
      char c = formatString[i];
      // check if the char is a %, if not just print it in the new string
      if(c == '%'){

        bool escape = false;
        char type = formatString[i+1];
        /*if constexpr (type == 'o'){
          // Small cond to check if type is really unknow
          if(std::is_pointer<T>::value || std::is_integral<T>::value || std::is_floating_point<T>::value || std::is_same<T,std::string>::value || std::is_same<T,bool>::value || std::is_same<T,char>::value){
            throw std::runtime_error(std::string("Error : %o was found, but the variable is supported"));
          }else{ // Check if to_string exsists
            //ADL
          }
        }*/
        if constexpr (std::is_null_pointer<T>::value){
          if(type == 'p'){
            stringFormated += "0x0";
          }else{
            // If empty string ?
            // ERROR : NULL POINTER FIND
          }
        }else if constexpr (std::is_pointer<T>::value){
          if(type == 'p'){
            std::ostringstream get_the_address; // init the stream
            get_the_address << value; // Put the adress of the pointer in the stream
            std::string address =  get_the_address.str(); // convert the stream into a string
            stringFormated += address; // add the string to our new one
          }else if(type == 's'){
            if constexpr (std::is_same<T,const char*>::value){
              stringFormated += value;
            }else{
              // ERROR : Not a string
              throw std::runtime_error(std::string("Error : %s was found, but the variable isn't a string"));
            }
          }else{
            // ERROR : No pointer required 
            throw std::runtime_error(std::string("Error : No pointer was required, but a pointer was given"));
          }
        }else{
          switch (type){
            case 'i':
            case 'd':
              if constexpr (std::is_integral<T>::value){
                stringFormated += std::to_string(value);
              }else{
                // ERROR : Not an integer
              throw std::runtime_error(std::string("Error : %d or %i was found, but the variable isn't an integer"));
              }
              break;
            case 'f':
              if constexpr (std::is_floating_point<T>::value){
                stringFormated += std::to_string(value);
              }else{
                // ERROR : Not a float
                throw std::runtime_error(std::string("Error : %f was found, but the variable isn't a float"));
              }
              break;
            case 'b':
              if constexpr (std::is_same<T,bool>::value){
                if(value){// Just evaluate the value as it's a boolean
                  stringFormated += "true";
                }
                else{
                  stringFormated += "false";
                }
              }else{
                // ERROR : Not a boolean
                throw std::runtime_error(std::string("Error : %b was found, but the variable isn't a boolean"));
              }
              break;
            case 's':
              if constexpr (std::is_same<T,std::string>::value){
                stringFormated += value;
              }else{
                // ERROR : Not a string
                throw std::runtime_error(std::string("Error : %s was found, but the variable isn't a string"));
              }
              break;
            case 'c':
              if constexpr (std::is_same<T,char>::value){
                stringFormated += value;
              }else{
                // ERROR : Not a char
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
                // ERROR : Not an integral
                throw std::runtime_error(std::string("Error : %x was found, but the variable isn't an integer"));
              }
              break;
            }
            case '%': // escape char
              stringFormated += c;
              stringFormated += type;
              i++;
              escape = true;
              break;
            default:
              throw std::runtime_error(std::string("Error : %") + type + std::string(" was found, but the type is unknown"));
              break;
          }
        }
        if(!escape){
          stringFormated += formatString.substr(i+2,formatString.length());
          return format(stringFormated, Fargs...);
        }
      }else{
        stringFormated += c;
      }
      // increase our counter
      i++;
    }
    return stringFormated;
  }
}
#endif // FP_FORMAT_H
