// Use a |JVF|>0.5 cut to compare the leading jet pT for truth jets, reco jets (w.o. the cut), and reco jets (with the cut)

void punto_4(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  // Extract and declare variables
  float evtw = -1;
  vector<float> *reco_R4_pt=0;
  vector<float> *truth_R4_pt=0;
  vector<float> *tracks_R4_pt=0;
  vector<float> *reco_R4_jvf=0;

  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);
  tree->SetBranchAddress("TrackJets_R4_pt", &tracks_R4_pt);
  tree->SetBranchAddress("RecoJets_R4_jvf", &reco_R4_jvf);
  
  // Create a canvas 800x600
  TCanvas *canvas = new TCanvas("Canvas","",800,600);

  // Create histograms
  TH1F *hist_leadreco_pt = new TH1F("","Lead Reco-jet p_{T}; p_{T}(GeV);Events",50,10,200);
  TH1F *hist_leadtruth_pt = new TH1F("","Lead Truth jet p_{T}; p_{T}(GeV);Events",50,10,200);
  TH1F *hist_leadtracks_pt = new TH1F("","Lead Tracks-jet p_{T}; p_{T}(GeV);Events",50,10,200);
  TH1F *hist_leadrecoWC_pt = new TH1F("","Lead Reco-jet with cut |JVF|>0.5; p_{T}(GeV);Events",50,10,200);

  // Let's fill those histograms
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      if(reco_R4_pt->size()>0){
	hist_leadreco_pt->Fill(reco_R4_pt->at(0)/1000.,evtw);
        }

      if(truth_R4_pt->size()>0){
	hist_leadtruth_pt->Fill(truth_R4_pt->at(0)/1000.,evtw);
	}
      
      if(tracks_R4_pt->size()>0){
	hist_leadtracks_pt->Fill(tracks_R4_pt->at(0)/1000.,evtw);
        }
      
      if(reco_R4_pt->size()>0 && fabs(reco_R4_jvf->at(0))>0.5){
	hist_leadrecoWC_pt->Fill(reco_R4_pt->at(0)/1000.,evtw);
        }
    }

  std::cout << "Done!" << std::endl;

  // Let's draw
  hist_leadrecoWC_pt->SetMarkerStyle(20);
  hist_leadrecoWC_pt->SetMarkerColor(1);
  hist_leadrecoWC_pt->Draw("");
  hist_leadreco_pt->SetMarkerStyle(21);
  hist_leadreco_pt->SetMarkerColor(38);
  hist_leadreco_pt->Draw("same");             //Plot on the same Canvas
  hist_leadtruth_pt->SetMarkerStyle(22);
  hist_leadtruth_pt->SetMarkerColor(46);
  hist_leadtruth_pt->Draw("same");
  hist_leadtracks_pt->SetMarkerStyle(23);
  hist_leadtracks_pt->SetMarkerColor(8);
  hist_leadtracks_pt->Draw("same");
  //canvas->SetLogy();                          //Log scale
  canvas->BuildLegend();
  canvas->Draw();

}
