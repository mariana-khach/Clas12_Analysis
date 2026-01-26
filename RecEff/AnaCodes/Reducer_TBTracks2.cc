//
// Created by marianav on 1/7/26.
//

#include <reader.h>
#include <writer.h>
#include <dictionary.h>

#include <vector>

#include <TFile.h>
#include <TH1D.h>

using namespace std;

std::string getSecondCurly(const std::string& s);
void FillReducedBank(hipo::bank &bTTrkgTBTracks2, hipo::bank &bTBTrkgTBTracks);




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
    sprintf(outputFile, "reduced_TBTracks2_clas_%d_%d.hipo", run, file);

    TFile file_out("TestOut_reducedrecon.root", "RECREATE");
    TH1D h_chi2_NDF1("h_chi2_NDF1", "", 200, 0., 100);
    TH1D h_z_vert("h_z_vert", "", 200, -20, 20);
    TH1D h_hitID("h_hitID", "", 1301, -0.5, 1300.5);
    TH1D h_hitsector("h_hitsector", "", 60, -5, 10);

    hipo::reader reader; //declaring HIPO file reader
    reader.open(inputFile); //open HIPO file, read the file header and load the schema dictionary

    hipo::dictionary factory; //declare empty schema dictionary
    reader.readDictionary(factory); //copy schema definitions into factory

    //factory.show();

    hipo::event event;
    int evCounter = 0;

    //Look up the schema definition (column names + types) by name
    //Creates a hipo::bank object (hipo::bank bTBTrkgTBTracks()) that can later be filled per event
   // hipo::bank bTBTrkgTBTracks(factory.getSchema("TimeBasedTrkg::TBTracks"));
    //use this bank to look at vertex distributions for reconstructed tracks
   // hipo::bank bTTrkgTbHits(factory.getSchema("TimeBasedTrkg::TBHits"));
    // use this bank to look at the hits corresponding to reconstructed tracks, id corresponds to index of the hit in DC::tdc, we use this to reduce DC::tot hits based on vertex cuts
    //hipo::bank bRecPart(factory.getSchema("REC::Particle"));
    hipo::bank bDCTot(factory.getSchema("DC::tdc"));
   // hipo::bank bECalADC(factory.getSchema("ECAL::adc"));
    //low level bank names to write in output hipo
    std::vector<std::string> v_DecodeBankNames = {"BMT::adc","BST::adc","CND::adc","CND::tdc","CTOF::adc","CTOF::tdc",
                                                "DC::jitter","ECAL::adc", "ECAL::tdc","FTCAL::adc","FTHODO::adc",
                                                "FTOF::adc", "FTOF::tdc","FTTRK::adc","HEL::adc","HTCC::adc","RAW::tdc",
                                               "RAW::vtp","RF::adc","RF::tdc","RICH::tdc","RUN::config","RUN::trigger","DC::tot"};
    std::vector<hipo::bank> v_DecodeBanks;  //vector of hipo::bank objects
    for (auto bankName : v_DecodeBankNames) {
        v_DecodeBanks.push_back(hipo::bank(factory.getSchema(bankName.c_str())));  //lokup schema and use it to construct hipo::bank
    }
    //Create a new TBTracks2 bank based on TBTracks to save good track info in the output file
    hipo::schema schTB = factory.getSchema("TimeBasedTrkg::TBTracks");  // original schema
    hipo::schema schTB2("TimeBasedTrkg::TBTracks2", 90, 1);  //group and item numbers should not coincide with existing ones
    std::string schTB2_struct_str=schTB.getSchemaString();
    std::string schTB2_struct_str_format = getSecondCurly(schTB2_struct_str);
    schTB2.parse(schTB2_struct_str_format);



    hipo::writer writer; //create an output writer object

    writer.getDictionary().addSchema(schTB2); //add TimeBasedTrkg::TBTracks2 to the writer's schema dictionary
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
          //  event.getStructure(bTBTrkgTBTracks);
           // event.getStructure(bTTrkgTbHits);
            event.getStructure(bDCTot);

            //int nTrk = bTBTrkgTBTracks.getRows(); // Number of rows of the bank


