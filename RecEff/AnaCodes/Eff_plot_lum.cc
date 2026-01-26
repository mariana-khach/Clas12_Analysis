//
// Created by marianav on 1/21/26.
//

#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>
#include <TGraphErrors.h>
#include <TAxis.h>

#include <vector>
#include <string>
#include <iostream>
#include <cmath>
#include <algorithm>

static bool read_ratio_entries(const std::string& filename,
                               const char* h_num_name,
                               const char* h_den_name,
                               double& ratio,
                               double& eratio)
{
    TFile* f = TFile::Open(filename.c_str(), "READ");
    if (!f || f->IsZombie()) {
        std::cerr << "Error opening " << filename << "\n";
        return false;
    }

    TH1* hnum = dynamic_cast<TH1*>(f->Get(h_num_name));
    TH1* hden = dynamic_cast<TH1*>(f->Get(h_den_name));

    if (!hnum || !hden) {
        std::cerr << "Missing histogram(s) in " << filename << " : "
                  << (hnum ? "" : h_num_name) << " "
                  << (hden ? "" : h_den_name) << "\n";
        f->Close();
        delete f;
        return false;
    }

    const double Nnum = hnum->GetEntries();
    const double Nden = hden->GetEntries();

    ratio  = 0.0;
    eratio = 0.0;

    if (Nden <= 0.0) {
        std::cerr << "Denominator has 0 entries in " << filename << "\n";
        f->Close();
        delete f;
        return false;
    }

    ratio = Nnum / Nden;

    // Poisson propagation for ratio r = Nnum/Nden (independent counts)
    if (Nnum > 0.0) {
        eratio = ratio * std::sqrt((1.0 / Nnum) + (1.0 / Nden));
    } else {
        eratio = 0.0;
    }

    f->Close();
    delete f;
    return true;
}

int main() {
    gStyle->SetOptStat(0);

    // Hist names
    const char* h_num_name = "h_p_match_TBTracks_neg";
    const char* h_den_name = "h_p_TBTracks2_neg";

    // X values you requested
    std::vector<double> xvals = {0.0, 45.0, 100.0, 150.0};

    // For each x, provide 3 files in THIS ORDER:
    //   [0] Denoised AI rec.
    //   [1] AI rec.
    //   [2] Conv. rec.
    //
    // Replace these placeholders with your actual filenames.
    std::vector<std::vector<std::string>> files_at_x = {
        // x = 0
        {"/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_denoised.root",  "/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_AI.root",  "/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_Conv.root"},
        // x = 45
        {"/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_denoised.root", "/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_AI.root", "/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_Conv.root"},
        // x = 100
        {"/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_denoised.root","/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_AI.root","/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_Conv.root"},
        // x = 150
        {"/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_denoised.root","/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_AI.root","/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_Conv.root"}
    };

    // Labels/styles (3 reconstruction types)
    std::vector<std::string> labels = {"Denoised AI rec.", "AI rec.", "Conv. rec."};
    std::vector<int> colors = {kRed+1, kBlue+1, kBlack};
    std::vector<int> mstyles = {20, 21, 22};

    // We will build 3 graphs, each with 4 points (x = 0,45,100,150)
    const int nReco = 3;
    std::vector<std::vector<double>> y(nReco), ey(nReco);
    for (int r = 0; r < nReco; r++) {
        y[r].assign(xvals.size(), 0.0);
        ey[r].assign(xvals.size(), 0.0);
    }

    // Compute ratios
    for (size_t ix = 0; ix < xvals.size(); ix++) {
        if (files_at_x[ix].size() != 3) {
            std::cerr << "files_at_x[" << ix << "] must have exactly 3 files.\n";
            return 1;
        }

        for (int r = 0; r < nReco; r++) {
            double ratio = 0.0, eratio = 0.0;
            bool ok = read_ratio_entries(files_at_x[ix][r], h_num_name, h_den_name, ratio, eratio);
            if (!ok) {
                // keep 0; still plot others
                ratio = 0.0;
                eratio = 0.0;
            }
            y[r][ix] = ratio;
            ey[r][ix] = eratio;
        }
    }

    // Determine y-range
    double ymax = 0.0;
    for (int r = 0; r < nReco; r++) {
        for (double v : y[r]) ymax = std::max(ymax, v);
    }
    if (ymax <= 0.0) ymax = 1.0;
    ymax *= 1.25;

    // Make canvas
    TCanvas* c = new TCanvas("c_ratio_vs_x", "TBTracks neg entry ratio vs X", 950, 700);

    // Frame: expand x range a bit for aesthetics
    double xmin = *std::min_element(xvals.begin(), xvals.end());
    double xmax = *std::max_element(xvals.begin(), xvals.end());
    double xpad = 0.05 * (xmax - xmin);
    if (xpad <= 0) xpad = 1.0;

    TH1F* frame = c->DrawFrame(xmin - xpad, 0.0, xmax + xpad, ymax);
    frame->SetTitle("Entries ratio vs X;X;Entries(h_{p match TBTracks neg}) / Entries(h_{p TBTracks2 neg})");

    // Create and draw graphs
    TLegend* leg = new TLegend(0.60, 0.70, 0.88, 0.88);
    leg->SetBorderSize(0);
    leg->SetFillStyle(0);
    leg->SetTextSize(0.035);

    for (int r = 0; r < nReco; r++) {
        TGraphErrors* gr = new TGraphErrors((int)xvals.size());
        for (size_t ix = 0; ix < xvals.size(); ix++) {
            gr->SetPoint((int)ix, xvals[ix], y[r][ix]);
            gr->SetPointError((int)ix, 0.0, ey[r][ix]);
        }

        gr->SetLineColor(colors[r]);
        gr->SetMarkerColor(colors[r]);
        gr->SetLineWidth(2);
        gr->SetMarkerStyle(mstyles[r]);
        gr->SetMarkerSize(1.3);

        // "PL" draws points connected by lines
        gr->Draw(r == 0 ? "PL SAME" : "PL SAME");
        leg->AddEntry(gr, labels[r].c_str(), "pl");
    }

    leg->Draw();

    c->SaveAs("TBTracks_neg_entryRatio_vsX.pdf");
    delete c;

    return 0;
}
