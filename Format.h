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
            }
          }else{
            // ERROR : NO POINTER REQUIRE BUT POINTER GIVEN
          }
        }else{
          switch (type){
            case 'i':
            case 'd':
              if(std::is_integral<T>::value){
                stringFormated += std::to_string(value);
              }else{
                // ERROR : NOT AN INTEGER
              }
              break;
            case 'f':
              if(std::is_floating_point<T>::value){
                stringFormated += std::to_string(value);
              }else{
                // ERROR : NOT A FLOAT
              }
              break;
            case 'b':
              if(std::is_same<T,bool>::value){
                if(value){
                  stringFormated += "true";
                }
                else{
                  stringFormated += "false";
                }
              }else{
                // ERROR : NOT A BOOLEAN
              }
              break;
            case 's':
              if(std::is_same<T,std::string>::value){
                stringFormated += value;
              }else{
                // ERROR : NOT A STRING
              }
              break;
            case 'c':
              if(std::is_same<T,char>::value){
                stringFormated += value;
              }else{
                // ERROR : NOT A CHAR
              }
              break;
            case 'p':
              // ERROR : Not a pointer !
              break;
            case 'x':{
              if(std::is_integral<T>::value){
                std::stringstream stream;
                stream << std::hex << value;
                std::string result(stream.str());
                stringFormated += "0x";
                stringFormated += result;
              }else{
                // ERROR : NOT AN INTEGER
              }
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
