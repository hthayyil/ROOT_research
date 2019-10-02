#include "TMath.h"
void lambdaSameWCorrection(){


		TH1D *mass2 = new TH1D ("mass2", "Lambda Same Charge Mass Reconstruction with Correction", 400, 1.08,1.15);
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
		float pz, px, py, tempPz, tempPx, tempPy;
		float pzt, pxt, pyt;
		float momsq, momsq2;
		const PROTONMASS = 0.938;
		const PIONMASS = 0.13957;
		

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
		//if (i > 1000) break;
		if (!(i%100)) cout<<i<<endl;

	 for (int j=0; j< nPart; j++){

	 	if (chg-> at(j)==0) continue;
	 		//if (abs(pdg->at(j)) == 2212) {
	 		tempPt = pt->at(j);
	 		tempPt+= gRandom->Gaus() *0.02 * tempPt;

    		pz = (tempPt*sinh(eta->at(j)));
    		

    		px = (tempPt* cos(phi->at(j)));
    		
    		py = (tempPt* sin(phi->at(j)));
    		
    		momsq = (tempPt)*(tempPt) + pz*pz;
    	 //}

    		for (int p=0; p< nPart; p++){
    			//if (abs(pdg-at(p))== 211) {
    			if (chg->at(p)* chg->at(j)> 0){


    				if (j == p) continue;
    				tempPt = pt->at(p);
	 				tempPt+= gRandom->Gaus() *0.02 * tempPt;


    				pzt = (tempPt*sinh(eta->at(p)));

    				pxt = (tempPt* cos(phi->at(p)));
    				

    	         	pyt = (tempPt* sin(phi->at(p)));
    	         	
    				momsq2= (tempPt)*(tempPt) + pzt*pzt;

    				if (pt->at(j) > pt->at(p)) {

    				e1 = sqrt (PROTONMASS*PROTONMASS + momsq );
    				e2 = sqrt (PIONMASS*PIONMASS + momsq2);
    			    }

    			   else {

    				e2 = sqrt (PROTONMASS*PROTONMASS + momsq );
    				e1 = sqrt (PIONMASS*PIONMASS + momsq2);
    			
    			    }
    			
    				pTotal = sqrt((px+pxt)*(px+pxt) + (py+pyt)*(py+pyt) + (pz+pzt)*(pz+pzt));
    				eTotal = e1 + e2;
    				mInv = sqrt ((eTotal*eTotal) - (pTotal*pTotal));


    				mass2->Fill(mInv);
    			}
    		//}
    	     }
    }//end of for j loop
	}// end of for i loop

file= new TFile("lambdaSameWCorrection.root","RECREATE");
mass2-> Write();


file->Write();
file-> Close();

	mass2->Draw();
	//t->GetEntry(10);
	//cout<<pt->at(1)<<endl;
	//cout <<nPart
}