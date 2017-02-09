#ifndef TSAVABLECANVAS_H
#define TSAVABLECANVAS_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <TCanvas.h>

namespace ROOT6tools {

class TSavableCanvas : public TCanvas {
public:
  TSavableCanvas();
  TSavableCanvas(const char *name, const char *title, int nx, int ny);
  virtual ~TSavableCanvas();

  void SaveCanvas(const char *basename);

  ClassDef(TSavableCanvas, 1);
};

} /* namespace ROOT6tools */

#endif
