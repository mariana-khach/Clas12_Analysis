//
// Created by marianav on 12/22/25.
//

// ===== Hipo headers =====
#include <reader.h>
#include <writer.h>
#include <dictionary.h>

#include <set>
#include <vector>

#include <TFile.h>
#include <TH1D.h>

using namespace std;

bool IsGoodTrack(double, double,double,double);
void FillReducedBank(std::set<int> trkIDs, hipo::bank &btbHits, hipo::bank &bdcTot, hipo::bank &bdcTotReduced);
std::string getSecondCurly(const std::string& s);
void FillCopyBank(std::set<int>&, hipo::bank &bTTrkgTBTracks2, hipo::bank &bTBTrkgTBTracks);

int main(int argc, char **argv) {
    if (argc < 3) {
        cerr << "Usage: ./test1.exe <RUN> <File>" << endl;
        cerr << "Exiting" << endl;
        exit(1);
    }


    int run = atoi(argv[1]);
    int file = atoi(argv[2]);

    char inputFile[256];
    char outputFile[256];
    sprintf(inputFile, "recon_clas_%d_%d.hipo", run, file);
    sprintf(outputFile, "reduced_clas_%d_%d_test.hipo", run, file);

    TFile file_out("TestOut.root", "RECREATE");
    TH1D h_chi2_NDF1("h_chi2_NDF1", "", 200, 0., 100);
    TH1D h_z_vert("h_z_vert", "", 200, -20, 20);
    TH1D h_x_vert("h_x_vert", "", 200, -20, 20);
    TH1D h_y_vert("h_y_vert", "", 200, -20, 20);
    TH1D h_z_vert_cut("h_z_vert_cut", "", 200, -20, 20);
    TH1D h_x_vert_cut("h_x_vert_cut", "", 200, -20, 20);
    TH1D h_y_vert_cut("h_y_vert_cut", "", 200, -20, 20);
    TH1D h_hitID("h_hitID", "", 1301, -0.5, 1300.5);

    hipo::reader reader; //declaring HIPO file reader
    reader.open(inputFile); //open HIPO file, read the file header and load the schema dictionary

    hipo::dictionary factory; //declare empty schema dictionary
    reader.readDictionary(factory); //copy schema definitions into factory

    //factory.show();

    hipo::event event;

    int evCounter = 0;
    int N_commonhit = 0;
    int N_events=0;

    //Look up the schema definition (column names + types) by name
    //Creates a hipo::bank object (hipo::bank bTBTrkgTBTracks()) that can later be filled per event
    hipo::bank bTBTrkgTBTracks(factory.getSchema("TimeBasedTrkg::TBTracks"));
    //use this bank to look at vertex distributions for reconstructed tracks
    hipo::bank bTTrkgTbHits(factory.getSchema("TimeBasedTrkg::TBHits"));
    // use this bank to look at the hits corresponding to reconstructed tracks, id corresponds to index of the hit in DC::tdc, we use this to reduce DC::tot hits based on vertex cuts
    hipo::bank bRecPart(factory.getSchema("REC::Particle"));
    hipo::bank bDCTot(factory.getSchema("DC::tdc"));
    //bank names except "DC::tdc" to write in output hipo
    std::vector<std::string> v_DecodeBankNames = {"BMT::adc","BST::adc","CND::adc","CND::tdc","CTOF::adc","CTOF::tdc",
                                                "DC::jitter","ECAL::adc", "ECAL::tdc","FTCAL::adc","FTHODO::adc",
                                                "FTOF::adc", "FTOF::tdc","FTTRK::adc","HEL::adc","HTCC::adc","RAW::tdc",
                                               "RAW::vtp","RF::adc","RF::tdc","RICH::tdc","RUN::config","RUN::trigger"};
    std::vector<hipo::bank> v_DecodeBanks;  //vector of hipo::bank objects
    for (auto bankName : v_DecodeBankNames) {
        v_DecodeBanks.push_back(hipo::bank(factory.getSchema(bankName.c_str())));  //lokup schema and use it to construct hipo::bank
    }





    hipo::writer writer; //create an output writer object


    //Create a new TBTracks2 bank based on TBTracks to save good track info in the output file
    hipo::schema schTB = factory.getSchema("TimeBasedTrkg::TBTracks");  // original schema
    hipo::schema schTB2("TimeBasedTrkg::TBTracks2", 90, 1);  //group and item numbers should not coincide with existing ones
    std::string schTB2_struct_str=schTB.getSchemaString();
    std::string schTB2_struct_str_format = getSecondCurly(schTB2_struct_str);
    schTB2.parse(schTB2_struct_str_format);
    writer.getDictionary().addSchema(schTB2); //add TimeBasedTrkg::TBTracks2 to the writer's schema dictionary
    //Create a new TBClusters2 bank based on TBClusters to save good track info in the output file
    hipo::schema schTBClust = factory.getSchema("TimeBasedTrkg::TBClusters");  // original schema
    hipo::schema schTBClust2("TimeBasedTrkg::TBClusters2", 110, 1);  //group and item numbers should not coincide with existing ones
    std::string schTBClust2_struct_str=schTBClust.getSchemaString();
    std::string schTBClust2_struct_str_format = getSecondCurly(schTBClust2_struct_str);
    schTBClust2.parse(schTB2_struct_str_format);
    writer.getDictionary().addSchema(schTBClust2); //add TimeBasedTrkg::TBClusters2 to the writer's schema dictionary




    hipo::schema sch_dcTOT = factory.getSchema("DC::tdc");
    //Ask the schema factory for the definition of the DC::tdc bank, Store it explicitly as a hipo::schema object
    writer.getDictionary().addSchema(sch_dcTOT); //add DC::tdc to the writer's schema dictionary

    std::vector<hipo::schema> v_DecodeSchemas;
    for (auto bankName : v_DecodeBankNames) {
        writer.getDictionary().addSchema(factory.getSchema(bankName.c_str()));
    }



    writer.open(outputFile);

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
            event.getStructure(bTTrkgTbHits);
            event.getStructure(bDCTot);

            int nTrk = bTBTrkgTBTracks.getRows(); // Number of rows of the bank

            int nGoodTrk = 0;

            std::set<int> s_goodTrkIDs; // This set will keep Track IDs of good tracks

            for (auto itrk = 0; itrk < nTrk; itrk++) {
                //loop through reconstructed trucks

                double chi2 = bTBTrkgTBTracks.getFloat("chi2", itrk);
                int ndf = bTBTrkgTBTracks.getInt("ndf", itrk);
                double z_vert = bTBTrkgTBTracks.getFloat("Vtx0_z", itrk);
                double x_vert = bTBTrkgTBTracks.getFloat("Vtx0_x", itrk);
                double y_vert = bTBTrkgTBTracks.getFloat("Vtx0_y", itrk);
                if (ndf > 0) {
                    h_chi2_NDF1.Fill(chi2 / ndf);
                    h_z_vert.Fill(z_vert);
                    h_x_vert.Fill(x_vert);
                    h_y_vert.Fill(y_vert);

                    if (IsGoodTrack(chi2 / ndf, x_vert,y_vert, z_vert)) {
                        s_goodTrkIDs.insert(itrk);
                        nGoodTrk = nGoodTrk + 1;

                        h_z_vert_cut.Fill(z_vert);
                        h_x_vert_cut.Fill(x_vert);
                        h_y_vert_cut.Fill(y_vert);
                    }
                }
            }
            int nTrkHits = bTTrkgTbHits.getRows();
            int nGoodTrkHits = 0; // Number of hits on Good track

            for (int itrkHit = 0; itrkHit < nTrkHits; itrkHit++) {
                int hitID = bTTrkgTbHits.getInt("id", itrkHit);
                int trkID = bTTrkgTbHits.getInt("trkID", itrkHit) - 1;
                h_hitID.Fill(hitID); // hitIDs start from 1

                if (s_goodTrkIDs.find(trkID) != s_goodTrkIDs.end()  && (hitID-1) <= bDCTot.getRows()) {
                    //If this hit’s track ID belongs to the set of “good” tracks and hit is not common to two clusters, count it
                    nGoodTrkHits = nGoodTrkHits + 1;
                }
            }


            if (nGoodTrk > 0) {
                hipo::event outEvent;
                hipo::bank bDCTotReduced(sch_dcTOT, nGoodTrkHits); //creates a new HIPO bank with a fixed number of rows to store a reduced copy of the DC::tot bank.
                hipo::bank bTTrkgTBTracks2(schTB2, nGoodTrk );

                //Using bTTrkgTbHits to select hits with track ids in s_goodTrkIDs and save corresponding hits from bDCTot in bDCTotReduced
                FillReducedBank(s_goodTrkIDs, bTTrkgTbHits, bDCTot, bDCTotReduced);
                FillCopyBank(s_goodTrkIDs,bTTrkgTBTracks2, bTBTrkgTBTracks); //Writing TBTracks2 using TBTracks


                //check amount of events with hits common to two clusters
                int nTrkHits = bTTrkgTbHits.getRows();
                N_events=N_events+1;
                for (int iTrkHit = 0; iTrkHit < nTrkHits; iTrkHit++) {
                    int trkID = bTTrkgTbHits.getInt("trkID", iTrkHit) - 1;

                    if (s_goodTrkIDs.find(trkID) != s_goodTrkIDs.end()) {
                        //if track id is in good track set
                        int hitID = bTTrkgTbHits.getInt("id", iTrkHit) - 1;
                        if (hitID > bDCTot.getRows()) {
                            N_commonhit=N_commonhit+1;
                            break;
                        }
                    }
                }






                outEvent.addStructure(bTTrkgTBTracks2);
                outEvent.addStructure(bDCTotReduced);
                for (auto decodeBank : v_DecodeBanks) {
                    event.getStructure(decodeBank);  //Reading necesary banks
                    outEvent.addStructure(decodeBank);//Writing necesary banks
                }

                // Other low level banks should be added as well, e.g. FTOF::adc, FTOF::tdc ...
                writer.addEvent(outEvent);
            }


            evCounter = evCounter + 1;
        }

        cout<<"-------------------------------------------------"<<endl;
        cout<<"N commonhit= "<<N_commonhit<<endl;
        cout<<"N events= "<<N_events<<endl;
        cout<<"Percentage=  "<<(float)N_commonhit/N_events*100<<endl;

    } catch (const char msg) {
        cerr << msg << endl;
    }


    //gDirectory->Write();
    file_out.cd();
    file_out.Write();
    file_out.Close();

    writer.close();
    writer.showSummary();


    return 0;
}

