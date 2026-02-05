//
// Created by marianav on 2/4/26.
//

#include <vector>
#include <string>
#include <iostream>

#include "TApplication.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TMultiGraph.h"
#include "TStyle.h"

struct GraphData {
  std::string name;
  std::vector<double> x, y, ex, ey;
};

TGraphErrors* MakeTGraphErrors(const GraphData& d,
                              int markerStyle,
                              int color)
{
  int n = d.x.size();
  if ((int)d.y.size() != n || (int)d.ex.size() != n || (int)d.ey.size() != n) {
    std::cerr << "Size mismatch for graph: " << d.name << std::endl;
    return nullptr;
  }

  auto* g = new TGraphErrors(n);
  g->SetName(d.name.c_str());

  for (int i = 0; i < n; i++) {
    g->SetPoint(i, d.x[i], d.y[i]);
    g->SetPointError(i, d.ex[i], d.ey[i]);
  }

  g->SetMarkerStyle(markerStyle);
  g->SetMarkerSize(1.1);
  g->SetLineWidth(2);
  g->SetLineColor(color);
  g->SetMarkerColor(color);

  return g;
}

void DrawThreeGraphs(const std::vector<GraphData>& graphs,
                     const std::string& canvasName,
                     const std::string& title,
                     const std::string& outPng)
{
  if (graphs.size() != 3) {
    std::cerr << "Expected exactly 3 graphs" << std::endl;
    return;
  }

  const int colors[3]  = {kBlue+1, kRed+1, kGreen+2};
  const int markers[3] = {20, 21, 22};

  auto* c = new TCanvas(canvasName.c_str(), title.c_str(), 900, 650);
  c->SetGrid();

  auto* mg = new TMultiGraph();

  for (int i = 0; i < 3; i++) {
    auto* g = MakeTGraphErrors(graphs[i], markers[i], colors[i]);
    if (g) mg->Add(g, "P");
  }

  mg->SetTitle(title.c_str());
  mg->Draw("A");

  mg->GetXaxis()->SetTitle("Lum.");
  mg->GetYaxis()->SetTitle("Eff.");

  mg->GetXaxis()->SetTitleSize(0.045);
  mg->GetYaxis()->SetTitleSize(0.045);
  mg->GetXaxis()->SetLabelSize(0.040);
  mg->GetYaxis()->SetLabelSize(0.040);

  auto* leg = new TLegend(0.62, 0.18, 0.88, 0.35);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);

  for (int i = 0; i < 3; i++) {
    leg->AddEntry(mg->GetListOfGraphs()->At(i),
                  graphs[i].name.c_str(),
                  "p");
  }

  leg->Draw();
  c->SaveAs(outPng.c_str());
}

int main(int argc, char** argv)
{
  // Needed so ROOT can create canvases in a standalone app
  TApplication app("app", &argc, argv);

  gStyle->SetOptStat(0);

  // ---------------- POSITIVE ----------------
  GraphData posA{
    "Conv. rec. (pos)",
    {0, 45, 100, 150},
    {0.9925, 0.9012, 0.7672, 0.5897},
    {0, 0, 0, 0},
    {0.0185, 0.0194, 0.0213, 0.0544}
  };

  GraphData posB{
    "AI rec. (pos)",
    {0, 45, 100, 150},
    {0.9907, 0.9559, 0.8801, 0.7652},
    {0, 0, 0, 0},
    {0.0184, 0.0187, 0.0200, 0.0526}
  };

  GraphData posC{
    "Denoised AI rec. (pos)",
    {0, 45, 100, 150},
    {0.9898, 0.9813, 0.9336, 0.8477},
    {0, 0, 0, 0},
    {0.0184, 0.0186, 0.0194, 0.0504}
  };

  // ---------------- NEGATIVE ----------------
  GraphData negA{
    "Conv. rec. (neg)",
    {0, 45, 100, 150},
    {0.9961, 0.8519, 0.8350, 0.4160},
    {0, 0, 0, 0},
    {0.0646, 0.0632, 0.0701, 0.1362}
  };

  GraphData negB{
    "AI rec. (neg)",
{0, 45, 100, 150},
{0.9761, 0.9089, 0.8424, 0.4938},
{0, 0, 0, 0},
{0.0633, 0.0622, 0.0644, 0.1341}
  };

  GraphData negC{
    "Denoised AI rec. (neg)",
{0, 45, 100, 150},
{0.9778, 0.9350, 0.9087, 0.5832},
{0, 0, 0, 0},
{0.0639, 0.0630, 0.0649, 0.1379}

  };

  DrawThreeGraphs({posA, posB, posC},
                  "c_pos",
                  "Efficiency vs Luminosity (Positive)",
                  "Plots/eff_vs_lum_pos_aiTracking_all.pdf");

  DrawThreeGraphs({negA, negB, negC},
                  "c_neg",
                  "Efficiency vs Luminosity (Negative)",
                  "Plots/eff_vs_lum_neg_aiTracking_all.pdf");

  // Comment this out if you do NOT want interactive windows
  // app.Run();

  return 0;
}
