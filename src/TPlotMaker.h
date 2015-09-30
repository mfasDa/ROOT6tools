#ifndef PLOT_H_
#define PLOT_H_
/*
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version. (See cxx source for full Copyright notice)
 */

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "TNamedStl.h"

class TCanvas;
class TH1;
class TLegend;
class TPaveText;
class TObject;
class TVirtualPad;

namespace r6tools {
  
  /// \class TPlotMaker
  /// \brief Helper class making the plot creation simple
  class TPlotMaker : public TNamedStl {
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
      void DrawFrame(std::string xtitle, std::string ytitle, double xmin, double xmax, double ymin, double ymax);
      void DrawLegend(double xmin, double ymin, double xmax, double ymax);
      void AddObjectToLegend(TObject *legobj, std::string title, std::string plotmode = "lep");
      void DrawLabel(double xmin, double ymin, double xmax, double ymax, std::string text);
      TLegend *GetRootLegend() { return fLegend; }
      void Update();
      
      void SetXTitleOffset(double offset);
      void SetYTitleOffset(double offset);
      
    private:
      TPlotMaker                      *fParent;
      int                             fPadID;
      TVirtualPad                     *fRootPad;
      TH1                             *fFrame;
      TLegend                         *fLegend;
      std::vector<TPaveText *>        fLabels;
    };
    
    TPlotMaker(std::string name);
    TPlotMaker(const TPlotMaker &ref);
    TPlotMaker &operator=(const TPlotMaker &ref);
    virtual ~TPlotMaker();
    
    void CreateCanvas(std::string canvastitle, int sizex, int sizey, int ncols, int nrows);
    std::shared_ptr<TPadMaker> OpenPad(int padID);
    void OpenPlot();
    void Update();
    void SavePlotAs(std::string filenamebase);
    
  protected:
    TCanvas                                         *fCanvas;
    int                                             fNpads;
    std::map<int, std::shared_ptr<TPadMaker>>       fPads;
  };
  
} /* namespace r6tools */

#endif /* PLOT_H_ */
