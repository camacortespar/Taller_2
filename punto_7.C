// Plot the response: For matched jets (use DeltaR<0.3), plot pTjet/pTtruth for 3 cases: truth_pT>20 GeV, 100 GeV, 500 GeV. Do this for track jets and reco jets.
void punto_7(){

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
  tree->SetBranchAddress("TruthJets_R4_pt", &truth_R4_pt);
  tree->SetBranchAddress("TruthJets_R4_eta", &truth_R4_eta);
  tree->SetBranchAddress("TruthJets_R4_phi", &truth_R4_phi);
  tree->SetBranchAddress("TruthJets_R4_m", &truth_R4_m);

  // Create a canvas 800x600
  TCanvas *canvas = new TCanvas("Canvas","",800,600);

  // Make some 2D-histograms
  TH1F *hist_reco_response20 = new TH1F("","Truth p_{T}>20 GeV;Reco p_{T}/Truth p_{T}; Events",20,0,2);
  TH1F *hist_reco_response100 = new TH1F("","Truth p_{T}>100 GeV;Reco p_{T}; Events",20,0,2);
  TH1F *hist_reco_response500 = new TH1F("","Truth p_{T}>500 GeV;Reco p_{T}; Events",20,0,2);
  
  // Let's fill those histograms
  int nentries, nbytes, i;
  nentries = (Int_t)tree->GetEntries();

  for (i = 0; i < nentries; i++)
    {
      nbytes = tree->GetEntry(i);

      if(reco_R4_pt->size()!=0){
        TLorentzVector recoJet;
        recoJet.SetPtEtaPhiM(reco_R4_pt->at(0),reco_R4_eta->at(0),reco_R4_phi->at(0),reco_R4_m->at(0));
        if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>20000.){
	  TLorentzVector truthJet;
	  truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0));
	  if(fabs(truthJet.DeltaR(recoJet))<0.3){
	    hist_reco_response20->Fill(reco_R4_pt->at(0)/truth_R4_pt->at(0),evtw);
	  }
	}
	if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>100000.){
	  TLorentzVector truthJet;
	  truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0));
	  if(fabs(truthJet.DeltaR(recoJet))<0.3){
	    hist_reco_response100->Fill(reco_R4_pt->at(0)/truth_R4_pt->at(0),evtw);
	  }
	}
	if(truth_R4_pt->size()!=0 && truth_R4_pt->at(0)>500000.){
	  TLorentzVector truthJet;
	  truthJet.SetPtEtaPhiM(truth_R4_pt->at(0),truth_R4_eta->at(0),truth_R4_phi->at(0),truth_R4_m->at(0));
	  if(fabs(truthJet.DeltaR(recoJet))<0.3){
	    hist_reco_response500->Fill(reco_R4_pt->at(0)/truth_R4_pt->at(0),evtw);
	  }
	}
      }
    }

  std::cout << "Done!" << std::endl;

  // Let's plot
  hist_reco_response20->SetMarkerStyle(20);
  hist_reco_response20->SetMarkerColor(2);
  hist_reco_response20->Draw("");
  hist_reco_response100->SetMarkerStyle(21);
  hist_reco_response100->SetMarkerColor(38);
  hist_reco_response100->Draw("same");
  hist_reco_response500->SetMarkerStyle(22);
  hist_reco_response500->SetMarkerColor(8);
  hist_reco_response500->Draw("same");
  //canvas->SetLogy();
  canvas->BuildLegend();
  canvas->Draw();

}
