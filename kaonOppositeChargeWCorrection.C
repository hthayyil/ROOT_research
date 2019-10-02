
#include "TMath.h"
void kaonOppositeChargeWCorrection(){


		TH1D *momentum = new TH1D("momentum","momentum",60,0.5,12);
        TH1D *charge = new TH1D("charge","charge",60,-2.,2.);
        TH1D *hEta = new TH1D("hEta","hEta",60,-6,6);
        TH1D *hPhi = new TH1D("hPhi","hPhi",60,-3.2,3.2);
        TH1D *mass = new TH1D ("mass", "Kaon Opposite Charge Mass Reconstruction With Correction ", 400, 0.48,0.52);

		//Load the file
		TFile *f = TFile::Open("withDecay_CUETP8M1_NEvt100000_DoFlatPthatTrue_FlatPower4p50_PthatMin40p0_PthatMax999999p0_20181120.root");
		


		//Get the tree from the file
		TTree * t = (TTree*) f->Get("genParticleTree");
		TTree * w = (TTree*) f-> Get("ak4GenJetTree_ESchemeWTA");	
		

		int nPart;
		int nEvent = t-> GetEntries();

		vector<float>* pt=0;
		float weight;
		vector<float>* phi;
		vector<float>* eta;
		//float *eta;

		vector<float>* pdg;
		vector<float>* chg;
		//vector <float>*e1;
		//vector <float>*e2;
		float e1 = 0;
		float e2 = 0;
		float mInv;
		float pz, px, py;
		float pzt, pxt, pyt;
		float momsq, momsq2;
		float eTotal, pTotal;
		const PIMASS = 0.13957;
		

		//t->SetBranchStatus("*", 0);
		t->SetBranchStatus("pt", 1);
		t->SetBranchAddress("pt", &pt);
		t->SetBranchAddress ("phi", &phi);
		t->SetBranchAddress ("eta", &eta);
		t->SetBranchAddress("pdg", &pdg);
		t->SetBranchAddress("chg", &chg);
		t->SetBranchAddress("nPart", &nPart);
		w-> SetBranchAddress("weight", &weight);

cout << nEvent<<endl;

	for (int i =0; i<nEvent; i++ ) {
		t->GetEntry(i);
		//cout <<nPart<<endl;
		//if (i > 1000) break;
		if (!(i%100)) cout<<i<<endl;

	 for (int j=0; j< nPart; j++){

	 	if (chg-> at(j)==0) continue;
		hEta->Fill(eta->at(j));
        hPhi-> Fill(phi->at(j));
        momentum->Fill(pt->at(j));
        charge->Fill(chg->at(j));


    	if (chg->at(j)>0){
    		tempPt = pt->at(j);
	 		tempPt+= gRandom->Gaus() *0.02 * tempPt;

    		pz = (tempPt*sinh(eta->at(j)));
    		

    		px = (tempPt* cos(phi->at(j)));
    		
    		py = (tempPt* sin(phi->at(j)));
    		
    		momsq = (tempPt)*(tempPt) + pz*pz;
    	    e1 = sqrt (PIMASS*PIMASS + momsq );
    	    }

    		for (int p=0; p< nPart; p++){
    			if (chg->at(p)< 0){
    				tempPt = pt->at(p);
	 				tempPt+= gRandom->Gaus() *0.02 * tempPt;


    				pzt = (tempPt*sinh(eta->at(p)));

    				pxt = (tempPt* cos(phi->at(p)));
    				

    	         	pyt = (tempPt* sin(phi->at(p)));
    	         	
    				momsq2= (tempPt)*(tempPt) + pzt*pzt;

    				e2 = sqrt (PIMASS*PIMASS + momsq2);

    				pTotal = sqrt((px+pxt)*(px+pxt) + (py+pyt)*(py+pyt) + (pz+pzt)*(pz+pzt));
    				eTotal = e1 + e2;
    				mInv = sqrt ((eTotal*eTotal) - (pTotal*pTotal));


    				mass->Fill(mInv);
    			}
    	     }


    }//end of for j loop
	}// end of for i loop

	/* 

	cCanvas = new TCanvas("cCanvas", "", 10,10, 700, 400);
	cCanvas-> Divide(4);
	cCanvas-> Draw();
	cCanvas-> cd(1);
	hEta-> Draw();
	cCanvas-> cd(2);
	hPhi-> Draw();
	cCanvas-> cd(3);
	cCanvas_3->SetLogy(1);
	momentum->Draw();
	cCanvas-> cd(4);
	charge->Draw();
     */
file= new TFile("kaonOppositeChargewCorrections.root","RECREATE");
mass-> Write();


file->Write();
file-> Close();

	mass->Draw();
	//mass->Draw();
	//t->GetEntry(10);
	//cout<<pt->at(1)<<endl;
	//cout <<nPart
}