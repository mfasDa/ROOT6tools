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
#include <array>
#include "TSavableCanvas.h"
#include "TString.h"

ClassImp(ROOT6tools::TSavableCanvas)

namespace ROOT6tools {

TSavableCanvas::TSavableCanvas():
    TCanvas()
{
}

TSavableCanvas::TSavableCanvas(const char *name, const char *title, int nx, int ny):
    TCanvas(name, title, nx, ny)
{
}

TSavableCanvas::~TSavableCanvas() { }

void TSavableCanvas::SaveCanvas(const char *basename){
    const std::array<const TString, 5> kFileTypes = {"eps", "pdf", "png", "jpg", "gif"};
    for(auto f : kFileTypes) this->SaveAs(Form("%s.%s", basename, f.Data()));
}

} /* namespace ROOT6tools */
