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

#include <TCanvas.h>
#include "TH1.h"
#include <TLegend.h>
#include <TPaveText.h>
#include <TVirtualPad.h>

namespace r6tools {
  
  TPlotMaker::TPlotMaker(std::string name):
  TNamedStl(name),
  fCanvas(nullptr),
  fNpads(0),
  fPads()
  {
  }
  
  TPlotMaker::TPlotMaker(const TPlotMaker &ref):
  TNamedStl(ref),
  fCanvas(ref.fCanvas),
  fNpads(ref.fNpads),
  fPads(ref.fPads)
  {}
  
  TPlotMaker &TPlotMaker::operator=(const TPlotMaker &ref){
    TNamedStl::operator=(ref);
    if(this != &ref){
      fNpads = ref.fNpads;
      fPads = ref.fPads;
    }
    return *this;
  }
  
  TPlotMaker::~TPlotMaker() {
  }
  
  void TPlotMaker::CreateCanvas(std::string canvastitle, int sizex, int sizey, int ncols, int nrows){
    fCanvas = new TCanvas(fName.Data(), canvastitle.c_str(), sizex, sizey);
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
  
  void TPlotMaker::SavePlotAs(std::string filenamebase){
    std::array<std::string, 5> endings = {{"eps", "pdf", "gif", "jpeg", "png"}};
    for(auto myend : endings)
      fCanvas->SaveAs(std::string(filenamebase + "." + myend).c_str());
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
  
  void TPlotMaker::TPadMaker::DrawFrame(std::string xtitle, std::string ytitle, double xmin, double xmax, double ymin, double ymax){
    if(gPad != fRootPad){
      fRootPad->cd();
    }
    fFrame = new TH1F(Form("axis_%s_%d", fParent->fName.Data(), fPadID), Form("; %s; %s", xtitle.c_str(), ytitle.c_str()), 100, xmin, xmax);
    fFrame->SetStats(false);
    fFrame->GetYaxis()->SetRangeUser(ymin, ymax);
    fFrame->Draw("axis");
  }
  
  void TPlotMaker::TPadMaker::DrawLegend(double xmin, double ymin, double xmax, double ymax){
    if(gPad != fRootPad){
      fRootPad->cd();
    }
    fLegend = new TLegend(xmin, ymin, xmax, ymax);
    fLegend->SetBorderSize(0);
    fLegend->SetFillStyle(0);
    fLegend->SetTextFont(42);
    fLegend->Draw();
  }
  
  void TPlotMaker::TPadMaker::AddObjectToLegend(TObject *legobj, std::string title, std::string plotmode){
    if(fLegend){
      fLegend->AddEntry(legobj, title.c_str(), plotmode.c_str());
    }
  }
  
  void TPlotMaker::TPadMaker::DrawLabel(double xmin, double ymin, double xmax, double ymax, std::string text){
    if(gPad != fRootPad){
      fRootPad->cd();
    }
    TPaveText *label = new TPaveText(xmin, ymin, xmax, ymax, "NDC");
    label->SetBorderSize(0);
    label->SetFillStyle(0);
    label->SetTextFont(42);
    label->AddText(text.c_str());
    label->Draw();
    fLabels.push_back(label);
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
