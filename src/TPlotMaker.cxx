/****************************************************************************
 * Various helpers making life easier when working with ROOT6               *
 * Copyright (C) 2015  Markus Fasel, Lawrence Berkeley National Laboratory  *
 *                                                                          *
 * This program is free software: you can redistribute it and/or modify     *
 * it under the terms of the GNU General Public License as published by     *
 * the Free Software Foundation, either version 3 of the License, or        *
 * (at your option) any later version.                                      *
 *                                                                          *
 * This program is distributed in the hope that it will be useful,          *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of           *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            *
 * GNU General Public License for more details.                             *
 *                                                                          *
 * You should have received a copy of the GNU General Public License        *
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.    *
 ****************************************************************************/
#include "TPlotMaker.h"

#include <array>

#include "TAxisFrame.h"
#include "TDefaultLegend.h"
#include "TNDCLabel.h"
#include "TSavableCanvas.h"
#include <TVirtualPad.h>

namespace ROOT6tools {
  
TPlotMaker::TPlotMaker(const char *name):
      TNamedSortable(name),
      fCanvas(nullptr),
      fNpads(0),
      fPads()
{
}

TPlotMaker::TPlotMaker(const TPlotMaker &ref):
      TNamedSortable(ref),
      fCanvas(ref.fCanvas),
      fNpads(ref.fNpads),
      fPads(ref.fPads)
{}

TPlotMaker &TPlotMaker::operator=(const TPlotMaker &ref){
  TNamedSortable::operator=(ref);
  if(this != &ref){
    fNpads = ref.fNpads;
    fPads = ref.fPads;
  }
  return *this;
}

TPlotMaker::~TPlotMaker() {
}

void TPlotMaker::CreateCanvas(const char *canvastitle, int sizex, int sizey, int ncols, int nrows){
  fCanvas = new TSavableCanvas(fName, canvastitle, sizex, sizey);
  fCanvas->Divide(ncols, nrows);
  fNpads = nrows * ncols;
}

std::shared_ptr<TPlotMaker::TPadMaker> TPlotMaker::OpenPad(int padID){
  std::shared_ptr<TPlotMaker::TPadMaker> result;
  if(!fCanvas){
    return result;
  }
  if(padID < 1 || padID > fNpads){
    return result;
  }
  auto exist = fPads.find(padID);
  if(exist != fPads.end()){
    exist->second->Open();
    return exist->second;
  } else {
    fCanvas->cd(padID);
    result = std::shared_ptr<TPlotMaker::TPadMaker>(new TPlotMaker::TPadMaker(this, padID, gPad));
    fPads.insert(std::pair<int, std::shared_ptr<TPlotMaker::TPadMaker>>(padID, result));
    return result;
  }
}

void TPlotMaker::OpenPlot(){
  fCanvas->cd();
}

void TPlotMaker::Update(){
  for(auto paditer : fPads)
    paditer.second->Update();
}

void TPlotMaker::SavePlotAs(const char *basename){
  fCanvas->SaveCanvas(basename);
}

TPlotMaker::TPadMaker::TPadMaker(TPlotMaker *parent, int id, TVirtualPad *rootpad):
      fParent(parent),
      fPadID(id),
      fRootPad(rootpad),
      fFrame(nullptr),
      fLegend(nullptr),
      fLabels()
{
}

TPlotMaker::TPadMaker::TPadMaker(const TPlotMaker::TPadMaker &ref):
      fParent(ref.fParent),
      fPadID(ref.fPadID),
      fRootPad(ref.fRootPad),
      fFrame(ref.fFrame),
      fLegend(ref.fLegend),
      fLabels(ref.fLabels)
{
}

TPlotMaker::TPadMaker &TPlotMaker::TPadMaker::operator=(const TPlotMaker::TPadMaker &ref){
  if(this != &ref){
    fParent = ref.fParent;
    fPadID = ref.fPadID;
    fRootPad = ref.fRootPad;
    fFrame = ref.fFrame;
    fLegend = ref.fLegend;
    fLabels = ref.fLabels;
  }
  return *this;
}

bool TPlotMaker::TPadMaker::operator==(const TPlotMaker::TPadMaker &ref) const {
  return fPadID == ref.fPadID;
}

bool TPlotMaker::TPadMaker::operator<(const TPlotMaker::TPadMaker &ref) const {
  return fPadID < ref.fPadID;
}

void TPlotMaker::TPadMaker::Open(){
  fRootPad->cd();
}

void TPlotMaker::TPadMaker::SetLog(bool x, bool y){
  if(x) fRootPad->SetLogx();
  if(y) fRootPad->SetLogy();
}

void TPlotMaker::TPadMaker::DrawFrame(const char *xtitle, const char *ytitle, double xmin, double xmax, double ymin, double ymax){
  if(gPad != fRootPad){
    fRootPad->cd();
  }
  fFrame = new TAxisFrame(Form("axis_%s_%d", fParent->fName.Data(), fPadID), xtitle, ytitle, xmin, xmax, ymin, ymax);
  fFrame->Draw("axis");
}

void TPlotMaker::TPadMaker::DrawLegend(double xmin, double ymin, double xmax, double ymax){
  if(gPad != fRootPad){
    fRootPad->cd();
  }
  fLegend = new TDefaultLegend(xmin, ymin, xmax, ymax);
  fLegend->Draw();
}

void TPlotMaker::TPadMaker::AddObjectToLegend(TObject *legobj, const char *title, const char *plotmode){
  if(fLegend){
    fLegend->AddEntry(legobj, title, plotmode);
  }
}

void TPlotMaker::TPadMaker::DrawLabel(double xmin, double ymin, double xmax, double ymax, const char * text){
  if(gPad != fRootPad){
    fRootPad->cd();
  }
  fLabels.push_back(new TNDCLabel(xmin, ymin, xmax, ymax, text));
}

void TPlotMaker::TPadMaker::Update(){
  fRootPad->Update();
}

void TPlotMaker::TPadMaker::SetXTitleOffset(double offset) {
  fFrame->GetXaxis()->SetTitleOffset(offset);
}

void TPlotMaker::TPadMaker::SetYTitleOffset(double offset) {
  fFrame->GetYaxis()->SetTitleOffset(offset);
}


} /* namespace r6tools */
