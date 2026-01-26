//
// Created by marianav on 1/13/26.
//

#include <writer.h>
#include <reader.h>


#include <vector>

#include <TFile.h>
#include <TH1D.h>
#include <TLorentzVector.h>

using namespace std;


bool IsSameTrack(double,double, double,double,double,double);






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

    sprintf(inputFile, "/w/hallb-scshelf2102/clas12/marianak/rec_eff_init/Conv_Rec_jobs/recon_reduced_clas_%d_%d_rand150.hipo", run, file);

    TFile file_out("Analysis_output/Analysis_out_Conv.root", "RECREATE");


    TH1D h_x_B("h_x_B","",100,0,1.2);
    TH1D h_nu("h_nu","",200,0,20);
    TH1D h_W("h_W","",100,0,6);
    TH1D h_Q2("h_Q2","",200,0,6);
    //Histograms for TimeBasedTrkg::TBTracks
    TH1D h_chi2_NDF1_TBTracks("h_chi2_NDF1_TBTracks", "", 200, 0., 100);
    TH1D h_z_vert_TBTracks("h_z_vert_TBTracks", "", 200, -20, 20);
    TH1D h_p_TBTracks("h_p_TBTracks", "", 20, 0, 12);
    TH1D h_theta_TBTracks("h_theta_TBTracks", "", 25, 0, 80);
    TH1D h_phi_TBTracks("h_phi_TBTracks","",24,0,360);
    TH1D h_p_TBTracks_neg("h_p_TBTracks_neg", "", 20, 0, 12);
    TH1D h_theta_TBTracks_neg("h_theta_TBTracks_neg", "", 25, 0, 80);
    TH1D h_phi_TBTracks_neg("h_phi_TBTracks_neg","",24,0,360);
    TH1D h_p_TBTracks_pos("h_p_TBTracks_pos", "", 20, 0, 12);
    TH1D h_theta_TBTracks_pos("h_theta_TBTracks_pos", "", 25, 0, 80);
    TH1D h_phi_TBTracks_pos("h_phi_TBTracks_pos","",24,0,360);
    //Histograms for TimeBasedTrkg::TBTracks2
    TH1D h_chi2_NDF1_TBTracks2("h_chi2_NDF1_TBTracks2", "", 200, 0., 100);
    TH1D h_z_vert_TBTracks2("h_z_vert_TBTracks2", "", 200, -20, 20);
    TH1D h_p_TBTracks2("h_p_TBTracks2", "", 20, 0, 12);
    TH1D h_theta_TBTracks2("h_theta_TBTracks2", "", 25, 0, 80);
    TH1D h_phi_TBTracks2("h_phi_TBTracks2","",24,0,360);
    TH1D h_p_TBTracks2_neg("h_p_TBTracks2_neg", "", 20,0,12);
    TH1D h_theta_TBTracks2_neg("h_theta_TBTracks2_neg", "", 25, 0, 80);
    TH1D h_phi_TBTracks2_neg("h_phi_TBTracks2_neg","",24,0,360);
    TH1D h_p_TBTracks2_pos("h_p_TBTracks2_pos", "", 20, 0, 12);
    TH1D h_theta_TBTracks2_pos("h_theta_TBTracks2_pos", "", 25, 0, 80);
    TH1D h_phi_TBTracks2_pos("h_phi_TBTracks2_pos","",24,0,360);
    //Histograms for matching tracks in TBTracks and TBTracks2
    TH1D h_p_match_TBTracks("h_p_match_TBTracks", "", 20, 0, 12);
    TH1D h_theta_match_TBTracks("h_theta_match_TBTracks", "", 25, 0, 80);
    TH1D h_phi_match_TBTracks("h_phi_match_TBTracks","",24,0,360);
    TH1D h_p_match_TBTracks_neg("h_p_match_TBTracks_neg", "", 20, 0, 12);
    TH1D h_theta_match_TBTracks_neg("h_theta_match_TBTracks_neg", "", 25, 0, 80);
    TH1D h_phi_match_TBTracks_neg("h_phi_match_TBTracks_neg","",24,0,360);
    TH1D h_p_match_TBTracks_pos("h_p_match_TBTracks_pos", "", 20, 0, 12);
    TH1D h_theta_match_TBTracks_pos("h_theta_match_TBTracks_pos", "", 25, 0, 80);
    TH1D h_phi_match_TBTracks_pos("h_phi_match_TBTracks_pos","",24,0,360);


   //Store weights to correctly calculate errors
    h_p_TBTracks.Sumw2();
    h_theta_TBTracks.Sumw2();
    h_phi_TBTracks.Sumw2();
    h_p_TBTracks_neg.Sumw2();
    h_theta_TBTracks_neg.Sumw2();
    h_phi_TBTracks_neg.Sumw2();
    h_p_TBTracks_pos.Sumw2();
    h_theta_TBTracks_pos.Sumw2();
    h_phi_TBTracks_pos.Sumw2();

    h_p_TBTracks2.Sumw2();
    h_theta_TBTracks2.Sumw2();
    h_phi_TBTracks2.Sumw2();
    h_p_TBTracks2_neg.Sumw2();
    h_theta_TBTracks2_neg.Sumw2();
    h_phi_TBTracks2_neg.Sumw2();
    h_p_TBTracks2_pos.Sumw2();
    h_theta_TBTracks2_pos.Sumw2();
    h_phi_TBTracks2_pos.Sumw2();

    h_p_match_TBTracks.Sumw2();
    h_theta_match_TBTracks.Sumw2();
    h_phi_match_TBTracks.Sumw2();
    h_p_match_TBTracks_neg.Sumw2();
    h_theta_match_TBTracks_neg.Sumw2();
    h_phi_match_TBTracks_neg.Sumw2();
    h_p_match_TBTracks_pos.Sumw2();
    h_theta_match_TBTracks_pos.Sumw2();
    h_phi_match_TBTracks_pos.Sumw2();


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
    hipo::bank bTBTrkgTBTracks2(factory.getSchema("TimeBasedTrkg::TBTracks2"));
    hipo::bank bRECParticle(factory.getSchema("REC::Particle"));




     try {
        while (reader.next() == true) {
            //looping through events

          //   if( evCounter > 15000 ){
            // 	break;
           //  }

            reader.read(event); //The bank gets populated with tracks from the current event

            /*
            * Reading necesary banks
            */
            event.getStructure(bTBTrkgTBTracks);
            event.getStructure(bTBTrkgTBTracks2);
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




            int nTrk2 = bTBTrkgTBTracks2.getRows(); // Number of rows of the bank
            //looping through TimeBasedTrkg::TBTracks2
            for (auto itrk = 0; itrk < nTrk2; itrk++) {
                //loop through reconstructed trucks


                double chi2_2 = bTBTrkgTBTracks2.getFloat("chi2", itrk);
                int ndf_2 = bTBTrkgTBTracks2.getInt("ndf", itrk);
                double z_vert_2 = bTBTrkgTBTracks2.getFloat("Vtx0_z", itrk);
                int charge_2=bTBTrkgTBTracks2.getInt("q", itrk);
                double p_x_2= bTBTrkgTBTracks2.getFloat("p0_x", itrk);
                double p_y_2= bTBTrkgTBTracks2.getFloat("p0_y", itrk);
                double p_z_2= bTBTrkgTBTracks2.getFloat("p0_z", itrk);
                double p_tot_2=sqrt(p_x_2*p_x_2+p_y_2*p_y_2+p_z_2*p_z_2);
                double theta_2=acos(p_z_2/p_tot_2) * 180.0 / M_PI;
                double phi_2=atan2(p_y_2,p_x_2); //phi is from -pi to pi
                phi_2=(phi_2 < 0) ? phi_2 + 2*M_PI : phi_2;
                phi_2=phi_2* 180.0 / M_PI;



                h_chi2_NDF1_TBTracks2.Fill(chi2_2 / ndf_2);
                h_z_vert_TBTracks2.Fill(z_vert_2);
                h_p_TBTracks2.Fill(p_tot_2);
                h_theta_TBTracks2.Fill(theta_2);
                h_phi_TBTracks2.Fill(phi_2);

                if (charge_2<0) {
                    h_p_TBTracks2_neg.Fill(p_tot_2);
                    h_theta_TBTracks2_neg.Fill(theta_2);
                    h_phi_TBTracks2_neg.Fill(phi_2);
                }

                if (charge_2>0) {
                    h_p_TBTracks2_pos.Fill(p_tot_2);
                    h_theta_TBTracks2_pos.Fill(theta_2);
                    h_phi_TBTracks2_pos.Fill(phi_2);
                }




                //looping through TimeBasedTrkg::TBTracks
                for (auto itrk = 0; itrk < nTrk; itrk++) {

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

                    if (IsSameTrack(p_tot,theta,phi,p_tot_2,theta_2,phi_2)) {


                        h_p_match_TBTracks.Fill(p_tot);
                        h_phi_match_TBTracks.Fill(phi_2);
                        h_theta_match_TBTracks.Fill(theta_2);

                        if (charge_2<0) {
                            h_p_match_TBTracks_neg.Fill(p_tot);
                            h_phi_match_TBTracks_neg.Fill(phi_2);
                            h_theta_match_TBTracks_neg.Fill(theta_2);
                        }

                        if (charge_2>0) {
                            h_p_match_TBTracks_pos.Fill(p_tot);
                            h_phi_match_TBTracks_pos.Fill(phi_2);
                            h_theta_match_TBTracks_pos.Fill(theta_2);
                        }

                    }

                }//end  of TBTracks loop




            }//end  of TBTracks2 loop





            int nPart = bRECParticle.getRows(); // Number of rows of the bank

            for (auto itrk = 0; itrk < nPart; itrk++) {
                //loop through reconstructed trucks

                double part_px = bRECParticle.getFloat("px", itrk);
                double part_py = bRECParticle.getFloat("py", itrk);
                double part_pz = bRECParticle.getFloat("pz", itrk);
                int part_pid = bRECParticle.getInt("pid", itrk);
                int part_status = abs(bRECParticle.getInt("status", itrk));
                double part_mom=sqrt(part_px*part_px+part_py*part_py+part_pz*part_pz);




                if (part_pid==el_pid  && part_status>2000 && part_status<4000) {

                    TLorentzVector p4_e(part_px,part_py,part_pz,part_mom);

                    double nu=(p4_beam-p4_e).E();
                    double Q2=-(p4_beam-p4_e).M2();
                    double x_B=Q2/(2*M_p*nu);
                    double W=(p4_beam-p4_e+p4_target).M();

                    h_x_B.Fill(x_B);
                    h_nu.Fill(nu);
                    h_W.Fill(W);
                    h_Q2.Fill(Q2);

                }


            }






            evCounter = evCounter + 1;
        }
    } catch (const char msg) {
        cerr << msg << endl;
    }




