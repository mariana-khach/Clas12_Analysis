//
// Created by marianav on 1/14/26.
//

#include <writer.h>
#include <reader.h>


#include <vector>

#include <TFile.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TLorentzVector.h>

using namespace std;


int main(int argc, char **argv) {

    if (argc < 3) {
        cerr << "Usage: ./test1.exe <RUN> <File>" << endl;
        cerr << "Exiting" << endl;
        exit(1);
    }

    int run = atoi(argv[1]);
    int file = atoi(argv[2]);

    char inputFile[256];
    const int el_pid=11;
    const double M_p=0.938; //GeV/c^2
    const double E_beam=10.6;  //GeV
    TLorentzVector p4_target(0.,0.,0.,M_p);
    TLorentzVector p4_beam(0.,0.,E_beam,E_beam);

    sprintf(inputFile, "recon_clas_%d_%d.hipo", run, file);

    TFile file_out("Analysis_beforereducing_out.root", "RECREATE");


    TH1D h_x_B("h_x_B","",100,0,1.2);
    TH1D h_nu("h_nu","",200,0,20);
    TH1D h_W("h_W","",300,0,6);
    TH1D h_Q2("h_Q2","",200,0,6);
    TH2D h2_theta_mom("h2_theta_mom","",200,0,20,200,0,180);
    //Histograms for TimeBasedTrkg::TBTracks
    TH1D h_chi2_NDF1_TBTracks("h_chi2_NDF1_TBTracks", "", 200, 0., 100);
    TH1D h_z_vert_TBTracks("h_z_vert_TBTracks", "", 200, -20, 20);
    TH1D h_p_TBTracks("h_p_TBTracks", "", 200, 0, 20);
    TH1D h_theta_TBTracks("h_theta_TBTracks", "", 200, 0, 180);
    TH1D h_phi_TBTracks("h_phi_TBTracks","",1080,0,360);
    TH1D h_p_TBTracks_neg("h_p_TBTracks_neg", "", 200, 0, 20);
    TH1D h_theta_TBTracks_neg("h_theta_TBTracks_neg", "", 200, 0, 180);
    TH1D h_phi_TBTracks_neg("h_phi_TBTracks_neg","",1080,0,360);
    TH1D h_p_TBTracks_pos("h_p_TBTracks_pos", "", 200, 0, 20);
    TH1D h_theta_TBTracks_pos("h_theta_TBTracks_pos", "", 200, 0, 180);
    TH1D h_phi_TBTracks_pos("h_phi_TBTracks_pos","",1080,0,360);



    hipo::reader reader; //declaring HIPO file reader
    reader.open(inputFile); //open HIPO file, read the file header and load the schema dictionary

    hipo::dictionary factory; //declare empty schema dictionary
    reader.readDictionary(factory); //copy schema definitions into factory

    //factory.show();

    hipo::event event;
    int evCounter = 0;

    //Look up the schema definition (column names + types) by name
    //Creates a hipo::bank object (hipo::bank bTBTrkgTBTracks()) that can later be filled per event
    hipo::bank bTBTrkgTBTracks(factory.getSchema("TimeBasedTrkg::TBTracks"));
    hipo::bank bRECParticle(factory.getSchema("REC::Particle"));




     try {
        while (reader.next() == true) {
            //looping through events

            // if( evCounter > 100 ){
            // 	break;
            // }

            reader.read(event); //The bank gets populated with tracks from the current event

            /*
            * Reading necesary banks
            */
           event.getStructure(bTBTrkgTBTracks);
           event.getStructure(bRECParticle);

            int nTrk = bTBTrkgTBTracks.getRows(); // Number of rows of the bank

            for (auto itrk = 0; itrk < nTrk; itrk++) {
                //loop through reconstructed trucks

                double chi2 = bTBTrkgTBTracks.getFloat("chi2", itrk);
                int ndf = bTBTrkgTBTracks.getInt("ndf", itrk);
                double z_vert = bTBTrkgTBTracks.getFloat("Vtx0_z", itrk);
                double p_x= bTBTrkgTBTracks.getFloat("p0_x", itrk);
                double p_y= bTBTrkgTBTracks.getFloat("p0_y", itrk);
                double p_z= bTBTrkgTBTracks.getFloat("p0_z", itrk);
                int charge=bTBTrkgTBTracks.getInt("q", itrk);
                double p_tot=sqrt(p_x*p_x+p_y*p_y+p_z*p_z);
                double theta=acos(p_z/p_tot) * 180.0 / M_PI;
                double phi=atan2(p_y,p_x); //phi is from -pi to pi
                phi=(phi < 0) ? phi + 2*M_PI : phi;
                phi=phi* 180.0 / M_PI;

                h_chi2_NDF1_TBTracks.Fill(chi2 / ndf);
                h_z_vert_TBTracks.Fill(z_vert);
                h_p_TBTracks.Fill(p_tot);
                h_theta_TBTracks.Fill(theta);
                h_phi_TBTracks.Fill(phi);

                if (charge<0) {
                    h_p_TBTracks_neg.Fill(p_tot);
                    h_theta_TBTracks_neg.Fill(theta);
                    h_phi_TBTracks_neg.Fill(phi);
                }

                if (charge>0) {
                    h_p_TBTracks_pos.Fill(p_tot);
                    h_theta_TBTracks_pos.Fill(theta);
                    h_phi_TBTracks_pos.Fill(phi);
                }



            }


            int nPart = bRECParticle.getRows(); // Number of rows of the bank

            for (auto itrk = 0; itrk < nPart; itrk++) {
                //loop through reconstructed trucks

                double part_px = bRECParticle.getFloat("px", itrk);
                double part_py = bRECParticle.getFloat("py", itrk);
                double part_pz = bRECParticle.getFloat("pz", itrk);
                int part_pid = bRECParticle.getInt("pid", itrk);
                int part_status = abs(bRECParticle.getInt("status", itrk));
                double part_mom=sqrt(part_px*part_px+part_py*part_py+part_pz*part_pz);



                if (part_pid==el_pid && part_status>=2000 && part_status<4000) {
               // if (part_pid==el_pid) {


                    TLorentzVector p4_e(part_px,part_py,part_pz,part_mom);

                    double nu=(p4_beam-p4_e).E();
                    double Q2=-(p4_beam-p4_e).M2();
                    double x_B=Q2/(2*M_p*nu);
                    double W=(p4_beam-p4_e+p4_target).M();
                    double theta=acos(part_pz/part_mom) * 180.0 / M_PI;

                    h_x_B.Fill(x_B);
                    h_nu.Fill(nu);
                    h_W.Fill(W);
                    h_Q2.Fill(Q2);
                    h2_theta_mom.Fill(part_mom, theta);

                }


            }





            evCounter = evCounter + 1;
        }
    } catch (const char msg) {
        cerr << msg << endl;
    }





    //gDirectory->Write();
    file_out.cd();
    file_out.Write();
    file_out.Close();


    return 0;


}