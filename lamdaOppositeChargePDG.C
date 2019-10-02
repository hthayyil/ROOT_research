
#include "TMath.h"
void lambdaOppositeChargePDG(){


		//Load the file
		TFile *f = TFile::Open("withDecay_CUETP8M1_NEvt100000_DoFlatPthatTrue_FlatPower4p50_PthatMin120p0_PthatMax999999p0_20181016.root");
		
		 TH1D *mass = new TH1D ("mass", "Proton-Pion", 400, 1.1,1.2);

		//Get the tree from the file
		TTree * t = (TTree*) f->Get("genParticleTree");
		TTree * w = (TTree*) f-> Get("ak4GenJetTree_ESchemeWTA");	
		

		int nPart;
		int nEvent = t-> GetEntries();

		vector<float>* pt=0;
		float weight;
		vector<float>* phi;
		vector<float>* eta;
		

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
		//cout <<nPart<<endl;
		if (i > 1000) break;
		if (!(i%100)) cout<<i<<endl;

	 for (int j=0; j< nPart; j++){

	 	if (chg-> at(j)==0) continue;
    	if (chg->at(j)>0){
    		if (pdg->at(j) == 2212) {
    		pz = (pt->at(j)*sinh(eta->at(j)));
    		px = (pt-> at(j)* cos(phi->at(j)));
    		py = (pt-> at(j)* sin(phi->at(j)));

    		momsq = (pt->at(j))*(pt->at(j)) + pz*pz;
    	    } 
    	    }

    		for (int p=0; p< nPart; p++){
    			if (chg->at(p)< 0){
    				if (pdg->at(p) ==-211) {


    				pzt = (pt->at(p)*sinh(eta->at(p)));
    				pxt = (pt-> at(p)* cos(phi->at(p)));
    	         	pyt = (pt-> at(p)* sin(phi->at(p)));

    				momsq2= (pt->at(p))*(pt->at(p)) + pzt*pzt;
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


    				mass->Fill(mInv);
    				}
    			}
    			}
    	     

    }//end of for j loop
	}// end of for i loop


	file= new TFile("lambdaOppositeChargePDG.root","RECREATE");
	mass-> Write();


file->Write();
file-> Close();

	mass->Draw();
	//mass->Draw();
	//t->GetEntry(10);
	//cout<<pt->at(1)<<endl;
	//cout <<nPart
}