bool IsGoodTrack(double chi2NDF, double vx, double vy,double vz) {
    const double VZ_MAX = -1.;
    const double VZ_MIN = -8.;
    const double CHi2NDF_MAX = 4.;
    const double V_xy_radius=5;

    return chi2NDF < CHi2NDF_MAX && vz > VZ_MIN && vz < VZ_MAX && sqrt(vx*vx+vy*vy)<V_xy_radius;
}

/*
 * This function loops over the entries of btbHits bank. It will check if the trackID is in the
 * set "trkIDs", if so then corresponding hit from the bdcTot bank will be written into the bdcTotReduced bank
*/
void FillReducedBank(std::set<int> trkIDs, hipo::bank &btbHits, hipo::bank &bdcTot, hipo::bank &bdcTotReduced) {
    // Ideally this function should never be called when the trkIDs is empty,
    // however it is always better to be saft and check beforehand
    if (trkIDs.empty()) {
        return;
    }

    int nTrkHits = btbHits.getRows();

    int reducedBankIndex = 0;
    for (int iTrkHit = 0; iTrkHit < nTrkHits; iTrkHit++) {
        int trkID = btbHits.getInt("trkID", iTrkHit) - 1;

        if (trkIDs.find(trkID) != trkIDs.end()) {
            //if track id is in good track set
            int hitID = btbHits.getInt("id", iTrkHit) - 1;
            //get the hit index that corresponds to hit index in DC::tdc and save to ouput bank

            //we don't save hits with large id that are common to two clusters
            if (hitID > bdcTot.getRows()) {
                continue;
            }

            //Take the sector value of hit hitID from the original DC::tdc bank and store it as row reducedBankIndex in the reduced bank.
            bdcTotReduced.putByte("sector", reducedBankIndex, bdcTot.getByte("sector", hitID)); //
            bdcTotReduced.putByte("layer", reducedBankIndex, bdcTot.getByte("layer", hitID));
            bdcTotReduced.putShort("component", reducedBankIndex, bdcTot.getShort("component", hitID));
            bdcTotReduced.putByte("order", reducedBankIndex, bdcTot.getByte("order", hitID));
            bdcTotReduced.putInt("TDC", reducedBankIndex, bdcTot.getInt("TDC", hitID));

            reducedBankIndex = reducedBankIndex + 1;
        }
    }
}



