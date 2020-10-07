// Repeat for track-jets and make a plot comparing three cases: reco-jets with and without the JVF cut, and track-jets

void punto_6(){

  // Let's open the TFile
  TFile *file = TFile::Open("Tracks_Clusters.root");
  TTree *tree = (TTree*) file->Get("JetRecoTree");
  tree->Print();

  // Extract and declare variables to construct the four-vectors
  float evtw = -1;
  vector<float> *reco_R4_jvf=0;
  //Reco
  vector<float> *reco_R4_pt=0;
  vector<float> *reco_R4_eta=0;
  vector<float> *reco_R4_phi=0;
  vector<float> *reco_R4_m=0;
  //Tracks
  vector<float> *tracks_R4_pt=0;
  vector<float> *tracks_R4_eta=0;
  vector<float> *tracks_R4_phi=0;
  vector<float> *tracks_R4_m=0;  
  //Truth
  vector<float> *truth_R4_pt=0;
  vector<float> *truth_R4_eta=0;
  vector<float> *truth_R4_phi=0;
  vector<float> *truth_R4_m=0;
  

  tree->SetBranchAddress("EventWeight", &evtw);
  tree->SetBranchAddress("RecoJets_R4_jvf", &reco_R4_jvf);
  tree->SetBranchAddress("RecoJets_R4_pt", &reco_R4_pt);
  tree->SetBranchAddress("RecoJets_R4_eta", &reco_R4_eta);
  tree->SetBranchAddress("RecoJets_R4_phi", &reco_R4_phi);
  tree->SetBranchAddress("RecoJets_R4_m", &reco_R4_m);  
  tree->SetBranchAddress("TrackJets_R4_pt", &tracks_R4_pt);
  tree->SetBranchAddress("TrackJets_R4_eta", &tracks_R4_eta);
  tree->SetBranchAddress("TrackJets_R4_phi", &tracks_R4_phi);
  tree->SetBranchAddress("TrackJets_R4_m", &tracks_R4_m);
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_eta", &truth_R4_eta);
  tree->SetBranchAddress("TruthJets_R4_phi", &truth_R4_phi);
  tree->SetBranchAddress("TruthJets_R4_m", &truth_R4_m);

  // Create a canvas 800x600
  TCanvas *canvas = new TCanvas("Canvas","",800,600);

  // Make some histograms
  TH1F *hist_DR_recoWC_truth = new TH1F("Delta R recoWC-reco-tracks","#Delta R - Reco with cut; #Delta R; Events",20,0,2);
  TH1F *hist_DR_reco_truth = new TH1F("","#Delta R - Reco; #Delta R; Events",20,0,2);
  TH1F *hist_DR_tracks_truth = new TH1F("","#Delta R - Tracks; #Delta R; Events",20,0,2);
  
  // Let's fill those histograms
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);

      if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>20000.){
	TLorentzVector truthJet;
	truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0));
	//RecoWC
	if(reco_R4_pt->size()!=0 && fabs(reco_R4_jvf->at(0))>0.5){
	  TLorentzVector recoWCJet;
	  recoWCJet.SetPtEtaPhiM(reco_R4_pt->at(0),reco_R4_eta->at(0),reco_R4_phi->at(0),reco_R4_m->at(0));
	  //Plot the Delta R
	  hist_DR_recoWC_truth->Fill(truthJet.DeltaR(recoWCJet),evtw);
	}
	//Reco
	if(reco_R4_pt->size()!=0){
	  TLorentzVector recoJet;
	  recoJet.SetPtEtaPhiM(reco_R4_pt->at(0),reco_R4_eta->at(0),reco_R4_phi->at(0),reco_R4_m->at(0));
	  //Plot the Delta R
	  hist_DR_reco_truth->Fill(truthJet.DeltaR(recoJet),evtw);
	}
	//Tracks
	if(tracks_R4_pt->size()!=0){
	  TLorentzVector tracksJet;
	  tracksJet.SetPtEtaPhiM(tracks_R4_pt->at(0),tracks_R4_eta->at(0),tracks_R4_phi->at(0),tracks_R4_m->at(0));
	  //Plot the Delta R
	  hist_DR_tracks_truth->Fill(truthJet.DeltaR(tracksJet),evtw);
	}
      }
    }

  std::cout << "Done!" << std::endl;

  // Plot
  hist_DR_recoWC_truth->Scale(1/hist_DR_recoWC_truth->Integral());
  hist_DR_recoWC_truth->SetMarkerStyle(20);
  hist_DR_recoWC_truth->SetMarkerColor(1);
  hist_DR_recoWC_truth->DrawNormalized("");

  hist_DR_reco_truth->Scale(1/hist_DR_reco_truth->Integral());
  hist_DR_reco_truth->SetMarkerStyle(21);
  hist_DR_reco_truth->SetMarkerColor(2);
  hist_DR_reco_truth->DrawNormalized("same");

  hist_DR_tracks_truth->Scale(1/hist_DR_tracks_truth->Integral());
  hist_DR_tracks_truth->SetMarkerStyle(22);
  hist_DR_tracks_truth->SetMarkerColor(8);
  hist_DR_tracks_truth->DrawNormalized("same");
  canvas->BuildLegend();
  canvas->Draw();
  
}
