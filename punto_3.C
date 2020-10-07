// Make plots for reco and truth jet pT vs. pileup. Interpret your results.

void punto_3(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  // Extract and declare variables
  UInt_t npv = -1;
  float mu = -1;
  float evtw = -1;
  vector<float> *reco_R4_pt=0;
  vector<float> *truth_R4_pt=0;
  
  tree->SetBranchAddress("NPV", &npv);
  tree->SetBranchAddress("mu_average", &mu);
  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);

  // Create a canvas 800x600
  TCanvas *canvas = new TCanvas("Canvas","",800,600);

  // Create 2D-histograms
  TH2F *hist_recojetpt_npv = new TH2F("Reco-jet p_{T} vs. NPV",";NPV; Jet p_{T}",50,1,50,20,0,200);
  TProfile *prof_recojetpt_npv = new TProfile("Profile Reco-jet p_{T} vs. NPV",";NPV; Jet p_{T}",50,1,50,0,200);
  TH2F *hist_truthjetpt_npv = new TH2F("Truth-jet p_{T} vs. NPV",";NPV; Jet p_{T}",50,1,50,20,0,200);
  TProfile *prof_truthjetpt_npv = new TProfile("Profile Truth-jet p_{T} vs. NPV",";NPV; Jet p_{T}",50,1,50,0,200);

  // Let's fill those histograms
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);

      if(reco_R4_pt->size()!=0 && reco_R4_pt->at(0)>20000.){
	for(int j=0; j<reco_R4_pt->size(); j++){
	  hist_recojetpt_npv->Fill(reco_R4_pt->at(j)/1000.,npv,evtw);
	  prof_recojetpt_npv->Fill(reco_R4_pt->at(j)/1000.,npv,evtw);
	}
      }
      if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>20000.){
	for(int j=0; j<truth_R4_pt->size(); j++){
	  hist_truthjetpt_npv->Fill(truth_R4_pt->at(j)/1000.,npv,evtw);
	  prof_truthjetpt_npv->Fill(truth_R4_pt->at(j)/1000.,npv,evtw);
	}
      }
    }

  std::cout << "Done!" << std::endl;

  // Let´s plot those histograms, just choose.
  
  //hist_recojetpt_npv->Draw("Colz");
  //prof_recojetpt_npv->Draw("");
  //hist_truthjetpt_npv->Draw("Colz");
  prof_truthjetpt_npv->Draw("");
  canvas->Draw();


}
