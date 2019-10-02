 {
file1 = new TFile("lambdaSameChargePDG.root", "READ");
//hist2-> Draw();


TH1F* background = (TH1F*) mass2->Clone("background");

background->SetLineColor(2);

background->Draw();
 
file2 = new TFile("lambdaOppositeChargePDG.root", "READ");

TH1F* signal = (TH1F*) mass->Clone("signal");

signal-> Draw();
background->Draw("same");
//return;
//signal->Scale(0.1*n2/n1);

//signal->Add(background,-1);
background->Fit("pol0","","",1.13,1.15);

float s1 = pol0->GetParameter(0);

cout<<s1<<endl;
background->Scale(1.0/s1);
signal->Fit("pol0","","",1.13,1.15);

float s2= pol0->GetParameter(0);
cout<<s2<<endl;
signal->Scale(1.0/s2);

gStyle->SetOptStat(0);
signal->SetMaximum(1.1);
signal->Draw();
background->Draw("same");

TH1F* newsignal = (TH1F*) signal->Clone("newsignal");

//cc = new TCanvas("cc","", 10,10, 400,400);
//cc->Draw();
newsignal->Add(background,-1);
int n = newsignal->GetMaximumBin();
float max = newsignal->GetBinContent(n);
newsignal->SetMaximum(max*1.2);
newsignal->SetMinimum(0);
newsignal->Draw();

}
//create a new TF1, total->Fit()
//set parameter to have central value of 3.1