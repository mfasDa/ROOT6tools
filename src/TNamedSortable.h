#ifndef TNAMEDSTL_H_
#define TNAMEDSTL_H_
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <TNamed.h>

namespace ROOT6tools {
  
/// \class TNamedSortable
/// \brief Extends TNamed with comparison operators, allowing the object
/// to be used in standard, sortable containers.
class TNamedSortable : public TNamed {
public:
  TNamedSortable();
  TNamedSortable(const char * name);
  TNamedSortable(const char * name, const char *title);
  virtual ~TNamedSortable() {}
    
  bool operator==(const TNamedSortable &ref) const;
  bool operator!=(const TNamedSortable &ref) const;
  bool operator<(const TNamedSortable &ref) const;
  bool operator>(const TNamedSortable &ref) const;

  ClassDef(TNamedSortable, 1);
};
  
} /* namespace r6tools */

#endif /* TNAMEDSTL_H_ */