//All charged particles
    TH1* hEff_vs_p = (TH1*) h_p_TBTracks.Clone("hEff_vs_p");
    hEff_vs_p->Divide(&h_p_TBTracks, &h_p_TBTracks2,1,1,"B");
    TH1* hEff_vs_theta = (TH1*) h_theta_TBTracks.Clone("hEff_vs_theta");
    hEff_vs_theta->Divide(&h_theta_TBTracks, &h_theta_TBTracks2,1,1,"B");
    TH1* hEff_vs_phi = (TH1*) h_phi_TBTracks.Clone("hEff_vs_phi");
    hEff_vs_phi->Divide(&h_phi_TBTracks, &h_phi_TBTracks2,1,1,"B");
//negative particles
    TH1* hEff_vs_p_neg = (TH1*) h_p_TBTracks_neg.Clone("hEff_vs_p_neg");
    hEff_vs_p_neg->Divide(&h_p_TBTracks_neg, &h_p_TBTracks2_neg,1,1,"B");
    TH1* hEff_vs_theta_neg = (TH1*) h_theta_TBTracks_neg.Clone("hEff_vs_theta_neg");
    hEff_vs_theta_neg->Divide(&h_theta_TBTracks_neg, &h_theta_TBTracks2_neg,1,1,"B");
    TH1* hEff_vs_phi_neg = (TH1*) h_phi_TBTracks_neg.Clone("hEff_vs_phi_neg");
    hEff_vs_phi_neg->Divide(&h_phi_TBTracks_neg, &h_phi_TBTracks2_neg,1,1,"B");
