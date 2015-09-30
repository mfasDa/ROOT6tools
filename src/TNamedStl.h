#ifndef TNAMEDSTL_H_
#define TNAMEDSTL_H_
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <string>

#include <TNamed.h>

namespace r6tools {
  
  /// \class TNamedStl
  /// \brief Extends TNamed with comparison operators, allowing the object
  /// to be used in standard, sortable containers.
  class TNamedStl : public TNamed {
  public:
    TNamedStl(std::string name);
    virtual ~TNamedStl() {}
    
    bool operator==(const TNamedStl &ref) const;
    bool operator!=(const TNamedStl &ref) const;
    bool operator<(const TNamedStl &ref) const;
    bool operator>(const TNamedStl &ref) const;
  };
  
} /* namespace r6tools */

#endif /* TNAMEDSTL_H_ */
