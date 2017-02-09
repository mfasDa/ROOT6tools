#ifndef TPLOTMAKER_H
#define TPLOTMAKER_H
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <map>
#include <memory>
#include <vector>

#include "TNamedSortable.h"

class TObject;
class TVirtualPad;

namespace ROOT6tools {

class TAxisFrame;
class TDefaultLegend;
class TNDCLabel;
class TSavableCanvas;
  
/// \class TPlotMaker
/// \brief Helper class making the plot creation simple
class TPlotMaker : public TNamedSortable {
public:

  /// \class TPadMaker
  /// \brief Collecting functionality connected to a single pad
  class TPadMaker {
  public:
    TPadMaker(TPlotMaker *parent, int id, TVirtualPad *rootpad = nullptr);
    TPadMaker(const TPadMaker &ref);
    TPadMaker &operator=(const TPadMaker &ref);
    bool operator==(const TPadMaker &ref) const;
    bool operator<(const TPadMaker &ref) const;
    ~TPadMaker() {}
      
    void Open();
    void SetLog(bool x, bool y);
    void DrawFrame(const char * xtitle, const char * ytitle, double xmin, double xmax, double ymin, double ymax);
    void DrawLegend(double xmin, double ymin, double xmax, double ymax);
    void AddObjectToLegend(TObject *legobj, const char * title, const char * plotmode = "lep");
    void DrawLabel(double xmin, double ymin, double xmax, double ymax, const char *text);
    TDefaultLegend *GetRootLegend() { return fLegend; }
    void Update();
      
    void SetXTitleOffset(double offset);
    void SetYTitleOffset(double offset);
      
  private:
    TPlotMaker                      *fParent;
    int                             fPadID;
    TVirtualPad                     *fRootPad;
    TAxisFrame                      *fFrame;
    TDefaultLegend                  *fLegend;
    std::vector<TNDCLabel *>        fLabels;
  };
    
  TPlotMaker(const char *name);
  TPlotMaker(const TPlotMaker &ref);
  TPlotMaker &operator=(const TPlotMaker &ref);
  virtual ~TPlotMaker();
    
  void CreateCanvas(const char *canvastitle, int sizex, int sizey, int ncols, int nrows);
  std::shared_ptr<TPadMaker> OpenPad(int padID);
  void OpenPlot();
  void Update();
  void SavePlotAs(const char *basename);
    
protected:
  TSavableCanvas                                 *fCanvas;
  int                                             fNpads;
  std::map<int, std::shared_ptr<TPadMaker>>       fPads;

  ClassDef(TPlotMaker, 1);
};
  
} /* namespace r6tools */

#endif /* PLOT_H_ */
