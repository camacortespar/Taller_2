// Compare the leading truth jet pT with the leading reco jet pT, with and without event weights.

void punto_1(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();
  
  // Extract and declare variables
  float evtw = -1;
  vector<float> *reco_R4_pt=0;
  vector<float> *truth_R4_pt=0;

  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);

  // Create a Canvas 800x600
  TCanvas *canvas = new TCanvas("Canvas","",800,600);

  // Create histograms: Leading jets pT
  TH1F *hist_leadtruth_pt = new TH1F("Lead Truth & Reco-jet","Lead Truth jet p_{T}; p_{T}(GeV);Events",50,10,200);
  TH1F *hist_leadreco_pt = new TH1F("","Lead Reco-jet p_{T}; p_{T}(GeV);Events",50,10,200);

  // Let's fill those histograms
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      //Choose if with EventWeight or not
      if(truth_R4_pt->size()>0){
	hist_leadtruth_pt->Fill(truth_R4_pt->at(0)/1000.,evtw);
	//hist_leadtruth_pt->Fill(truth_R4_pt->at(0)/1000.);
	}
      if(reco_R4_pt->size()>0){
	hist_leadreco_pt->Fill(reco_R4_pt->at(0)/1000.,evtw);
	//hist_leadreco_pt->Fill(reco_R4_pt->at(0)/1000.);
	}
    }

  std::cout << "Done!" << std::endl;

  // Let's draw
  hist_leadtruth_pt->SetMarkerStyle(20);
  hist_leadtruth_pt->SetMarkerColor(2);
  hist_leadtruth_pt->SetFillColor(46);
  hist_leadtruth_pt->Draw("");
  hist_leadreco_pt->SetMarkerStyle(21);
  hist_leadreco_pt->SetFillColor(38);
  hist_leadreco_pt->Draw("same");             //Plot on the same Canvas
  canvas->SetLogy();                          //Log scale
  canvas->BuildLegend();
  canvas->Draw();

}

