#ifndef TNDCLABEL_H
#define TNDCLABEL_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <TPaveText.h>

namespace ROOT6tools {

class TNDCLabel : public TPaveText {
public:
  TNDCLabel();
  TNDCLabel(double xmin, double ymin, double xmax, double ymax, const char *text);
  virtual ~TNDCLabel();

  ClassDef(TNDCLabel, 1);
};

} /* namespace ROOT6tools */

#endif
