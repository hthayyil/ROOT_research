 {

C= new TCanvas("C", "Kaon Invariant Mass", 10,10, 700,700);
C->Divide(1,2);
C->Draw();
C_1->cd();
file1 = new TFile("kaonsameCharge.root", "READ");
//hist2-> Draw();


TH1F* background = (TH1F*) mass2->Clone("background");

background->SetLineColor(2);

//signal->Draw("same");

file2 = new TFile("kaonOppositeCharge.root", "READ");

TH1F* signal = (TH1F*) mass->Clone("signal");


//signal->Add(background,-1);
background->Fit("pol0","","",0.505,0.515);

float s1 = pol0->GetParameter(0);

cout<<s1<<endl;
background->Scale(1.0/s1);
signal->Fit("pol0","","",0.505,0.515);

float s2= pol0->GetParameter(0);
cout<<s2<<endl;
signal->Scale(1.0/s2);

gStyle->SetOptStat(0);
signal->SetMaximum(1.1);
signal->Draw();
background->Draw("same");

TH1F* newsignal = (TH1F*) signal->Clone("newsignal");


newsignal->Add(background,-1);

int nMax = newsignal->GetMaximumBin();
float max = newsignal->GetBinContent(nMax);

newsignal->SetMaximum(max*1.2);
newsignal->SetMinimum(0);
C_2->cd();
newsignal->Draw();

}
//create a new TF1, total->Fit()
//set parameter to have central value of 3.1