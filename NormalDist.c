#include <cstdlib>

void NormalDist() {

double n = 10.0;
double x = 0.0;

//random = gRandom-> Rndm();

histo = new TH1F("histo","First Assignment",100,-n,n);

for(int i = 0; i< 100000; i ++) {
	
    x = (( double) rand() / (RAND_MAX));
	histo->Fill( (2*x * n -n));
	//histo -> Fill((x * n )) ;
float hsum = 0;
for (int i = -n; i <=n; i++) {
	hsum+=histo->GetBinContent(i);

   histo->Scale(1/ hsum);
  }
	
	//h1fv2->Fill(gRandom->Rndm()*-n);
//histo.Fit(guas);
}
histo->SetMinimum(-n);
histo->Draw();
histo->Draw("same");

//bin width, integral

}