/*
            for (auto itrk = 0; itrk < nTrk; itrk++) {
                //loop through reconstructed trucks

                double chi2 = bTBTrkgTBTracks.getFloat("chi2", itrk);
                int ndf = bTBTrkgTBTracks.getInt("ndf", itrk);
                double z_vert = bTBTrkgTBTracks.getFloat("Vtx0_z", itrk);

                h_chi2_NDF1.Fill(chi2 / ndf);
                h_z_vert.Fill(z_vert);

            }

            int nTrkHits = bTTrkgTbHits.getRows();

            for (int itrkHit = 0; itrkHit < nTrkHits; itrkHit++) {
                int hitID = bTTrkgTbHits.getInt("id", itrkHit);
                h_hitID.Fill(hitID); // hitIDs start from
            }
*/
            int nhit=bDCTot.getRows();
            for (auto i=0;i<nhit;i++) {
                int dc_sect=bDCTot.getByte("sector", i);
                h_hitsector.Fill(dc_sect);
            }



            hipo::event outEvent;
            //Saving banks to a file
/*
            hipo::bank bTTrkgTBTracks2(schTB2, nTrk);
            FillReducedBank(bTTrkgTBTracks2, bTBTrkgTBTracks); //Writing TBTracks2 using TBTracks
            outEvent.addStructure(bTTrkgTBTracks2);
            for (auto decodeBank : v_DecodeBanks) {
                event.getStructure(decodeBank);//Reading necesary banks
                outEvent.addStructure(decodeBank); //Writing necesary banks
            }
*/
            // Other low level banks should be added as well, e.g. FTOF::adc, FTOF::tdc ...
            writer.addEvent(outEvent);

            evCounter = evCounter + 1;
        }
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


// Function for string filtering
std::string getSecondCurly(const std::string& s)
{
    size_t firstClose  = s.find('}');
    size_t secondOpen  = s.find('{', firstClose + 1);
    size_t secondClose = s.find('}', secondOpen + 1);

    return s.substr(secondOpen + 1, secondClose - secondOpen - 1);
}


