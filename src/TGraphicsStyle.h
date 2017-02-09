#ifndef TGRAPHICSSTYLE_H
#define TGRAPHICSSTYLE_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <Rtypes.h>

class TH1;
class TGraphErrors;

namespace ROOT6tools {
  
/// \class TGraphicsStyle
/// \brief Style definition applied to histograms
class TGraphicsStyle {
public:
  TGraphicsStyle(Color_t color = kBlack, Style_t marker = 20);
  virtual ~TGraphicsStyle() {}

  Color_t GetColor() const { return fColor; }
  Marker_t GetMarker() const { return fMarker; }
    
  void DefineHistogram(TH1 *hist) const;
  void DefineGraph(TGraphErrors *graph) const;
    
protected:
  Color_t           fColor;
  Style_t           fMarker;
};
  
} /* namespace r6tools */

#endif /* TGRAPHICSSTYLE_H_ */
