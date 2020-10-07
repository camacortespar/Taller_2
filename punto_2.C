// Repeat exercise for all jets pT.

void punto_2(){

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

  // Create histograms: All jets pT
  TH1F *hist_truth_pt = new TH1F("Truth & Reco-jet","Truth-jet p_{T}; p_{T}(GeV);Events",50,10,200);
  TH1F *hist_reco_pt = new TH1F("","Reco-jet p_{T}; p_{T}(GeV);Events",50,10,200);

  // Let's fill those histograms
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      // Choose if with EventWeight or not
      if(truth_R4_pt->size()>0){
	for(int j=0; j<truth_R4_pt->size(); j++){
	  //hist_truth_pt->Fill(truth_R4_pt->at(j)/1000.,evtw);
	  hist_truth_pt->Fill(truth_R4_pt->at(j)/1000.);
	}
      }
      if(reco_R4_pt->size()>0){
	for(int j=0; j<reco_R4_pt->size(); j++){
	  //hist_reco_pt->Fill(reco_R4_pt->at(j)/1000.,evtw);
	  hist_reco_pt->Fill(reco_R4_pt->at(j)/1000.);
	}
      }
    }

  std::cout << "Done!" << std::endl;

  // Let's draw
  hist_truth_pt->SetMarkerStyle(20);
  hist_truth_pt->SetMarkerColor(2);
  hist_truth_pt->SetFillColor(46);
  hist_truth_pt->Draw("");
  hist_reco_pt->SetMarkerStyle(21);
  hist_reco_pt->SetFillColor(38);
  hist_reco_pt->Draw("same");                 //Plot on the same Canvas
  canvas->SetLogy();                          //Log scale
  canvas->BuildLegend();
  canvas->Draw();

}
