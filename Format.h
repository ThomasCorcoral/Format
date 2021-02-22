#ifndef FP_FORMAT_H
#define FP_FORMAT_H

#include <string>

namespace fp {
  /**
   * @brief Insert all parameter into a formated string
   */
  std::string format(const std::string& formatString){
    return formatString;
  }

  template<typename T, typename... Targs>
  std::string format(const std::string& formatString, T value, Targs ... Fargs) {
    std::string stringFormated;
    int i = 0;
    while(i < formatString.length()){
      char c = formatString[i];

      if(c == '%'){
        if(formatString[i+1] == '%'){
          stringFormated += formatString[i+1];
          i++;
        }
      }else{
        stringFormated += "True";
        stringFormated += formatString.substr(i+2,formatString.length());
        return format(stringFormated, Fargs...);
      }

    }
    return stringFormated;
  }

}


#endif // FP_FORMAT_H
