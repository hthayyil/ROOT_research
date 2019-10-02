#include <cstdlib>
void Background(){

float hsum = 0.0;
float hwidth =0.0;
float scale = 1.1;
float x = 0.0;
int nbins = 100;
float value = 0;
float hwidth =0;
float hsum = 0.0;
int b; 
float boltzmann = 3.829293706979*(10**(-23));


function = new TF1 ("function","exp(-x)/boltzmann", 1, 5);
//function-> SetParameter(1, );

hist2 = new TH1F("hist2","Background",nbins,1,5);
hist2->Sumw2();

for(int i = 0; i< 1000000; i ++) {
   x = double (rand()) / (RAND_MAX) * 5;
   y = double (rand()) / (RAND_MAX);
   if (y <= function->Eval(x) ) {
 		hist2->Fill(x);
	}
}

float scale =function->Integral(0,5);
for (int i = 0; i <=nbins; i++)  {
	hsum += hist2->GetBinContent(i);
    hwidth = hist2->GetBinWidth(1);
}
cout << scale<<endl;
scale = scale/(hsum*hwidth) ;

hist2->Scale(scale);
hist2-> Draw();
function->Draw("same");

file= new TFile("Background.root","RECREATE");
hist2-> Write();
function-> Write();

file->Write();
file-> Close();

return;

}