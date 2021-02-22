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
        switch (type){
          case 'i':
          case 'd':
            // TODO : Check the type typeid ?
          case 'f':
            // TODO : Check the type typeid ?
            break;
          case 'b':
            // TODO : Check the type typeid ?
            if(value){
              stringFormated += "true";
            }else{
              stringFormated += "false";
            }
            stringFormated += formatString.substr(i+2,formatString.length());
            return format(stringFormated, Fargs...);
            break;
          case 's':
            // TODO : Check the type typeid ?
            break;
          case 'c':
            // TODO : Check the type typeid ?
            break;
          case 'x':
            // TODO : Check the type typeid ?
            break;
          case '%':
            stringFormated += type;
            stringFormated += formatString.substr(i+3,formatString.length());
            return format(stringFormated, value, Fargs...);
          default:
            break;
        }
      }else{
        stringFormated += c;
      }
      i++;

    }
    return stringFormated;
  }

}


#endif // FP_FORMAT_H
