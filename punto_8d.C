// Investigate the Large-R jets: (d) Make the same comparisson for the jet mass.

void punto_8d(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  // Extract and declare variables
  float evtw = -1;
  vector<float> *reco_R10_m=0;
  vector<float> *reco_R10_trim_m=0;
  vector<float> *truth_R10_m=0;
  vector<float> *truth_R10_trim_m=0;

  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R10_m", &reco_R10_m);
  tree->SetBranchAddress("RecoJets_R10_Trimmed_m", &reco_R10_trim_m);
  tree->SetBranchAddress("TruthJets_R10_m", &truth_R10_m);
  tree->SetBranchAddress("TruthJets_R10_Trimmed_m", &truth_R10_trim_m);

  // Create a Canvas 800x600
  TCanvas *canvas = new TCanvas("Canvas","",800,600);

  // Create histograms: Leading jets pT
  TH1F *hist_leadreco_m = new TH1F("","Lead Reco Large jet m; m;Events",50,10,200);
  TH1F *hist_leadreco_trim_m = new TH1F("","Lead Reco Trimmed Large jet m; m;Events",50,10,200);
  TH1F *hist_leadtruth_m = new TH1F("","Lead Truth Large jet m; m;Events",50,10,200);
  TH1F *hist_leadtruth_trim_m = new TH1F("","Lead Truth Trimmed Large jet m; m;Events",50,10,200);
  hist_leadreco_m->SetAxisRange(1e3, 1e10, "Y");
  // Let's fill those histograms
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);

      if(reco_R10_m->size()>0){
	hist_leadreco_m->Fill(reco_R10_m->at(0)/1000.,evtw);

      }
      if(reco_R10_trim_m->size()>0){
	hist_leadreco_trim_m->Fill(reco_R10_trim_m->at(0)/1000.,evtw);

      }
      if(truth_R10_m->size()>0){
	hist_leadtruth_m->Fill(truth_R10_m->at(0)/1000.,evtw);

      }
      if(truth_R10_trim_m->size()>0){
	hist_leadtruth_trim_m->Fill(truth_R10_trim_m->at(0)/1000.,evtw);

      }
    }

  std::cout << "Done!" << std::endl;

  // Let's draw
  hist_leadreco_m->SetMarkerStyle(20);
  hist_leadreco_m->SetMarkerColor(1);
  hist_leadreco_m->Draw("");
  hist_leadreco_trim_m->SetMarkerStyle(21);
  hist_leadreco_trim_m->SetMarkerColor(46);
  hist_leadreco_trim_m->Draw("same");
  hist_leadtruth_m->SetMarkerStyle(22);
  hist_leadtruth_m->SetMarkerColor(38);
  hist_leadtruth_m->Draw("same");
  hist_leadtruth_trim_m->SetMarkerStyle(23);
  hist_leadtruth_trim_m->SetMarkerColor(8);
  hist_leadtruth_trim_m->Draw("same");             //Plot on the same Canvas
  canvas->SetLogy();                          //Log scale
  canvas->BuildLegend();
  canvas->Draw();

}
