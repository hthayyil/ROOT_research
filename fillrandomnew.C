void fillrandomnew() {
   //Fill a 1-D histogram from a parametric function
   // To see the output of this macro, click begin_html <a href="gif/fillrandom.gif">here</a>. end_html
   //Author: Rene Brun
   
   // A function (any dimension) or a formula may reference
   // an already defined formula
   //
   						// creating a histogram thats symmetrical with x number of bins, 
						// the graph should be a stright line almost and integral will be = 1
						// (normal distribution)
						// if 5 bins than each bin = .2, 10 than .1, 20 than .05 etc
						// x = Rand -> Rndm() and scale these x to fit the above mentioned graph
 						//change the formula xgaus to be 2x - x^2 = y whatever
			        	// this will be the graph that all your values must fit
  // sqroot = new TF1("sqroot","x*gaus(0) + [3]*abs(sin(x)/x)",0,10);
  // sqroot->SetParameters(10,4,1,20);
   

//float scale = sqroot->Integral(0,10);
   //   sqroot->SetLineColor(4);
   //sqroot->SetLineWidth(6);
  // sqroot->Draw();
   
//int n =20;
  // h1f = new TH1F("h1f","Test of an Observed Distribution",n,0,10);
  // h1f->SetFillColor(45);
   
  // h1f->FillRandom("sqroot",100000);
   //creating what FillRandom does except by hand using a for/ if loop
   
// i is the bin numbers            10 bins from 0 to 1
function = new TF1 ("function","2*x-(x*x)", 0, 10);
double n = 10.0;
//random = gRandom-> Rndm();
h1fv2 = new TH1F("h1fv2","First Assignment",100,-n,n);
for(int i = 0; i< 10000; i ++) 
	h1fv2->Fill(gRandom-> Gaus(0., 2.0));
	//h1fv2->Fill(gRandom->Rndm()*-n);

//h1fv2.Fit(guas);

h1fv2->SetMinimum(0);
h1fv2->Draw();
h1fv2->Draw("same");

return;

/*
float hsum = 0;
for (int i = 1; i <=n; i++)
	hsum+=h1f->GetBinContent(i);

   scale /= hsum*h1f->GetBinWidth(1);

   h1f->Scale(scale);
  // h1f->Draw("same");
  
cout<<hsum<<endl;

  //h1f->Draw();
   //
   // Open a ROOT file and save the formula, function and histogram
   //
   */
   TFile myfile("fillrandom.root","RECREATE");
   
   sqroot->Write();
   h1f->Write();
   
}