//positive particles
    TH1* hEff_vs_p_pos = (TH1*) h_p_TBTracks_pos.Clone("hEff_vs_p_pos");
    hEff_vs_p_pos->Divide(&h_p_TBTracks_pos, &h_p_TBTracks2_pos,1,1,"B");
    TH1* hEff_vs_theta_pos = (TH1*) h_theta_TBTracks_pos.Clone("hEff_vs_theta_pos");
    hEff_vs_theta_pos->Divide(&h_theta_TBTracks_pos, &h_theta_TBTracks2_pos,1,1,"B");
    TH1* hEff_vs_phi_pos = (TH1*) h_phi_TBTracks_pos.Clone("hEff_vs_phi_pos");
    hEff_vs_phi_pos->Divide(&h_phi_TBTracks_pos, &h_phi_TBTracks2_pos,1,1,"B");




    //Efficiency with matching tracks in TBTracks and TBTracks2
    TH1* hEff_vs_p_match = (TH1*) h_p_match_TBTracks.Clone("hEff_vs_p_match");
    hEff_vs_p_match->Divide(&h_p_match_TBTracks, &h_p_TBTracks2,1,1,"B");
    TH1* hEff_vs_theta_match = (TH1*) h_theta_match_TBTracks.Clone("hEff_vs_theta_match");
    hEff_vs_theta_match->Divide(&h_theta_match_TBTracks, &h_theta_TBTracks2,1,1,"B");
    TH1* hEff_vs_phi_match = (TH1*) h_phi_match_TBTracks.Clone("hEff_vs_phi_match");
    hEff_vs_phi_match->Divide(&h_phi_match_TBTracks, &h_phi_TBTracks2,1,1,"B");
    //negative particles
    TH1* hEff_vs_p_match_neg = (TH1*) h_p_match_TBTracks_neg.Clone("hEff_vs_p_match_neg");
    hEff_vs_p_match_neg->Divide(&h_p_match_TBTracks_neg, &h_p_TBTracks2_neg,1,1,"B");
    TH1* hEff_vs_theta_match_neg = (TH1*) h_theta_match_TBTracks_neg.Clone("hEff_vs_theta_match_neg");
    hEff_vs_theta_match_neg->Divide(&h_theta_match_TBTracks_neg, &h_theta_TBTracks2_neg,1,1,"B");
    TH1* hEff_vs_phi_match_neg = (TH1*) h_phi_match_TBTracks_neg.Clone("hEff_vs_phi_match_neg");
    hEff_vs_phi_match_neg->Divide(&h_phi_match_TBTracks_neg, &h_phi_TBTracks2_neg,1,1,"B");
    //positive particles
    TH1* hEff_vs_p_match_pos = (TH1*) h_p_match_TBTracks_pos.Clone("hEff_vs_p_match_pos");
    hEff_vs_p_match_pos->Divide(&h_p_match_TBTracks_pos, &h_p_TBTracks2_pos,1,1,"B");
    TH1* hEff_vs_theta_match_pos = (TH1*) h_theta_match_TBTracks_pos.Clone("hEff_vs_theta_match_pos");
    hEff_vs_theta_match_pos->Divide(&h_theta_match_TBTracks_pos, &h_theta_TBTracks2_pos,1,1,"B");
    TH1* hEff_vs_phi_match_pos = (TH1*) h_phi_match_TBTracks_pos.Clone("hEff_vs_phi_match_pos");
    hEff_vs_phi_match_pos->Divide(&h_phi_match_TBTracks_pos, &h_phi_TBTracks2_pos,1,1,"B");





    //gDirectory->Write();
    file_out.cd();
    file_out.Write();
    file_out.Close();


    return 0;


}




bool IsSameTrack(double p1,double theta1,double phi1,double p2,double theta2,double phi2) {

    double p_range=0.1;  //GeV/c
    double phi_range=1.5; //Deg.
    double theta_range=2.5;  //Deg.

    return abs(p1-p2)<p_range && abs(theta1-theta2)<theta_range && abs(phi1-phi2)<phi_range;

}