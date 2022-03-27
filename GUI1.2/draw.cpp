//draw.cpp

#include "TColor.h"
#include "TLatex.h"
#include "TCanvas.h"
#include "TGSplitter.h"
#include "TG3DLine.h"
#include "TGraphErrors.h"
#include "TMultiGraph.h"
#include "TAxis.h"
#include "TLegend.h"

#include <vector>

#include "draw.h"
//#include "nuclear_data.h"
#include "iostream"

draw::draw(const TGWindow * p, const TGWindow * main, char *name, TString Draw_Option_In, TString Draw_Option_Spn_In)
{
	Draw_Option = Draw_Option_In;
	Draw_Option_Spn = Draw_Option_Spn_In;
	SetCleanup(kDeepCleanup);
	SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	Sp_DrawFrame = new TGVerticalFrame(this, 800, 1500);
	AddFrame(Sp_DrawFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 10, 10, 5, 5));
	Sp_DrawFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	TGHSplitter *hsplitter0 = new TGHSplitter(Sp_DrawFrame,200,2);
	Sp_DrawFrame->AddFrame(hsplitter0, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));

	ZANFrame = new TGHorizontalFrame(Sp_DrawFrame, 800, 40);
	Sp_DrawFrame->AddFrame(ZANFrame, new TGLayoutHints(kLHintsTop | kLHintsLeft, 0, 0, 0, 0));
	ZANFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));

	ZminText = new TGTextEntry(ZANFrame, new TGTextBuffer(100), 10000);
	ZminText->SetText("Z(min) = ");
	ZANFrame->AddFrame(ZminText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ZminText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ZminText->SetAlignment(kTextCenterX);
	ZminText->Resize(140, 40);
	ZminText->SetEnabled(kFALSE);
	ZminText->SetFrameDrawn(kFALSE);
	ZminText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	ZminText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);

	ZminNumber = new TGNumberEntry(ZANFrame, 0, 0, TGNumberFormat::kNESInteger);
	ZANFrame->AddFrame(ZminNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ZminNumber->GetButtonUp()->ChangeOptions(ZminNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	ZminNumber->GetButtonDown()->ChangeOptions(ZminNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	ZminNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ZminNumber->Resize(70, 40);
	ZminNumber->SetNumber(82);
	ZminNumber->Associate(this);

	ZmaxText = new TGTextEntry(ZANFrame, new TGTextBuffer(100), 10000);
	ZmaxText->SetText("Z(max) = ");
	ZANFrame->AddFrame(ZmaxText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ZmaxText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ZmaxText->SetAlignment(kTextCenterX);
	ZmaxText->Resize(140, 40);
	ZmaxText->SetEnabled(kFALSE);
	ZmaxText->SetFrameDrawn(kFALSE);
	ZmaxText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	ZmaxText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	ZmaxNumber = new TGNumberEntry(ZANFrame, 0, 0, TGNumberFormat::kNESInteger);
	ZANFrame->AddFrame(ZmaxNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ZmaxNumber->GetButtonUp()->ChangeOptions(ZmaxNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	ZmaxNumber->GetButtonDown()->ChangeOptions(ZmaxNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	ZmaxNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	ZmaxNumber->Resize(70, 40);
	ZmaxNumber->SetNumber(82);
	ZmaxNumber->Associate(this);

	ZEvenOddFrame = new TGVerticalFrame(ZANFrame, 70, 40);
	ZANFrame->AddFrame(ZEvenOddFrame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	ZEvenOddFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	ZEvenCheckButton = new TGCheckButton(ZEvenOddFrame, "Even", 0);
	ZEvenCheckButton->SetOn(kTRUE);
	ZEvenCheckButton->Resize(70, 20);
	ZEvenOddFrame->AddFrame(ZEvenCheckButton, new TGLayoutHints(kLHintsExpandX | kLHintsExpandX, 20, 0, 0, 5));
	ZOddCheckButton = new TGCheckButton(ZEvenOddFrame, "Odd", 0);
	ZOddCheckButton->SetOn(kTRUE);
	ZOddCheckButton->Resize(70, 20);
	ZEvenOddFrame->AddFrame(ZOddCheckButton, new TGLayoutHints(kLHintsExpandX | kLHintsExpandX, 20, 0, 5, 0));

	NminText = new TGTextEntry(ZANFrame, new TGTextBuffer(100), 10000);
	NminText->SetText("N(min) = ");
	ZANFrame->AddFrame(NminText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NminText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NminText->SetAlignment(kTextCenterX);
	NminText->Resize(140, 40);
	NminText->SetEnabled(kFALSE);
	NminText->SetFrameDrawn(kFALSE);
	NminText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NminText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	NminNumber = new TGNumberEntry(ZANFrame, 0, 0, TGNumberFormat::kNESInteger);
	ZANFrame->AddFrame(NminNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NminNumber->GetButtonUp()->ChangeOptions(NminNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	NminNumber->GetButtonDown()->ChangeOptions(NminNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	NminNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NminNumber->Resize(70, 40);
	NminNumber->SetNumber(126);
	NminNumber->Associate(this);

	NmaxText = new TGTextEntry(ZANFrame, new TGTextBuffer(100), 10000);
	NmaxText->SetText("N(max) = ");
	ZANFrame->AddFrame(NmaxText, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NmaxText->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NmaxText->SetAlignment(kTextCenterX);
	NmaxText->Resize(140, 40);
	NmaxText->SetEnabled(kFALSE);
	NmaxText->SetFrameDrawn(kFALSE);
	NmaxText->ChangeBackground(TColor::RGB2Pixel(62, 62, 62));
	NmaxText->SetTextColor(TColor::RGB2Pixel(131, 131, 131), false);
	NmaxNumber = new TGNumberEntry(ZANFrame, 0, 0, TGNumberFormat::kNESInteger);
	ZANFrame->AddFrame(NmaxNumber, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NmaxNumber->GetButtonUp()->ChangeOptions(NmaxNumber->GetButtonUp()->GetOptions() ^ kRaisedFrame);
	NmaxNumber->GetButtonDown()->ChangeOptions(NmaxNumber->GetButtonDown()->GetOptions() ^ kRaisedFrame);
	NmaxNumber->GetNumberEntry()->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	NmaxNumber->Resize(70, 40);
	NmaxNumber->SetNumber(126);
	NmaxNumber->Associate(this);

	NEvenOddFrame = new TGVerticalFrame(ZANFrame, 70, 40);
	ZANFrame->AddFrame(NEvenOddFrame, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 0, 0, 0, 0));
	NEvenOddFrame->SetBackgroundColor(TColor::RGB2Pixel(62, 62, 62));
	NEvenCheckButton = new TGCheckButton(NEvenOddFrame, "Even", 0);
	NEvenCheckButton->SetOn(kTRUE);
	NEvenCheckButton->Resize(70, 20);
	NEvenOddFrame->AddFrame(NEvenCheckButton, new TGLayoutHints(kLHintsExpandX | kLHintsExpandX, 20, 0, 0, 5));
	NOddCheckButton = new TGCheckButton(NEvenOddFrame, "Odd", 0);
	NOddCheckButton->SetOn(kTRUE);
	NOddCheckButton->Resize(70, 20);
	NEvenOddFrame->AddFrame(NOddCheckButton, new TGLayoutHints(kLHintsExpandX | kLHintsExpandX, 20, 0, 5, 0));

	DrawB = new TGTextButton(ZANFrame, "  Draw  ", DrawButton);
	ZANFrame->AddFrame(DrawB, new TGLayoutHints(kLHintsCenterX | kLHintsCenterY, 30, 0, 0, 0));
	DrawB->SetFont("-adobe-helvetica-bold-r-*-*-20-*-*-*-*-*-iso8859-1", false);
	DrawB->Resize(80, 40);
	DrawB->SetTextColor(TColor::RGB2Pixel(255, 255, 255));
	DrawB->SetBackgroundColor(TColor::RGB2Pixel(34, 151, 159));
	DrawB->Associate(this);

	TGHSplitter *hsplitter1 = new TGHSplitter(Sp_DrawFrame,400,2);
	Sp_DrawFrame->AddFrame(hsplitter1, new TGLayoutHints(kLHintsTop | kLHintsExpandX,0,0,10,10));
	hsplitter1->SetBackgroundColor(TColor::RGB2Pixel(0,0,0));

	FrameCanvas = new TRootEmbeddedCanvas("Sp", Sp_DrawFrame, 200, 800);
	Sp_DrawFrame->AddFrame(FrameCanvas, new TGLayoutHints(kLHintsExpandX | kLHintsExpandY, 0, 0, 0, 0));
	Int_t wid = FrameCanvas->GetCanvasWindowId();
	TCanvas *can  = new TCanvas("Canvas", 100, 400, wid);
	can->SetGridy(1);
	FrameCanvas->AdoptCanvas(can);
	

	MapSubwindows();
	Resize();
	CenterOnParent();
	SetWindowName(name);
	MapWindow();
}
draw::~draw(){}

Bool_t draw::ProcessMessage(Long_t msg,Long_t parm1, Long_t parm2)
{
	switch (GET_MSG(msg))
	{
		case kC_COMMAND:
			switch (GET_SUBMSG(msg))
			{
				case kCM_BUTTON:
					switch (parm1)
					{
						case DrawButton:
						{
								Int_t Zmin = ZminNumber->GetNumber();
								Int_t Zmax = ZmaxNumber->GetNumber();
								Int_t Nmin = NminNumber->GetNumber();
								Int_t Nmax = NmaxNumber->GetNumber();
								if(Zmin <= Zmax &&  Nmin <= Nmax)
								{
									TMultiGraph *mg = new TMultiGraph();
									mg->GetXaxis()->CenterTitle("1");
									mg->GetYaxis()->CenterTitle("1");
									TLegend *leg = new TLegend(0.85, 0.1, 0.97, 0.9);
									//SP_ISOTOPE
									if(Draw_Option == "ISOTOPE")
									{
										TGraphErrors *GraphTmp[Zmax-Zmin+1];
										TGraphErrors *GraphTmpExt[Zmax-Zmin+1];
										std::vector<Int_t> npoint;
										std::vector<Int_t> npointExt;
										std::vector<TString> NuclearName;
										Double_t ymin;
										Double_t ymax;
										Bool_t bxyMinMax = true;
										for(int i=0; i<Zmax-Zmin+1; i++)
										{
											GraphTmp[i] = new TGraphErrors();
											GraphTmpExt[i] = new TGraphErrors();
											npoint.push_back(0);
											npointExt.push_back(0);
											NuclearName.push_back("");
										}
										for(Int_t i=Zmin; i<=Zmax; i++)
										{
											if(i%2==0 && !ZEvenCheckButton->IsOn())
												continue;
											if(i%2!=0 && !ZOddCheckButton->IsOn())
												continue;
											for(Int_t j=Nmin; j<=Nmax; j++)
											{
												if(j%2==0 && !NEvenCheckButton->IsOn())
													continue;
												if(j%2!=0 && !NOddCheckButton->IsOn())
													continue;
												nuclear_data* Nuclear_data = new nuclear_data(i, i+j, j);
												nuclear_data* Nuclear_data_daughter;
												Double_t TheResultValue = 0.0;
												if(Draw_Option_Spn == "Sp")
												{
													mg->SetTitle("; N; Sp (MeV)");
													Nuclear_data_daughter = new nuclear_data(i-1, i-1+j, j);
													TheResultValue = 938.78320 + Nuclear_data_daughter->getmass() - Nuclear_data->getmass();
												}
												else if(Draw_Option_Spn == "Sn")
												{
													mg->SetTitle("; N; Sn (MeV)");
													Nuclear_data_daughter = new nuclear_data(i, i-1+j, j-1);
													TheResultValue = 939.56555 + Nuclear_data_daughter->getmass() - Nuclear_data->getmass();
												}
												Double_t TheResultError = sqrt(Nuclear_data->geterror()*Nuclear_data->geterror() + Nuclear_data_daughter->geterror()*Nuclear_data_daughter->geterror());
												if(Nuclear_data->getemass() > 999.0 || Nuclear_data_daughter->getemass() > 999.0)
													continue;
												else
												{
													NuclearName.at(i-Zmin) = TString(Nuclear_data->getname());
													GraphTmp[i-Zmin]->SetPoint(npoint.at(i-Zmin), j, TheResultValue);
													GraphTmp[i-Zmin]->SetPointError(npoint.at(i-Zmin), 0, TheResultError);
													npoint.at(i-Zmin)++;
													if(bxyMinMax)
													{
														ymin = TheResultValue - TheResultError;
														ymax = TheResultValue + TheResultError;
													}
													bxyMinMax = false;
													if(ymin > TheResultValue - TheResultError)
														ymin = TheResultValue - TheResultError;
													if(ymax < TheResultValue + TheResultError)
														ymax = TheResultValue + TheResultError;
													
													if(!Nuclear_data->getflag() || !Nuclear_data_daughter->getflag())
													{
														GraphTmpExt[i-Zmin]->SetPoint(npoint.at(i-Zmin), j, TheResultValue);
														GraphTmpExt[i-Zmin]->SetPointError(npoint.at(i-Zmin), 0, TheResultError);
														npointExt.at(i-Zmin)++;
													}
												}
												delete Nuclear_data;
												delete Nuclear_data_daughter;
											}
										}
										Int_t nGraphTmp = 0;
										for(int i=Zmin; i<=Zmax; i++)
										{
											if(i%2==0 && !ZEvenCheckButton->IsOn())
												continue;
											if(i%2!=0 && !ZOddCheckButton->IsOn())
												continue;
											GraphTmp[i-Zmin]->SetLineStyle(1);
											GraphTmp[i-Zmin]->SetLineWidth(2);
											GraphTmp[i-Zmin]->SetMarkerSize(1.5);
											if(nGraphTmp < 11)
											{
												if(nGraphTmp+3==10)
												{
													GraphTmp[i-Zmin]->SetLineColor(50);
													GraphTmp[i-Zmin]->SetMarkerColor(50);
												}
												else
												{
													GraphTmp[i-Zmin]->SetLineColor(nGraphTmp+3);
													GraphTmp[i-Zmin]->SetMarkerColor(nGraphTmp+3);
												}
											}
											else
											{
												GraphTmp[i-Zmin]->SetLineColor(3*nGraphTmp+3);
												GraphTmp[i-Zmin]->SetMarkerColor(3*nGraphTmp+3);
											}
											if(nGraphTmp < 11)
												GraphTmp[i-Zmin]->SetMarkerStyle(20+nGraphTmp);
											else if(nGraphTmp <= 22)
												GraphTmp[i-Zmin]->SetMarkerStyle(9+nGraphTmp);
											else if(nGraphTmp <= 33)
												GraphTmp[i-Zmin]->SetMarkerStyle(nGraphTmp-2);
											nGraphTmp++;
											if(npoint.at(i-Zmin)>0)
											{
												mg->Add(GraphTmp[i-Zmin], "PEL");
												leg->AddEntry(GraphTmp[i-Zmin], NuclearName.at(i-Zmin), "LPF");
											}
										}
										mg->GetXaxis()->SetRangeUser(Double_t(Nmin)-0.5, Double_t(Nmax)+2.0);
										mg->GetXaxis()->SetLimits(Double_t(Nmin)-0.5, Double_t(Nmax)+2.0);
										mg->GetYaxis()->SetRangeUser(ymin-0.2, ymax+0.2);
										mg->GetYaxis()->SetLimits(ymin-0.2, ymax+0.2);
										TCanvas *DrawCanvas = FrameCanvas->GetCanvas();
										DrawCanvas->cd();
										mg->Draw("A");
										leg->SetTextFont(13);
										leg->SetMargin(0.6);
										leg->Draw();
										DrawCanvas->Update();
										for(int i=Zmin; i<=Zmax; i++)
										{
											delete GraphTmp[i-Zmin];
											delete GraphTmpExt[i-Zmin];
										}
									}
									if(Draw_Option == "ISOTONE")
									{
										TGraphErrors *GraphTmp[Nmax-Nmin+1];
										TGraphErrors *GraphTmpExt[Nmax-Nmin+1];
										std::vector<Int_t> npoint;
										std::vector<Int_t> npointExt;
										std::vector<TString> NName;
										Double_t ymin;
										Double_t ymax;
										Bool_t bxyMinMax = true;
										for(int i=0; i<Nmax-Nmin+1; i++)
										{
											GraphTmp[i] = new TGraphErrors();
											GraphTmpExt[i] = new TGraphErrors();
											npoint.push_back(0);
											npointExt.push_back(0);
											NName.push_back("");
										}
										for(Int_t i=Nmin; i<=Nmax; i++)
										{
											if(i%2==0 && !NEvenCheckButton->IsOn())
												continue;
											if(i%2!=0 && !NOddCheckButton->IsOn())
												continue;
											for(Int_t j=Zmin; j<=Zmax; j++)
											{
												if(j%2==0 && !ZEvenCheckButton->IsOn())
													continue;
												if(j%2!=0 && !ZOddCheckButton->IsOn())
													continue;
												nuclear_data* Nuclear_data = new nuclear_data(j, i+j, i);
												nuclear_data* Nuclear_data_daughter;
												Double_t TheResultValue = 0.0;
												if(Draw_Option_Spn == "Sp")
												{
													mg->SetTitle("; Z; Sp (MeV)");
													Nuclear_data_daughter = new nuclear_data(j-1, j-1+i, i);
													TheResultValue = 938.78320 + Nuclear_data_daughter->getmass() - Nuclear_data->getmass();
												}
												else if(Draw_Option_Spn == "Sn")
												{
													mg->SetTitle("; Z; Sn (MeV)");
													Nuclear_data_daughter = new nuclear_data(j, j-1+i, i-1);
													TheResultValue = 939.56555 + Nuclear_data_daughter->getmass() - Nuclear_data->getmass();
												}
												Double_t TheResultError = sqrt(Nuclear_data->geterror()*Nuclear_data->geterror() + Nuclear_data_daughter->geterror()*Nuclear_data_daughter->geterror());
												if(Nuclear_data->getemass() > 999.0 || Nuclear_data_daughter->getemass() > 999.0)
													continue;
												else
												{
													NName.at(i-Nmin) = Form("N = %d", i);
													GraphTmp[i-Nmin]->SetPoint(npoint.at(i-Nmin), j, TheResultValue);
													GraphTmp[i-Nmin]->SetPointError(npoint.at(i-Nmin), 0, TheResultError);
													npoint.at(i-Nmin)++;
													if(bxyMinMax)
													{
														ymin = TheResultValue - TheResultError;
														ymax = TheResultValue + TheResultError;
													}
													bxyMinMax = false;
													if(ymin > TheResultValue - TheResultError)
														ymin = TheResultValue - TheResultError;
													if(ymax < TheResultValue + TheResultError)
														ymax = TheResultValue + TheResultError;
													
													if(!Nuclear_data->getflag() || !Nuclear_data_daughter->getflag())
													{
														GraphTmpExt[i-Nmin]->SetPoint(npoint.at(i-Nmin), j, TheResultValue);
														GraphTmpExt[i-Nmin]->SetPointError(npoint.at(i-Nmin), 0, TheResultError);
														npointExt.at(i-Nmin)++;
													}
												}
												delete Nuclear_data;
												delete Nuclear_data_daughter;
											}
										}
										Int_t nGraphTmp = 0;
										for(int i=Nmin; i<=Nmax; i++)
										{
											if(i%2==0 && !NEvenCheckButton->IsOn())
												continue;
											if(i%2!=0 && !NOddCheckButton->IsOn())
												continue;
											GraphTmp[i-Nmin]->SetLineStyle(1);
											GraphTmp[i-Nmin]->SetLineWidth(2);
											GraphTmp[i-Nmin]->SetMarkerSize(1.5);
											if(nGraphTmp < 11)
											{
												if(nGraphTmp+3==10)
												{
													GraphTmp[i-Nmin]->SetLineColor(50);
													GraphTmp[i-Nmin]->SetMarkerColor(50);
												}
												else
												{
													GraphTmp[i-Nmin]->SetLineColor(nGraphTmp+3);
													GraphTmp[i-Nmin]->SetMarkerColor(nGraphTmp+3);
												}
											}
											else
											{
												GraphTmp[i-Nmin]->SetLineColor(3*nGraphTmp+3);
												GraphTmp[i-Nmin]->SetMarkerColor(3*nGraphTmp+3);
											}
											if(nGraphTmp < 11)
												GraphTmp[i-Nmin]->SetMarkerStyle(20+nGraphTmp);
											else if(nGraphTmp <= 22)
												GraphTmp[i-Nmin]->SetMarkerStyle(9+nGraphTmp);
											else if(nGraphTmp <= 33)
												GraphTmp[i-Nmin]->SetMarkerStyle(nGraphTmp-2);
											nGraphTmp++;
											if(npoint.at(i-Nmin)>0)
											{
												mg->Add(GraphTmp[i-Nmin], "PEL");
												leg->AddEntry(GraphTmp[i-Nmin], NName.at(i-Nmin), "LPF");
											}
										}
										mg->GetXaxis()->SetRangeUser(Double_t(Zmin)-0.5, Double_t(Zmax)+2.0);
										mg->GetXaxis()->SetLimits(Double_t(Zmin)-0.5, Double_t(Zmax)+2.0);
										mg->GetYaxis()->SetRangeUser(ymin-0.2, ymax+0.2);
										mg->GetYaxis()->SetLimits(ymin-0.2, ymax+0.2);
										TCanvas *DrawCanvas = FrameCanvas->GetCanvas();
										DrawCanvas->cd();
										mg->Draw("A");
										leg->SetTextFont(13);
										leg->SetMargin(0.6);
										leg->Draw();
										DrawCanvas->Update();
										for(int i=Nmin; i<=Nmax; i++)
										{
											delete GraphTmp[i-Nmin];
											delete GraphTmpExt[i-Nmin];
										}

									}
									delete mg;
									delete leg;
								}
								else
									std::cout << "Error : Zmin/Zmax or Nmin/Nmax input!"<<std::endl;
							break;
						}
						default:
							break;
					}
				default:
					break;
			}
		default:
			break;
	}
	return kTRUE;
}
