#ifndef TDEFAULTLEGEND_H
#define TDEFAULTLEGEND_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <TLegend.h>

namespace ROOT6tools {

class TDefaultLegend : public TLegend {
public:
  TDefaultLegend();
  TDefaultLegend(double xmin, double ymin, double xmax, double ymax);
  virtual ~TDefaultLegend();

  ClassDef(TDefaultLegend, 1);
};

} /* namespace ROOT6tools */

#endif