void FillReducedBank(hipo::bank &bTTrkgTBTracks2, hipo::bank &bTBTrkgTBTracks) {
    int nTrk = bTBTrkgTBTracks.getRows(); // Number of rows of the bank

    for (auto itrk = 0; itrk < nTrk; itrk++) {
        //loop through reconstructed trucks

        bTTrkgTBTracks2.putShort("id", itrk, bTBTrkgTBTracks.getShort("id", itrk));
        bTTrkgTBTracks2.putShort("status", itrk, bTBTrkgTBTracks.getShort("status", itrk));
        bTTrkgTBTracks2.putByte("sector", itrk, bTBTrkgTBTracks.getByte("sector", itrk));
        bTTrkgTBTracks2.putFloat("c1_x", itrk, bTBTrkgTBTracks.getFloat("c1_x", itrk));
        bTTrkgTBTracks2.putFloat("c1_y", itrk, bTBTrkgTBTracks.getFloat("c1_y", itrk));
        bTTrkgTBTracks2.putFloat("c1_z", itrk, bTBTrkgTBTracks.getFloat("c1_z", itrk));
        bTTrkgTBTracks2.putFloat("c1_ux", itrk, bTBTrkgTBTracks.getFloat("c1_ux", itrk));
        bTTrkgTBTracks2.putFloat("c1_uy", itrk, bTBTrkgTBTracks.getFloat("c1_uy", itrk));
        bTTrkgTBTracks2.putFloat("c1_uz", itrk, bTBTrkgTBTracks.getFloat("c1_uz", itrk));
        bTTrkgTBTracks2.putFloat("c3_x", itrk, bTBTrkgTBTracks.getFloat("c3_x", itrk));
        bTTrkgTBTracks2.putFloat("c3_y", itrk, bTBTrkgTBTracks.getFloat("c3_y", itrk));
        bTTrkgTBTracks2.putFloat("c3_z", itrk, bTBTrkgTBTracks.getFloat("c3_z", itrk));
        bTTrkgTBTracks2.putFloat("c3_ux", itrk, bTBTrkgTBTracks.getFloat("c3_ux", itrk));
        bTTrkgTBTracks2.putFloat("c3_uy", itrk, bTBTrkgTBTracks.getFloat("c3_uy", itrk));
        bTTrkgTBTracks2.putFloat("c3_uz", itrk, bTBTrkgTBTracks.getFloat("c3_uz", itrk));
        bTTrkgTBTracks2.putFloat("t1_x", itrk, bTBTrkgTBTracks.getFloat("t1_x", itrk));
        bTTrkgTBTracks2.putFloat("t1_y", itrk, bTBTrkgTBTracks.getFloat("t1_y", itrk));
        bTTrkgTBTracks2.putFloat("t1_z", itrk, bTBTrkgTBTracks.getFloat("t1_z", itrk));
        bTTrkgTBTracks2.putFloat("t1_px", itrk, bTBTrkgTBTracks.getFloat("t1_px", itrk));
        bTTrkgTBTracks2.putFloat("t1_py", itrk, bTBTrkgTBTracks.getFloat("t1_py", itrk));
        bTTrkgTBTracks2.putFloat("t1_pz", itrk, bTBTrkgTBTracks.getFloat("t1_pz", itrk));
        bTTrkgTBTracks2.putFloat("Vtx0_x", itrk, bTBTrkgTBTracks.getFloat("Vtx0_x", itrk));
        bTTrkgTBTracks2.putFloat("Vtx0_y", itrk, bTBTrkgTBTracks.getFloat("Vtx0_y", itrk));
        bTTrkgTBTracks2.putFloat("Vtx0_z", itrk, bTBTrkgTBTracks.getFloat("Vtx0_z", itrk));
        bTTrkgTBTracks2.putFloat("p0_x", itrk, bTBTrkgTBTracks.getFloat("p0_x", itrk));
        bTTrkgTBTracks2.putFloat("p0_y", itrk, bTBTrkgTBTracks.getFloat("p0_y", itrk));
        bTTrkgTBTracks2.putFloat("p0_z", itrk, bTBTrkgTBTracks.getFloat("p0_z", itrk));
        bTTrkgTBTracks2.putShort("Cross1_ID", itrk, bTBTrkgTBTracks.getShort("Cross1_ID", itrk));
        bTTrkgTBTracks2.putShort("Cross2_ID", itrk, bTBTrkgTBTracks.getShort("Cross2_ID", itrk));
        bTTrkgTBTracks2.putShort("Cross3_ID", itrk, bTBTrkgTBTracks.getShort("Cross3_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster1_ID", itrk, bTBTrkgTBTracks.getShort("Cluster1_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster2_ID", itrk, bTBTrkgTBTracks.getShort("Cluster2_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster3_ID", itrk, bTBTrkgTBTracks.getShort("Cluster3_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster4_ID", itrk, bTBTrkgTBTracks.getShort("Cluster4_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster5_ID", itrk, bTBTrkgTBTracks.getShort("Cluster5_ID", itrk));
        bTTrkgTBTracks2.putShort("Cluster6_ID", itrk, bTBTrkgTBTracks.getShort("Cluster6_ID", itrk));
        bTTrkgTBTracks2.putByte("q", itrk, bTBTrkgTBTracks.getByte("q", itrk));
        bTTrkgTBTracks2.putFloat("pathlength", itrk, bTBTrkgTBTracks.getFloat("pathlength", itrk));
        bTTrkgTBTracks2.putFloat("chi2", itrk, bTBTrkgTBTracks.getFloat("chi2", itrk));
        bTTrkgTBTracks2.putShort("ndf", itrk, bTBTrkgTBTracks.getShort("ndf", itrk));
        bTTrkgTBTracks2.putShort("ndf0", itrk, bTBTrkgTBTracks.getShort("ndf0", itrk));

    }
}






