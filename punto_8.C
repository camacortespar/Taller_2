// Investigate the Large-R jets: (a) Plot the leading jet pT for reco_R10 and reco_R10_Trimmed jets (b) Plot the leading jet pT for truth_R10 and truth_R10_Trimmed jets (c) Compare all plots. How can you explain the differences? 

void punto_8(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  // Extract and declare variables
  float evtw = -1;
  vector<float> *reco_R10_pt=0;
  vector<float> *reco_R10_trim_pt=0;
  vector<float> *truth_R10_pt=0;
  vector<float> *truth_R10_trim_pt=0;

  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R10_pt", &reco_R10_pt);
  tree->SetBranchAddress("RecoJets_R10_Trimmed_pt", &reco_R10_trim_pt);
  tree->SetBranchAddress("TruthJets_R10_pt", &truth_R10_pt);
  tree->SetBranchAddress("TruthJets_R10_Trimmed_pt", &truth_R10_trim_pt);

  // Create a Canvas 800x600
  TCanvas *canvas = new TCanvas("Canvas","",800,600);

  // Create histograms: Leading jets pT
  TH1F *hist_leadreco_pt = new TH1F("","Lead Reco Large jet p_{T}; p_{T}(GeV);Events",50,10,200);
  TH1F *hist_leadreco_trim_pt = new TH1F("","Lead Reco Trimmed Large jet p_{T}; p_{T}(GeV);Events",50,10,200);
  TH1F *hist_leadtruth_pt = new TH1F("","Lead Truth Large jet p_{T}; p_{T}(GeV);Events",50,10,200);
  TH1F *hist_leadtruth_trim_pt = new TH1F("","Lead Truth Trimmed Large jet p_{T}; p_{T}(GeV);Events",50,10,200);
  hist_leadreco_pt->SetAxisRange(1e3, 1e10, "Y");
  // Let's fill those histograms
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);
      
      if(reco_R10_pt->size()>0){
	hist_leadreco_pt->Fill(reco_R10_pt->at(0)/1000.,evtw);
	
      }
      if(reco_R10_trim_pt->size()>0){
	hist_leadreco_trim_pt->Fill(reco_R10_trim_pt->at(0)/1000.,evtw);
	
      }
      if(truth_R10_pt->size()>0){
	hist_leadtruth_pt->Fill(truth_R10_pt->at(0)/1000.,evtw);
	
      }
      if(truth_R10_trim_pt->size()>0){
	hist_leadtruth_trim_pt->Fill(truth_R10_trim_pt->at(0)/1000.,evtw);
	
      }
    }

  std::cout << "Done!" << std::endl;

  // Let's draw
  hist_leadreco_pt->SetMarkerStyle(20);
  hist_leadreco_pt->SetMarkerColor(1);
  hist_leadreco_pt->Draw("");
  hist_leadreco_trim_pt->SetMarkerStyle(21);
  hist_leadreco_trim_pt->SetMarkerColor(46);
  hist_leadreco_trim_pt->Draw("same");
  hist_leadtruth_pt->SetMarkerStyle(22);
  hist_leadtruth_pt->SetMarkerColor(38);
  hist_leadtruth_pt->Draw("same");
  hist_leadtruth_trim_pt->SetMarkerStyle(23);
  hist_leadtruth_trim_pt->SetMarkerColor(8);  
  hist_leadtruth_trim_pt->Draw("same");             //Plot on the same Canvas
  canvas->SetLogy();                          //Log scale
  canvas->BuildLegend();
  canvas->Draw();

}
