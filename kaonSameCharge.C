#include "TMath.h"
void kaonSameCharge(){


		//Load the file
		TFile *f = TFile::Open("withDecay_CUETP8M1_NEvt100000_DoFlatPthatTrue_FlatPower4p50_PthatMin40p0_PthatMax999999p0_20181120.root");
		
		//Get the tree from the file
		TTree * t = (TTree*) f->Get("genParticleTree");
		TTree * w = (TTree*) f-> Get("ak4GenJetTree_ESchemeWTA");	
		TH1D *mass2 = new TH1D ("mass2", "Kaon Same Charge Mass Reconstruction", 400, 0.48,0.52);

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
		const KMASS = 0.13957;
		

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
		//if (i > 20000) break;
		if (!(i%100)) cout<<i<<endl;

	 for (int j=0; j< nPart; j++){

	 	if (chg-> at(j)==0) continue;
	
    		pz = (pt->at(j)*sinh(eta->at(j)));
    		px = (pt-> at(j)* cos(phi->at(j)));
    		py = (pt-> at(j)* sin(phi->at(j)));

    		momsq = (pt->at(j))*(pt->at(j)) + pz*pz;
    	    e1 = sqrt (KMASS*KMASS + momsq );
    	    

    		for (int p=0; p< nPart; p++){
    			if (chg->at(p)* chg->at(j)> 0){

    				if (j == p) continue;

    				pzt = (pt->at(p)*sinh(eta->at(p)));
    				pxt = (pt-> at(p)* cos(phi->at(p)));
    	         	pyt = (pt-> at(p)* sin(phi->at(p)));

    				momsq2= (pt->at(p))*(pt->at(p)) + pzt*pzt;
    				e2 = sqrt (KMASS*KMASS + momsq2);

    				pTotal = sqrt((px+pxt)*(px+pxt) + (py+pyt)*(py+pyt) + (pz+pzt)*(pz+pzt));
    				eTotal = e1 + e2;
    				mInv = sqrt ((eTotal*eTotal) - (pTotal*pTotal));


    				mass2->Fill(mInv);
    			}
    	     }
    }//end of for j loop
	}// end of for i loop

file= new TFile("kaonSameCharge.root","RECREATE");
mass2-> Write();


file->Write();
file-> Close();

	mass2->Draw();
	//t->GetEntry(10);
	//cout<<pt->at(1)<<endl;
	//cout <<nPart
}