
void RandomSum(int N = 4){

float hsum = 0.0;
float hwidth =0.0;
float scale = 0.0;
float x = 0.0;

int nbins = 100;
int b; 


h1fv2 = new TH1F("h1fv2","Central Limit Theorem",nbins,0,1);	
h1fv2->Sumw2();


for (int i = 0; i<100000; i++){
	x= gRandom-> Rndm();
	for ( b = 0; b< N-1; b++) {
		//x= gRandom-> Rndm();
		x+= gRandom-> Rndm();
}
	

	h1fv2->Fill(x/N);

  
}
//TF1 * norm = new TF1("norm","   formula ...",0,1);
function = new TF1 ("function","2*x-(x*x)", 0, 2);

h1fv2->Fit("gaus");

h1fv2->Draw();

}