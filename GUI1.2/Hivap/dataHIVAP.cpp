//data.cpp
#include<iostream>

//#define n 11 //核素个数
//#define m 7 //绘制的数据个数

using namespace std;

void data(Int_t nZ, Int_t nN, Int_t nZ_Draw_min, Int_t nZ_Draw_max, Int_t nN_Draw_min, Int_t nN_Draw_max, Double_t Cf, Double_t y_min, Double_t y_max, Double_t cbx, Double_t texx =90.0, TString filename = "hivaperg.dat")
{
		TString scf, HIVAP_file_name, Exp_file_name, lat, canvas_name;
		scf.Form("C_{f} = %.2f", Cf);
		canvas_name.Form("HIVAP");
		lat.Form("%s", scf.Data());
		Double_t HIVAP_Energy_cm[100] = {0};
		Double_t HIVAP_Energy_Exp[100] = {0};
		Int_t* HIVAP_np = new Int_t[nZ*nN];
		memset(HIVAP_np, 0, nZ*nN * sizeof(Int_t));
		Double_t** HIVAP_cross_section = new Double_t*[nZ*nN];
		TString* name = new TString[nZ*nN];
		for(int i=0; i<nZ*nN; i++)
		{
				HIVAP_cross_section[i] = new Double_t[100];
				memset(HIVAP_cross_section[i], 0, 100*sizeof(Double_t));
		}

		ifstream HIVAP_file(filename);
		string stmp;
		Double_t dtmp;
		Int_t nEnergyHivap = 0;
		Int_t nCrosssectionHivapTmp = 0;
		Int_t nCrosssectionHivap = 0;
		if(HIVAP_file.is_open())    
		{
			HIVAP_file>>stmp;
			HIVAP_file>>dtmp;
			HIVAP_file>>stmp;
			cout << "Q  =  " << dtmp << " " << stmp << endl;
			getline(HIVAP_file, stmp);
			getline(HIVAP_file, stmp);

                for(int i=0; i<2*nZ; i++)
                {
                    getline(HIVAP_file, stmp);
                }
                getline(HIVAP_file, stmp);
                HIVAP_file>>stmp;
                HIVAP_file>>Cf;
                cout << "Cf = " << Cf << endl;
                getline(HIVAP_file, stmp);
                for(int i=0; i<3*nZ; i++)
                {
                    getline(HIVAP_file, stmp);
                }
                getline(HIVAP_file, stmp);
                getline(HIVAP_file, stmp);
                getline(HIVAP_file, stmp);
                getline(HIVAP_file, stmp);
                getline(HIVAP_file, stmp);
                while(getline(HIVAP_file, stmp))
                {
                    string stmptmp;
                    if(stmp.size()>5)
                    {
                        stmptmp = stmp.substr(1, 5);
                        if(stmptmp=="HIVAP")
                        {
                            getline(HIVAP_file, stmp);
                            getline(HIVAP_file, stmp);
                            getline(HIVAP_file, stmp);
                            getline(HIVAP_file, stmp);
                            getline(HIVAP_file, stmp);
                            getline(HIVAP_file, stmp);
                            while(1)
                            {
                                getline(HIVAP_file, stmp);
                                if(stmp.size()!=0)
                                {
                                    HIVAP_file.seekg(-stmp.size(), ios::cur);
                                    HIVAP_file >> HIVAP_Energy_Exp[nEnergyHivap] >> dtmp >> dtmp >> dtmp >> dtmp >> dtmp >> dtmp >> dtmp;
                                    getline(HIVAP_file, stmp);
                                    nEnergyHivap++;
                                //  cout << nEnergyHivap-1 << "\t" << HIVAP_Energy_Exp[nEnergyHivap-1] <<endl;
                                }
                                else
                                    break;
                            }
                        }
                    }
                    if(stmp.size()>18)
                    {
                        stmptmp = stmp.substr(5, 12);//6,12
                        if(stmptmp=="Querschnitte")
                        {
                            getline(HIVAP_file, stmp);
                            for(int nz=0; nz<nZ; nz++)
                            {
                                HIVAP_file >> stmp;
                                for(int i=0; i<nN; i++)
                                {
                                    HIVAP_file >> name[nz*nN+i];
                                }
                                getline(HIVAP_file, stmp);
                                nCrosssectionHivapTmp = nCrosssectionHivap;
                                while(1)
                                {
                                    if(stmp.size()!=0)
                                    {
                                        HIVAP_file.seekg(-stmp.size(), ios::cur);
                                        HIVAP_file >> HIVAP_Energy_cm[nCrosssectionHivapTmp];
                                        for(int i=0; i<nN; i++)
                                        {
                                            HIVAP_file >> HIVAP_cross_section[nz*nN+i][nCrosssectionHivapTmp];
                                        }
                                        getline(HIVAP_file, stmp);
                                        nCrosssectionHivapTmp++;
                                       getline(HIVAP_file, stmp);
                                    }
                                    else
                                        break;
                                }
                            }
                            nCrosssectionHivap = nCrosssectionHivapTmp;
                        }
                    }
                }
		}
		else
		{
				cout<<"Fail to open the HIVAP file"<<endl;
				return ;
		}
		HIVAP_file.close();
		TGraph *HIVAP[nZ*nN]; 
		TGraphErrors *Exp[nZ*nN];
		for(int i=0; i<nZ*nN; i++)  
		{
				HIVAP[i] = new TGraph;
				Exp[i] = new TGraphErrors;
		}
		
		for(int i=0; i<nZ; i++)
		{
			for(int j=0; j<nN; j++)
			{
				for(int k=0; k<100; k++)
				{
					if(HIVAP_Energy_cm[i*nN+j]>0)
					{
						if(k > 0 && HIVAP_cross_section[i*nN+j][k]*1E3 < y_min && HIVAP_cross_section[i*nN+j][k-1]*1E3 > y_min)					break;
						if(HIVAP_cross_section[i*nN+j][k]*1E3 > y_min)
						{
							HIVAP[i*nN+j]->SetPoint(HIVAP_np[i*nN+j], HIVAP_Energy_cm[k], HIVAP_cross_section[i*nN+j][k]*1000.0);
							HIVAP_np[i*nN+j]++;
						}
					}
				}
			}

		}
		
		
		TMultiGraph *mg = new TMultiGraph();
		TLegend *leg = new TLegend(0.8, 0.1, 0.9, 0.9);

		Int_t ngraph = 0;
		for(int i=nZ_Draw_min-1; i<nZ_Draw_max; i++)
		{
			for(int j=nN_Draw_min-1; j<nN_Draw_max; j++)
			{
				if(HIVAP_np[i*nN+j] > 2)
				{

					if(ngraph < 11)
						HIVAP[i*nN+j]->SetMarkerStyle(20+ngraph);
					else if(ngraph <= 22)
						HIVAP[i*nN+j]->SetMarkerStyle(9+ngraph);
					else if(ngraph <= 33)
						HIVAP[i*nN+j]->SetMarkerStyle(ngraph-2);
					HIVAP[i*nN+j]->SetMarkerSize(1.0);
					if(ngraph < 11)
					{
						if(ngraph+3 == 10)  HIVAP[i*nN+j]->SetMarkerColor(50);
						else HIVAP[i*nN+j]->SetMarkerColor(ngraph+3);
						if(ngraph+3 == 10)  HIVAP[i*nN+j]->SetLineColor(50);
						else  HIVAP[i*nN+j]->SetLineColor(ngraph+3);
					}
					else
					{
						HIVAP[i*nN+j]->SetMarkerColor(3*ngraph+3);
						HIVAP[i*nN+j]->SetLineColor(3*ngraph+3);
					}
					HIVAP[i*nN+j]->SetLineStyle(2);
					HIVAP[i*nN+j]->SetLineWidth(2);
					ngraph++;
				}
			}
		}
		for(int i=nZ_Draw_min-1; i<nZ_Draw_max; i++)
		{
			for(int j=nN_Draw_min-1; j<nN_Draw_max; j++)
			{
				if(HIVAP_np[i*nN+j] > 2)
				{
					mg->Add(HIVAP[i*nN+j], "CP");
					leg->AddEntry(HIVAP[i*nN+j], name[i*nN+j]);
				}
			}
		}
		mg->SetTitle("Cross Section; Excitation Energy [MeV]; Cross section [#mub]");
		mg->GetYaxis()->CenterTitle("1");
		mg->GetXaxis()->CenterTitle("1");
		mg->GetXaxis()->SetTitleOffset(1.4);
		mg->GetYaxis()->SetTitleOffset(1.4);
		mg->GetYaxis()->SetRangeUser(y_min, y_max);
//		mg->GetYaxis()->SetRangeUser(1.0E-7, 5.0E2);
//		mg->GetXaxis()->SetRangeUser(0.1, 140.0);
//		mg->GetXaxis()->SetLimits(20.0, 150.0);
		TLatex *text = new TLatex(texx, (y_max/10), lat);
		text->SetTextFont(12);
		TArrow* acb = new TArrow(cbx, 10*y_min, cbx, y_min, 0.02,"|>");
		acb->SetAngle(30);
		acb->SetLineWidth(2);
		acb->SetLineColor(1);
		acb->SetFillColor(1);
		TLatex *texta = new TLatex(cbx-5, 18*y_min, "B_{Bass}");
		mg->Draw("A");
		acb->Draw();
		text->Draw();
		texta->Draw();
		leg->Draw();
		gPad->SetLogy(1);
}
