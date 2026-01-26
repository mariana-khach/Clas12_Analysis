//
// Created by marianav on 1/21/26.
//

#include <TFile.h>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TStyle.h>

#include <vector>
#include <string>
#include <iostream>

int main() {
    gStyle->SetOptStat(0);

    // --- ROOT files to compare (same histogram name exists in each) ---
    std::vector<std::string> filenames = {
        "/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_denoised.root",
        "/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_AI.root",
        "/w/hallb-scshelf2102/clas12/marianak/builds/RecEff/bin/Analysis_output/Analysis_out_Conv.root"
    };


    // -----------------------------------
    // Legend labels (same order)
    // -----------------------------------
    std::vector<std::string> labels = {
        "Denoised AI rec.",
        "AI rec.",
        "Conv. rec."
    };

    // --- Histogram names: one output figure per name ---
    std::vector<std::string> histnames = {
        "hEff_vs_theta_match_pos",
        "hEff_vs_p_match_pos",
        "hEff_vs_phi_match_pos",
        "hEff_vs_theta_match_neg",
        "hEff_vs_p_match_neg",
        "hEff_vs_phi_match_neg"
    };

    // --- Colors per file (cycled) ---
    std::vector<int> colors = {kRed, kBlue, kMagenta, kOrange+7, kCyan+2};

    // Loop over histogram names: each creates its own canvas + output file
    for (const auto& hname : histnames) {

        TCanvas *c = new TCanvas(
            Form("c_%s", hname.c_str()),
            hname.c_str(),
            900, 700
        );

        TLegend *leg = new TLegend(0.60, 0.70, 0.88, 0.88);
        leg->SetBorderSize(0);
        leg->SetFillStyle(0);

        bool first = true;

        for (size_t i = 0; i < filenames.size(); i++) {

            TFile *f = TFile::Open(filenames[i].c_str(), "READ");
            if (!f || f->IsZombie()) {
                std::cerr << "Error opening " << filenames[i] << "\n";
                continue;
            }

            TH1 *h = dynamic_cast<TH1*>(f->Get(hname.c_str()));
            if (!h) {
                std::cerr << "Histogram '" << hname << "' not found in " << filenames[i] << "\n";
                f->Close();
                continue;
            }

            // Clone so histogram remains valid after file closes
            TH1 *hc = dynamic_cast<TH1*>(h->Clone(Form("%s_fromFile%zu", hname.c_str(), i)));
            hc->SetDirectory(nullptr);

            hc->SetLineColor(colors[i % colors.size()]);
            hc->SetLineWidth(2);
            hc->SetMarkerStyle(0);

            // ---- Y-axis: same for ALL histograms ----
            hc->SetMinimum(0.0);
            hc->SetMaximum(1.05);

            // Set X-axis range only for theta histograms
            if (hname == "hEff_vs_theta_match_pos" || hname == "hEff_vs_theta_match_neg") {
                hc->GetXaxis()->SetRangeUser(10.0, 35.0);
            }

            // ---- Automatic X-axis label ----
            if (hname.find("theta") != std::string::npos) {
                hc->GetXaxis()->SetTitle("#theta [Deg.]");
            }
            else if (hname.find("_p_") != std::string::npos ||
                     hname.find("vs_p") != std::string::npos) {
                hc->GetXaxis()->SetTitle("p [GeV/c]");
                     }
            else if (hname.find("phi") != std::string::npos) {
                hc->GetXaxis()->SetTitle("#phi [Deg.]");
            }

            // ---- Y-axis label ----
            hc->GetYaxis()->SetTitle("Efficiency");


            if (first) {
                //hc->SetTitle(Form("%s; ;Efficiency", hname.c_str()));
                hc->Draw("HIST");
                first = false;
            } else {
                hc->Draw("HIST SAME");
            }

            leg->AddEntry(hc, labels[i].c_str(), "l");
            f->Close();
            delete f;
        }

        leg->Draw();
        c->SaveAs(Form("Plots/%s_overlay_noback.pdf", hname.c_str()));

        delete c; // legend is owned by pad/canvas, so this is fine
    }

    return 0;
}