// Function for string filtering
std::string getSecondCurly(const std::string& s)
{
    size_t firstClose  = s.find('}');
    size_t secondOpen  = s.find('{', firstClose + 1);
    size_t secondClose = s.find('}', secondOpen + 1);

    return s.substr(secondOpen + 1, secondClose - secondOpen - 1);
}






void FillCopyBank(std::set<int> &trk_ID_set,hipo::bank &bTTrkgTBTracks2, hipo::bank &bTBTrkgTBTracks) {
    int nTrk = bTBTrkgTBTracks.getRows(); // Number of rows of the bank

    int bankInd = 0;
    for (auto itrk = 0; itrk < nTrk; itrk++) {

        if (trk_ID_set.find(itrk) == trk_ID_set.end()) {
            continue;
        }
        //loop through reconstructed trucks

        bTTrkgTBTracks2.putShort("id", bankInd, bTBTrkgTBTracks.getShort("id", itrk));
        bTTrkgTBTracks2.putShort("status", bankInd, bTBTrkgTBTracks.getShort("status", itrk));
        bTTrkgTBTracks2.putByte("sector", bankInd, bTBTrkgTBTracks.getByte("sector", itrk));
        bTTrkgTBTracks2.putFloat("c1_x", bankInd, bTBTrkgTBTracks.getFloat("c1_x", itrk));
        bTTrkgTBTracks2.putFloat("c1_y", bankInd, bTBTrkgTBTracks.getFloat("c1_y", itrk));
        bTTrkgTBTracks2.putFloat("c1_z", bankInd, bTBTrkgTBTracks.getFloat("c1_z", itrk));
        bTTrkgTBTracks2.putFloat("c1_ux", bankInd, bTBTrkgTBTracks.getFloat("c1_ux", itrk));
        bTTrkgTBTracks2.putFloat("c1_uy", bankInd, bTBTrkgTBTracks.getFloat("c1_uy", itrk));
        bTTrkgTBTracks2.putFloat("c1_uz", bankInd, bTBTrkgTBTracks.getFloat("c1_uz", itrk));
        bTTrkgTBTracks2.putFloat("c3_x", bankInd, bTBTrkgTBTracks.getFloat("c3_x", itrk));
        bTTrkgTBTracks2.putFloat("c3_y", bankInd, bTBTrkgTBTracks.getFloat("c3_y", itrk));
        bTTrkgTBTracks2.putFloat("c3_z", bankInd, bTBTrkgTBTracks.getFloat("c3_z", itrk));
        bTTrkgTBTracks2.putFloat("c3_ux", bankInd, bTBTrkgTBTracks.getFloat("c3_ux", itrk));
        bTTrkgTBTracks2.putFloat("c3_uy", bankInd, bTBTrkgTBTracks.getFloat("c3_uy", itrk));
        bTTrkgTBTracks2.putFloat("c3_uz", bankInd, bTBTrkgTBTracks.getFloat("c3_uz", itrk));
        bTTrkgTBTracks2.putFloat("t1_x", bankInd, bTBTrkgTBTracks.getFloat("t1_x", itrk));
        bTTrkgTBTracks2.putFloat("t1_y", bankInd, bTBTrkgTBTracks.getFloat("t1_y", itrk));
        bTTrkgTBTracks2.putFloat("t1_z", bankInd, bTBTrkgTBTracks.getFloat("t1_z", itrk));
        bTTrkgTBTracks2.putFloat("t1_px", bankInd, bTBTrkgTBTracks.getFloat("t1_px", itrk));
        bTTrkgTBTracks2.putFloat("t1_py", bankInd, bTBTrkgTBTracks.getFloat("t1_py", itrk));
        bTTrkgTBTracks2.putFloat("t1_pz", bankInd, bTBTrkgTBTracks.getFloat("t1_pz", itrk));
        bTTrkgTBTracks2.putFloat("Vtx0_x", bankInd, bTBTrkgTBTracks.getFloat("Vtx0_x", itrk));
        bTTrkgTBTracks2.putFloat("Vtx0_y", bankInd, bTBTrkgTBTracks.getFloat("Vtx0_y", itrk));
        bTTrkgTBTracks2.putFloat("Vtx0_z", bankInd, bTBTrkgTBTracks.getFloat("Vtx0_z", itrk));
        bTTrkgTBTracks2.putFloat("p0_x", bankInd, bTBTrkgTBTracks.getFloat("p0_x", itrk));
        bTTrkgTBTracks2.putFloat("p0_y", bankInd, bTBTrkgTBTracks.getFloat("p0_y", itrk));
        bTTrkgTBTracks2.putFloat("p0_z", bankInd, bTBTrkgTBTracks.getFloat("p0_z", itrk));
        bTTrkgTBTracks2.putShort("Cross1_ID", bankInd, bTBTrkgTBTracks.getShort("Cross1_ID", itrk));
        bTTrkgTBTracks2.putShort("Cross2_ID", bankInd, bTBTrkgTBTracks.getShort("Cross2_ID", itrk));
        bTTrkgTBTracks2.putShort("Cross3_ID", bankInd, bTBTrkgTBTracks.getShort("Cross3_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster1_ID", bankInd, bTBTrkgTBTracks.getShort("Cluster1_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster2_ID", bankInd, bTBTrkgTBTracks.getShort("Cluster2_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster3_ID", bankInd, bTBTrkgTBTracks.getShort("Cluster3_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster4_ID", bankInd, bTBTrkgTBTracks.getShort("Cluster4_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster5_ID", bankInd, bTBTrkgTBTracks.getShort("Cluster5_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster6_ID", bankInd, bTBTrkgTBTracks.getShort("Cluster6_ID", itrk));
        bTTrkgTBTracks2.putByte("q", bankInd, bTBTrkgTBTracks.getByte("q", itrk));
        bTTrkgTBTracks2.putFloat("pathlength", bankInd, bTBTrkgTBTracks.getFloat("pathlength", itrk));
        bTTrkgTBTracks2.putFloat("chi2", bankInd, bTBTrkgTBTracks.getFloat("chi2", itrk));
        bTTrkgTBTracks2.putShort("ndf", bankInd, bTBTrkgTBTracks.getShort("ndf", itrk));
        bTTrkgTBTracks2.putShort("ndf0", bankInd, bTBTrkgTBTracks.getShort("ndf0", itrk));
        bankInd = bankInd + 1;
    }
}
