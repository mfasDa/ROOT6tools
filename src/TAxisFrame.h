#ifndef TAXISFRAME_H
#define TAXISFRAME_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <TH1F.h>

namespace ROOT6tools {

class TAxisFrame : public TH1F {
public:
  TAxisFrame();
  TAxisFrame(const char *name, const char *xtitle, const char *ytitle, double xmin, double xmax, double ymin, double ymax);
  virtual ~TAxisFrame();

  ClassDef(TAxisFrame, 1);
};

} /* namespace ROOT6tools */

#endif
