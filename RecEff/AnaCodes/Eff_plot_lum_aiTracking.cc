//
// Created by marianav on 2/4/26.
//


#include <vector>
#include <string>
#include <iostream>
#include <cmath>

#include "TApplication.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TMultiGraph.h"
#include "TStyle.h"
#include "TF1.h"
#include "TGraphAsymmErrors.h"

struct GraphData {
  std::string name;
  std::vector<double> x, y, ex, ey;

  // Line parameters: y = intercept + slope * x
  double intercept = 0.0;
  double slope     = 0.0;
  double interceptErr = 0.0;
  double slopeErr     = 0.0;

  // If you have covariance cov(a,b), you can add it later.
};

TGraphErrors* MakeTGraphErrors(const GraphData& d, int markerStyle, int color)
{
  int n = (int)d.x.size();
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

// Compute x-range from points (fallback if empty)
static void GetXRangeFromData(const GraphData& d, double& xmin, double& xmax)
{
  if (d.x.empty()) { xmin = 0; xmax = 1; return; }
  xmin = d.x[0];
  xmax = d.x[0];
  for (double xv : d.x) {
    if (xv < xmin) xmin = xv;
    if (xv > xmax) xmax = xv;
  }
  // Add a tiny padding so lines aren't clipped exactly at endpoints
  double pad = 0.02 * (xmax - xmin);
  if (pad <= 0) pad = 1.0;
  xmin -= pad;
  xmax += pad;
}

// Create a ±1σ band as a filled TGraphAsymmErrors
TGraphAsymmErrors* MakeLineBand(const GraphData& d,
                                double xmin, double xmax,
                                int npts,
                                int color)
{
  auto* band = new TGraphAsymmErrors(npts);
  band->SetName((d.name + "_band").c_str());

  for (int i = 0; i < npts; i++) {
    double x = xmin + (xmax - xmin) * i / (npts - 1.0);
    double y = d.intercept + d.slope * x;

    // error propagation assuming intercept and slope are independent:
    // sigma_y^2 = sigma_a^2 + (x^2)*(sigma_b^2)
    double sy = std::sqrt(d.interceptErr * d.interceptErr +
                          (x * d.slopeErr) * (x * d.slopeErr));

    band->SetPoint(i, x, y);
    band->SetPointError(i, 0.0, 0.0, sy, sy);
  }

  band->SetFillStyle(3004);   // hatched
  band->SetFillColor(color);
  band->SetLineColor(color);
  band->SetMarkerColor(color);
  band->SetLineWidth(1);

  return band;
}

// Create the central line as TF1
TF1* MakeLineTF1(const GraphData& d, double xmin, double xmax, int color)
{
  auto* f = new TF1((d.name + "_line").c_str(), "[0] + [1]*x", xmin, xmax);
  f->SetParameter(0, d.intercept);
  f->SetParameter(1, d.slope);
  f->SetLineColor(color);
  f->SetLineWidth(2);
  f->SetLineStyle(1);
  return f;
}

void DrawThreeGraphs(const std::vector<GraphData>& graphs,
                     const std::string& canvasName,
                     const std::string& title,
                     const std::string& outPng,
                     bool drawLineBands = true)
{
  if (graphs.size() != 3) {
    std::cerr << "Expected exactly 3 graphs" << std::endl;
    return;
  }

  const int colors[3]  = {kBlue+1, kRed+1, kGreen+2};
  const int markers[3] = {20, 21, 22};

  auto* c = new TCanvas(canvasName.c_str(), title.c_str(), 900, 650);
  c->SetGrid();
  c->SetTopMargin(0.08);

  auto* mg = new TMultiGraph();

  // Create point graphs
  TGraphErrors* g[3] = {nullptr, nullptr, nullptr};
  for (int i = 0; i < 3; i++) {
    g[i] = MakeTGraphErrors(graphs[i], markers[i], colors[i]);
    if (!g[i]) return;
    mg->Add(g[i], "P");
  }

  mg->SetTitle(title.c_str());
  mg->Draw("A");

  mg->GetXaxis()->SetTitle("Lum.");
  mg->GetYaxis()->SetTitle("Eff.");
  mg->GetXaxis()->SetTitleOffset(1.1);
  mg->GetYaxis()->SetTitleOffset(1.2);

  // Draw line bands + lines on top of the points
  for (int i = 0; i < 3; i++) {
    double xmin, xmax;
    GetXRangeFromData(graphs[i], xmin, xmax);

    if (drawLineBands) {
      auto* band = MakeLineBand(graphs[i], xmin, xmax, 200, colors[i]);
      band->Draw("3"); // filled band
    }

    auto* fline = MakeLineTF1(graphs[i], xmin, xmax, colors[i]);
    fline->Draw("SAME");
  }

  // Legend
  auto* leg = new TLegend(0.58, 0.16, 0.88, 0.38);
  leg->SetBorderSize(0);
  leg->SetFillStyle(0);

  // Add entries: points + line (and band)
  for (int i = 0; i < 3; i++) {
    leg->AddEntry(g[i], (graphs[i].name + " (points)").c_str(), "p");
    // The TF1 is not directly referenced here; this is fine visually.
    leg->AddEntry((TObject*)nullptr,
                  Form("  line: y=%.4f%+.4f x", graphs[i].intercept, graphs[i].slope),
                  "");
    if (drawLineBands) {
      leg->AddEntry((TObject*)nullptr,
                    Form("  #sigma(a)=%.4f, #sigma(b)=%.4f", graphs[i].interceptErr, graphs[i].slopeErr),
                    "");
    }
  }

  leg->Draw();

  c->SaveAs(outPng.c_str());
}

int main(int argc, char** argv)
{
  TApplication app("app", &argc, argv);
  gStyle->SetOptStat(0);

  // --------------------
  // x,y,ex,ey and intercept/slope/errors
  // -------------------------

  // ---------------- POSITIVE ----------------
  GraphData posA{
    "Conv. rec. (pos)",
    {0, 45, 100, 150},
    {0.5223, 0.4743, 0.4038, 0.3252},
    {0, 0, 0, 0},
{0.0097, 0.0102, 0.0112, 0.0117},
/*intercept*/ 0.52745, /*slope*/ -0.00130,
/*interceptErr*/ 0.00818, /*slopeErr*/ 0.00010
  };

  GraphData posB{
    "AI rec. (pos)",
    {0, 45, 100, 150},
    {0.5229, 0.5045, 0.4645, 0.4062},
    {0, 0, 0, 0},
{0.0097, 0.0099, 0.0105, 0.0110},
/*intercept*/ 0.53100, /*slope*/ -0.00076,
/*interceptErr*/ 0.00807, /*slopeErr*/ 0.00009
  };

  GraphData posC{
    "Denoised AI rec. (pos)",
    {0, 45, 100, 150},
    {0.5234, 0.5189, 0.4937, 0.4583},
    {0, 0, 0, 0},
{0.0097,0.0098,0.0103,0.0102},
/*intercept*/ 0.53079, /*slope*/ -0.00044,
/*interceptErr*/ 0.00805, /*slopeErr*/ 0.00009
  };

  // ---------------- NEGATIVE ----------------
  GraphData negA{
    "Conv. rec. (neg)",
    {0, 45, 100, 150},
    {0.0826, 0.0706, 0.0692, 0.0489},
    {0, 0, 0, 0},
{0.0054, 0.0052, 0.0058, 0.0054},
/*intercept*/ 0.08254, /*slope*/ -0.00020,
/*interceptErr*/ 0.00438, /*slopeErr*/ 0.00005
  };

  GraphData negB{
    "AI rec. (neg)",
{0, 45, 100, 150},
{0.0824, 0.0767, 0.0711, 0.0605},
{0, 0, 0, 0},
{0.0053, 0.0052, 0.0054, 0.0053},
    /*intercept*/ 0.08304, /*slope*/ -0.00014,
    /*interceptErr*/ 0.00437, /*slopeErr*/ 0.00005
  };

  GraphData negC{
    "Denoised AI rec. (neg)",
{0, 45, 100, 150},
{0.0819, 0.0783, 0.0761, 0.0699},
{0, 0, 0, 0},
{0.0054, 0.0053, 0.0054, 0.0052},
    /*intercept*/ 0.08213, /*slope*/ -0.00008,
    /*interceptErr*/ 0.00438, /*slopeErr*/ 0.00005
  };



  DrawThreeGraphs({posA, posB, posC},
                  "c_pos",
                  "Efficiency vs Luminosity (Positive)",
                  "Plots/eff_vs_lum_pos.pdf",
                  false);

  DrawThreeGraphs({negA, negB, negC},
                  "c_neg",
                  "Efficiency vs Luminosity (Negative)",
                  "Plots/eff_vs_lum_neg.pdf",
                  false
                  );

  // For batch plotting, keep this commented:
  // app.Run();

  return 0;
}
